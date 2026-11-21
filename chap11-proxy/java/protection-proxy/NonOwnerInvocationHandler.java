import java.lang.reflect.InvocationHandler;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/** Proxy handler for other users: may read and rate, but may not change personal data. */
public class NonOwnerInvocationHandler implements InvocationHandler {
    Person person;

    public NonOwnerInvocationHandler(Person person) {
        this.person = person;
    }

    // Called for every method on the proxy; forwards allowed calls to the real person via reflection.
    public Object invoke(Object proxy, Method method, Object[] args)
            throws IllegalAccessException {
        try {
            if (method.getName().startsWith("get")) {
                return method.invoke(person, args);
            } else if (method.getName().equals("setGeekRating")) {
                return method.invoke(person, args);
            } else if (method.getName().startsWith("set")) {
                throw new IllegalAccessException();
            }
        } catch (InvocationTargetException e) {
            // Exceptions thrown by the real method arrive wrapped in InvocationTargetException.
            e.printStackTrace();
        }
        // Unrecognized methods are silently ignored (null).
        return null;
    }
}
