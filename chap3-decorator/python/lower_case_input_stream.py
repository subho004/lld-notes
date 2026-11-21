"""Java InputStream decorator example: FilterInputStream (Decorator base) and LowerCaseInputStream."""

from typing import BinaryIO


class FilterInputStream:
    """Minimal stand-in for java.io.FilterInputStream: wraps another stream."""

    def __init__(self, in_stream: BinaryIO) -> None:
        self.in_stream = in_stream

    def read(self) -> int:
        b = self.in_stream.read(1)
        return b[0] if b else -1

    # Python stand-in for Java's read(byte[], int, int); a distinct name since Python lacks overloads.
    def read_into(self, b: bytearray, offset: int = 0, length: int = -1) -> int:
        if length < 0:
            length = len(b) - offset
        data = self.in_stream.read(length)
        if not data:
            return -1
        b[offset:offset + len(data)] = data
        return len(data)

    def close(self) -> None:
        self.in_stream.close()


class LowerCaseInputStream(FilterInputStream):
    """Concrete Decorator: lower-cases each byte read from the wrapped stream."""

    def read(self) -> int:
        c = super().read()
        # Pass -1 (end of stream) through unchanged.
        return c if c == -1 else ord(chr(c).lower())

    def read_into(self, b: bytearray, offset: int = 0, length: int = -1) -> int:
        result = super().read_into(b, offset, length)
        for i in range(offset, offset + max(result, 0)):
            b[i] = ord(chr(b[i]).lower())
        return result
