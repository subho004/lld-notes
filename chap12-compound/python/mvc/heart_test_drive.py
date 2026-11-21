"""Scripted session showing a HeartModel driving the DJ view via HeartController."""

from __future__ import annotations

from controller_interface import ControllerInterface
from heart_controller import HeartController
from heart_model import HeartModel


def main() -> None:
    heart_model = HeartModel()
    controller: ControllerInterface = HeartController(heart_model)
    # Narrow the type so the view can be reached; the interface does not expose it.
    assert isinstance(controller, HeartController)
    view = controller.view

    view.show()
    for second in range(1, 21):
        for _ in range(20):  # 20 frames of 50 ms
            heart_model.advance(50)
            view.tick()
        if second % 5 == 0:
            print(f"-- t = {second}s, heart rate {heart_model.get_heart_rate()}")
            view.show()

    print("-- the heart view ignores the controls")
    view.start_menu_item.click()
    view.increase_bpm_button.click()


if __name__ == "__main__":
    main()
