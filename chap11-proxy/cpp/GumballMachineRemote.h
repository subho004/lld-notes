// Remote-proxy pieces: GumballMachineRemote (Subject interface),
// GumballMachineStub (Remote Proxy) and Naming (in-process registry).
#pragma once
#include <memory>
#include <string>

#include "Rmi.h"

// Java returns a (serializable) State; across "RMI" the caller only ever
// prints it, so the remote interface returns the state's description by value.
class GumballMachineRemote : public Remote {
public:
    virtual int getCount() = 0;
    virtual std::string getLocation() = 0;
    virtual std::string getState() = 0;
    // Remote proxy factory used by Naming::lookup.
    virtual std::shared_ptr<GumballMachineRemote> makeStub() = 0;
};

// Remote Proxy: same interface as the real machine, forwards each call to it.
// Holds a shared_ptr so the target outlives the stub.
class GumballMachineStub : public GumballMachineRemote {
    std::shared_ptr<GumballMachineRemote> target;

public:
    explicit GumballMachineStub(std::shared_ptr<GumballMachineRemote> t) : target(std::move(t)) {}
    int getCount() override { return target->getCount(); }
    std::string getLocation() override { return target->getLocation(); }
    std::string getState() override { return target->getState(); }
    std::shared_ptr<GumballMachineRemote> makeStub() override { return target->makeStub(); }
};

// Stand-in for java.rmi.Naming. Function-local static avoids static
// initialization order problems in this header-only registry.
class Naming {
    static std::map<std::string, std::shared_ptr<GumballMachineRemote>>& registry() {
        static std::map<std::string, std::shared_ptr<GumballMachineRemote>> r;
        return r;
    }

public:
    static void rebind(const std::string& name, std::shared_ptr<GumballMachineRemote> obj) {
        registry()[name] = std::move(obj);
    }
    static std::shared_ptr<GumballMachineRemote> lookup(const std::string& name) {
        auto it = registry().find(name);
        if (it == registry().end()) throw RemoteException("NotBoundException: " + name);
        // Return a stub, not the registered object, so clients always go through the proxy.
        return std::make_shared<GumballMachineStub>(it->second);
    }
};
