package adaptive;

import java.util.Enumeration;
import java.util.Iterator;

/** Adapter: presents a legacy Enumeration through the newer Iterator interface. */
public class EnumerationIterator<T> implements Iterator<T> {
    Enumeration<T> enumeration;

    public EnumerationIterator(Enumeration<T> enumeration) {
        this.enumeration = enumeration;
    }

    public boolean hasNext() {
        return enumeration.hasMoreElements();
    }

    public T next() {
        return enumeration.nextElement();
    }

        // Enumeration has no remove(), so this operation cannot be adapted.
    public void remove() {
        throw new UnsupportedOperationException();
    }
}
