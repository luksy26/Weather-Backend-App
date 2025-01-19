#include "WeatherClient.h"
#include "WeatherServer.h"
#include <chrono>
#include <cstdlib> // For std::atoi
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#ifdef _WIN32
#include <psapi.h>
#include <windows.h>
#else
#include <sys/resource.h>
#endif
#include "Commands/CommandInvoker.h"
#include "Commands/UpdateWeatherDataCommand.h"

// Function to get memory usage (in kilobytes)
long getMemoryUsage() {
#ifdef _WIN32
	PROCESS_MEMORY_COUNTERS memCounters;
	if (GetProcessMemoryInfo(GetCurrentProcess(), &memCounters,
							 sizeof(memCounters))) {
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
	if (GetProcessTimes(GetCurrentProcess(), &creationTime, &exitTime,
						&kernelTime, &userTime)) {
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

DeviceType getRandomDeviceType() {
	int number = rand() % 2;
	return number == 0 ? DeviceType::Android : DeviceType::iOS;
}

int main(int argc, char *argv[]) {
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
	// Initialize Proxy
	auto weatherServiceProxy = std::make_shared<WeatherServiceProxy>(server);

	std::vector<std::shared_ptr<WeatherClient>> clients;

	// Track initial resource usage
	std::cout << "Initial Memory Usage: " << getMemoryUsage()
			  << " KB, Initial CPU Time: " << getCPUTime() << " seconds\n";

	std::array<std::string, 3> locations = {"Paris", "Bucharest",
											"Los Angeles"};

	for (int i = 0; i < num_clients; ++i) {
		auto client = std::make_shared<WeatherClient>(

			"Client" + std::to_string(i), getRandomDeviceType(), server);
		clients.push_back(client);
		client->subscribeToLocation(locations.at(i % 3));
	}

	// Measure resource usage after subscription
	std::cout << "After Subscription - Memory Usage: " << getMemoryUsage()
			  << " KB, CPU Time: " << getCPUTime() << " seconds\n";

	// Create Command Invoker
	CommandInvoker invoker;

	// Add commands to the invoker
	invoker.addCommand(std::make_shared<UpdateWeatherDataCommand>(
		weatherServiceProxy, "Paris", "Sunny, 22°C", false));
	invoker.addCommand(std::make_shared<UpdateWeatherDataCommand>(
		weatherServiceProxy, "Bucharest", "Rainy, 15°C", true));
	invoker.addCommand(std::make_shared<UpdateWeatherDataCommand>(
		weatherServiceProxy, "Los Angeles", "Cloudy, 12°C", false));

	invoker.executeCommands();

	// Measure resource usage after sending updates
	std::cout << "After Sending Updates - Memory Usage: " << getMemoryUsage()
			  << " KB, CPU Time: " << getCPUTime() << " seconds\n";

	for (int i = 0; i < num_clients; ++i) {
		clients[i]->unsubscribeFromLocation(locations.at(i % 3));
	}

	// Measure resource usage after unsubscribing
	std::cout << "After UnsubscriptionF - Memory Usage: " << getMemoryUsage()
			  << " KB, CPU Time: " << getCPUTime() << " seconds\n";

	return 0;
}
