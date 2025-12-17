#include "list.hh"
#include <iostream>

List::List(){}


List::~List()
{
    if(!empty()){
        last_->next = nullptr;
        }
}

void List::insert_at_the_beginning(int i)
{
    first_ = std::make_shared<List_item>(List_item{i, first_});
    if (empty()){
        last_ = first_;
    }
    last_->next = first_;
    size_++;
}

void List::insert_at_the_end(int i)
{
    if (empty()){
        insert_at_the_beginning(i);
        return;
    }
    last_->next = std::make_shared<List_item>(List_item{i, first_});
    last_ = last_->next;
    size_++;
}

void List::remove_first()
{
    if (empty()){
        return;
    }
    if (size_ == 1){
        last_->next = nullptr;
        first_ = nullptr;
        last_ = nullptr;
    }
    else{
        first_ = first_->next;
        last_->next = first_;
    }
    size_--;
}

void List::remove_last()
{
    if (empty()){
        return;
    }
    std::shared_ptr<List_item> second_to_last = first_;
    while(second_to_last->next != last_){
        second_to_last = second_to_last->next;
    }
    second_to_last->next = first_;
    last_ = second_to_last;
    size_--;
}

void List::print()
{
    if (empty()){
        std::cout << "No elements" << std::endl;
        return;
    }
    std::cout << "List elements: ";
    std::shared_ptr<List_item> current = first_;
    while(current->next != first_){
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << current->data << std::endl;
}

bool List::empty()
{
    return size_ == 0;
}


