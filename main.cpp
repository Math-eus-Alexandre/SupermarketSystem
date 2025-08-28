#include <iostream>
using namespace std;

void setMenuOption(int &opcaoMenu)
{
    cout << "Insira uma opção do menu";
    cin >> opcaoMenu;
}

void cadastrarProduto()
{
    cout << "Cadastro de produto selecionado";
}

void venderProduto()
{
    cout << "Venda de produto selecionada";
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
            cadastrarProduto();
            break;
        }
        case 2:
        {
            venderProduto();
            break;
        }
        case 3:
        {
            deveFechar = true;
            break;
        }
        }
    }

    return 0;
}