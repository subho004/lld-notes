// Concrete Subject: WeatherData stores measurements and notifies observers.
#pragma once
#include <algorithm>
#include <memory>
#include <vector>

#include "Observer.h"

// Concrete Subject. Observers are held as weak_ptr: the subject does not own them,
// so there is no ownership cycle and destroyed observers are skipped safely.
class WeatherData : public Subject {
public:
    void registerObserver(const std::shared_ptr<Observer>& o) override {
        observers.push_back(o);
    }

    void removeObserver(const std::shared_ptr<Observer>& o) override {
        observers.erase(
            std::remove_if(observers.begin(), observers.end(),
                           [&o](const std::weak_ptr<Observer>& w) {
                               auto sp = w.lock();
                               return !sp || sp == o;  // also drops dead observers
                           }),
            observers.end());
    }

    void notifyObservers() override {
        auto snapshot = observers;  // safe if an observer unregisters during update
        for (auto& w : snapshot) {
            if (auto observer = w.lock()) {
                observer->update();
            }
        }
    }

    // Hook called when new data arrives; triggers the notification.
    void measurementsChanged() { notifyObservers(); }

    void setMeasurements(float temperature, float humidity, float pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        measurementsChanged();
    }

    float getTemperature() const { return temperature; }
    float getHumidity() const { return humidity; }
    float getPressure() const { return pressure; }

private:
    std::vector<std::weak_ptr<Observer>> observers;
    float temperature = 0.0f;
    float humidity = 0.0f;
    float pressure = 0.0f;
};
