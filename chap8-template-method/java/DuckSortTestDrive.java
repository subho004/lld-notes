import java.util.Arrays;

/**
 * Demo: Arrays.sort() is a template method that defers comparison to Duck.compareTo.
 * The sort is stable, so equal-weight ducks keep their original order.
 */
public class DuckSortTestDrive {
    public static void main(String[] args) {
        Duck[] ducks = {
                new Duck("Daffy", 8),
                new Duck("Dewey", 2),
                new Duck("Howard", 7),
                new Duck("Louie", 2),
                new Duck("Donald", 10),
                new Duck("Huey", 2)
        };
        System.out.println("Before sorting:");
        printDucks(ducks);
        Arrays.sort(ducks);
        System.out.println("\nAfter sorting:");
        printDucks(ducks);
    }

    public static void printDucks(Duck[] ducks) {
        for (Duck duck : ducks) {
            System.out.println(duck);
        }
    }
}
