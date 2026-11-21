"""Protection-proxy demo (client). Wraps the same PersonImpl in an owner proxy
and a non-owner proxy and shows which calls each one allows.
"""
import os
import sys
from typing import Dict

# Make sibling modules importable when run from another directory.
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from invocation_handler import InvocationHandler, new_proxy_instance  # noqa: E402
from non_owner_invocation_handler import NonOwnerInvocationHandler  # noqa: E402
from owner_invocation_handler import OwnerInvocationHandler  # noqa: E402
from person import Person  # noqa: E402
from person_impl import PersonImpl  # noqa: E402


class MatchMakingTestDrive:
    def __init__(self) -> None:
        self.dating_db: Dict[str, Person] = {}
        self.initialize_database()

    def drive(self) -> None:
        joe = self.get_person_from_database("Joe Javabean")
        owner_proxy = self.get_owner_proxy(joe)
        print("Name is " + owner_proxy.get_name())
        owner_proxy.set_interests("bowling, Go")
        print("Interests set from owner proxy")
        try:
            owner_proxy.set_geek_rating(10)
        except Exception:
            print("Can't set rating from owner proxy")
        print("Rating is " + str(owner_proxy.get_geek_rating()))

        non_owner_proxy = self.get_non_owner_proxy(joe)
        print("Name is " + non_owner_proxy.get_name())
        try:
            non_owner_proxy.set_interests("bowling, Go")
        except Exception:
            print("Can't set interests from non owner proxy")
        non_owner_proxy.set_geek_rating(3)
        print("Rating set from non owner proxy")
        print("Rating is " + str(non_owner_proxy.get_geek_rating()))

    def get_owner_proxy(self, person: Person) -> Person:
        return self.get_proxy(OwnerInvocationHandler(person))

    def get_non_owner_proxy(self, person: Person) -> Person:
        return self.get_proxy(NonOwnerInvocationHandler(person))

    def get_proxy(self, handler: InvocationHandler) -> Person:
        # Dynamic proxy: Python's replacement for Proxy.newProxyInstance.
        return new_proxy_instance(Person, handler)

    def get_person_from_database(self, name: str) -> Person:
        return self.dating_db[name]

    def initialize_database(self) -> None:
        joe = PersonImpl()
        joe.set_name("Joe Javabean")
        joe.set_interests("cars, computers, music")
        joe.set_geek_rating(7)
        self.dating_db[joe.get_name()] = joe

        kelly = PersonImpl()
        kelly.set_name("Kelly Klosure")
        kelly.set_interests("ebay, movies, music")
        kelly.set_geek_rating(6)
        self.dating_db[kelly.get_name()] = kelly


def main() -> None:
    MatchMakingTestDrive().drive()


if __name__ == "__main__":
    main()
