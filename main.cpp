#include "WeatherServer.h"
#include "WeatherClient.h"

int main() {
    auto server = std::make_shared<WeatherServer>();
    auto client1 = std::make_shared<WeatherClient>("Client1", server);
    auto client2 = std::make_shared<WeatherClient>("Client2", server);

    client1->subscribeToLocation("New York");
    client2->subscribeToLocation("New York");
    client1->subscribeToLocation("Los Angeles");

    // Server updates weather data
    server->updateWeatherData("New York", "Sunny, 75°F");
    server->updateWeatherData("Los Angeles", "Cloudy, 65°F");

    // Client requests weather report for an arbitrary location
    client2->requestWeatherReport("San Francisco");

    // Client unsubscribes and server updates data again
    client1->unsubscribeFromLocation("New York");
    server->updateWeatherData("New York", "Rainy, 60°F");

    return 0;
}
