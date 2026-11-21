/**
 * Concrete Iterator for the fixed-size MenuItem array in DinnerMenu.
 */
public class DinerMenuIterator implements Iterator {
    MenuItem[] items;
    int position = 0;

    public DinerMenuIterator(MenuItem[] items) {
        this.items = items;
    }

    public MenuItem next() {
        return items[position++];
    }

    // The array is pre-allocated, so a null slot marks the end of the real items.
    public boolean hasNext() {
        return position < items.length && items[position] != null;
    }

    public void remove() {
        throw new UnsupportedOperationException("You shouldn't be trying to remove menu items");
    }
}
