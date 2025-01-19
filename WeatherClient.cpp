#include "WeatherClient.h"
#include "Notifications/NotificationsAbstractFactory.h"
#include "Proxy/WeatherService.h"
#include <sstream>

// Create Notification based on Device Type (using the abstract factory)
std::shared_ptr<NotificationFactory>
createNotification(DeviceType device_type) {
	std::shared_ptr<NotificationFactory> factory;

	// Choose the correct factory based on the device type
	if (device_type == DeviceType::Android) {

		factory = std::make_shared<AndroidNotificationFactory>();
	} else if (device_type == DeviceType::iOS) {

		factory = std::make_shared<AppleNotificationFactory>();
	} else {
		throw std::invalid_argument("Unknown DeviceType provided");
	}

	return factory;
}

WeatherClient::WeatherClient(const std::string &name, DeviceType device_type,
							 std::shared_ptr<WeatherService> server)
	: name(name), server(std::move(server)) {
	notificationFactory = createNotification(device_type);
}

void WeatherClient::subscribeToLocation(const std::string &location) {
	server->subscribeClient(shared_from_this(), location);
}

void WeatherClient::unsubscribeFromLocation(const std::string &location) {
	server->unsubscribeClient(shared_from_this(), location);
}

void WeatherClient::requestWeatherReport(const std::string &location) {
	std::string report = server->getWeatherReport(location);
}

void WeatherClient::receiveNotification(const std::string &location,
										const std::string &condition) {}

std::string WeatherClient::to_string() const {
	std::ostringstream oss;

	// Add client name
	oss << "WeatherClient [Name: " << name;

	// Add notification details
	if (notificationFactory) {
		oss << ", Notification Factory: "
			<< typeid(*notificationFactory).name();
	} else {
		oss << ", Notification Factory: None";
	}

	// Add WeatherService pointer
	oss << ", WeatherService: " << (server ? "Linked" : "Not Linked") << "]";

	return oss.str();
}