/**
 * Aggregate interface: every menu hands out an Iterator, so clients (Waitress) stay independent of the storage type.
 */
public interface Menu {
    public Iterator createIterator();
}
