package adaptive;

import java.util.ArrayList;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.List;

/** Client: reads an Iterator through the Enumeration interface via the IteratorEnumeration adapter. */
public class IteratorEnumerationTestDrive {
    public static void main(String[] args) {
        List<String> list = new ArrayList<String>();
        list.add("Iterator");
        list.add("to");
        list.add("Enumeration");

        Iterator<String> iterator = list.iterator();
        Enumeration<String> enumeration = new IteratorEnumeration<String>(iterator);

        System.out.println("Iterating with IteratorEnumeration:");
        while (enumeration.hasMoreElements()) {
            System.out.println(enumeration.nextElement());
        }
    }
}
