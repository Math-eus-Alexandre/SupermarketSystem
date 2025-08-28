#include <iostream>
using namespace std;

void setMenuOption(int &opcaoMenu)
{
    cout << "Insira uma opção do menu";
    cin >> opcaoMenu;
}

int main()
{
    int opcaoMenu = -1;
    bool deveFechar = false;

    while (deveFechar == false)
    {
        setMenuOption(opcaoMenu);

        switch (opcaoMenu)
        {
        case 1:
        {
            break;
        }
        }
    }
    cout << "Hello World";

    return 0;
}