#pragma once
// Tiny in-process stand-in for java.rmi (Remote, RemoteException, Naming).
// No network: Naming::lookup returns a stub (the remote proxy) that forwards
// every call to the bound object.
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

// Stand-in for java.rmi.RemoteException; inherits runtime_error constructors.
class RemoteException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

// Marker interface (java.rmi.Remote); virtual destructor for polymorphic deletion.
class Remote {
public:
    virtual ~Remote() = default;
};
