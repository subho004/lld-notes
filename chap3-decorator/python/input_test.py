"""Client for the java.io-style example: reads test.txt through LowerCaseInputStream."""

import sys

from lower_case_input_stream import LowerCaseInputStream


def main() -> None:
    # Stack the decorator over a plain binary file, as java.io does with FileInputStream.
    try:
        with open("test.txt", "rb") as f:
            in_stream = LowerCaseInputStream(f)
            while True:
                c = in_stream.read()
                if c < 0:
                    break
                sys.stdout.write(chr(c))
    except OSError as e:
        print(e, file=sys.stderr)


if __name__ == "__main__":
    main()
