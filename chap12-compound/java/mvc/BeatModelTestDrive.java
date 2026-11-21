/**
 * Headless demo: drives BeatModel directly with lambda observers (about 7 seconds of timing-based output).
 */
public class BeatModelTestDrive {
    public static void main(String[] args) throws Exception {
        BeatModelInterface model = new BeatModel();
        model.initialize();

        model.registerObserver((BeatObserver) () -> System.out.println("BEAT"));
        model.registerObserver((BPMObserver) () -> System.out.println("BPM: " + model.getBPM()));

        System.out.println("Starting BeatModel at 90 BPM...");
        model.on();
        Thread.sleep(4000);

        System.out.println("Setting BPM to 120...");
        model.setBPM(120);
        Thread.sleep(3000);

        System.out.println("Stopping BeatModel...");
        model.off();
    }
}
