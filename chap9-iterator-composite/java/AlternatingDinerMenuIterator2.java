import java.util.Calendar;

/**
 * Concrete Iterator: an identical copy of AlternatingDinerMenuIterator (every other item, starting at 7 % 2).
 * Not used by the test drives.
 */
public class AlternatingDinerMenuIterator2 implements Iterator {
    MenuItem[] items;
    int position;

    public AlternatingDinerMenuIterator2(MenuItem[] items) {
        this.items = items;
        position = Calendar.DAY_OF_WEEK % 2;
    }

    public boolean hasNext() {
        if (position >= items.length || items[position] == null) {
            return false;
        } else {
            return true;
        }
    }

    public MenuItem next() {
        MenuItem menuItem = items[position];
        position = position + 2;
        return menuItem;
    }

    // Notice that this Iterator implementation does not support remove().
    public void remove() {
        throw new UnsupportedOperationException("Alternating Diner Menu Iterator does not support remove()");
    }
}
