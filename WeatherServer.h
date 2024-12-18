
#ifndef WEATHER_SERVER_H
#define WEATHER_SERVER_H

#include "Proxy/WeatherService.h"

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class WeatherService;

// Forward declaration of client
class WeatherClient;

class WeatherServer : public WeatherService {
  public:
	// Register a client for location updates
	void subscribeClient(const std::shared_ptr<WeatherClient> &client,
						 const std::string &location);

	// Unsubscribe a client from location updates
	void unsubscribeClient(const std::shared_ptr<WeatherClient> &client,
						   const std::string &location);

	// Notify clients of weather updates
	void notifyClients(const std::string &location,
					   const std::string &weatherCondition,
					   const bool severeWeatherCondition);

	// Add weather report for a location
	void updateWeatherData(const std::string &location,
						   const std::string &condition,
						   const bool severeWeatherCondition);

	// Retrieve the weather report for a specific location
	std::string getWeatherReport(const std::string &location);

  private:
	// hashmap from location -> clients
	std::unordered_map<std::string,
					   std::unordered_set<std::shared_ptr<WeatherClient>>>
		subscribers;
	// hashmap from location -> weather condition
	std::unordered_map<std::string, std::string> weatherData;
};

#endif // WEATHER_SERVER_H