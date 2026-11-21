/**
 * Client: stacks decorators around a base drink at runtime, e.g.
 * new Whip(new Mocha(new Expresso())), and prints description and cost.
 */
public class StarbuzzCoffee {
    public static void main(String[] args) {
        Beverage beverage = new Expresso();
        System.out.println(beverage.getDescription() + " $" + beverage.cost());

        // Each assignment re-wraps the variable, so the outermost decorator is the new reference.
        Beverage beverage2 = new DarkRoast();
        beverage2 = new Mocha(beverage2);
        beverage2 = new Mocha(beverage2);
        beverage2 = new Whip(beverage2);
        System.out.println(beverage2.getDescription() + " $" + beverage2.cost());

        Beverage beverage3 = new HouseBlend();
        beverage3 = new Soy(beverage3);
        beverage3 = new Mocha(beverage3);
        beverage3 = new Whip(beverage3);
        System.out.println(beverage3.getDescription() + " $" + beverage3.cost());

        Beverage latte = new Expresso();
        latte = new Mocha(latte);
        latte = new Mocha(latte);
        latte = new Soy(latte);
        latte = new Whip(latte);
        // Prints 2.5900000000000003: plain double addition, no rounding is applied.
        System.out.println(latte.getDescription() + " $" + latte.cost());

        // Size is set on the base drink before wrapping; decorators forward getSize().
        Beverage beverage4 = new HouseBlend();
        beverage4.setSize(Size.GRANDE);
        beverage4 = new Soy(beverage4);
        beverage4 = new Mocha(beverage4);
        beverage4 = new Whip(beverage4);
        System.out.println(beverage4.getDescription() + " $" + beverage4.cost());
    }
}
