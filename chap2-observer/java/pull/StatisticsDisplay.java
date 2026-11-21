package pull;

/**
 * Concrete Observer (pull model) and DisplayElement. Tracks running average/max/min temperature.
 */
public class StatisticsDisplay implements Observer, DisplayElement {
    private float maxTemp = 0.0f;
    // Initial max/min are sentinels so the first reading replaces them.
    private float minTemp = 200.0f;
    private float tempSum = 0.0f;
    private int numReadings;
    private WeatherData weatherData;

    // Registers itself with the subject on construction; the subject keeps it alive.
    public StatisticsDisplay(WeatherData weatherData) {
        this.weatherData = weatherData;
        weatherData.registerObserver(this);
    }

    // Notified without data: pulls the values it needs from the subject via getters.
    public void update() {
        float temperature = weatherData.getTemperature();
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
