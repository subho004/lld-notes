/**
 * Client/driver: wires displays to the subject and feeds it measurements.
 */
public class WeatherStation {
    public static void main(String[] args) {
        WeatherData weatherData = new WeatherData();

        CurrentConditionsDisplay currentDisplay = new CurrentConditionsDisplay(weatherData);
        StatisticsDisplay statisticsDisplay = new StatisticsDisplay(weatherData);
        ForecastDisplay forecastDisplay = new ForecastDisplay(weatherData);
        HeatIndexDisplay heatIndexDisplay = new HeatIndexDisplay(weatherData);

        System.out.println("--- Weather update 1 ---");
        weatherData.setMeasurements(80, 65, 30.4f);

        System.out.println("\n--- Weather update 2 ---");
        weatherData.setMeasurements(82, 70, 29.2f);

        System.out.println("\n--- Weather update 3 ---");
        weatherData.setMeasurements(78, 90, 29.2f);

        System.out.println("\n--- Removing current conditions display ---");
        // After removal, the current-conditions display stops receiving updates.
        weatherData.removeObserver(currentDisplay);

        System.out.println("\n--- Weather update 4 ---");
        weatherData.setMeasurements(75, 60, 29.5f);
    }
}
