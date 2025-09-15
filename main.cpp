#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");   // Windows
#else
    system("clear"); // Linux/Mac
#endif
}

struct Produto{
    string nome;
    string preco;    
};

//Função usada para formatar o arquivo produtos em uma struct Produto. Usada pelo readProdutos()
Produto separaCamposProd(string linha) {
    Produto prod;
    string campo;
    int prodIndex = 0;

    for (int c = 0; c < linha.length(); c++) {
        char letra = linha[c];
        if (letra == ',') {
            if (prodIndex == 0) {
                prod.nome = campo;
            } else if (prodIndex == 1) {
                prod.preco = campo;
            }
            campo = "";
            prodIndex++;
        } else {
            campo += letra;
        }
    }

    if (prodIndex == 1) {
        prod.preco = campo;
    }

    return prod;
}

vector<Produto> readProdutos(string table){
        vector<Produto> produtos;
        string linha;
        fstream reader(table);
        while (getline(reader, linha)) {
        Produto prodFormatado = separaCamposProd(linha);
        produtos.push_back(prodFormatado);
        }
        reader.close();
        return produtos;
    }



void setMenuOption(int &opcaoMenu)
{
    // clearScreen();
    cout << "===========================================================\n"
         << "|                                                         |\n"
         << "|                    (1) Cadastro                         |\n"
         << "|                    (2) Venda                            |\n"
         << "|                    (3) Sair                             |\n"
         << "|                                                         |\n"
         << "===========================================================\n";

    cin >> opcaoMenu;
}

void cadastrarProduto()
{
    cout << "Cadastro de produto selecionado" << endl;

    // string teste = "produtos.csv";
    // readProdutos(teste);
}

void venderProduto(vector<Produto> produtos)
{
    cout << "Venda de produto selecionada" << endl;
    cout << produtos[0].nome << endl;
    cout << produtos[1].nome << endl;
}

int main()
{
    vector<Produto> produtos = readProdutos("produtos.csv");
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
            venderProduto(produtos);
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