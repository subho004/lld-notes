// Console simulation of the Swing observer example (no GUI).
// FakeButton stands in for JButton (the subject); main() "clicks" it.
// Deviation from Java: fake frame/button, since Swing needs a display.
#include <cctype>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Empty event passed to listeners.
struct ActionEvent {};

// Observer interface (Swing's ActionListener).
class ActionListener {
public:
    virtual ~ActionListener() = default;
    virtual void actionPerformed(const ActionEvent& event) = 0;
};

// Stand-in for JButton: Subject that notifies its listeners on click().
class FakeButton {
public:
    explicit FakeButton(std::string text) : text(std::move(text)) {}

    // Object listener: button shares ownership of the listener.
    void addActionListener(std::shared_ptr<ActionListener> listener) {
        listeners.push_back([listener](const ActionEvent& e) { listener->actionPerformed(e); });
    }
    // Lambda listener: std::function plays the role of Java's functional interface.
    void addActionListener(std::function<void(const ActionEvent&)> listener) {
        listeners.push_back(std::move(listener));
    }

    // Notify all listeners in registration order.
    void click() {
        ActionEvent event;
        for (auto& l : listeners) l(event);
    }
    const std::string& getText() const { return text; }

private:
    std::string text;
    std::vector<std::function<void(const ActionEvent&)>> listeners;
};

// Stand-in for JFrame; setVisible(true) just prints one line.
class FakeFrame {
public:
    explicit FakeFrame(std::string title) : title(std::move(title)) {}
    void add(FakeButton* b) { content = b; }
    void setSize(int w, int h) { width = w; height = h; }
    void setVisible(bool v) {
        if (v) {
            std::cout << "[frame '" << title << "' " << width << "x" << height
                      << " shown with button '" << content->getText() << "']\n";
        }
    }

private:
    std::string title;
    int width = 0, height = 0;
    FakeButton* content = nullptr;  // non-owning: the button outlives the frame's use
};

// Concrete Observer.
class AngelListener : public ActionListener {
public:
    void actionPerformed(const ActionEvent&) override {
        std::cout << "Don't do it, you might regret it!\n";
    }
};

// Concrete Observer.
class DevilListener : public ActionListener {
public:
    void actionPerformed(const ActionEvent&) override {
        std::cout << "Come on, do it!\n";
    }
};

class SwingObserverExample {
public:
    void goNormal() {
        frame = std::make_unique<FakeFrame>("Swing Observer - Normal");
        FakeButton button("Should I do it?");
        button.addActionListener(std::make_shared<AngelListener>());
        button.addActionListener(std::make_shared<DevilListener>());
        showFrame(button);
    }

    // Same observers as goNormal, but as lambdas instead of listener classes.
    void goLambda() {
        frame = std::make_unique<FakeFrame>("Swing Observer - Lambda");
        FakeButton button("Should I do it?");
        button.addActionListener([](const ActionEvent&) { std::cout << "Don't do it, you might regret it!\n"; });
        button.addActionListener([](const ActionEvent&) { std::cout << "Come on, do it!\n"; });
        showFrame(button);
    }

private:
    void showFrame(FakeButton& button) {
        frame->add(&button);
        frame->setSize(300, 300);
        frame->setVisible(true);
        // Simulation only: stands in for a real user click.
        std::cout << "[user clicks the button]\n";
        button.click();
    }

    std::unique_ptr<FakeFrame> frame;  // sole owner of the frame
};

int main(int argc, char** argv) {
    std::string mode = argc > 1 ? argv[1] : "normal";
    for (auto& c : mode) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    SwingObserverExample example;
    if (mode == "lambda") {
        example.goLambda();
    } else {
        example.goNormal();
    }
    return 0;
}
