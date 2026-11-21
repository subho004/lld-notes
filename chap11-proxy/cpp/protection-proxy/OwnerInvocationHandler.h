// Protection-proxy handler for the owner: may read all and set all fields
// except the geek rating.
#pragma once
#include <memory>

#include "InvocationHandler.h"

// Access policy for the owner; forwards allowed calls to the real Person.
// shared_ptr: the same Person is shared by the database and handlers.
class OwnerInvocationHandler : public InvocationHandler {
    std::shared_ptr<Person> person;

public:
    explicit OwnerInvocationHandler(std::shared_ptr<Person> p) : person(std::move(p)) {}

    Value invoke(const std::string& method, const Args& args) override {
        // Order matters: the specific setGeekRating rule must precede the generic set* rule.
        if (method.rfind("get", 0) == 0) {
            return invokeOn(*person, method, args);
        } else if (method == "setGeekRating") {
            throw IllegalAccessException();
        } else if (method.rfind("set", 0) == 0) {
            return invokeOn(*person, method, args);
        }
        return std::monostate{};
    }
};
