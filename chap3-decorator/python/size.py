"""Size enum shared by beverages and decorators (supporting type, not part of the pattern itself)."""
from enum import Enum


class Size(Enum):
    # Drink size; decorators forward it to the wrapped drink (Soy prices by size).
    TALL = "TALL"
    GRANDE = "GRANDE"
    VENTI = "VENTI"

    # Print as the bare name ("TALL") to match Java's enum toString().
    def __str__(self) -> str:
        return self.value
