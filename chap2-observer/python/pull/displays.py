"""Concrete Observers: four weather displays that also implement DisplayElement.

Pull model: update() takes no arguments and reads the subject's getters.
"""
from java_float import f32, java_str
from observer import DisplayElement, Observer
from weather_data import WeatherData


class CurrentConditionsDisplay(Observer, DisplayElement):
    # Concrete Observer: shows the latest temperature and humidity.
    def __init__(self, weather_data: WeatherData) -> None:
        self._temperature = 0.0
        self._humidity = 0.0
        self._weather_data = weather_data
        weather_data.register_observer(self)  # subscribe to the subject

    def update(self) -> None:
        self._temperature = self._weather_data.get_temperature()
        self._humidity = self._weather_data.get_humidity()
        self.display()

    def display(self) -> None:
        print("Current conditions: " + java_str(self._temperature)
              + "F degrees and " + java_str(self._humidity) + "% humidity")


class StatisticsDisplay(Observer, DisplayElement):
    # Concrete Observer: keeps running average/max/min temperature.
    def __init__(self, weather_data: WeatherData) -> None:
        self._max_temp = 0.0
        self._min_temp = 200.0
        self._temp_sum = 0.0
        self._num_readings = 0
        self._weather_data = weather_data
        weather_data.register_observer(self)  # subscribe to the subject

    def update(self) -> None:
        temperature = self._weather_data.get_temperature()
        # f32 after each step emulates Java float arithmetic.
        self._temp_sum = f32(self._temp_sum + temperature)
        self._num_readings += 1
        if temperature > self._max_temp:
            self._max_temp = temperature
        if temperature < self._min_temp:
            self._min_temp = temperature
        self.display()

    def display(self) -> None:
        avg = f32(self._temp_sum / self._num_readings)
        print("Avg/Max/Min temperature = "
              + java_str(avg) + "/" + java_str(self._max_temp) + "/" + java_str(self._min_temp))


class ForecastDisplay(Observer, DisplayElement):
    # Concrete Observer: compares the new pressure with the previous one.
    def __init__(self, weather_data: WeatherData) -> None:
        self._current_pressure = f32(29.92)  # float32 like Java's float literal
        self._last_pressure = 0.0
        self._weather_data = weather_data
        weather_data.register_observer(self)  # subscribe to the subject

    def update(self) -> None:
        self._last_pressure = self._current_pressure
        self._current_pressure = self._weather_data.get_pressure()
        self.display()

    def display(self) -> None:
        print("Forecast: ", end="")
        if self._current_pressure > self._last_pressure:
            print("Improving weather on the way!")
        elif self._current_pressure == self._last_pressure:
            print("More of the same")
        else:
            print("Watch out for cooler, rainy weather")


class HeatIndexDisplay(Observer, DisplayElement):
    # Concrete Observer: derives a heat index from temperature and humidity.
    def __init__(self, weather_data: WeatherData) -> None:
        self._heat_index = 0.0
        self._weather_data = weather_data
        weather_data.register_observer(self)  # subscribe to the subject

    def update(self) -> None:
        temperature = self._weather_data.get_temperature()
        humidity = self._weather_data.get_humidity()
        self._heat_index = self._compute_heat_index(temperature, humidity)
        self.display()

    def _compute_heat_index(self, t: float, rh: float) -> float:
        return f32(0.5 * (t + 61.0 + ((t - 68.0) * 1.2) + (rh * 0.094)))

    def display(self) -> None:
        print("Heat index is " + java_str(self._heat_index))
