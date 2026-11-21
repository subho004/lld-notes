// View: DJView, observer of the model and client of the controller strategy.
#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "BeatBar.h"
#include "BeatModelInterface.h"
#include "ControllerInterface.h"
#include "Observers.h"
#include "SwingSim.h"

// Console view.  Same structure as the Java class (createView, createControls,
// actionPerformed, observer callbacks) with headless fake widgets.
//
// Create with DJView::create(): registering `this` with the model needs a
// shared_ptr to self, which is not available inside a constructor.  The
// controller owns the view; the view only borrows the controller.
// Observer of both beats and BPM changes; enable_shared_from_this is part of
// the creation scheme explained above.
class DJView : public BeatObserver, public BPMObserver, public std::enable_shared_from_this<DJView> {
    std::shared_ptr<BeatModelInterface> model;
    ControllerInterface* controller;  // non-owning: the controller owns the view

    // Private so that instances only come from create() and always live in a shared_ptr.
    DJView(ControllerInterface* controller, std::shared_ptr<BeatModelInterface> model)
        : model(std::move(model)), controller(controller) {}

public:
    // Widgets are exclusively owned by the view; unique_ptr since they are created later
    // in createView()/createControls().
    std::unique_ptr<BeatBar> beatBar;
    std::unique_ptr<Label> bpmOutputLabel;
    std::unique_ptr<Label> bpmLabel;
    std::unique_ptr<TextField> bpmTextField;
    std::unique_ptr<Button> setBPMButton;
    std::unique_ptr<Button> increaseBPMButton;
    std::unique_ptr<Button> decreaseBPMButton;
    std::unique_ptr<MenuItem> startMenuItem;
    std::unique_ptr<MenuItem> stopMenuItem;

    static std::shared_ptr<DJView> create(ControllerInterface* controller,
                                          std::shared_ptr<BeatModelInterface> model) {
        std::shared_ptr<DJView> view(new DJView(controller, std::move(model)));
        // DJView is both observer types, so the overload needs an explicit upcast.
        view->model->registerObserver(std::static_pointer_cast<BeatObserver>(view));
        view->model->registerObserver(std::static_pointer_cast<BPMObserver>(view));
        return view;
    }

    void createView() {
        bpmOutputLabel = std::make_unique<Label>("offline");
        beatBar = std::make_unique<BeatBar>();
        beatBar->setValue(0);
        std::cout << "[GUI] window 'View' opened (beat bar + BPM label)" << std::endl;
    }

    void createControls() {
        startMenuItem = std::make_unique<MenuItem>("Start");
        // Menu items delegate straight to the controller (Strategy).
        startMenuItem->addActionListener([this](const ActionEvent&) { controller->start(); });
        stopMenuItem = std::make_unique<MenuItem>("Stop");
        stopMenuItem->addActionListener([this](const ActionEvent&) { controller->stop(); });

        bpmTextField = std::make_unique<TextField>();
        bpmLabel = std::make_unique<Label>("Enter BPM:");
        setBPMButton = std::make_unique<Button>("Set");
        increaseBPMButton = std::make_unique<Button>(">>");
        decreaseBPMButton = std::make_unique<Button>("<<");
        auto listener = [this](const ActionEvent& e) { actionPerformed(e); };
        setBPMButton->addActionListener(listener);
        increaseBPMButton->addActionListener(listener);
        decreaseBPMButton->addActionListener(listener);
        std::cout << "[GUI] window 'Control' opened (menu Start/Stop, text field, Set, >>, <<)" << std::endl;
    }

    void enableStopMenuItem() { stopMenuItem->setEnabled(true); }
    void disableStopMenuItem() { stopMenuItem->setEnabled(false); }
    void enableStartMenuItem() { startMenuItem->setEnabled(true); }
    void disableStartMenuItem() { startMenuItem->setEnabled(false); }

    // Dispatch on the event source; the view never changes the model itself.
    void actionPerformed(const ActionEvent& event) {
        if (event.getSource() == setBPMButton.get()) {
            try {
                const std::string& s = bpmTextField->getText();
                std::size_t used = 0;
                int bpm = std::stoi(s, &used);
                if (used != s.size()) throw std::invalid_argument("trailing characters");
                controller->setBPM(bpm);
            } catch (const std::logic_error&) {  // NumberFormatException
                bpmTextField->setText(std::to_string(model->getBPM()));
            }
        } else if (event.getSource() == increaseBPMButton.get()) {
            controller->increaseBPM();
        } else if (event.getSource() == decreaseBPMButton.get()) {
            controller->decreaseBPM();
        }
    }

    // BPMObserver callback: re-read the model and refresh the label.
    void updateBPM() override {
        if (model) {
            int bpm = model->getBPM();
            if (bpmOutputLabel) {
                if (bpm == 0) {
                    bpmOutputLabel->setText("offline");
                } else {
                    bpmOutputLabel->setText("Current BPM: " + std::to_string(bpm));
                }
            }
        }
    }

    // BeatObserver callback: flash the bar to full; tick() decays it.
    void updateBeat() override {
        if (beatBar) beatBar->setValue(100);
    }

    // --- console additions ---------------------------------------------------
    void tick() {  // one 50 ms animation frame of the beat bar
        if (beatBar) beatBar->step();
    }

    void show() const {
        std::cout << "[View] " << beatBar->render() << " " << bpmOutputLabel->getText() << std::endl;
    }
};
