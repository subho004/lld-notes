"""Subject interface for the protection proxy: the Person that dating-service
clients see. Proxies and PersonImpl both satisfy it.
"""
from abc import ABC, abstractmethod


class Person(ABC):
    """Subject: getters/setters whose access depends on who is calling."""
    @abstractmethod
    def get_name(self) -> str: ...

    @abstractmethod
    def get_gender(self) -> str: ...

    @abstractmethod
    def get_interests(self) -> str: ...

    @abstractmethod
    def get_geek_rating(self) -> int: ...

    @abstractmethod
    def set_name(self, name: str) -> None: ...

    @abstractmethod
    def set_gender(self, gender: str) -> None: ...

    @abstractmethod
    def set_interests(self, interests: str) -> None: ...

    @abstractmethod
    def set_geek_rating(self, rating: int) -> None: ...
