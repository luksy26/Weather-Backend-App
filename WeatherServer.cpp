#include "WeatherServer.h"
#include "WeatherClient.h"
#include <algorithm>

void WeatherServer::subscribeClient(
	const std::shared_ptr<WeatherClient> &client, const std::string &location) {
	subscribers[location].insert(client);
}

void WeatherServer::unsubscribeClient(
	const std::shared_ptr<WeatherClient> &client, const std::string &location) {
	auto &clients = subscribers[location];
	clients.erase(client);
}

void WeatherServer::notifyClients(const std::string &location,
								  const std::string &weatherCondition,
								  const bool severeWeatherCondition) {
	for (auto &client : subscribers[location]) {
		if (severeWeatherCondition) {
			client->getNotificationFactory()
				->createSevereWeatherNotification()
				->notify(client->getName(), location, weatherCondition);
		} else {
			client->getNotificationFactory()
				->createDailyUpdateNotification()
				->notify(client->getName(), location, weatherCondition);
		}

		// client->receiveNotification(location, weatherCondition);
	}
}

void WeatherServer::updateWeatherData(const std::string &location,
									  const std::string &condition,
									  const bool severeWeatherCondition) {
	weatherData[location] = condition;
	notifyClients(location, condition, severeWeatherCondition);
}

std::string WeatherServer::getWeatherReport(const std::string &location) {
	return weatherData.count(location) ? weatherData[location]
									   : "No data available";
}
