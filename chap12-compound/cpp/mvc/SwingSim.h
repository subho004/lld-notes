#pragma once
// Tiny headless stand-ins for the Swing widgets used by DJView.  Nothing is
// drawn; click() plays the role of the user pressing a button / menu item.
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

// Simulated ActionEvent: carries the widget that was clicked (as an opaque pointer).
struct ActionEvent {
    const void* source;
    const void* getSource() const { return source; }
};

using ActionListener = std::function<void(const ActionEvent&)>;

// Simulated JLabel: just holds text.
class Label {
protected:
    std::string text;

public:
    explicit Label(std::string t = "") : text(std::move(t)) {}
    void setText(const std::string& t) { text = t; }
    const std::string& getText() const { return text; }
};

// Simulated JTextField: inherits Label's constructors.
class TextField : public Label {
public:
    using Label::Label;
};

// Simulated JButton: enabled flag plus listeners, driven by click().
class Button {
protected:
    std::string text;
    bool enabled = true;
    std::vector<ActionListener> listeners;

public:
    explicit Button(std::string t) : text(std::move(t)) {}
    void addActionListener(ActionListener l) { listeners.push_back(std::move(l)); }
    void setEnabled(bool e) { enabled = e; }
    bool isEnabled() const { return enabled; }
    void click() {
        if (!enabled) {
            std::cout << "[GUI] '" << text << "' is disabled, click ignored" << std::endl;
            return;
        }
        std::cout << "[GUI] click '" << text << "'" << std::endl;
        for (auto& l : listeners) l(ActionEvent{this});
    }
};

// Simulated JMenuItem: behaves exactly like a Button.
class MenuItem : public Button {
public:
    using Button::Button;
};
