// Client / test drive (pull model): creates the subject and displays, then feeds readings.
#include <iostream>

#include "Displays.h"
#include "WeatherData.h"

int main() {
    WeatherData weatherData;

    // The subject keeps only weak_ptrs, so we hold the displays to keep them alive.
    auto current = CurrentConditionsDisplay::create(weatherData);
    auto statistics = StatisticsDisplay::create(weatherData);
    auto forecast = ForecastDisplay::create(weatherData);
    auto heatIndex = HeatIndexDisplay::create(weatherData);

    std::cout << "--- Weather update 1 ---\n";
    weatherData.setMeasurements(80, 65, 30.4f);

    std::cout << "\n--- Weather update 2 ---\n";
    weatherData.setMeasurements(82, 70, 29.2f);

    std::cout << "\n--- Weather update 3 ---\n";
    weatherData.setMeasurements(78, 90, 29.2f);
    return 0;
}
