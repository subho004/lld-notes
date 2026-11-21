"""View: DJView, observer of the model and client of the controller strategy."""

from __future__ import annotations

from beat_bar import BeatBar
from beat_model_interface import BeatModelInterface
from controller_interface import ControllerInterface
from observers import BeatObserver, BPMObserver
from swing_sim import ActionEvent, Button, Label, MenuItem, TextField


class DJView(BeatObserver, BPMObserver):
    """Console view.  Keeps the Java structure (createView, createControls,
    actionPerformed, observer callbacks) but the widgets are headless fakes
    and show() prints the state instead of painting a window."""

    def __init__(self, controller: ControllerInterface, model: BeatModelInterface) -> None:
        self.controller = controller
        self.model = model
        # Observer: the view subscribes to both kinds of model events. Java uses
        # overloads here; Python needs two distinct method names.
        model.register_beat_observer(self)
        model.register_bpm_observer(self)
        self.beat_bar: BeatBar | None = None
        self.bpm_output_label: Label | None = None

    def create_view(self) -> None:
        self.bpm_output_label = Label("offline")
        self.beat_bar = BeatBar()
        self.beat_bar.set_value(0)
        print("[GUI] window 'View' opened (beat bar + BPM label)")

    def create_controls(self) -> None:
        # Menu items delegate straight to the controller (Strategy).
        self.start_menu_item = MenuItem("Start")
        self.start_menu_item.add_action_listener(lambda e: self.controller.start())
        self.stop_menu_item = MenuItem("Stop")
        self.stop_menu_item.add_action_listener(lambda e: self.controller.stop())

        self.bpm_text_field = TextField()
        self.bpm_label = Label("Enter BPM:")
        self.set_bpm_button = Button("Set")
        self.increase_bpm_button = Button(">>")
        self.decrease_bpm_button = Button("<<")
        self.set_bpm_button.add_action_listener(self.action_performed)
        self.increase_bpm_button.add_action_listener(self.action_performed)
        self.decrease_bpm_button.add_action_listener(self.action_performed)
        print("[GUI] window 'Control' opened (menu Start/Stop, text field, Set, >>, <<)")

    def enable_stop_menu_item(self) -> None:
        self.stop_menu_item.set_enabled(True)

    def disable_stop_menu_item(self) -> None:
        self.stop_menu_item.set_enabled(False)

    def enable_start_menu_item(self) -> None:
        self.start_menu_item.set_enabled(True)

    def disable_start_menu_item(self) -> None:
        self.start_menu_item.set_enabled(False)

    def action_performed(self, event: ActionEvent) -> None:
        # Dispatch on the event source; the view never changes the model itself.
        if event.get_source() is self.set_bpm_button:
            try:
                bpm = int(self.bpm_text_field.get_text())
                self.controller.set_bpm(bpm)
            except ValueError:
                # Bad input: restore the field from the model (Java NumberFormatException path).
                self.bpm_text_field.set_text(str(self.model.get_bpm()))
        elif event.get_source() is self.increase_bpm_button:
            self.controller.increase_bpm()
        elif event.get_source() is self.decrease_bpm_button:
            self.controller.decrease_bpm()

    def update_bpm(self) -> None:
        # BPMObserver callback: re-read the model and refresh the label.
        if self.model is not None:
            bpm = self.model.get_bpm()
            if self.bpm_output_label is not None:
                if bpm == 0:
                    self.bpm_output_label.set_text("offline")
                else:
                    self.bpm_output_label.set_text("Current BPM: " + str(bpm))

    def update_beat(self) -> None:
        # BeatObserver callback: flash the bar to full; tick() decays it.
        if self.beat_bar is not None:
            self.beat_bar.set_value(100)

    # --- console additions -------------------------------------------------
    def tick(self) -> None:
        """One 50 ms animation frame of the beat bar."""
        if self.beat_bar is not None:
            self.beat_bar.step()

    def show(self) -> None:
        assert self.beat_bar is not None and self.bpm_output_label is not None
        print(f"[View] {self.beat_bar.render()} {self.bpm_output_label.get_text()}")
