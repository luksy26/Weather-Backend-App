#include "Commands/CommandInvoker.h"
#include "Commands/RequestWeatherReportCommand.h"
#include "Commands/UpdateWeatherDataCommand.h"
#include "WeatherClient.h"
#include "WeatherServer.h"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#define MAX_TEMPERATURE 38

DeviceType getRandomDeviceType() {
	int number = rand() % 2;
	return number == 0 ? DeviceType::Android : DeviceType::iOS;
}

void getSubscribeTimeResults(
	int num_clients, const std::string &location,
	const std::shared_ptr<WeatherServer> &server,
	std::vector<std::shared_ptr<WeatherClient>> &clients,
	float &total_subscribe_time, float &min_subscribe, float &max_subscribe) {
	total_subscribe_time = 0.0f;
	max_subscribe = std::numeric_limits<float>::min();
	min_subscribe = std::numeric_limits<float>::max();

	for (int i = 0; i < num_clients; ++i) {
		auto client = std::make_shared<WeatherClient>(
			"Client" + std::to_string(i), getRandomDeviceType(), server);
		clients.push_back(client);

		// All clients subscribe to the same location
		auto start_subscribe = std::chrono::high_resolution_clock::now();
		client->subscribeToLocation(location);
		auto end_subscribe = std::chrono::high_resolution_clock::now();

		auto subscribe_time =
			std::chrono::duration_cast<std::chrono::microseconds>(
				end_subscribe - start_subscribe)
				.count() /
			1000.0f;
		max_subscribe = std::max(max_subscribe, subscribe_time);
		min_subscribe = std::min(min_subscribe, subscribe_time);
		total_subscribe_time += subscribe_time;
	}
}

void getNotificationTimeResults(
	int num_updates, CommandInvoker &invoker,
	std::shared_ptr<WeatherServiceProxy> weatherServiceProxy,
	const std::string &location, float &total_notify_time, float &min_notify,
	float &max_notify) {

	for (int i = 0; i < num_updates; ++i) {
		auto start_notify = std::chrono::high_resolution_clock::now();
		invoker.addCommand(std::make_shared<UpdateWeatherDataCommand>(
			weatherServiceProxy, location,
			"Temperature: " + std::to_string(i % MAX_TEMPERATURE) + "°C",
			i % 2));
		invoker.executeCommands();
		auto end_notify = std::chrono::high_resolution_clock::now();
		auto notify_time =
			std::chrono::duration_cast<std::chrono::microseconds>(end_notify -
																  start_notify)
				.count() /
			1000.0f;
		max_notify = std::max(max_notify, notify_time);
		min_notify = std::min(min_notify, notify_time);
		total_notify_time += notify_time;
	}
}

void getRequestUpdateTimeResults(
	CommandInvoker &invoker,
	std::vector<std::shared_ptr<WeatherClient>> &clients,
	const std::string &location, float &total_request_time, float &min_request,
	float &max_request) {
	for (const auto &client : clients) {
		auto start_request = std::chrono::high_resolution_clock::now();
		invoker.addCommand(
			std::make_shared<RequestWeatherReportCommand>(client, location));
		invoker.executeCommands();
		auto end_request = std::chrono::high_resolution_clock::now();

		auto request_time =
			std::chrono::duration_cast<std::chrono::microseconds>(end_request -
																  start_request)
				.count() /
			1000.0f;
		max_request = std::max(max_request, request_time);
		min_request = std::min(min_request, request_time);
		total_request_time += request_time;
	}
}

void getUnsubscribeTimeResults(
	const std::vector<std::shared_ptr<WeatherClient>> &clients,
	const std::string &location, float &total_unsubscribe_time,
	float &min_unsubscribe, float &max_unsubscribe) {
	for (const auto &client : clients) {
		auto start_unsubscribe = std::chrono::high_resolution_clock::now();
		client->unsubscribeFromLocation(location);
		auto end_unsubscribe = std::chrono::high_resolution_clock::now();

		auto unsubscribe_time =
			std::chrono::duration_cast<std::chrono::microseconds>(
				end_unsubscribe - start_unsubscribe)
				.count() /
			1000.0f;
		max_unsubscribe = std::max(max_unsubscribe, unsubscribe_time);
		min_unsubscribe = std::min(min_unsubscribe, unsubscribe_time);
		total_unsubscribe_time += unsubscribe_time;
	}
}

// Function to display the results
void getResults(int num_clients, int num_updates, float total_subscribe_time,
				float min_subscribe, float max_subscribe,
				float total_notify_time, float min_notify, float max_notify,
				float total_request_time, float min_request, float max_request,
				float total_unsubscribe_time, float min_unsubscribe,
				float max_unsubscribe) {
	// Output results
	std::cout << "For " << num_clients << " clients and " << num_updates
			  << " updates:\n";

	std::cout << "Total Subscribe Time: " << total_subscribe_time << " ms\n";
	std::cout << "Avg Subscribe Time per Client: "
			  << total_subscribe_time / num_clients
			  << " ms. Min: " << min_subscribe << "ms. Max: " << max_subscribe
			  << "ms.\n";

	std::cout << "Total Notify Time: " << total_notify_time << " ms\n";
	std::cout << "Avg Notify Time per Update: "
			  << total_notify_time / num_updates << " ms. Min: " << min_notify
			  << "ms. Max: " << max_notify << "ms.\n";

	std::cout << "Total Request Time: " << total_request_time << " ms\n";
	std::cout << "Avg Request Time per Client: "
			  << total_request_time / num_clients << " ms. Min: " << min_request
			  << "ms. Max: " << max_request << "ms.\n";

	std::cout << "Total Unsubscribe Time: " << total_unsubscribe_time
			  << " ms\n";
	std::cout << "Avg Unsubscribe Time per Client: "
			  << total_unsubscribe_time / num_clients
			  << " ms. Min: " << min_unsubscribe
			  << "ms. Max: " << max_unsubscribe << "ms.\n";
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

	// Create clients and subscribe them to a single location
	std::string location = "Paris";

	float total_subscribe_time = 0;
	float max_subscribe = std::numeric_limits<float>::min();
	float min_subscribe = std::numeric_limits<float>::max();

	getSubscribeTimeResults(num_clients, location, server, clients,
							total_subscribe_time, min_subscribe, max_subscribe);

	// Send multiple updates and measure latency

	float total_notify_time = 0;
	float max_notify = std::numeric_limits<float>::min();
	float min_notify = std::numeric_limits<float>::max();

	// Create Command Invoker
	CommandInvoker invoker;

	// Add commands to the invoker
	getNotificationTimeResults(num_updates, invoker, weatherServiceProxy,
							   location, total_notify_time, min_notify,
							   max_notify);

	// Measure weather report request latency
	float total_request_time = 0;
	float max_request = std::numeric_limits<float>::min();
	float min_request = std::numeric_limits<float>::max();

	getRequestUpdateTimeResults(invoker, clients, location, total_request_time,
								min_request, max_request);

	// Measure unsubscribe latency
	float total_unsubscribe_time = 0;
	float max_unsubscribe = std::numeric_limits<float>::min();
	float min_unsubscribe = std::numeric_limits<float>::max();

	getUnsubscribeTimeResults(clients, location, total_unsubscribe_time,
							  min_unsubscribe, max_unsubscribe);

	getResults(num_clients, num_updates, total_subscribe_time, min_subscribe,
			   max_subscribe, total_notify_time, min_notify, max_notify,
			   total_request_time, min_request, max_request,
			   total_unsubscribe_time, min_unsubscribe, max_unsubscribe);

	return 0;
}
