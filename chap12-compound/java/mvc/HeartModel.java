import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * Model: simulates a drifting heart rate on its own thread and notifies observers.
 * Starts its thread in the constructor; uses time-seeded Random, so output differs per run.
 */
public class HeartModel implements HeartModelInterface, Runnable {
    List<BeatObserver> beatObservers = new ArrayList<BeatObserver>();
    List<BPMObserver> bpmObservers = new ArrayList<BPMObserver>();
    int time = 1000;
    int bpm = 90;
    Random random = new Random(System.currentTimeMillis());
    Thread thread;

    public HeartModel() {
        thread = new Thread(this);
        thread.start();
    }

    // Each cycle nudges the beat interval randomly; changes outside 50-120 BPM are ignored.
    public void run() {
        int lastrate = -1;

        while (true) {
            int change = random.nextInt(10);
            if (random.nextInt(2) == 0) {
                change = 0 - change;
            }
            int rate = 60000 / (time + change);
            if (rate < 120 && rate > 50) {
                time += change;
                notifyBeatObservers();
                if (rate != lastrate) {
                    lastrate = rate;
                    notifyBPMObservers();
                }
            }
            try {
                Thread.sleep(time);
            } catch (Exception e) {
            }
        }
    }

    public int getHeartRate() {
        return 60000 / time;
    }

    public void registerObserver(BeatObserver o) {
        beatObservers.add(o);
    }

    public void removeObserver(BeatObserver o) {
        beatObservers.remove(o);
    }

    public void notifyBeatObservers() {
        for (int i = 0; i < beatObservers.size(); i++) {
            BeatObserver observer = beatObservers.get(i);
            observer.updateBeat();
        }
    }

    public void registerObserver(BPMObserver o) {
        bpmObservers.add(o);
    }

    public void removeObserver(BPMObserver o) {
        bpmObservers.remove(o);
    }

    public void notifyBPMObservers() {
        for (int i = 0; i < bpmObservers.size(); i++) {
            BPMObserver observer = bpmObservers.get(i);
            observer.updateBPM();
        }
    }
}
