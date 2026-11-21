import java.util.AbstractList;
import java.util.List;

/**
 * Template method via inheritance: AbstractList builds iteration and subList()
 * on top of the get()/size() steps implemented here. set() makes it writable.
 */
public class MyStringList extends AbstractList<String> {
    private String[] myList;

    public MyStringList(String[] strings) {
        myList = strings;
    }

    @Override
    public String get(int index) {
        return myList[index];
    }

    @Override
    public int size() {
        return myList.length;
    }

    @Override
    public String set(int index, String element) {
        String oldString = myList[index];
        myList[index] = element;
        return oldString;
    }
}
