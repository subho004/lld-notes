"""Injectable random source for the WinnerState draw (Java: java.util.Random).

Default is deterministic (never a winner) so output is reproducible.
  GUMBALL_RANDOM=1      -> truly random (time-seeded), like the Java original
  GUMBALL_SEED=<int>    -> reproducible pseudo-random sequence
"""
import os
import random
import time
from abc import ABC, abstractmethod


# Strategy-like interface for the random draw; lets tests inject a fixed source.
class RandomSource(ABC):
    @abstractmethod
    def next_int(self, bound: int) -> int:
        """Return an int in [0, bound)."""


class FixedRandom(RandomSource):
    """Always returns the same value (default 1 => 'winner' is never drawn)."""

    def __init__(self, value: int = 1) -> None:
        self.value = value

    def next_int(self, bound: int) -> int:
        return self.value % bound


class PseudoRandom(RandomSource):
    def __init__(self, seed: int) -> None:
        self._rng = random.Random(seed)

    def next_int(self, bound: int) -> int:
        return self._rng.randrange(bound)


# Picks the source from env vars: GUMBALL_RANDOM, then GUMBALL_SEED, else deterministic.
def default_random_source() -> RandomSource:
    if os.environ.get("GUMBALL_RANDOM") == "1":
        return PseudoRandom(int(time.time() * 1000))
    seed = os.environ.get("GUMBALL_SEED")
    if seed is not None:
        return PseudoRandom(int(seed))
    return FixedRandom(1)
