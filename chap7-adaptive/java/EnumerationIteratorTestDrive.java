package adaptive;

import java.util.Enumeration;
import java.util.Iterator;
import java.util.Vector;

/** Client: iterates a Vector's Enumeration via EnumerationIterator. Note: the raw type below causes unchecked warnings. */
public class EnumerationIteratorTestDrive {
    public static void main(String[] args) {
        Vector<String> vector = new Vector<String>();
        vector.add("Java");
        vector.add("Adapter");
        vector.add("Pattern");

        Enumeration<String> enumeration = vector.elements();
        Iterator<String> iterator = new EnumerationIterator(enumeration);

        System.out.println("Iterating with EnumerationIterator:");
        while (iterator.hasNext()) {
            System.out.println(iterator.next());
        }
    }
}
