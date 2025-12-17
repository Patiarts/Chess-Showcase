#include <iostream>
#include "two_way_list.hh"

TwoWayList::TwoWayList(){}

TwoWayList::TwoWayList(const TwoWayList *from){
    int from_size = from->size();
    for(int i = from_size-1; i >= 0; i--){
        insert(from->get_at(i));
    }
}

TwoWayList::~TwoWayList(){}

void TwoWayList::insert_in_numerical_order(int i)
{
    insert(i);
}

int TwoWayList::length() const
{
    return size_;
}

void TwoWayList::remove_value(int i)
{
    pop_value(i);
}

bool TwoWayList::has_value(int i)
{
    return has(i);
}

void TwoWayList::insert(int i)
{
    std::shared_ptr<List_item> new_item = std::make_shared<List_item>(List_item{i});
    if (empty()){
        first_ = new_item;
        last_ = new_item;
        size_++;
        return;
    }

    std::shared_ptr<List_item> first_geq = first_;
    while(first_geq->data < i){
        first_geq = first_geq->next;
        if (first_geq == nullptr){
            new_item->prev = last_;
            last_.lock()->next = new_item;
            last_ = new_item;
            size_++;
            return;
        }
    }

    if (first_geq == first_){
        first_ = new_item;
    }
    else{
        first_geq->prev.lock()->next = new_item;
    }

    new_item->next = first_geq;
    new_item->prev = first_geq->prev;
    first_geq->prev = new_item;

    size_++;
}

void TwoWayList::pop_front()
{
    if (empty()){
        return;
    }
    pop(first_);
}

void TwoWayList::pop_back()
{
    if (empty()){
        return;
    }
    pop(last_.lock());
}

void TwoWayList::pop_value(int i)
{
    if (empty()){
        return;
    }

    std::shared_ptr<List_item> i_tem = first_;
    while(i_tem->data != i){
        if (i_tem->next == nullptr){
            return;
        }
        i_tem = i_tem->next;
    }
    pop(i_tem);
}

void TwoWayList::pop_at(size_t n)
{
    if (n >= size_){
        throw std::range_error("invalid TwoWayList index");
    }

    std::shared_ptr nth = first_;
    for(size_t i = 0; i < n; i++){
        nth = nth->next;
    }
    pop(nth);
}

void TwoWayList::remove_duplicates()
{
    if(empty()){
        return;
    }
    std::shared_ptr<List_item> current = first_;
    while(current->next != nullptr){
        (current->data == current->next->data)? current = pop(current) : current=current->next;
    }
}

int TwoWayList::get_at(size_t n) const
{
    if (n >= size_){
        throw std::range_error("invalid TwoWayList index");
    }

    std::shared_ptr nth = first_;
    for(size_t i = 0; i < n; i++){
        nth = nth->next;
    }
    return nth->data;
}

int TwoWayList::find(int i) const
{
    if (empty()){
        return -1;
    }

    int inx = 0;
    std::shared_ptr<List_item> i_tem = first_;
    while(i_tem->data != i){
        i_tem = i_tem->next;
        if (i_tem == nullptr){
            return -1;
        }
        inx++;
    }
    return inx;
}

bool TwoWayList::has(int i) const
{
    return find(i) >= 0;
}

bool TwoWayList::empty() const
{
    return size_ == 0;
}

size_t TwoWayList::size() const
{
    return size_;
}

void TwoWayList::print()
{
    int count = 0;
    std::cout << "Size " << size_ << ": [";
    std::shared_ptr<List_item> current = first_;
    while(current != nullptr){
        count++;
        std::cout << current->data;
        current = current->next;
        if (current != nullptr){
            std::cout << ", ";
        }
        else{break;}
    }
    std::cout << "]: Count " << count << std::endl << std::endl;
}

std::shared_ptr<TwoWayList::List_item> TwoWayList::pop(std::shared_ptr<List_item> item)
{
    if (item == first_){
        first_ = (size_ > 1)? first_->next : nullptr;
    }
    else if (item == last_.lock() && size_ == 1){
        first_ = nullptr;
    }
    else if (item == last_.lock()){
        last_ = last_.lock()->prev;
        last_.lock()->next = nullptr;
    }
    else{
        item->prev.lock()->next = item->next;
        item->next->prev = item->prev;
    }
    size_--;
    return item->next;
}



