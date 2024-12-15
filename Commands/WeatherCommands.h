// File: WeatherCommands.h
#ifndef WEATHER_COMMANDS_H
#define WEATHER_COMMANDS_H

#include "Command.h"
#include "WeatherReceiver.h"

class OnDemandWeatherCommand : public Command {
  private:
	WeatherReceiver &receiver; // Receiver to perform the action
	std::string location;	   // Location for the weather request

  public:
	OnDemandWeatherCommand(WeatherReceiver &recv, const std::string &loc)
		: receiver(recv), location(loc) {}

	void execute() override {
		receiver.logRequest(location);	 // Log the request
		receiver.fetchWeather(location); // Fetch weather data
	}
};

#endif // WEATHER_COMMANDS_H
