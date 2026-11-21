// Scripted session showing a HeartModel driving the DJ view via HeartController.
#include <iostream>
#include <memory>

#include "HeartController.h"
#include "HeartModel.h"

int main() {
    auto heartModel = std::make_shared<HeartModel>();
    auto controller = std::make_unique<HeartController>(heartModel);
    DJView& view = *controller->view;

    view.show();
    for (int second = 1; second <= 20; second++) {
        for (int i = 0; i < 20; i++) {  // 20 frames of 50 ms
            heartModel->advance(50);
            view.tick();
        }
        if (second % 5 == 0) {
            std::cout << "-- t = " << second << "s, heart rate " << heartModel->getHeartRate() << std::endl;
            view.show();
        }
    }

    std::cout << "-- the heart view ignores the controls" << std::endl;
    view.startMenuItem->click();
    view.increaseBPMButton->click();
    return 0;
}
