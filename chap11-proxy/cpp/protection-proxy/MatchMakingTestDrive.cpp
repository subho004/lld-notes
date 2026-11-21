// Protection-proxy demo (client): wraps one PersonImpl in an owner proxy and a
// non-owner proxy and shows which calls each one allows.
#include <exception>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "InvocationHandler.h"
#include "NonOwnerInvocationHandler.h"
#include "OwnerInvocationHandler.h"
#include "Person.h"
#include "PersonImpl.h"

class MatchMakingTestDrive {
    // Values are shared_ptr<Person> so proxies' handlers can share the same object.
    std::map<std::string, std::shared_ptr<Person>> datingDB;

public:
    MatchMakingTestDrive() { initializeDatabase(); }

    void drive() {
        auto joe = getPersonFromDatabase("Joe Javabean");
        auto ownerProxy = getOwnerProxy(joe);
        std::cout << "Name is " << ownerProxy->getName() << "\n";
        ownerProxy->setInterests("bowling, Go");
        std::cout << "Interests set from owner proxy\n";
        try {
            ownerProxy->setGeekRating(10);
        } catch (const std::exception&) {
            std::cout << "Can't set rating from owner proxy\n";
        }
        std::cout << "Rating is " << ownerProxy->getGeekRating() << "\n";

        auto nonOwnerProxy = getNonOwnerProxy(joe);
        std::cout << "Name is " << nonOwnerProxy->getName() << "\n";
        try {
            nonOwnerProxy->setInterests("bowling, Go");
        } catch (const std::exception&) {
            std::cout << "Can't set interests from non owner proxy\n";
        }
        nonOwnerProxy->setGeekRating(3);
        std::cout << "Rating set from non owner proxy\n";
        std::cout << "Rating is " << nonOwnerProxy->getGeekRating() << "\n";
    }

    std::shared_ptr<Person> getOwnerProxy(std::shared_ptr<Person> person) {
        // Wrap the real Person in a proxy driven by the owner policy.
        return newProxyInstance(std::make_shared<OwnerInvocationHandler>(std::move(person)));
    }

    std::shared_ptr<Person> getNonOwnerProxy(std::shared_ptr<Person> person) {
        // Same Person, different policy: the proxy decides what each caller may do.
        return newProxyInstance(std::make_shared<NonOwnerInvocationHandler>(std::move(person)));
    }

    std::shared_ptr<Person> getPersonFromDatabase(const std::string& name) { return datingDB.at(name); }

    void initializeDatabase() {
        auto joe = std::make_shared<PersonImpl>();
        joe->setName("Joe Javabean");
        joe->setInterests("cars, computers, music");
        joe->setGeekRating(7);
        datingDB[joe->getName()] = joe;

        auto kelly = std::make_shared<PersonImpl>();
        kelly->setName("Kelly Klosure");
        kelly->setInterests("ebay, movies, music");
        kelly->setGeekRating(6);
        datingDB[kelly->getName()] = kelly;
    }
};

int main() {
    MatchMakingTestDrive test;
    test.drive();
    return 0;
}
