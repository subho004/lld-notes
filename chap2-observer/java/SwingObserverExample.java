import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;

/**
 * Observer pattern in Swing: JButton is the Subject and each ActionListener is an Observer.
 * Needs a display; throws HeadlessException when run headless.
 * Pass "lambda" as the first argument to use lambdas instead of listener classes.
 */
public class SwingObserverExample {
    JFrame frame;

    public static void main(String[] args) {
        String mode = args.length > 0 ? args[0] : "normal";
        SwingObserverExample example = new SwingObserverExample();

        if ("lambda".equalsIgnoreCase(mode)) {
            example.goLambda();
        } else {
            example.goNormal();
        }
    }

    public void goNormal() {
        frame = new JFrame("Swing Observer - Normal");
        JButton button = new JButton("Should I do it?");

        // Listeners are notified in registration order (angel, then devil).
        button.addActionListener(new AngelListener());
        button.addActionListener(new DevilListener());

        showFrame(button);
    }

    // ActionListener is a functional interface, so lambdas replace the inner classes.
    public void goLambda() {
        frame = new JFrame("Swing Observer - Lambda");
        JButton button = new JButton("Should I do it?");

        button.addActionListener(event -> System.out.println("Don't do it, you might regret it!"));
        button.addActionListener(event -> System.out.println("Come on, do it!"));

        showFrame(button);
    }

    private void showFrame(JButton button) {
        frame.getContentPane().add(BorderLayout.CENTER, button);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 300);
        frame.setVisible(true);
    }

    /**
     * Concrete Observer: reacts to button clicks.
     */
    class AngelListener implements ActionListener {
        public void actionPerformed(ActionEvent event) {
            System.out.println("Don't do it, you might regret it!");
        }
    }

    /**
     * Concrete Observer: reacts to button clicks.
     */
    class DevilListener implements ActionListener {
        public void actionPerformed(ActionEvent event) {
            System.out.println("Come on, do it!");
        }
    }
}
