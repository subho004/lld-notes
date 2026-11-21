// java.io-style example: InputStream, FileInputStream, FilterInputStream and LowerCaseInputStream.
// Header-only for simplicity; all classes are small.
#pragma once

#include <cctype>
#include <cstddef>
#include <fstream>
#include <memory>
#include <string>
#include <utility>

// Component: abstract stream interface (C++ streams have no decorator hierarchy, so it is hand-written).
class InputStream {
public:
    virtual ~InputStream() = default;
    virtual int read() = 0;  // -1 at end of stream
    virtual int read(char* b, std::size_t offset, std::size_t length) = 0;
};

// Concrete Component: reads bytes from a file.
class FileInputStream : public InputStream {
public:
    explicit FileInputStream(const std::string& name) : file(name, std::ios::binary) {
        // Mirror Java's FileNotFoundException message.
        if (!file) throw std::ios_base::failure(name + " (No such file or directory)");
    }
    int read() override {
        int c = file.get();
        return c == std::char_traits<char>::eof() ? -1 : c;
    }
    int read(char* b, std::size_t offset, std::size_t length) override {
        file.read(b + offset, static_cast<std::streamsize>(length));
        std::streamsize n = file.gcount();
        return n == 0 ? -1 : static_cast<int>(n);
    }

private:
    std::ifstream file;
};

// Decorator base, like java.io.FilterInputStream: owns the wrapped stream via unique_ptr
// and forwards every call to it.
class FilterInputStream : public InputStream {
public:
    explicit FilterInputStream(std::unique_ptr<InputStream> s) : in(std::move(s)) {}
    int read() override { return in->read(); }
    int read(char* b, std::size_t offset, std::size_t length) override {
        return in->read(b, offset, length);
    }

protected:
    std::unique_ptr<InputStream> in;
};

// Concrete Decorator: lower-cases bytes as they pass through.
class LowerCaseInputStream : public FilterInputStream {
public:
    using FilterInputStream::FilterInputStream;

    int read() override {
        // Delegate to the wrapped stream first, then transform; -1 (end of stream) passes through.
        int c = FilterInputStream::read();
        return c == -1 ? c : std::tolower(c);
    }
    int read(char* b, std::size_t offset, std::size_t length) override {
        int result = FilterInputStream::read(b, offset, length);
        for (std::size_t i = offset; result > 0 && i < offset + static_cast<std::size_t>(result); i++) {
            b[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(b[i])));
        }
        return result;
    }
};
