// Controller for HeartModel: shows it in the DJ view through HeartAdapter.
#pragma once
#include <memory>

#include "ControllerInterface.h"
#include "DJView.h"
#include "HeartAdapter.h"
#include "HeartModelInterface.h"

// Concrete Strategy whose controls are all no-ops: a heart cannot be commanded.
class HeartController : public ControllerInterface {
    std::shared_ptr<HeartModelInterface> model;

public:
    std::shared_ptr<DJView> view;

    explicit HeartController(std::shared_ptr<HeartModelInterface> m) : model(std::move(m)) {
        // Adapter lets the unchanged DJView observe a HeartModel.
        view = DJView::create(this, std::make_shared<HeartAdapter>(model));
        view->createView();
        view->createControls();
        view->disableStopMenuItem();
        view->disableStartMenuItem();
    }

    void start() override {}
    void stop() override {}
    void increaseBPM() override {}
    void decreaseBPM() override {}
    void setBPM(int) override {}
};
