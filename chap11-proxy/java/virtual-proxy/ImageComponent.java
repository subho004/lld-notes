import java.awt.Graphics;

import javax.swing.Icon;
import javax.swing.JComponent;

/** Client: a Swing component that paints an Icon without knowing whether it is the proxy or the real image. */
class ImageComponent extends JComponent {
    private static final long serialVersionUID = 1L;
    private Icon icon;

    public ImageComponent(Icon icon) {
        this.icon = icon;
    }

    // Swapped for a fresh ImageProxy when the user picks another album.
    public void setIcon(Icon icon) {
        this.icon = icon;
    }

    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        int w = icon.getIconWidth();
        int h = icon.getIconHeight();
        // Center the icon in the fixed 800x600 frame; the proxy reports 800x600 until the real image loads.
        int x = (800 - w) / 2;
        int y = (600 - h) / 2;
        icon.paintIcon(this, g, x, y);
    }
}
