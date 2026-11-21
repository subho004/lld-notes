"""PersonImpl: the Real Subject. Holds the data and has no access checks;
the proxy and its handlers enforce permissions.
"""
from person import Person


class PersonImpl(Person):
    """Real Subject: plain data holder."""
    def __init__(self) -> None:
        self.name = ""
        self.gender = ""
        self.interests = ""
        self.rating = 0
        self.rating_count = 0

    def get_name(self) -> str:
        return self.name

    def get_gender(self) -> str:
        return self.gender

    def get_interests(self) -> str:
        return self.interests

    def get_geek_rating(self) -> int:
        if self.rating_count == 0:
            return 0
        # Integer average, matching Java's int division.
        return self.rating // self.rating_count

    def set_name(self, name: str) -> None:
        self.name = name

    def set_gender(self, gender: str) -> None:
        self.gender = gender

    def set_interests(self, interests: str) -> None:
        self.interests = interests

    def set_geek_rating(self, rating: int) -> None:
        self.rating += rating
        self.rating_count += 1
