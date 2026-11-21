/**
 * Client: builds ducks via an Abstract Factory, groups them in Flocks (Composite),
 * attaches a Quackologist (Observer) and prints the QuackCounter total.
 */
public class DuckSimulator {
    public static void main(String[] args) {
        DuckSimulator simulator = new DuckSimulator();
        AbstractDuckFactory duckFactory = new CountingDuckFactory();
        simulator.simulate(duckFactory);
    }

    void simulate(AbstractDuckFactory duckFactory) {
        Quackable redheadDuck = duckFactory.createRedheadDuck();
        Quackable duckCall = duckFactory.createDuckCall();
        Quackable rubberDuck = duckFactory.createRubberDuck();
        // Adapter: the Goose is made to look like a Quackable.
        Quackable gooseDuck = new GooseAdapter(new Goose());

        Flock flockOfDucks = new Flock();

        flockOfDucks.add(redheadDuck);
        flockOfDucks.add(duckCall);
        flockOfDucks.add(rubberDuck);
        flockOfDucks.add(gooseDuck);

        Flock flockOfMallards = new Flock();

        Quackable mallardOne = duckFactory.createMallardDuck();
        Quackable mallardTwo = duckFactory.createMallardDuck();
        Quackable mallardThree = duckFactory.createMallardDuck();
        Quackable mallardFour = duckFactory.createMallardDuck();

        flockOfMallards.add(mallardOne);
        flockOfMallards.add(mallardTwo);
        flockOfMallards.add(mallardThree);
        flockOfMallards.add(mallardFour);

        // Composite: a Flock is itself a Quackable, so flocks nest inside flocks.
        flockOfDucks.add(flockOfMallards);

        System.out.println("\nDuck Simulator: With Observer");

        Quackologist quackologist = new Quackologist();
        // Registering on the outer flock cascades down to every duck inside it.
        flockOfDucks.registerObserver(quackologist);

        simulate(flockOfDucks);

        System.out.println("\nThe ducks quacked " + QuackCounter.getQuacks() + " times");
    }

    // Works for a single duck or a whole Flock alike.
    void simulate(Quackable duck) {
        duck.quack();
    }
}
