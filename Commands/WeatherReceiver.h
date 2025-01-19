// File: WeatherReceiver.h
#ifndef WEATHER_RECEIVER_H
#define WEATHER_RECEIVER_H

#include "../Proxy/WeatherService.h"
#include <iostream>
#include <string>

class WeatherServer;

class WeatherReceiver {
  public:
	std::shared_ptr<WeatherService> weatherService;

	explicit WeatherReceiver(std::shared_ptr<WeatherService> weatherService)
		: weatherService(std::move(weatherService)) {}

	void fetchWeather(const std::string &location) {
		// Simulate fetching weather data
	}

	void logRequest(const std::string &location) {}
};

#endif // WEATHER_RECEIVER_H
