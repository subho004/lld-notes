"""Console test drive for BeatModel: observers are plain callables, time is simulated."""

from __future__ import annotations

from beat_model import BeatModel
from beat_model_interface import BeatModelInterface
from observers import FunctionBeatObserver, FunctionBPMObserver


def main() -> None:
    model: BeatModelInterface = BeatModel()
    model.initialize()

    model.register_beat_observer(FunctionBeatObserver(lambda: print("BEAT")))
    model.register_bpm_observer(
        FunctionBPMObserver(lambda: print("BPM: " + str(model.get_bpm())))
    )

    print("Starting BeatModel at 90 BPM...")
    model.on()
    model.advance(4000)  # Thread.sleep(4000)

    print("Setting BPM to 120...")
    model.set_bpm(120)
    model.advance(3000)  # Thread.sleep(3000)

    print("Stopping BeatModel...")
    model.off()


if __name__ == "__main__":
    main()
