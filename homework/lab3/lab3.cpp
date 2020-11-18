// lab3.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "NodeStatic.cpp"
#include "NodeDynamic.cpp"
#include "TreeDynamic.cpp"
#include "TreeStatic.cpp"

void v_tree_test();
void v_tree_test_dynamic();
void swap_test();
void swap_test_dynamic();
void count_test();

int main()
{
    v_tree_test();
	v_tree_test_dynamic();
    swap_test();
    swap_test_dynamic();
    count_test();
}

void v_tree_test()
{
    NodeStatic<int> c_root;
    c_root.addNewChild();
    c_root.addNewChild();
	
    c_root.getChild(0)->setValue(1);
    c_root.getChild(1)->setValue(2);
	
    c_root.getChild(0)->addNewChild();
    c_root.getChild(0)->addNewChild();
	
    c_root.getChild(0)->getChild(0)->setValue(11);
    c_root.getChild(0)->getChild(1)->setValue(12);
	
    c_root.getChild(1)->addNewChild();
    c_root.getChild(1)->addNewChild();
	
    c_root.getChild(1)->getChild(0)->setValue(21);
    c_root.getChild(1)->getChild(1)->setValue(22);

    cout << "all below" << endl;
    c_root.printAllBelow();
    cout <<endl<< "all up" << endl;
    c_root.getChild(0)->getChild(1)->printUp();
    cout<<endl;
}//void v_tree_test()

void v_tree_test_dynamic()
{
    NodeDynamic c_root;
    c_root.addNewChild();
    c_root.addNewChild();

    c_root.getChild(0)->setValue(1);
    c_root.getChild(1)->setValue(2);

    c_root.getChild(0)->addNewChild();
    c_root.getChild(0)->addNewChild();

    c_root.getChild(0)->getChild(0)->setValue(11);
    c_root.getChild(0)->getChild(1)->setValue(12);

    c_root.getChild(1)->addNewChild();
    c_root.getChild(1)->addNewChild();

    c_root.getChild(1)->getChild(0)->setValue(21);
    c_root.getChild(1)->getChild(1)->setValue(22);

    cout << "all below" << endl;
    c_root.printAllBelow();

    c_root.~NodeDynamic();
}//void v_tree_test()

void swap_test()
{

    NodeStatic<int> c_root;
    c_root.addNewChild();
    c_root.addNewChild();

    c_root.getChild(0)->setValue(1);
    c_root.getChild(1)->setValue(2);

    c_root.getChild(0)->addNewChild();
    c_root.getChild(0)->addNewChild();

    c_root.getChild(0)->getChild(0)->setValue(11);
    c_root.getChild(0)->getChild(1)->setValue(12);

    c_root.getChild(1)->addNewChild();
    c_root.getChild(1)->addNewChild();

    c_root.getChild(1)->getChild(0)->setValue(21);
    c_root.getChild(1)->getChild(1)->setValue(22);

    TreeStatic<int> treeStatic;
    treeStatic.moveSubTree(treeStatic.getRoot(), c_root, c_root);
    cout<<endl<<"printing the tree"<<endl;
    treeStatic.printTree();
}

void swap_test_dynamic()
{
    NodeDynamic c_root;
    c_root.addNewChild();
    c_root.addNewChild();

    c_root.getChild(0)->setValue(1);
    c_root.getChild(1)->setValue(2);

    c_root.getChild(0)->addNewChild();
    c_root.getChild(0)->addNewChild();

    c_root.getChild(0)->getChild(0)->setValue(11);
    c_root.getChild(0)->getChild(1)->setValue(12);

    c_root.getChild(1)->addNewChild();
    c_root.getChild(1)->addNewChild();

    c_root.getChild(1)->getChild(0)->setValue(21);
    c_root.getChild(1)->getChild(1)->setValue(22);

    cout <<endl<< "all below" << endl;
    c_root.printAllBelow();

    TreeDynamic treeDynamic;
    treeDynamic.moveSubTree(treeDynamic.getRoot(), &c_root, &c_root);
    cout<<endl<<"printing tree dynamic"<<endl;
    treeDynamic.printTree();

    c_root.~NodeDynamic();
}

void count_test()
{
    NodeStatic<int> c_root;
    c_root.addNewChild();
    c_root.addNewChild();

    c_root.getChild(0)->setValue(3);
    c_root.getChild(1)->setValue(4);

    c_root.getChild(0)->addNewChild();
    c_root.getChild(0)->addNewChild();

    c_root.getChild(0)->getChild(0)->setValue(11);
    c_root.getChild(0)->getChild(1)->setValue(4);

    c_root.getChild(1)->addNewChild();
    c_root.getChild(1)->addNewChild();

    c_root.getChild(1)->getChild(0)->setValue(4);
    c_root.getChild(1)->getChild(1)->setValue(22);

    cout <<endl<< "all below" << endl;
    c_root.printAllBelow();
    cout<<endl;
    cout << "amount of times 4 is repeated: ";
    cout << c_root.countOccurrences(4) << endl;
    cout << "amount of times 22 is repeated: ";
    cout << c_root.countOccurrences(22) << endl;
}