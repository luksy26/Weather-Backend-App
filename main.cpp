#include "Commands/CommandInvoker.h"
#include "Commands/WeatherCommands.h"
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

	// Update weather data on the server
	weatherServiceProxy->updateWeatherData("Paris", "Sunny, 22°C");
	weatherServiceProxy->updateWeatherData("Bucharest", "Rainy, 15°C");
	weatherServiceProxy->updateWeatherData("Los Angeles", "Cloudy, 12°C");
	weatherServiceProxy->updateWeatherData("Rome", "Sunny, 15°C");

	// Demonstrating Proxy Pattern: Request weather reports
	std::cout << "\n**Using Proxy to Fetch Weather Reports**\n";
	client1->requestWeatherReport("New York"); // Through server initially
	client1->requestWeatherReport("New York"); // Now from proxy cache

	client2->requestWeatherReport("Los Angeles"); // Through server
	client2->requestWeatherReport("Los Angeles"); // From proxy cache

	// Create Notification Factories
	std::shared_ptr<NotificationFactory> androidFactory =
		std::make_shared<AndroidNotificationFactory>();
	std::shared_ptr<NotificationFactory> appleFactory =
		std::make_shared<AppleNotificationFactory>();

	std::cout << "\n**Sending Notifications to Clients**\n";

	// Send notifications using Abstract Factory Pattern
	auto androidUpdate = androidFactory->createDailyUpdateNotification();
	auto appleAlert = appleFactory->createSevereWeatherNotification();

	androidUpdate->notify("Client1", "New York");
	appleAlert->notify("Client2", "Los Angeles");

	// Demonstrating Command Pattern: On-demand Weather Commands
	std::cout << "\n**Using Command Pattern for On-Demand Requests**\n";
	CommandInvoker invoker;
	WeatherReceiver weatherReceiver;

	auto onDemandCommand1 =
		std::make_shared<OnDemandWeatherCommand>(weatherReceiver, "New York");
	auto onDemandCommand2 = std::make_shared<OnDemandWeatherCommand>(
		weatherReceiver, "Los Angeles");

	invoker.addCommand(onDemandCommand1);
	invoker.addCommand(onDemandCommand2);
	invoker.executeCommands();

	return 0;
}
