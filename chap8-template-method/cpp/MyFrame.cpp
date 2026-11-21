// Headless stand-in for the Swing MyFrame: Frame plays JFrame, Graphics prints
// its draw calls, and main() plays the toolkit that calls paint().
#include <iostream>
#include <string>

// Simulated java.awt.Graphics: prints each draw call instead of drawing.
class Graphics {
public:
    void drawString(const std::string& text, int x, int y) {
        std::cout << "  drawString('" << text << "', " << x << ", " << y << ")\n";
    }
};

// Simulated JFrame: the framework side that calls the paint() hook.
class Frame {
public:
    explicit Frame(std::string title) : title(std::move(title)) {}
    // Virtual destructor and virtual paint() so subclasses can be used through Frame.
    virtual ~Frame() = default;

    void setSize(int w, int h) { width = w; height = h; }
    void setVisible(bool v) {
        visible = v;
        if (v) {
            std::cout << "Frame '" << title << "' shown (" << width << "x" << height << ")\n";
            Graphics g;
            paint(g);  // the toolkit calls the paint hook
        }
    }
    virtual void paint(Graphics&) { std::cout << "  super.paint: background cleared\n"; }

protected:
    std::string title;
    int width = 0, height = 0;
    bool visible = false;
};

// Concrete subclass: overrides the paint() hook, as Swing code would.
class MyFrame : public Frame {
public:
    explicit MyFrame(const std::string& title) : Frame(title) { setSize(300, 300); }
    void paint(Graphics& g) override {
        Frame::paint(g);
        g.drawString("Hello, World!", 100, 100);
    }
};

int main() {
    MyFrame frame("Hello, World!");
    frame.setVisible(true);
}
