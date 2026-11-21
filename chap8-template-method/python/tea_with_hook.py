"""Concrete class TeaWithHook: overrides the condiment hook to ask the user about lemon."""
from caffeine_beverage_with_hook import CaffeineBeverageWithHook
from coffee_with_hook import get_user_input  # shared stdin helper


class TeaWithHook(CaffeineBeverageWithHook):
    def brew(self) -> None:
        print("Steeping the tea")

    def add_condiments(self) -> None:
        print("Adding Lemon")

    # Overrides the hook from the base class; EOF counts as "no".
    def customer_wants_condiments(self) -> bool:
        answer = self._get_user_input()
        return answer.lower().startswith("y")

    def _get_user_input(self) -> str:
        return get_user_input("Would you like lemon with your tea (y/n)? ")
