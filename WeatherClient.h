#include "Notifications/NotificationsAbstractFactory.h"
#include "Proxy/WeatherServiceProxy.h"
#include <iostream>
#include <memory>
#include <string>

enum class DeviceType { Android, iOS };

class WeatherService;

class WeatherClient : public std::enable_shared_from_this<WeatherClient> {
  public:
	WeatherClient(const std::string &name, DeviceType device_type,
				  std::shared_ptr<WeatherService> server);

	// Subscribe to updates for a specific location
	void subscribeToLocation(const std::string &location);

	// Unsubscribe from updates for a specific location
	void unsubscribeFromLocation(const std::string &location);

	// Request a weather report for an arbitrary location
	void requestWeatherReport(const std::string &location);

	// Receive a notification from the server
	void receiveNotification(const std::string &location,
							 const std::string &condition);

	// Add to_string method
	std::string to_string() const;

  private:
	std::string name;
	std::shared_ptr<WeatherService> server;
	std::shared_ptr<NotificationFactory> notificationFactory;
};
