#include "WeatherServer.h"
#include "WeatherClient.h"
#include <chrono>
#include <iostream>
#include <memory>

int main() {
    auto server = std::make_shared<WeatherServer>();
    auto client = std::make_shared<WeatherClient>("LatencyClient", server);

    // Subscribe client to a location
    std::string location = "TestCity";
    auto start_subscribe = std::chrono::high_resolution_clock::now();
    client->subscribeToLocation(location);
    auto end_subscribe = std::chrono::high_resolution_clock::now();

    // Measure notification latency
    server->updateWeatherData(location, "Sunny");
    auto end_notify = std::chrono::high_resolution_clock::now();

    // Calculate durations
    auto subscribe_time = 
        std::chrono::duration_cast<std::chrono::microseconds>(
            end_subscribe - start_subscribe
            ).count();
    auto notify_time = 
        std::chrono::duration_cast<std::chrono::microseconds>(
            end_notify - end_subscribe
            ).count();

    std::cout << "Subscribe Time: " << subscribe_time 
        << " microseconds\n";
    std::cout << "Notify Time: " << notify_time 
        << " microseconds\n";

    return 0;
}
