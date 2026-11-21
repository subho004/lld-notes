package pull;

/**
 * Client/driver: wires displays to the subject and feeds it measurements.
 */
public class WeatherStation {
    public static void main(String[] args) {
        WeatherData weatherData = new WeatherData();

        // Displays are not stored: the subject's observer list keeps them alive.
        new CurrentConditionsDisplay(weatherData);
        new StatisticsDisplay(weatherData);
        new ForecastDisplay(weatherData);
        new HeatIndexDisplay(weatherData);

        System.out.println("--- Weather update 1 ---");
        weatherData.setMeasurements(80, 65, 30.4f);

        System.out.println("\n--- Weather update 2 ---");
        weatherData.setMeasurements(82, 70, 29.2f);

        System.out.println("\n--- Weather update 3 ---");
        weatherData.setMeasurements(78, 90, 29.2f);
    }
}
