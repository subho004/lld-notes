import java.util.List;

/**
 * Demo: iteration and subList() work although only get()/size() were implemented.
 */
public class MyStringListTestDrive {
    public static void main(String[] args) {
        String[] ducks = { "Mallard Duck", "Redhead Duck", "Rubber Duck", "Decoy Duck" };
        MyStringList ducksList = new MyStringList(ducks);
        List<String> ducksSubList = ducksList.subList(2, 3);

        System.out.println("Full list:");
        for (String duck : ducksList) {
            System.out.println(duck);
        }

        System.out.println("\nSublist (index 2, one item):");
        for (String duck : ducksSubList) {
            System.out.println(duck);
        }
    }
}
