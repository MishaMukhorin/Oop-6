//
// Created by Misha on 16.05.2024.
//

#include "CStringList.h"


int main() {
    CStringList list;
    list.AddToEnd("Hello");
    list.AddToEnd("World");
    list.AddToBeginning("Start");

    for (const auto& str : list) {
        std::cout << str << std::endl;
    }

    return 0;
}
