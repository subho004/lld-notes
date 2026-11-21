"""Scripted session for the DJ view (the Java version just opens windows)."""

from __future__ import annotations

from beat_controller import BeatController
from beat_model import BeatModel
from beat_model_interface import BeatModelInterface
from controller_interface import ControllerInterface
from dj_view import DJView


def run_for(model: BeatModelInterface, view: DJView, ms: int) -> None:
    """Replaces the Swing event loop / background threads: 50 ms frames."""
    for _ in range(ms // 50):
        model.advance(50)
        view.tick()


def main() -> None:
    model: BeatModelInterface = BeatModel()
    controller: ControllerInterface = BeatController(model)
    # Narrow the type so the view can be reached; the interface does not expose it.
    assert isinstance(controller, BeatController)
    view = controller.view

    view.show()
    print("-- user picks DJ Control > Start")
    view.start_menu_item.click()
    view.start_menu_item.click()  # disabled now
    run_for(model, view, 1000)
    view.show()

    print("-- user types 120 and presses Set")
    view.bpm_text_field.set_text("120")
    view.set_bpm_button.click()
    run_for(model, view, 1000)
    view.show()

    print("-- user presses >> twice and << once")
    view.increase_bpm_button.click()
    view.increase_bpm_button.click()
    view.decrease_bpm_button.click()
    view.show()

    print("-- user types garbage and presses Set")
    view.bpm_text_field.set_text("abc")
    view.set_bpm_button.click()
    print(f"text field now: {view.bpm_text_field.get_text()}")

    print("-- user picks DJ Control > Stop")
    view.stop_menu_item.click()
    run_for(model, view, 1000)
    view.show()


if __name__ == "__main__":
    main()
