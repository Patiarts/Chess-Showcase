#ifndef TWO_WAY_LIST_H
#define TWO_WAY_LIST_H

#include <memory>


class TwoWayList
{
public:
    TwoWayList();
    TwoWayList(const TwoWayList *from); // Constructs a copy of from.
    virtual ~TwoWayList();

    void insert_in_numerical_order(int i);
    int length() const;
    void remove_value(int i);
    bool has_value(int i);

    void insert(int i); // adds i to the list, between j<i and k>i.
    void pop_front(); // removes first element. If empty, do nothing.
    void pop_back(); // removes last element. If empty, do nothing.
    void pop_value(int i); // removes first i from list. If no i, do nothing.
    void pop_at(size_t n); // removes n:th element. If n>=size, throws range exception.

    void remove_duplicates();

    int get_at(size_t n) const; // gets n:th element. if n>= size, throws range exception.
    int find(int i) const; // returns index of i, and -1 if there is no i.
    bool has(int i) const; // returns true if i in list, false if not.
    bool empty() const; // returns true if no elements, false if yes elements.
    size_t size() const;

    void print();
private:
    struct List_item{
        int data;
        std::shared_ptr<List_item> next = nullptr;
        std::weak_ptr<List_item> prev = next;
    };

    std::shared_ptr<List_item> pop(std::shared_ptr<List_item> item); // Pops elements directly via pointers. Called by all public popper methods.

    size_t size_ = 0;
    std::shared_ptr<List_item> first_ = nullptr;
    std::weak_ptr<List_item> last_ = first_;
};

#endif // TWO_WAY_LIST_H
