//
// Created by Misha on 16.05.2024.
//

#include <deque>
#include "CStringList.h"
int main() {
    std::deque<int> myDeque = {1, 2, 3, 4, 5};

    // Get an iterator to the past-the-end element
    auto it = myDeque.end();

    // Decrement the iterator to point to the last element
    --it;

    // Now it points to the last element, we can dereference it
    std::cout << "Last element: " << *it << std::endl;

    return 0;
}
//
//int main() {
//    CStringList list;
//    list.AddToEnd("Hello");
//    list.AddToEnd("World");
//    list.AddToBeginning("Start");
//
//    for (const auto& str : list) {
//        std::cout << str << std::endl;
//    }
//
//    return 0;
//}
