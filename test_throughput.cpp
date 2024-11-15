#include "WeatherServer.h"
#include "WeatherClient.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

int main() {
    auto server = std::make_shared<WeatherServer>();
    std::vector<std::shared_ptr<WeatherClient>> clients;

    // Create multiple clients and subscribe them to a location
    std::string location = "TestCity";
    int num_clients = 100000; // Value to adjust
    for (int i = 0; i < num_clients; ++i) {
        auto client = std::make_shared<WeatherClient>(
            "Client" + std::to_string(i), server
            );
        client->subscribeToLocation(location);
        clients.push_back(client);
    }

    // Measure throughput
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i) { // Send multiple notifications
        server->updateWeatherData(
            location, "Condition #" + std::to_string(i)
            );
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = 
        std::chrono::duration_cast<std::chrono::milliseconds>(
            end - start
            ).count();

    // Notifications per second
    double throughput = (num_clients * 100.0) / (duration / 1000.0);

    std::cout << "For " << num_clients << " clients:\n";
    std::cout << "Total Time: " << duration << " ms\n";
    std::cout << "Throughput: " << throughput 
        << " notifications/second\n";

    return 0;
}
