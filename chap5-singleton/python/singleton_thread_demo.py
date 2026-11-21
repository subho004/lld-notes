"""Extra (no Java counterpart): many threads race for the singletons."""
import threading
from typing import List

from chocolate_boiler import ChocolateBoiler
from singleton import NewSingleton, Singleton

THREADS = 8


def main() -> None:
    barrier = threading.Barrier(THREADS)
    classic: List[object] = [None] * THREADS
    via_new: List[object] = [None] * THREADS
    boilers: List[object] = [None] * THREADS

    def worker(i: int) -> None:
        barrier.wait()  # release all threads at once to maximise the race
        classic[i] = Singleton.get_instance()
        via_new[i] = NewSingleton()
        boilers[i] = ChocolateBoiler.get_instance()

    threads = [threading.Thread(target=worker, args=(i,)) for i in range(THREADS)]
    for t in threads:
        t.start()
    for t in threads:
        t.join()

    # True when every thread saw the same object (identity compared via id()).
    def one(objs: List[object]) -> str:
        return str(len({id(o) for o in objs}) == 1).lower()

    print(f"Singleton, {THREADS} threads, one instance? {one(classic)}")
    print(f"NewSingleton, {THREADS} threads, one instance? {one(via_new)}")
    print(f"ChocolateBoiler, {THREADS} threads, one instance? {one(boilers)}")

    # Hammer the shared boiler; each fill/boil/drain cycle is guarded by its lock.
    # Reaching into _lock deliberately: the RLock lets the multi-step cycle stay atomic
    # while the inner synchronized methods re-acquire it (like C++ mutex()).
    boiler = ChocolateBoiler.get_instance()
    cycles = [0] * THREADS

    def cook(i: int) -> None:
        for _ in range(100):
            with boiler._lock:  # make the whole cycle atomic
                boiler.fill()
                boiler.boil()
                boiler.drain()
                if boiler.is_empty():
                    cycles[i] += 1

    threads = [threading.Thread(target=cook, args=(i,)) for i in range(THREADS)]
    for t in threads:
        t.start()
    for t in threads:
        t.join()
    print(f"Completed cycles: {sum(cycles)}")
    print(f"Boiler empty at end? {str(boiler.is_empty()).lower()}")


if __name__ == "__main__":
    main()
