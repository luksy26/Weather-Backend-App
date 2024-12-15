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
								  const std::string &weatherCondition) {
	for (auto &client : subscribers[location]) {
		client->receiveNotification(location, weatherCondition);
	}
}

void WeatherServer::updateWeatherData(const std::string &location,
									  const std::string &condition) {
	weatherData[location] = condition;
	notifyClients(location, condition);
}

std::string WeatherServer::getWeatherReport(const std::string &location) {
	return weatherData.count(location) ? weatherData[location]
									   : "No data available";
}
