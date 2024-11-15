#include "WeatherClient.h"
#include "WeatherServer.h"

WeatherClient::WeatherClient(
    const std::string& name,
    std::shared_ptr<WeatherServer> server
    )
    : name(name), server(std::move(server)) {}

void WeatherClient::subscribeToLocation(const std::string& location) {
    server->subscribeClient(shared_from_this(), location);
    std::cout << name << " subscribed to " << location << "\n";
}

void WeatherClient::unsubscribeFromLocation(const std::string& location) {
    server->unsubscribeClient(shared_from_this(), location);
    std::cout << name << " unsubscribed from " << location << "\n";
}

void WeatherClient::requestWeatherReport(const std::string& location) {
    std::string report = server->getWeatherReport(location);
    std::cout << name << " requested weather for " 
                << location << ": " << report << "\n";
}

void WeatherClient::receiveNotification(
    const std::string& location,
    const std::string& condition
    ) {
    std::cout << name << " received update for " 
                << location << ": " << condition << "\n";
}
