/**
 * Adapter: presents a HeartModel as a BeatModelInterface so DJView can display heart rate.
 */
public class HeartAdapter implements BeatModelInterface {
    HeartModelInterface heart;

    public HeartAdapter(HeartModelInterface heart) {
        this.heart = heart;
    }

    // No-op: a heart cannot be started, stopped or set, so these operations do nothing.
    public void initialize() {
    }

    public void on() {
    }

    public void off() {
    }

    // Translation: BPM is the heart rate.
    public int getBPM() {
        return heart.getHeartRate();
    }

    public void setBPM(int bpm) {
    }

    // Observer calls pass straight through to the heart model.
    public void registerObserver(BeatObserver o) {
        heart.registerObserver(o);
    }

    public void removeObserver(BeatObserver o) {
        heart.removeObserver(o);
    }

    public void registerObserver(BPMObserver o) {
        heart.registerObserver(o);
    }

    public void removeObserver(BPMObserver o) {
        heart.removeObserver(o);
    }
}
