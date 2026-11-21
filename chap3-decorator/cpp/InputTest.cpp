// Client for the java.io-style example: reads test.txt through LowerCaseInputStream.
#include <iostream>
#include <memory>

#include "LowerCaseInputStream.h"

int main() {
    int c;
    // Decorators stack by moving ownership inward: LowerCaseInputStream owns the FileInputStream.
    try {
        std::unique_ptr<InputStream> in =
            std::make_unique<LowerCaseInputStream>(std::make_unique<FileInputStream>("test.txt"));
        while ((c = in->read()) >= 0) {
            std::cout << static_cast<char>(c);
        }
    } catch (const std::ios_base::failure& e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
