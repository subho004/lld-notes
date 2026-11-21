/**
 * Controller for the heart model: the view is built on a HeartAdapter and all controls are no-ops (read-only).
 */
public class HeartController implements ControllerInterface {
    HeartModelInterface model;
    DJView view;

    public HeartController(HeartModelInterface model) {
        this.model = model;
        view = new DJView(this, new HeartAdapter(model));
        view.createView();
        view.createControls();
        view.disableStopMenuItem();
        view.disableStartMenuItem();
    }

    // No-ops: heart rate cannot be controlled.
    public void start() {
    }

    public void stop() {
    }

    public void increaseBPM() {
    }

    public void decreaseBPM() {
    }

    public void setBPM(int bpm) {
    }
}
