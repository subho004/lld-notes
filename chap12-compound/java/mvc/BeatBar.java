import javax.swing.JProgressBar;

/**
 * View widget: a progress bar that jumps to 100 on each beat and decays by 25% every 50 ms.
 * Runs its own thread and needs Swing (display).
 */
public class BeatBar extends JProgressBar implements Runnable {
    private static final long serialVersionUID = 2L;
    // Unused field; the bar is this object itself.
    JProgressBar progressBar;
    Thread thread;

    public BeatBar() {
        thread = new Thread(this);
        setMaximum(100);
        thread.start();
    }

    // Decay loop: the thread never ends; it is stopped only when the JVM exits.
    public void run() {
        while (true) {
            int value = getValue();
            value = (int) (value * .75);
            setValue(value);
            repaint();
            try {
                Thread.sleep(50);
            } catch (Exception e) {
            }
        }
    }
}
