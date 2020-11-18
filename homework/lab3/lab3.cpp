// lab3.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "NodeStatic.cpp"
#include "NodeDynamic.cpp"
#include "TreeDynamic.h"
#include "TreeStatic.cpp"

void v_tree_test();
void v_tree_test_dynamic();
int main()
{
    v_tree_test();
	v_tree_test_dynamic();

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
// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
