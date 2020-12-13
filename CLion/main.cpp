#include <iostream>
#include "SmartPointer.h"
#include "Tab.h"

#include "print.h"
#include "CTable.h"

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

    void tabTest()
    {
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
    }

    void cTableTest()
    {
        {
            CTable tab1("1", 5);
            CTable tab2("2", 7);
            CTable tab3("3", 8);

            tab1.vPrint();
            tab2.vPrint();
            tab3.vPrint();

            //tab3 = tab1 + tab2;

            tab3.vPrint();

            tab3--.vPrint();
        }
        {
            CTable c_tab_0, c_tab_1;
            c_tab_0.bSetNewSize(6);
            c_tab_1.bSetNewSize(4);
            /* initialize table */

            print("adding value to tab1 after it is moved");
            c_tab_1.vSetValueAt(2, 123);
            print("tab0");
            c_tab_0.vPrint();
            print("tab1");
            c_tab_1.vPrint();
            c_tab_1 = c_tab_1 + c_tab_1;
            print("tab1 = tab1 + tab1");
            c_tab_1.vPrint();
            c_tab_0 = std::move(c_tab_1);
            print("tab0 after moving tab1 to it");
            c_tab_0.vPrint();
        }
    }

int main() {
    print("\n\n\n");
    pointersTest();
    print("\n\n\n");
    print("\n\n\n");
    tabTest();
    print("\n\n\n");
    print("\n\n\n");
    cTableTest();
    print("\n\n\n");
    return 0;
}
