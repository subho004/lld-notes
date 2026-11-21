import java.awt.Graphics;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;

/**
 * Hook example: Swing calls paint() when it needs to draw ("don't call us").
 * Requires a display; not headless-runnable.
 */
public class MyFrame extends JFrame {
    public MyFrame(String title) {
        super(title);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(300, 300);
    }

    /** Hook invoked by the toolkit; adds custom drawing after the default painting. */
    @Override
    public void paint(Graphics g) {
        super.paint(g);
        g.drawString("Hello, World!", 100, 100);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            MyFrame frame = new MyFrame("Hello, World!");
            frame.setVisible(true);
        });
    }
}
