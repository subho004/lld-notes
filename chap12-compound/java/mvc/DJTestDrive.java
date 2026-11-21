/**
 * Entry point: wires BeatModel to BeatController (opens Swing windows, needs a display).
 */
public class DJTestDrive {
    public static void main(String[] args) {
        BeatModelInterface model = new BeatModel();
        ControllerInterface controller = new BeatController(model);
    }
}
