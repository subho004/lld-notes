"""Controller (Strategy for the view) that drives a BeatModel."""

from __future__ import annotations

from beat_model_interface import BeatModelInterface
from controller_interface import ControllerInterface
from dj_view import DJView


class BeatController(ControllerInterface):
    """Concrete Strategy: turns user actions from the view into BeatModel calls
    and keeps the Start/Stop menu items in sync."""

    def __init__(self, model: BeatModelInterface) -> None:
        self.model = model
        # The view registers itself with the model as an observer in its constructor.
        self.view = DJView(self, model)
        self.view.create_view()
        self.view.create_controls()
        self.view.disable_stop_menu_item()
        self.view.enable_start_menu_item()
        model.initialize()

    def start(self) -> None:
        self.model.on()
        self.view.disable_start_menu_item()
        self.view.enable_stop_menu_item()

    def stop(self) -> None:
        self.model.off()
        self.view.disable_stop_menu_item()
        self.view.enable_start_menu_item()

    def increase_bpm(self) -> None:
        bpm = self.model.get_bpm()
        self.model.set_bpm(bpm + 1)

    def decrease_bpm(self) -> None:
        bpm = self.model.get_bpm()
        self.model.set_bpm(bpm - 1)

    def set_bpm(self, bpm: int) -> None:
        self.model.set_bpm(bpm)
