"""Controller for HeartModel: shows it in the DJ view through HeartAdapter."""

from __future__ import annotations

from controller_interface import ControllerInterface
from dj_view import DJView
from heart_adapter import HeartAdapter
from heart_model_interface import HeartModelInterface


class HeartController(ControllerInterface):
    """Concrete Strategy whose controls are all no-ops: a heart cannot be commanded."""

    def __init__(self, model: HeartModelInterface) -> None:
        self.model = model
        # Adapter lets the unchanged DJView observe a HeartModel.
        self.view = DJView(self, HeartAdapter(model))
        self.view.create_view()
        self.view.create_controls()
        self.view.disable_stop_menu_item()
        self.view.disable_start_menu_item()

    def start(self) -> None:
        pass

    def stop(self) -> None:
        pass

    def increase_bpm(self) -> None:
        pass

    def decrease_bpm(self) -> None:
        pass

    def set_bpm(self, bpm: int) -> None:
        pass
