// Concrete Observers: four weather displays implementing Observer and DisplayElement.
// Push model: update() receives the measurements as arguments.
#pragma once
#include <iostream>
#include <memory>

#include "JavaFloat.h"
#include "Observer.h"
#include "WeatherData.h"

// Displays register themselves with the subject, which needs a shared_ptr to
// `this`. That is impossible inside a constructor, so each display is built
// through a static create() factory (enable_shared_from_this).
// Concrete Observer: shows the latest temperature and humidity.
class CurrentConditionsDisplay : public Observer, public DisplayElement,
                                 public std::enable_shared_from_this<CurrentConditionsDisplay> {
public:
    static std::shared_ptr<CurrentConditionsDisplay> create(WeatherData& weatherData) {
        std::shared_ptr<CurrentConditionsDisplay> d(new CurrentConditionsDisplay(weatherData));
        weatherData.registerObserver(d);  // safe now: d is already owned by a shared_ptr
        return d;
    }

    void update(float temperature, float humidity, float /*pressure*/) override {
        this->temperature = temperature;
        this->humidity = humidity;
        display();
    }

    void display() override {
        std::cout << "Current conditions: " << javaStr(temperature)
                  << "F degrees and " << javaStr(humidity) << "% humidity\n";
    }

private:
    explicit CurrentConditionsDisplay(WeatherData&) {}  // push model: no need to keep the subject
    float temperature = 0.0f;
    float humidity = 0.0f;
};

// Concrete Observer: keeps running average/max/min temperature.
class StatisticsDisplay : public Observer, public DisplayElement,
                          public std::enable_shared_from_this<StatisticsDisplay> {
public:
    static std::shared_ptr<StatisticsDisplay> create(WeatherData& weatherData) {
        std::shared_ptr<StatisticsDisplay> d(new StatisticsDisplay(weatherData));
        weatherData.registerObserver(d);  // safe now: d is already owned by a shared_ptr
        return d;
    }

    void update(float temperature, float /*humidity*/, float /*pressure*/) override {
        tempSum += temperature;
        numReadings++;
        if (temperature > maxTemp) maxTemp = temperature;
        if (temperature < minTemp) minTemp = temperature;
        display();
    }

    void display() override {
        std::cout << "Avg/Max/Min temperature = " << javaStr(tempSum / static_cast<float>(numReadings))
                  << "/" << javaStr(maxTemp) << "/" << javaStr(minTemp) << "\n";
    }

private:
    explicit StatisticsDisplay(WeatherData&) {}  // push model: no need to keep the subject
    float maxTemp = 0.0f;
    float minTemp = 200.0f;
    float tempSum = 0.0f;
    int numReadings = 0;
};

// Concrete Observer: compares the new pressure with the previous one.
class ForecastDisplay : public Observer, public DisplayElement,
                        public std::enable_shared_from_this<ForecastDisplay> {
public:
    static std::shared_ptr<ForecastDisplay> create(WeatherData& weatherData) {
        std::shared_ptr<ForecastDisplay> d(new ForecastDisplay(weatherData));
        weatherData.registerObserver(d);  // safe now: d is already owned by a shared_ptr
        return d;
    }

    void update(float /*temperature*/, float /*humidity*/, float pressure) override {
        lastPressure = currentPressure;
        currentPressure = pressure;
        display();
    }

    void display() override {
        std::cout << "Forecast: ";
        if (currentPressure > lastPressure) {
            std::cout << "Improving weather on the way!\n";
        } else if (currentPressure == lastPressure) {
            std::cout << "More of the same\n";
        } else {
            std::cout << "Watch out for cooler, rainy weather\n";
        }
    }

private:
    explicit ForecastDisplay(WeatherData&) {}  // push model: no need to keep the subject
    float currentPressure = 29.92f;
    float lastPressure = 0.0f;
};

// Concrete Observer: derives a heat index from temperature and humidity.
class HeatIndexDisplay : public Observer, public DisplayElement,
                         public std::enable_shared_from_this<HeatIndexDisplay> {
public:
    static std::shared_ptr<HeatIndexDisplay> create(WeatherData& weatherData) {
        std::shared_ptr<HeatIndexDisplay> d(new HeatIndexDisplay(weatherData));
        weatherData.registerObserver(d);  // safe now: d is already owned by a shared_ptr
        return d;
    }

    void update(float temperature, float humidity, float /*pressure*/) override {
        heatIndex = computeHeatIndex(temperature, humidity);
        display();
    }

    void display() override {
        std::cout << "Heat index is " << javaStr(heatIndex) << "\n";
    }

private:
    explicit HeatIndexDisplay(WeatherData&) {}  // push model: no need to keep the subject
    static float computeHeatIndex(float t, float rh) {
        return static_cast<float>(0.5 * (t + 61.0 + ((t - 68.0) * 1.2) + (rh * 0.094)));
    }
    float heatIndex = 0.0f;
};
