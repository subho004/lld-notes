import java.util.Calendar;

/**
 * Concrete Iterator over the DinnerMenu array that visits every other item.
 * Quirk: Calendar.DAY_OF_WEEK is the constant 7, so the start is always 7 % 2 = 1. Unused by the test drives.
 */
public class AlternatingDinerMenuIterator implements Iterator {
    MenuItem[] items;
    int position;

    public AlternatingDinerMenuIterator(MenuItem[] items) {
        this.items = items;
        position = Calendar.DAY_OF_WEEK % 2;
    }

    public MenuItem next() {
        MenuItem menuItem = items[position];
        position = position + 2;
        return menuItem;
    }

    // Stops at the array end or at the first empty (null) slot.
    public boolean hasNext() {
        if (position >= items.length || items[position] == null) {
            return false;
        } else {
            return true;
        }
    }

    public void remove() {
        throw new UnsupportedOperationException(
                "Alternating Diner Menu Iterator does not support remove()");
    }
}
