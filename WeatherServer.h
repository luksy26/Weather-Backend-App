#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

// Forward declaration of client
class WeatherClient;

class WeatherServer {
public:
    // Register a client for location updates
    void subscribeClient(
        const std::shared_ptr<WeatherClient>& client,
        const std::string& location
        );
    
    // Unsubscribe a client from location updates
    void unsubscribeClient(
        const std::shared_ptr<WeatherClient>& client,
        const std::string& location);

    // Notify clients of weather updates
    void notifyClients(
        const std::string& location,
        const std::string& weatherCondition
        );

    // Add weather report for a location
    void updateWeatherData(
        const std::string& location,
        const std::string& condition);

    // Retrieve the weather report for a specific location
    std::string getWeatherReport(
        const std::string& location
        );

private:
    // hashmap from location -> clients
    std::unordered_map<
            std::string,
            std::vector<std::shared_ptr<WeatherClient>>
            > subscribers;
    // hashmap from location -> weather condition
    std::unordered_map<std::string, std::string> weatherData;
};
