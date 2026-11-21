import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * Concrete class that overrides the hook to ask the user (reads stdin).
 */
public class CoffeeWithHook extends CaffeineBeverageWithHook {
    public void brew() {
        System.out.println("Dripping Coffee through filter");
    }

    public void addCondiments() {
        System.out.println("Adding Sugar and Milk");
    }

    /** Overrides the hook; any answer starting with "y" means yes. */
    public boolean customerWantsCondiments() {
        String answer = getUserInput();
        return answer.toLowerCase().startsWith("y");
    }

    private String getUserInput() {
        String answer = null;
        System.out.print("Would you like sugar and milk in your coffee (y/n)? ");
        // Quirk: a new reader per question; with fully piped stdin the first one buffers all input, so a later readLine() returns null (NPE above).
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        try {
            answer = in.readLine();
        } catch (IOException ioe) {
            System.err.println("IO error trying to read your answer");
        }
        return answer;
    }

    public static void main(String[] args) {
        CoffeeWithHook coffee = new CoffeeWithHook();
        coffee.prepareRecipe();
    }
}
