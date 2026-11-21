package pull;

/**
 * Concrete Observer (pull model) and DisplayElement. Predicts weather by comparing the new pressure with the previous one.
 */
public class ForecastDisplay implements Observer, DisplayElement {
    private float currentPressure = 29.92f;
    private float lastPressure;
    private WeatherData weatherData;

    // Registers itself with the subject on construction; the subject keeps it alive.
    public ForecastDisplay(WeatherData weatherData) {
        this.weatherData = weatherData;
        weatherData.registerObserver(this);
    }

    // Notified without data: pulls the values it needs from the subject via getters.
    public void update() {
        // Shift the previous reading before storing the new one.
        lastPressure = currentPressure;
        currentPressure = weatherData.getPressure();
        display();
    }

    public void display() {
        System.out.print("Forecast: ");
        if (currentPressure > lastPressure) {
            System.out.println("Improving weather on the way!");
        } else if (currentPressure == lastPressure) {
            System.out.println("More of the same");
        } else {
            System.out.println("Watch out for cooler, rainy weather");
        }
    }
}
