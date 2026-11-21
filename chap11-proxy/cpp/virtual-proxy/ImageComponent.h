// ImageComponent: client of the virtual proxy. Paints any Icon without
// knowing whether it is an ImageProxy or a real ImageIcon.
#pragma once
#include <memory>

#include "SwingSim.h"

class ImageComponent : public Component {
    // shared_ptr<Icon>: the component and the caller may share the proxy.
    std::shared_ptr<Icon> icon;

public:
    explicit ImageComponent(std::shared_ptr<Icon> i) : icon(std::move(i)) {}

    void setIcon(std::shared_ptr<Icon> i) { icon = std::move(i); }

    void repaint() override {
        Component::repaint();
        Graphics g;
        paintComponent(g);  // the toolkit would paint asynchronously
    }

    void paintComponent(Graphics& g) {
        int w = icon->getIconWidth();
        int h = icon->getIconHeight();
        int x = (800 - w) / 2;
        int y = (600 - h) / 2;
        icon->paintIcon(*this, g, x, y);
    }
};
