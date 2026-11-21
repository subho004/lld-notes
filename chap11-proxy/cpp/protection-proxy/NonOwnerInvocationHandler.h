// Protection-proxy handler for other users: may read all and may only set
// the geek rating.
#pragma once
#include <memory>

#include "InvocationHandler.h"

// Access policy for non-owners; forwards allowed calls to the real Person.
// shared_ptr: the same Person is shared by the database and handlers.
class NonOwnerInvocationHandler : public InvocationHandler {
    std::shared_ptr<Person> person;

public:
    explicit NonOwnerInvocationHandler(std::shared_ptr<Person> p) : person(std::move(p)) {}

    Value invoke(const std::string& method, const Args& args) override {
        // Order matters: the specific setGeekRating rule must precede the generic set* rule.
        if (method.rfind("get", 0) == 0) {
            return invokeOn(*person, method, args);
        } else if (method == "setGeekRating") {
            return invokeOn(*person, method, args);
        } else if (method.rfind("set", 0) == 0) {
            throw IllegalAccessException();
        }
        return std::monostate{};
    }
};
