import java.io.InputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.File;

/**
 * Client: reads test.txt through the LowerCaseInputStream decorator.
 * Run from the java/ folder, since the file path is relative.
 */
public class InputTest {
    public static void main(String[] args) {
        int c;
        try {
            InputStream in = new LowerCaseInputStream(new FileInputStream("test.txt"));
            while ((c = in.read()) >= 0) {
                System.out.print((char) c);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
