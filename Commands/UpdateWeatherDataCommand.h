#include "Command.h"

class UpdateWeatherDataCommand : public Command {
	std::shared_ptr<WeatherService> weatherService;
	std::string location;
	std::string weatherCondition;
	bool severeWeatherCondition;

  public:
	UpdateWeatherDataCommand(std::shared_ptr<WeatherService> service,
							 const std::string &location,
							 const std::string &condition,
							 const bool severeWeatherCondition)
		: weatherService(std::move(service)), location(location),
		  weatherCondition(condition),
		  severeWeatherCondition(severeWeatherCondition) {}

	void execute() override {
		weatherService->updateWeatherData(location, weatherCondition,
										  severeWeatherCondition);
		}
};