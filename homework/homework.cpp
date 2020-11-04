// homework.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>


const int FIVE = 5;

bool b_alloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY);
bool b_fill_table_2_dim(int*** piTable, int iSizeX, int iSizeY);
bool b_dealloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY);
void v_alloc_table_add_5(int iSize);
int main()
{
    int** piTable = NULL;
    int iSizeX = 3;
    int iSizeY = 5;
    //b_alloc_table_2_dim(&piTable, iSizeX, iSizeY);
    //b_fill_table_2_dim(&piTable, iSizeX, iSizeY);
    //b_dealloc_table_2_dim(&piTable, iSizeX, iSizeY);

    v_alloc_table_add_5(6);
    return 0;
}

bool b_alloc_table_2_dim(int *** piTable, int iSizeX, int iSizeY)
{
    *piTable = new int * [iSizeX];
    for (int i = 0; i < iSizeX; i++)
    {
        (*piTable)[i] = new int[iSizeY];
    }
    return true;
}

bool b_fill_table_2_dim(int*** piTable, int iSizeX, int iSizeY)
{
    int counter = 0;
    for (int i = 0; i < iSizeX; i++)
    {
        for (int j = 0; j < iSizeY; j++)
        {
            (*piTable)[i][j] = counter++ + FIVE;
            std::cout << (*piTable)[i][j] << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return true;
}

bool b_dealloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY)
{
    for (int i = 0; i < iSizeX; i++)
    {
        delete [] (*piTable)[i];
    }
    delete [] *piTable;
    return true;
}

void v_alloc_table_add_5(int iSize)
{
    int* table = new int[iSize];
    //normal order
   /* for (int i = 0; i < iSize; i++)
    {
        table[i] = i + FIVE;
        std::cout << table[i] << ", ";
    }*/
    
    //reversed order
    for (int i = iSize - 1; i >=0; i--)
    {
        table[i] = i + FIVE;
        std::cout << table[i] << ", ";
    }
    std::cout << std::endl;
    delete [] table;
}



// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
