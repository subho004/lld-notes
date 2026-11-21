package pull;

import java.util.ArrayList;
import java.util.List;

/**
 * Concrete Subject. Holds the observer list and the measurements, and notifies observers when they change.
 */
public class WeatherData implements Subject {
    private List<Observer> observers;
    private float temperature;
    private float humidity;
    private float pressure;

    public WeatherData() {
        observers = new ArrayList<Observer>();
    }

    public void registerObserver(Observer o) {
        observers.add(o);
    }

    public void removeObserver(Observer o) {
        observers.remove(o);
    }

    // Notifies in registration order; an observer unregistering mid-loop would throw ConcurrentModificationException.
    public void notifyObservers() {
        for (Observer observer : observers) {
            observer.update();
        }
    }

    // Hook called whenever new measurements arrive.
    public void measurementsChanged() {
        notifyObservers();
    }

    public void setMeasurements(float temperature, float humidity, float pressure) {
        this.temperature = temperature;
        this.humidity = humidity;
        this.pressure = pressure;
        measurementsChanged();
    }

    public float getTemperature() {
        return temperature;
    }

    public float getHumidity() {
        return humidity;
    }

    public float getPressure() {
        return pressure;
    }
}
