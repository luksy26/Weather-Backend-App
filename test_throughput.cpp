#include "Commands/CommandInvoker.h"
#include "Commands/UpdateWeatherDataCommand.h"
#include "WeatherClient.h"
#include "WeatherServer.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

#define MAX_TEMPERATURE 38

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
		std::cerr << "Error: Number of clients and updates must be "
					 "positive integers.\n";
		return 1;
	}

	auto server = std::make_shared<WeatherServer>();
	auto weatherServiceProxy = std::make_shared<WeatherServiceProxy>(server);
	std::vector<std::shared_ptr<WeatherClient>> clients;

	std::array<std::string, 3> locations = {"Paris", "Bucharest",
											"Los Angeles"};

	for (int i = 0; i < num_clients; ++i) {
		auto client = std::make_shared<WeatherClient>(
			"Client" + std::to_string(i), getRandomDeviceType(), server);
		client->subscribeToLocation(locations.at(i % 3));
		clients.push_back(client);
	}

	// Measure throughput
	auto start = std::chrono::high_resolution_clock::now();

	// Create Command Invoker
	CommandInvoker invoker;

	for (int i = 0; i < num_updates; i++) {
		invoker.addCommand(std::make_shared<UpdateWeatherDataCommand>(
			weatherServiceProxy, locations.at(i % 3),
			"Temperature: " + std::to_string(i % MAX_TEMPERATURE) + "°C",
			i % 2));
	}

	// Add commands to the invoker
	invoker.executeCommands();

	auto end = std::chrono::high_resolution_clock::now();

	auto duration =
		std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
			.count();

	// Notifications per second
	double throughput = (num_clients * num_updates) / (duration / 1000.0f);

	std::cout << "For " << num_clients << " clients and " << num_updates
			  << " location updates:\n";
	std::cout << "Total Time: " << duration << " ms\n";
	std::cout << "Throughput: " << throughput << " notifications/second\n";

	return 0;
}
