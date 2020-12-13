#include <iostream>
#include "SmartPointer.h"
#include "Tab.h"

#include "print.h"

void pointersTest()
{
    SmartPointer<int> pointer(new int(8));
    print("value pointer is pointing at:\t" << *pointer);

    //creating a separate block just for pointer1
    {
        print("<block>");
        SmartPointer<int> pointer1 = pointer;
        print("value pointer1 is pointing at:\t" << *pointer1);

        //incrementing value of pointer to prove value of pointer1 will also increment
        (*pointer)++;
        print("value pointer1 is pointing at:\t" << *pointer1);
        print("</block>");
    }
    SmartPointer<int> pointer2(new int(12));
    pointer2 = pointer;
    print("value pointer2 is pointing at:\t" << *pointer2);
    print("value pointer is pointing at:\t" << *pointer);
}

int main() {
//    print("\n\n\n");
//    pointersTest();
//    print("\n\n\n");

    Tab tab;
    Tab other;
    print("tab");
    tab.toString();
    print("other");
    other.toString();
    tab = std::move(other);
    print("tab");
    tab.toString();
    print("other (empty after moving):");
    other.toString();

    return 0;
}
