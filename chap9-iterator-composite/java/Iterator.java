/**
 * Iterator interface: sequential access to MenuItems without exposing the collection.
 * Note this is the chapter's own type, not java.util.Iterator (and it has no remove()).
 */
public interface Iterator {
    boolean hasNext();

    MenuItem next();
}
