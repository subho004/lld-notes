/**
 * Entry point: wires HeartModel to HeartController (opens Swing windows, needs a display).
 */
public class HeartTestDrive {
    public static void main(String[] args) {
        HeartModel heartModel = new HeartModel();
        ControllerInterface controller = new HeartController(heartModel);
    }
}
