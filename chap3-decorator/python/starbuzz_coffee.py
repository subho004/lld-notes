"""Client: builds decorated drinks (Starbuzz Coffee) and prints description and cost."""

from beverage import Beverage, DarkRoast, Expresso, HouseBlend
from condiment_decorator import Mocha, Soy, Whip
from size import Size


def main() -> None:
    # Each reassignment wraps the previous drink in another decorator (client of the pattern).
    beverage: Beverage = Expresso()
    # f-string of a float uses repr (shortest round-trip), matching Java's Double.toString.
    print(f"{beverage.get_description()} ${beverage.cost()}")

    beverage2: Beverage = DarkRoast()
    beverage2 = Mocha(beverage2)
    beverage2 = Mocha(beverage2)
    beverage2 = Whip(beverage2)
    print(f"{beverage2.get_description()} ${beverage2.cost()}")

    beverage3: Beverage = HouseBlend()
    beverage3 = Soy(beverage3)
    beverage3 = Mocha(beverage3)
    beverage3 = Whip(beverage3)
    print(f"{beverage3.get_description()} ${beverage3.cost()}")

    latte: Beverage = Expresso()
    latte = Mocha(latte)
    latte = Mocha(latte)
    latte = Soy(latte)
    latte = Whip(latte)
    print(f"{latte.get_description()} ${latte.cost()}")

    beverage4: Beverage = HouseBlend()
    beverage4.set_size(Size.GRANDE)
    beverage4 = Soy(beverage4)
    beverage4 = Mocha(beverage4)
    beverage4 = Whip(beverage4)
    print(f"{beverage4.get_description()} ${beverage4.cost()}")


if __name__ == "__main__":
    main()
