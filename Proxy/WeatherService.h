#ifndef WEATHER_SERVICE_H
#define WEATHER_SERVICE_H

#include <string>
#include <memory>

class WeatherClient;

class WeatherService {
  public:
	virtual std::string getWeatherReport(const std::string &location) = 0;

	// Register a client for location updates
	virtual void subscribeClient(const std::shared_ptr<WeatherClient> &client,
								 const std::string &location) = 0;

	// Unsubscribe a client from location updates
	virtual void unsubscribeClient(const std::shared_ptr<WeatherClient> &client,
								   const std::string &location) = 0;

	// Notify clients of weather updates
	virtual void notifyClients(const std::string &location,
							   const std::string &weatherCondition,
							   const bool severeWeatherCondition) = 0;

	// Add weather report for a location
	virtual void updateWeatherData(const std::string &location,
								   const std::string &condition,
								   const bool severeWeatherCondition) = 0;

	virtual ~WeatherService() = default;
};

#endif // WEATHER_SERVICE_H
