import java.io.FilterInputStream;
import java.io.InputStream;
import java.io.IOException;

/**
 * Concrete Decorator (java.io example): wraps any InputStream and lower-cases
 * every byte read through it. FilterInputStream is the JDK's decorator base.
 */
public class LowerCaseInputStream extends FilterInputStream {
    public LowerCaseInputStream(InputStream in) {
        super(in);
    }

    // Decorates the single-byte read; -1 (end of stream) must pass through untouched.
    public int read() throws IOException {
        int c = super.read();
        return (c == -1 ? c : Character.toLowerCase((char) c));
    }

    // Only the first `result` bytes were filled, hence the bounded loop.
    public int read(byte[] b, int offset, int length) throws IOException {
        int result = super.read(b, offset, length);
        for (int i = offset; i < offset + result; i++) {
            b[i] = (byte) Character.toLowerCase((char) b[i]);
        }
        return result;
    }

    public int read(byte[] b) throws IOException {
        int result = super.read(b);
        for (int i = 0; i < result; i++) {
            b[i] = (byte) Character.toLowerCase((char) b[i]);
        }
        return result;
    }
}