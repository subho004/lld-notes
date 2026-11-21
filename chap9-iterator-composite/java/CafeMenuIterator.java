import java.util.Map;

/**
 * Concrete Iterator that adapts java.util.Iterator (from the map's values()) to this chapter's own Iterator interface.
 */
public class CafeMenuIterator implements Iterator {
    Map<String, MenuItem> items;
    // Fully qualified because the unqualified name Iterator refers to this chapter's own interface.
    java.util.Iterator<MenuItem> iterator;

    public CafeMenuIterator(Map<String, MenuItem> items) {
        this.items = items;
        this.iterator = items.values().iterator();
    }

    public MenuItem next() {
        return iterator.next();
    }

    public boolean hasNext() {
        return iterator.hasNext();
    }
}
