#include <iostream>
#include "two_way_list.hh"

int main()
{
    TwoWayList listA = TwoWayList();


    std::string input_string = "";
    while(true){
        std::cout << "Add to A: ";
        getline(std::cin, input_string);

        if (input_string.empty()){
            break;
        }

        listA.insert(stoi(input_string));
        listA.print();
    }


    std::cout << "Creating B as copy of A... ";
    TwoWayList listB = TwoWayList(&listA);
    std::cout << "Done!" << std::endl;
    listB.print();

    std::cout << "Removing duplicates from B... ";
    listB.remove_duplicates();
    std::cout << "Done!" << std::endl;
    listB.print();

    std::cout << "Removing first and last from B... ";
    listB.pop_front();
    listB.pop_back();
    std::cout << "Done!" << std::endl;
    listB.print();



    while(true){
        std::cout << "Pop from A at: ";
        getline(std::cin, input_string);

        if (input_string.empty()){
            break;
        }

        listA.pop_at(stoi(input_string));
        listA.print();
    }


    while(true){
        std::cout << "Find in A: ";
        getline(std::cin, input_string);

        if (input_string.empty()){
            break;
        }
        if (listA.has(stoi(input_string))){
            std::cout << listA.find(stoi(input_string)) << std::endl << std::endl;
        }
        else{
            std::cout << "no " << stoi(input_string) << " in A" << std::endl << std::endl;
        }
    }


    std::cout << "List A empty? " << listA.empty() << ". List B empty? " << listB.empty() << "." << std::endl << std::endl;
}
