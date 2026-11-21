"""Concrete class CoffeeWithHook, plus the shared stdin helper used by both hook subclasses."""
import sys

from caffeine_beverage_with_hook import CaffeineBeverageWithHook


# One shared stdin stream (unlike Java's new BufferedReader per question), so piped input works.
def get_user_input(prompt: str) -> str:
    print(prompt, end="", flush=True)
    line = sys.stdin.readline()  # "" on EOF (Java would hit a NullPointerException)
    return line.rstrip("\r\n")


class CoffeeWithHook(CaffeineBeverageWithHook):
    """Concrete subclass that overrides the hook to ask the user about condiments."""

    def brew(self) -> None:
        print("Dripping Coffee through filter")

    def add_condiments(self) -> None:
        print("Adding Sugar and Milk")

    # Overrides the hook; EOF gives "" which counts as "no".
    def customer_wants_condiments(self) -> bool:
        answer = self._get_user_input()
        return answer.lower().startswith("y")

    def _get_user_input(self) -> str:
        return get_user_input("Would you like sugar and milk in your coffee (y/n)? ")


def main() -> None:
    coffee = CoffeeWithHook()
    coffee.prepare_recipe()


if __name__ == "__main__":
    main()
