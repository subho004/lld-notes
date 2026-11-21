import java.lang.reflect.InvocationHandler;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/** Proxy handler for the owner: may read and change own data, but may not rate themselves. */
public class OwnerInvocationHandler implements InvocationHandler {
    Person person;

    public OwnerInvocationHandler(Person person) {
        this.person = person;
    }

    // Called for every method on the proxy; forwards allowed calls to the real person via reflection.
    public Object invoke(Object proxy, Method method, Object[] args)
            throws IllegalAccessException {
        try {
            if (method.getName().startsWith("get")) {
                return method.invoke(person, args);
            } else if (method.getName().equals("setGeekRating")) {
                throw new IllegalAccessException();
            } else if (method.getName().startsWith("set")) {
                return method.invoke(person, args);
            }
        } catch (InvocationTargetException e) {
            // Exceptions thrown by the real method arrive wrapped in InvocationTargetException.
            e.printStackTrace();
        }
        // Unrecognized methods are silently ignored (null).
        return null;
    }
}
