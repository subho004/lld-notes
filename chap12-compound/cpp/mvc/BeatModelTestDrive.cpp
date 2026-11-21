// Console test drive for BeatModel: observers are function wrappers, time is simulated.
#include <iostream>
#include <memory>

#include "BeatModel.h"
#include "BeatModelInterface.h"
#include "Observers.h"

int main() {
    std::shared_ptr<BeatModelInterface> model = std::make_shared<BeatModel>();
    model->initialize();

    // Observers must outlive the model's weak references, so keep them in locals.
    auto beat = std::make_shared<FunctionBeatObserver>([] { std::cout << "BEAT" << std::endl; });
    auto bpm = std::make_shared<FunctionBPMObserver>(
        [&model] { std::cout << "BPM: " << model->getBPM() << std::endl; });
    model->registerObserver(beat);
    model->registerObserver(bpm);

    std::cout << "Starting BeatModel at 90 BPM..." << std::endl;
    model->on();
    model->advance(4000);  // Thread.sleep(4000)

    std::cout << "Setting BPM to 120..." << std::endl;
    model->setBPM(120);
    model->advance(3000);  // Thread.sleep(3000)

    std::cout << "Stopping BeatModel..." << std::endl;
    model->off();
    return 0;
}
