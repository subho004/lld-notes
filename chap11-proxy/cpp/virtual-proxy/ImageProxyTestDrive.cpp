// Virtual-proxy demo. Replaces the Swing menu with explicit menuItemClicked()
// calls and drives the fake clock via Scheduler::tick().
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "ImageComponent.h"
#include "ImageProxy.h"
#include "SwingSim.h"

// Client wiring: the ImageComponent shows an ImageProxy for the chosen album.
class ImageProxyTestDrive {
    // Insertion order instead of Java's Hashtable order.
    std::vector<std::pair<std::string, std::string>> albums;

public:
    std::string frameTitle = "Album Cover Viewer";
    std::unique_ptr<ImageComponent> imageComponent;

    ImageProxyTestDrive() {
        albums = {
            {"Buddha Bar", "http://images.amazon.com/images/P/B00009XBYK.01.LZZZZZZZ.jpg"},
            {"Ima", "http://images.amazon.com/images/P/B000005IRM.01.LZZZZZZZ.jpg"},
            {"Karma", "http://images.amazon.com/images/P/B000005DCB.01.LZZZZZZZ.gif"},
            {"MCMXC a.D.", "http://images.amazon.com/images/P/B000002URV.01.LZZZZZZZ.jpg"},
            {"Northern Exposure", "http://images.amazon.com/images/P/B000003SFN.01.LZZZZZZZ.jpg"},
            {"Selected Ambient Works, Vol. 2", "http://images.amazon.com/images/P/B000002MNZ.01.LZZZZZZZ.jpg"},
        };
        imageComponent = std::make_unique<ImageComponent>(
            std::make_shared<ImageProxy>(getAlbumUrl("Selected Ambient Works, Vol. 2")));
        std::cout << "Frame '" << frameTitle << "' visible, menu: Favorite Albums [";
        for (std::size_t i = 0; i < albums.size(); i++) {
            std::cout << (i ? ", " : "") << "'" << albums[i].first << "'";
        }
        std::cout << "]\n";
    }

    void frameRepaint() {
        Graphics g;
        imageComponent->paintComponent(g);
    }

    // What each JMenuItem's ActionListener does.
    void menuItemClicked(const std::string& name) {
        std::cout << "Menu item '" << name << "' clicked\n";
        imageComponent->setIcon(std::make_shared<ImageProxy>(getAlbumUrl(name)));
        frameRepaint();
    }

    std::string getAlbumUrl(const std::string& name) const {
        for (const auto& a : albums)
            if (a.first == name) return a.second;
        return "";
    }
};

static void ticks(int n) {
    for (int t = 1; t <= n; t++) {
        std::cout << "Tick " << t << ": background loading advances\n";
        Scheduler::instance().tick();
    }
}

int main() {
    ImageProxyTestDrive drive;
    std::cout << "Initial paint:\n";
    drive.frameRepaint();
    ticks(2);

    drive.menuItemClicked("Karma");
    std::cout << "Window repaints while still loading:\n";
    drive.frameRepaint();
    ticks(2);
    drive.menuItemClicked("Ima");
    Scheduler::instance().tick();
    Scheduler::instance().tick();
    std::cout << "Done\n";
    return 0;
}
