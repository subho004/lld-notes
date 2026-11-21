// Concrete Strategy: BeatController, the controller for a BeatModel.
#pragma once
#include <memory>

#include "BeatModelInterface.h"
#include "ControllerInterface.h"
#include "DJView.h"

// Translates view actions into model calls and keeps Start/Stop items in sync.
class BeatController : public ControllerInterface {
    std::shared_ptr<BeatModelInterface> model;  // shared with the view

public:
    std::shared_ptr<DJView> view;  // owned here; the view only borrows `this`

    explicit BeatController(std::shared_ptr<BeatModelInterface> m) : model(std::move(m)) {
        // `this` is passed raw: the view must not own its owner.
        view = DJView::create(this, model);
        view->createView();
        view->createControls();
        view->disableStopMenuItem();
        view->enableStartMenuItem();
        model->initialize();
    }

    void start() override {
        model->on();
        view->disableStartMenuItem();
        view->enableStopMenuItem();
    }

    void stop() override {
        model->off();
        view->disableStopMenuItem();
        view->enableStartMenuItem();
    }

    void increaseBPM() override {
        int bpm = model->getBPM();
        model->setBPM(bpm + 1);
    }

    void decreaseBPM() override {
        int bpm = model->getBPM();
        model->setBPM(bpm - 1);
    }

    void setBPM(int bpm) override { model->setBPM(bpm); }
};
