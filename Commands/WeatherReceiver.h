// File: WeatherReceiver.h
#ifndef WEATHER_RECEIVER_H
#define WEATHER_RECEIVER_H

#include <iostream>
#include <string>

class WeatherReceiver {
  public:
	void fetchWeather(const std::string &location) {
		// Simulate fetching weather data
		std::cout << "Fetching on-demand weather for " << location << "...\n";
		std::cout << "Weather for " << location << ": Sunny, 22°C\n";
	}

	void logRequest(const std::string &location) {
		std::cout << "Logging request for weather data at location: "
				  << location << "\n";
	}
};

#endif // WEATHER_RECEIVER_H
