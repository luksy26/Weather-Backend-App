#include <iostream>
#include <string>
#include <memory>

class WeatherServer;

class WeatherClient : public std::enable_shared_from_this<WeatherClient> {
public:
    WeatherClient(
        const std::string& name,
        std::shared_ptr<WeatherServer> server
        );

    // Subscribe to updates for a specific location
    void subscribeToLocation(const std::string& location);

    // Unsubscribe from updates for a specific location
    void unsubscribeFromLocation(const std::string& location);

    // Request a weather report for an arbitrary location
    void requestWeatherReport(const std::string& location);

    // Receive a notification from the server
    void receiveNotification(
        const std::string& location,
        const std::string& condition
        );

private:
    std::string name;
    std::shared_ptr<WeatherServer> server;
};
