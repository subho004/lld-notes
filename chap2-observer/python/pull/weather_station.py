"""Client / test drive: wires the displays to WeatherData and feeds it readings."""
from displays import (CurrentConditionsDisplay, ForecastDisplay,
                      HeatIndexDisplay, StatisticsDisplay)
from weather_data import WeatherData


def main() -> None:
    weather_data = WeatherData()

    # Displays register themselves in their constructors; the subject's observer
    # list keeps them alive, so no variables are needed (matches Java's `new X(wd)`).
    CurrentConditionsDisplay(weather_data)
    StatisticsDisplay(weather_data)
    ForecastDisplay(weather_data)
    HeatIndexDisplay(weather_data)

    print("--- Weather update 1 ---")
    weather_data.set_measurements(80, 65, 30.4)

    print("\n--- Weather update 2 ---")
    weather_data.set_measurements(82, 70, 29.2)

    print("\n--- Weather update 3 ---")
    weather_data.set_measurements(78, 90, 29.2)


if __name__ == "__main__":
    main()
