// Scripted session for the DJ view (the Java version just opens windows).
#include <iostream>
#include <memory>

#include "BeatController.h"
#include "BeatModel.h"
#include "BeatModelInterface.h"
#include "ControllerInterface.h"

// Replaces the Swing event loop / background threads: 50 ms frames.
static void runFor(BeatModelInterface& model, DJView& view, int ms) {
    for (int i = 0; i < ms / 50; i++) {
        model.advance(50);
        view.tick();
    }
}

int main() {
    std::shared_ptr<BeatModelInterface> model = std::make_shared<BeatModel>();
    // The controller owns the view; keep it alive for the whole session.
    auto controller = std::make_unique<BeatController>(model);
    DJView& view = *controller->view;

    view.show();
    std::cout << "-- user picks DJ Control > Start" << std::endl;
    view.startMenuItem->click();
    view.startMenuItem->click();  // disabled now
    runFor(*model, view, 1000);
    view.show();

    std::cout << "-- user types 120 and presses Set" << std::endl;
    view.bpmTextField->setText("120");
    view.setBPMButton->click();
    runFor(*model, view, 1000);
    view.show();

    std::cout << "-- user presses >> twice and << once" << std::endl;
    view.increaseBPMButton->click();
    view.increaseBPMButton->click();
    view.decreaseBPMButton->click();
    view.show();

    std::cout << "-- user types garbage and presses Set" << std::endl;
    view.bpmTextField->setText("abc");
    view.setBPMButton->click();
    std::cout << "text field now: " << view.bpmTextField->getText() << std::endl;

    std::cout << "-- user picks DJ Control > Stop" << std::endl;
    view.stopMenuItem->click();
    runFor(*model, view, 1000);
    view.show();
    return 0;
}
