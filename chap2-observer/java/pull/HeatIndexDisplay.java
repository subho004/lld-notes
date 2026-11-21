package pull;

/**
 * Concrete Observer (pull model) and DisplayElement. Shows a heat index derived from temperature and humidity.
 */
public class HeatIndexDisplay implements Observer, DisplayElement {
    private float heatIndex = 0.0f;
    private WeatherData weatherData;

    // Registers itself with the subject on construction; the subject keeps it alive.
    public HeatIndexDisplay(WeatherData weatherData) {
        this.weatherData = weatherData;
        weatherData.registerObserver(this);
    }

    // Notified without data: pulls the values it needs from the subject via getters.
    public void update() {
        float temperature = weatherData.getTemperature();
        float humidity = weatherData.getHumidity();
        heatIndex = computeHeatIndex(temperature, humidity);
        display();
    }

    // Approximate heat-index formula; result narrowed back to float.
    private float computeHeatIndex(float t, float rh) {
        return (float) (0.5 * (t + 61.0 + ((t - 68.0) * 1.2) + (rh * 0.094)));
    }

    public void display() {
        System.out.println("Heat index is " + heatIndex);
    }
}
