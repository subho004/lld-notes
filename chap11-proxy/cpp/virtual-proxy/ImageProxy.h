// ImageProxy: Virtual Proxy for ImageIcon. Creates the real icon lazily on
// first paint, showing a placeholder meanwhile.
#pragma once
#include <memory>
#include <string>

#include "SwingSim.h"

// Virtual Proxy. enable_shared_from_this lets paintIcon() create a weak_ptr to
// itself for the background load; must be created with make_shared.
class ImageProxy : public Icon, public std::enable_shared_from_this<ImageProxy> {
    // Real subject, owned exclusively; null until the load completes.
    std::unique_ptr<ImageIcon> imageIcon;
    std::string imageURL;
    bool retrieving = false;

public:
    explicit ImageProxy(std::string url) : imageURL(std::move(url)) {}

    // Placeholder size (the window size) until the real icon exists.
    int getIconWidth() override { return imageIcon ? imageIcon->getIconWidth() : 800; }
    int getIconHeight() override { return imageIcon ? imageIcon->getIconHeight() : 600; }

    void setImageIcon(std::unique_ptr<ImageIcon> icon) { imageIcon = std::move(icon); }

    void paintIcon(Component& c, Graphics& g, int x, int y) override {
        if (imageIcon) {
            imageIcon->paintIcon(c, g, x, y);
        } else {
            g.drawString("Loading album cover, please wait...", x + 300, y + 190);
            // Start at most one background load; repeated repaints must not restart it.
            if (!retrieving) {
                retrieving = true;
                // weak_ptr: the pending "thread" must not keep a replaced proxy alive.
                std::weak_ptr<ImageProxy> self = shared_from_this();
                // Raw pointer: the component outlives pending loads in this demo.
                Component* comp = &c;
                auto thread = std::make_shared<SimulatedThread>([self, comp]() {
                    if (auto p = self.lock()) {
                        p->setImageIcon(std::make_unique<ImageIcon>(p->imageURL, "Album Cover"));
                        comp->repaint();
                    }
                });
                thread->start();
            }
        }
    }
};
