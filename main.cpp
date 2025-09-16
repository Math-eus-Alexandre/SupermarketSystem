#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void clearScreen()
{
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Linux/Mac
#endif
}

struct Produto
{
    string nome;
    float preco;
};

vector<vector<string>> readTabela(string table)
{
    vector<vector<string>> registros;
    fstream reader(table);
    string linha;

    while (getline(reader, linha))
    {
        vector<string> celulas;
        string valorCelula;

        for (int i = 0; i < linha.length(); i++)
        {
            char currentChar = linha[i];

            if (currentChar == ',')
            {
                celulas.push_back(valorCelula);
                valorCelula = "";
            }
            else
            {
                valorCelula.push_back(currentChar);

                // Se for o último caracter, salva a palavra armazenada na lista de células
                if (i == linha.length() - 1)
                {
                    celulas.push_back(valorCelula);
                }
            }
        }

        registros.push_back(celulas);
    }
    reader.close();

    return registros;
}

vector<Produto> readProdutos()
{
    vector<Produto> produtos;
    vector<vector<string>> produtosNaoFormatados;

    produtosNaoFormatados = readTabela("produtos.csv");

    for (int i = 0; i < produtosNaoFormatados.size(); i++)
    {
        cout << produtosNaoFormatados[i][1] << endl;
        Produto produto;
        produto.nome = produtosNaoFormatados[i][0];
        produto.preco = stof(produtosNaoFormatados[i][1]);

        produtos.push_back(produto);
    }

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
    vector<Produto> produtos = readProdutos();

    for (int i = 0; i < produtos.size(); i++)
    {
        Produto produto = produtos[i];
        cout << "Produto:" << endl
             << "Nome: " << produto.nome << " Preco: " << produto.preco << endl;
    }

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