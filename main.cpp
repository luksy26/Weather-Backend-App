#include "Commands/CommandInvoker.h"
#include "Commands/RequestWeatherReportCommand.h"
#include "Commands/UpdateWeatherDataCommand.h"
#include "Notifications/NotificationTypes.h"
#include "Notifications/NotificationsAbstractFactory.h"
#include "Proxy/WeatherServiceProxy.h"
#include "WeatherClient.h"
#include "WeatherServer.h"
#include <chrono>
#include <memory>
#include <thread>

int main() {
	// Initialize Server
	auto weatherServer = std::make_shared<WeatherServer>();

	// Initialize Proxy
	auto weatherServiceProxy =
		std::make_shared<WeatherServiceProxy>(weatherServer);

	// Create Clients
	auto client1 = std::make_shared<WeatherClient>(
		"Client1", DeviceType::Android, weatherServiceProxy);
	auto client2 = std::make_shared<WeatherClient>("Client2", DeviceType::iOS,
												   weatherServiceProxy);

	std::cout << "Clients have been created with the following configuration:\n"
			  << client1->to_string() << "\n";

	std::cout << client2->to_string() << "\n";

	// Clients subscribe to locations
	client1->subscribeToLocation("Paris");
	client1->subscribeToLocation("Bucharest");
	client1->subscribeToLocation("Rome");
	client2->subscribeToLocation("Los Angeles");
	client2->subscribeToLocation("New York");

	// std::cout << "\n**Updating weather data in the server**\n";
	// Update weather data on the server
	// weatherServiceProxy->updateWeatherData("Paris", "Sunny, 22°C", false);
	// weatherServiceProxy->updateWeatherData("Bucharest", "Rainy, 15°C", true);
	// weatherServiceProxy->updateWeatherData("Los Angeles", "Cloudy, 12°C",
	// 									   false);
	// weatherServiceProxy->updateWeatherData("Rome", "Sunny, 15°C", false);

	// // Demonstrating Proxy Pattern: Request weather reports
	// std::cout << "\n**Using Proxy to Fetch Weather Reports**\n";
	// client1->requestWeatherReport("Paris"); // Through server initially
	// client1->requestWeatherReport("Paris"); // Now from proxy cache

	// client2->requestWeatherReport("Los Angeles"); // Through server
	// client2->requestWeatherReport("Los Angeles"); // From proxy cache

	// Demonstrating Command Pattern: On-demand Weather Commands
	std::cout << "\n**Using Command Pattern for On-Demand Requests**\n";

	// Create Command Invoker
	CommandInvoker invoker;

	// Add commands to the invoker
	invoker.addCommand(std::make_shared<UpdateWeatherDataCommand>(
		weatherServiceProxy, "Paris", "Sunny, 22°C", false));
	invoker.addCommand(std::make_shared<UpdateWeatherDataCommand>(
		weatherServiceProxy, "Bucharest", "Rainy, 15°C", true));
	invoker.addCommand(std::make_shared<UpdateWeatherDataCommand>(
		weatherServiceProxy, "Los Angeles", "Cloudy, 12°C", false));
	invoker.addCommand(std::make_shared<UpdateWeatherDataCommand>(
		weatherServiceProxy, "Rome", "Sunny, 15°C", false));

	invoker.addCommand(
		std::make_shared<RequestWeatherReportCommand>(client1, "Paris"));
	invoker.addCommand(
		std::make_shared<RequestWeatherReportCommand>(client1, "Paris"));
	invoker.addCommand(
		std::make_shared<RequestWeatherReportCommand>(client2, "Los Angeles"));
	invoker.addCommand(
		std::make_shared<RequestWeatherReportCommand>(client2, "Los Angeles"));

	// Execute all commands
	invoker.executeCommands();

	return 0;
}
