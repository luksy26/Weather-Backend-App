#ifndef WEATHER_SERVICE_PROXY_H
#define WEATHER_SERVICE_PROXY_H

#include "WeatherService.h"

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class WeatherService;

class WeatherServiceProxy : public WeatherService {
  private:
	std::shared_ptr<WeatherService> realService; // Use WeatherService interface
	std::unordered_map<std::string,
					   std::pair<std::string, std::chrono::time_point<
												  std::chrono::steady_clock>>>
		cache;
	std::chrono::seconds cacheExpiry = std::chrono::seconds(10); // Cache TTL

  public:
	explicit WeatherServiceProxy(std::shared_ptr<WeatherService> realService)
		: realService(std::move(realService)) {}

	std::string getWeatherReport(const std::string &location) {
		auto now = std::chrono::steady_clock::now();

		// Check cache validity
		if (cache.find(location) != cache.end()) {
			auto &[cachedReport, timestamp] = cache[location];
			if (now - timestamp < cacheExpiry) {

				return cachedReport;
			}
		}

		// Fetch fresh data from the real service if cache is expired or missing

		std::string freshReport = realService->getWeatherReport(location);

		// Update the cache
		cache[location] = {freshReport, now};

		return freshReport;
	}

	// Register a client for location updates
	void subscribeClient(const std::shared_ptr<WeatherClient> &client,
						 const std::string &location) {

		realService->subscribeClient(client, location);
	}

	// Unsubscribe a client from location updates
	void unsubscribeClient(const std::shared_ptr<WeatherClient> &client,
						   const std::string &location) {
		realService->unsubscribeClient(client, location);
	}

	// Notify clients of weather updates
	void notifyClients(const std::string &location,
					   const std::string &weatherCondition,
					   const bool severeWeatherCondition) {
		realService->notifyClients(location, weatherCondition,
								   severeWeatherCondition);
	}

	// Add weather report for a location
	void updateWeatherData(const std::string &location,
						   const std::string &condition,
						   const bool severeWeatherCondition) {

		realService->updateWeatherData(location, condition,
									   severeWeatherCondition);
	}
};

#endif // WEATHER_SERVICE_PROXY_H
