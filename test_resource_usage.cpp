#include <chrono>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cstdlib> // For std::atoi
#include "WeatherServer.h"
#include "WeatherClient.h"

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#else
#include <sys/resource.h>
#endif

// Function to get memory usage (in kilobytes)
long getMemoryUsage() {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS memCounters;
    if (GetProcessMemoryInfo(
            GetCurrentProcess(),
            &memCounters,
            sizeof(memCounters)
            )) {
        return memCounters.WorkingSetSize / 1024; // In KB
    }
    return 0;
#else
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        return usage.ru_maxrss; // In KB
    }
    return -1;
#endif
}

// Function to get CPU time (in seconds)
double getCPUTime() {
#ifdef _WIN32
    FILETIME creationTime, exitTime, kernelTime, userTime;
    if (GetProcessTimes(
            GetCurrentProcess(),
            &creationTime,
            &exitTime,
            &kernelTime,
            &userTime
            )) {
        ULARGE_INTEGER kernel, user;
        kernel.LowPart = kernelTime.dwLowDateTime;
        kernel.HighPart = kernelTime.dwHighDateTime;
        user.LowPart = userTime.dwLowDateTime;
        user.HighPart = userTime.dwHighDateTime;
        return (kernel.QuadPart + user.QuadPart) / 1e7; // Convert to seconds
    }
    return 0;
#else
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        return usage.ru_utime.tv_sec + usage.ru_utime.tv_usec / 1e6 +
               usage.ru_stime.tv_sec + usage.ru_stime.tv_usec / 1e6;
    }
    return -1;
#endif
}

int main(int argc, char* argv[]) {
    // Parse command-line arguments
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] 
            << " <number_of_clients> <number_of_updates>\n";
        return 1;
    }

    int num_clients = std::atoi(argv[1]);
    int num_updates = std::atoi(argv[2]);

    if (num_clients <= 0 || num_updates <= 0) {
        std::cerr << "Error: Number of clients and updates"
            "must be positive integers.\n";
        return 1;
    }

    auto server = std::make_shared<WeatherServer>();
    std::vector<std::shared_ptr<WeatherClient>> clients;

    // Create clients and subscribe them to a single location
    std::string location = "TestLocation";

    // Track initial resource usage
    std::cout << "Initial Memory Usage: " << getMemoryUsage() 
        << " KB, Initial CPU Time: " << getCPUTime() << " seconds\n";

    for (int i = 0; i < num_clients; ++i) {
        auto client = std::make_shared<WeatherClient>(
            
            "Client" + std::to_string(i), server);
        clients.push_back(client);
        client->subscribeToLocation(location);
    }

    // Measure resource usage after subscription
    std::cout << "After Subscription - Memory Usage: " << getMemoryUsage() 
        << " KB, CPU Time: " << getCPUTime() << " seconds\n";

    // Send multiple updates
    for (int i = 0; i < num_updates; ++i) {
        server->updateWeatherData(location, "Condition #" + std::to_string(i));
    }

    // Measure resource usage after sending updates
    std::cout << "After Sending Updates - Memory Usage: " << getMemoryUsage() 
        << " KB, CPU Time: " << getCPUTime() << " seconds\n";

    // Unsubscribe clients
    for (const auto& client : clients) {
        client->unsubscribeFromLocation(location);
    }

    // Measure resource usage after unsubscribing
    std::cout << "After Unsubscription - Memory Usage: " << getMemoryUsage() 
        << " KB, CPU Time: " << getCPUTime() << " seconds\n";

    return 0;
}
