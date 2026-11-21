#pragma once
// Hand-written replacement for java.lang.reflect.InvocationHandler / Proxy.
//
// C++ has no runtime reflection, so Proxy.newProxyInstance cannot generate a
// Person implementation on the fly.  Instead:
//   * PersonProxy (hand-written) implements Person and routes EVERY call to an
//     InvocationHandler as (method name, argument list), like Java's proxy;
//   * invokeOn() is the hand-written "Method.invoke" that dispatches a method
//     name back onto a real Person.
// The handlers (Owner/NonOwner) are then identical in spirit to the Java ones.
#include <memory>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

#include "Person.h"

// Thrown by a handler when the caller may not use a method.
class IllegalAccessException : public std::runtime_error {
public:
    IllegalAccessException() : std::runtime_error("IllegalAccessException") {}
};

// Dynamic argument/return type replacing Java's Object (monostate = void).
using Value = std::variant<std::monostate, int, std::string>;
using Args = std::vector<Value>;

// Interface for access-control policies (Owner/NonOwner). Virtual destructor
// because handlers are held by shared_ptr<InvocationHandler>.
class InvocationHandler {
public:
    virtual ~InvocationHandler() = default;
    virtual Value invoke(const std::string& method, const Args& args) = 0;
};

// Poor man's Method.invoke(person, args).
inline Value invokeOn(Person& p, const std::string& method, const Args& a) {
    if (method == "getName") return p.getName();
    if (method == "getGender") return p.getGender();
    if (method == "getInterests") return p.getInterests();
    if (method == "getGeekRating") return p.getGeekRating();
    if (method == "setName") p.setName(std::get<std::string>(a.at(0)));
    else if (method == "setGender") p.setGender(std::get<std::string>(a.at(0)));
    else if (method == "setInterests") p.setInterests(std::get<std::string>(a.at(0)));
    else if (method == "setGeekRating") p.setGeekRating(std::get<int>(a.at(0)));
    else throw std::invalid_argument("no such method: " + method);
    return std::monostate{};
}

// Proxy: implements Person and forwards every call to its handler.
// The handler is shared_ptr so it lives as long as the proxy.
class PersonProxy : public Person {
    std::shared_ptr<InvocationHandler> handler;

public:
    explicit PersonProxy(std::shared_ptr<InvocationHandler> h) : handler(std::move(h)) {}

    std::string getName() override { return std::get<std::string>(handler->invoke("getName", {})); }
    std::string getGender() override { return std::get<std::string>(handler->invoke("getGender", {})); }
    std::string getInterests() override { return std::get<std::string>(handler->invoke("getInterests", {})); }
    int getGeekRating() override { return std::get<int>(handler->invoke("getGeekRating", {})); }
    void setName(const std::string& n) override { handler->invoke("setName", {n}); }
    void setGender(const std::string& g) override { handler->invoke("setGender", {g}); }
    void setInterests(const std::string& i) override { handler->invoke("setInterests", {i}); }
    void setGeekRating(int r) override { handler->invoke("setGeekRating", {r}); }
};

// Proxy.newProxyInstance equivalent (fixed to the Person interface).
inline std::shared_ptr<Person> newProxyInstance(std::shared_ptr<InvocationHandler> handler) {
    return std::make_shared<PersonProxy>(std::move(handler));
}
