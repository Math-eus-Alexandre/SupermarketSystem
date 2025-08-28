#include <iostream>
using namespace std;

void setMenuOption(int &opcaoMenu)
{
    cout << "===========================================================\n"
         << "|                                                         |\n"
         << "|                    (1) Cadastro                         |\n"
         << "|                    (2) Venda                            |\n"
         << "|                    (3) Sair                             |\n"
         << "|                                                         |\n"
         << "===========================================================\n";

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