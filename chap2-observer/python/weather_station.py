"""Client / test drive: wires the displays to WeatherData and feeds it readings."""
from displays import (CurrentConditionsDisplay, ForecastDisplay,
                      HeatIndexDisplay, StatisticsDisplay)
from weather_data import WeatherData


def main() -> None:
    weather_data = WeatherData()

    # Each display registers itself with the subject in its constructor.
    current_display = CurrentConditionsDisplay(weather_data)
    statistics_display = StatisticsDisplay(weather_data)
    forecast_display = ForecastDisplay(weather_data)
    heat_index_display = HeatIndexDisplay(weather_data)

    print("--- Weather update 1 ---")
    weather_data.set_measurements(80, 65, 30.4)

    print("\n--- Weather update 2 ---")
    weather_data.set_measurements(82, 70, 29.2)

    print("\n--- Weather update 3 ---")
    weather_data.set_measurements(78, 90, 29.2)

    print("\n--- Removing current conditions display ---")
    weather_data.remove_observer(current_display)

    print("\n--- Weather update 4 ---")
    weather_data.set_measurements(75, 60, 29.5)


if __name__ == "__main__":
    main()
