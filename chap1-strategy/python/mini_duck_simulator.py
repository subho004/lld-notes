"""Entry point (client): exercises the Strategy pattern with ducks and a duck call."""
from duck import Duck, MallardDuck, ModelDuck
from duck_call import DuckCall
from fly_behavior import FlyRocketPowered


def main() -> None:
    # Client code: programs against Duck, not concrete subclasses.
    print("Mallard Duck")
    mallard: Duck = MallardDuck()
    mallard.perform_fly()
    mallard.perform_quack()

    print("Model Duck")
    model: Duck = ModelDuck()
    model.perform_fly()
    # Runtime swap of the strategy: the model duck now flies with a rocket.
    model.set_fly_behavior(FlyRocketPowered())
    model.perform_fly()

    print("Duck Call!")
    duck_call = DuckCall()
    duck_call.perform_quack()


if __name__ == "__main__":
    main()
