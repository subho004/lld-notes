"""Principle of Least Knowledge demo: Car wraps Engine, Wheels and Doors so clients never touch them."""
class Engine:
    """Component of Car; _running is private by convention only."""

    def __init__(self) -> None:
        self._running = False

    def start(self) -> None:
        self._running = True
        print("Engine started")

    def stop(self) -> None:
        self._running = False
        print("Engine stopped")

    def is_running(self) -> bool:
        return self._running


class Wheels:
    """Component of Car."""

    def rotate(self) -> None:
        print("Wheels rotating")

    def stop(self) -> None:
        print("Wheels stopped")


class Doors:
    """Component of Car; _locked is private by convention only."""

    def __init__(self) -> None:
        self._locked = False

    def lock(self) -> None:
        self._locked = True
        print("Doors locked")

    def unlock(self) -> None:
        self._locked = False
        print("Doors unlocked")

    def is_locked(self) -> bool:
        return self._locked


class Car:
    """Talks only to its own components; clients call Car, never its parts (Law of Demeter)."""

    def __init__(self, engine: Engine, wheels: Wheels, doors: Doors) -> None:
        self._engine = engine
        self._wheels = wheels
        self._doors = doors

    def start(self) -> None:
        # Car coordinates its parts so the client does not have to.
        self._doors.unlock()
        self._engine.start()

    def drive(self) -> None:
        if not self._engine.is_running():
            print("Cannot drive - start the car first")
            return
        self._wheels.rotate()
        print("Driving...")

    def stop(self) -> None:
        self._wheels.stop()
        self._engine.stop()

    def park(self) -> None:
        self.stop()
        self._doors.lock()
        print("Parked")

    def refuel(self) -> None:
        if self._engine.is_running():
            print("Cannot refuel while engine is running")
            return
        print("Refueling...")
