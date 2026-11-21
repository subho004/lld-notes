"""Concrete Subject: WeatherData holds the measurements and the observer list."""
from typing import List

from java_float import f32
from observer import Observer, Subject


class WeatherData(Subject):
    # Concrete Subject: stores state and notifies registered observers.
    def __init__(self) -> None:
        self._observers: List[Observer] = []
        self._temperature = 0.0
        self._humidity = 0.0
        self._pressure = 0.0

    def register_observer(self, o: Observer) -> None:
        self._observers.append(o)

    def remove_observer(self, o: Observer) -> None:
        if o in self._observers:
            self._observers.remove(o)

    def notify_observers(self) -> None:
        # Iterate over a copy so an observer may unregister during the loop
        # (Java would throw ConcurrentModificationException here).
        for observer in list(self._observers):
            observer.update(self._temperature, self._humidity, self._pressure)

    def measurements_changed(self) -> None:
        # Hook called when new data arrives; triggers the notification.
        self.notify_observers()

    def set_measurements(self, temperature: float, humidity: float, pressure: float) -> None:
        # Java parameters are 32-bit floats; emulate that rounding.
        self._temperature = f32(temperature)
        self._humidity = f32(humidity)
        self._pressure = f32(pressure)
        self.measurements_changed()

    def get_temperature(self) -> float:
        return self._temperature

    def get_humidity(self) -> float:
        return self._humidity

    def get_pressure(self) -> float:
        return self._pressure
