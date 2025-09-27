#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void clearScreen(){
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Linux/Mac
#endif
}

//Structs:
struct Produto
{
    string nome;
    float preco;
    int qtd_estoque;
};

//Funções de Leitura e escrita em arquivos.
void writeTabela(string table, vector<string> celulas){
    ofstream writer(table, ios::app);
    for (int i = 0; i < celulas.size() ; i++){
        writer << celulas[i];
        //se for a ultima celula ele não escreve a virgula, deixando o final da linha somente com a quebra.
        if (i < celulas.size() - 1){
            writer << ',';
        }
    }
    writer << endl;
    writer.close();
}

vector<vector<string>> readTabela(string table)
{
    vector<vector<string>> registros;
    ifstream reader(table);
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


//Funções de gravação e leitura estruturadas para cada arquivo.

//Produtos
void writeProdutos(Produto produto){
    vector<string> celulas;
    celulas.push_back(produto.nome);
    celulas.push_back(to_string(produto.preco));
    celulas.push_back(to_string(produto.qtd_estoque));
    writeTabela("produtos.csv", celulas);
}

vector<Produto> readProdutos(){
    vector<Produto> produtos;
    vector<vector<string>> produtosNaoFormatados;

    produtosNaoFormatados = readTabela("produtos.csv");

    for (int i = 0; i < produtosNaoFormatados.size(); i++)
    {
        Produto produto;
        produto.nome = produtosNaoFormatados[i][0];
        produto.preco = stof(produtosNaoFormatados[i][1]);
        produto.qtd_estoque = stoi(produtosNaoFormatados[i][2]);

        produtos.push_back(produto);
    }

    return produtos;
}


//Funções de formatação e verificação dos cadastros.
void handleProdutos(Produto novo_produto){
    vector<Produto> produtos = readProdutos();
    bool isNew = true;

    for (int i = 0; i < produtos.size(); i++){
        if (novo_produto.nome == produtos[i].nome){
            isNew = false;
            i = produtos.size();
        }else{
            isNew = true;
        }
    }
    
    if (isNew){
        writeProdutos(novo_produto);
    }else{
        cout<<"produto já existe";
    }

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

void cadastrarProduto(){

    Produto produto;
    cout << "Cadastro de produto selecionado" << endl;
    cout << "Digite os dados do produto a ser cadastrado, sendo esses Nome, Preco e Quantidade de entrada: " << endl;
    cin >> produto.nome >> produto.preco >> produto.qtd_estoque;

    handleProdutos(produto);
    
    // string teste = "produtos.csv";
    // readProdutos(teste);
}

void venderProduto()
{
    vector<Produto> produtos = readProdutos();
    cout << "Venda de produto selecionada" << endl;
    cout << produtos[0].nome << endl;
    cout << produtos[1].nome << endl;
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