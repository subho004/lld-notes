// Client / test drive: creates the subject and displays, then feeds readings.
#include <iostream>

#include "Displays.h"
#include "WeatherData.h"

int main() {
    WeatherData weatherData;

    // The caller owns the displays via shared_ptr; the subject only holds weak_ptrs.
    auto currentDisplay = CurrentConditionsDisplay::create(weatherData);
    auto statisticsDisplay = StatisticsDisplay::create(weatherData);
    auto forecastDisplay = ForecastDisplay::create(weatherData);
    auto heatIndexDisplay = HeatIndexDisplay::create(weatherData);

    std::cout << "--- Weather update 1 ---\n";
    weatherData.setMeasurements(80, 65, 30.4f);

    std::cout << "\n--- Weather update 2 ---\n";
    weatherData.setMeasurements(82, 70, 29.2f);

    std::cout << "\n--- Weather update 3 ---\n";
    weatherData.setMeasurements(78, 90, 29.2f);

    std::cout << "\n--- Removing current conditions display ---\n";
    weatherData.removeObserver(currentDisplay);

    std::cout << "\n--- Weather update 4 ---\n";
    weatherData.setMeasurements(75, 60, 29.5f);
    return 0;
}
