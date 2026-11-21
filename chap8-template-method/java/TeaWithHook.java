import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * Concrete class that overrides the hook to ask the user (reads stdin).
 */
public class TeaWithHook extends CaffeineBeverageWithHook {
    public void brew() {
        System.out.println("Steeping the tea");
    }

    public void addCondiments() {
        System.out.println("Adding Lemon");
    }

    /** Overrides the hook; any answer starting with "y" means yes. */
    public boolean customerWantsCondiments() {
        String answer = getUserInput();
        return answer.toLowerCase().startsWith("y");
    }

    private String getUserInput() {
        String answer = null;
        System.out.print("Would you like lemon with your tea (y/n)? ");
        // Quirk: new reader per question; piped input needs a delay between lines (see CoffeeWithHook).
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        try {
            answer = in.readLine();
        } catch (IOException ioe) {
            System.err.println("IO error trying to read your answer");
        }
        return answer;
    }
}
