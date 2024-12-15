
#include "Command.h"

class RequestWeatherReportCommand : public Command {
	std::shared_ptr<WeatherClient> client;
	std::string location;

  public:
	RequestWeatherReportCommand(std::shared_ptr<WeatherClient> client,
								const std::string &location)
		: client(std::move(client)), location(location) {}

	void execute() override { client->requestWeatherReport(location); }
};