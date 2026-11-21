/**
 * Concrete Observer (push model) and DisplayElement. Tracks running average/max/min temperature.
 */
public class StatisticsDisplay implements Observer, DisplayElement {
    // Initial max/min are sentinels (0 and 200) so the first reading replaces them.
    private float maxTemp = 0.0f;
    private float minTemp = 200.0f;
    private float tempSum = 0.0f;
    private int numReadings;
    private WeatherData weatherData;

    // Registers itself with the subject on construction; the subject keeps it alive.
    public StatisticsDisplay(WeatherData weatherData) {
        this.weatherData = weatherData;
        weatherData.registerObserver(this);
    }

    // Called by WeatherData.notifyObservers() with pushed values.
    public void update(float temperature, float humidity, float pressure) {
        tempSum += temperature;
        numReadings++;

        if (temperature > maxTemp) {
            maxTemp = temperature;
        }
        if (temperature < minTemp) {
            minTemp = temperature;
        }

        display();
    }

    public void display() {
        System.out.println("Avg/Max/Min temperature = "
                + (tempSum / numReadings) + "/" + maxTemp + "/" + minTemp);
    }
}
