// AbstractList<T> (template methods) and SubList<T> (view), after java.util.AbstractList; header-only because templates.
#pragma once
#include <cstddef>
#include <memory>
#include <stdexcept>

// Minimal java.util.AbstractList: subclasses supply get/size (and set);
// iteration and subList are built on top of them (template-method style).
template <typename T>
class AbstractList {
public:
    // Virtual destructor: subList() returns a unique_ptr<AbstractList<T>> to a derived SubList.
    virtual ~AbstractList() = default;

    // Abstract steps every concrete list must provide.
    virtual T get(std::size_t index) const = 0;
    virtual std::size_t size() const = 0;
    // Optional step: read-only by default (Java UnsupportedOperationException).
    virtual T set(std::size_t, const T&) { throw std::logic_error("unsupported operation"); }

    // Minimal iterator so range-for works; built only on get()/size().
    class Iterator {
    public:
        Iterator(const AbstractList* list, std::size_t i) : list_(list), i_(i) {}
        T operator*() const { return list_->get(i_); }
        Iterator& operator++() { ++i_; return *this; }
        bool operator!=(const Iterator& o) const { return i_ != o.i_; }
    private:
        const AbstractList* list_;
        std::size_t i_;
    };
    Iterator begin() const { return Iterator(this, 0); }
    Iterator end() const { return Iterator(this, size()); }

    // View onto [from, to) of this list. The parent must outlive the view.
    std::unique_ptr<AbstractList<T>> subList(std::size_t from, std::size_t to);
};

// Live view onto a range of the parent. Holds a raw non-owning pointer because the parent
// must outlive the view (Java relies on GC for that).
template <typename T>
class SubList : public AbstractList<T> {
public:
    SubList(AbstractList<T>* parent, std::size_t start, std::size_t end)
        : parent_(parent), start_(start), end_(end) {}
    T get(std::size_t i) const override {
        if (i >= size()) throw std::out_of_range("index");
        return parent_->get(start_ + i);
    }
    std::size_t size() const override { return end_ - start_; }
    T set(std::size_t i, const T& e) override {
        if (i >= size()) throw std::out_of_range("index");
        return parent_->set(start_ + i, e);
    }
private:
    AbstractList<T>* parent_;
    std::size_t start_, end_;
};

// Defined after SubList because it needs the complete type; unique_ptr gives the caller sole ownership.
template <typename T>
std::unique_ptr<AbstractList<T>> AbstractList<T>::subList(std::size_t from, std::size_t to) {
    if (from > to || to > size()) throw std::out_of_range("bad sublist range");
    return std::make_unique<SubList<T>>(this, from, to);
}
