import java.io.File;
import java.util.ArrayList;
import java.util.List;

import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.Line;

/**
 * Model: generates beats on its own thread and notifies BeatObservers and BPMObservers.
 * Needs clap.wav in the working directory for sound; runs silently without it.
 */
public class BeatModel implements BeatModelInterface, Runnable {
    List<BeatObserver> beatObservers = new ArrayList<BeatObserver>();
    List<BPMObserver> bpmObservers = new ArrayList<BPMObserver>();
    int bpm = 90;
    Thread thread;
    boolean stop = false;
    Clip clip;

    public void initialize() {
        try {
            File resource = new File("clap.wav");
            if (resource.exists()) {
                clip = (Clip) AudioSystem.getLine(new Line.Info(Clip.class));
                clip.open(AudioSystem.getAudioInputStream(resource));
            } else {
                System.out.println("clap.wav not found; running without audio");
            }
        } catch (Exception ex) {
            System.out.println("Could not load clap.wav; running without audio");
        }
    }

    // Resets to 90 BPM and starts a beat thread.
    public void on() {
        bpm = 90;
        notifyBPMObservers();
        thread = new Thread(this);
        stop = false;
        thread.start();
    }

    public void off() {
        stopBeat();
        stop = true;
    }

    // Beat loop: beat, notify, then sleep 60000/BPM ms.
    public void run() {
        while (!stop) {
            playBeat();
            notifyBeatObservers();
            try {
                Thread.sleep(60000 / getBPM());
            } catch (Exception e) {
            }
        }
    }

    // Notifies BPM observers so the view refreshes.
    public void setBPM(int bpm) {
        this.bpm = bpm;
        notifyBPMObservers();
    }

    public int getBPM() {
        return bpm;
    }

    // Overloaded: one registration per observer type.
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

    public void playBeat() {
        if (clip != null) {
            clip.setFramePosition(0);
            clip.start();
        }
    }

    public void stopBeat() {
        if (clip != null) {
            clip.setFramePosition(0);
            clip.stop();
        }
    }
}
