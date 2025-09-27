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
    float qtd_estoque;
};


//função que substitui a virgula pelos caracteres de escape
string escaparVirgula(const string &campo)
{
    string resultado = campo;
    int pos = 0;
    while ((pos = resultado.find(",", pos)) != string::npos)
    {
        resultado.replace(pos, 1, "$##");
        pos += 3; // pula o tamanho da sequência
    }
    return resultado;
}

//função que substitui os caracteres de escape pela virgula
string desescaparVirgula(const string &campo)
{
    string resultado = campo;
    int pos = 0;
    while ((pos = resultado.find("$##", pos)) != string::npos)
    {
        resultado.replace(pos, 3, ",");
        pos += 1;
    }
    return resultado;
}

void writeTabela(string table, vector<string> celulas){
    ofstream writer(table, ios::app);
    for (int i = 0; i < celulas.size() ; i++){
        writer << escaparVirgula(celulas[i]);
        //se for a ultima celula ele não escreve a virgula, deixando o final da linha somente com a quebra.
        if (i < celulas.size() - 1){
            writer << ',';
        }
    }
    writer << endl;
    writer.close();
}

void replaceTabela(string table, vector<vector<string>> vetCelulas){
    ofstream writer(table);
    vector<string> celula;
    
    for (int i = 0; i < vetCelulas.size() ; i++){
        for (int j = 0; j < vetCelulas[i].size(); j++){
            writer << vetCelulas[i][j];
            if (j < vetCelulas[i].size() - 1){
                writer << ',';
            }
        }
        writer << endl;        
    }
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
                celulas.push_back(desescaparVirgula(valorCelula));
                valorCelula = "";
            }
            else
            {
                valorCelula.push_back(currentChar);
            }
        }
        celulas.push_back(desescaparVirgula(valorCelula));
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
    writeTabela("produtos.txt", celulas);
}

void updateProdutos(Produto produto){
    vector<vector<string>> produtos;
    produtos = readTabela("produtos.txt");

    for (int i = 0; i < produtos.size(); i++){
        if (produtos[i][0] == produto.nome){
            produtos[i][1] = to_string(produto.preco);
            produtos[i][2] = to_string(stof(produtos[i][2]) + produto.qtd_estoque);
        }
    }
    replaceTabela("produtos.txt", produtos);
}

vector<Produto> readProdutos(){
    vector<Produto> produtos;
    vector<vector<string>> produtosNaoFormatados;

    produtosNaoFormatados = readTabela("produtos.txt");

    for (int i = 0; i < produtosNaoFormatados.size(); i++)
    {
        Produto produto;
        produto.nome = produtosNaoFormatados[i][0];
        produto.preco = stof(produtosNaoFormatados[i][1]);
        produto.qtd_estoque = stof(produtosNaoFormatados[i][2]);

        produtos.push_back(produto);
    }

    return produtos;
}


//Funções de formatação e verificação dos cadastros.
void handleProdutos(Produto produto){
    vector<Produto> produtos = readProdutos();
    bool isNew = true;

    //verifica se é um novo produto.
    for (int i = 0; i < produtos.size(); i++){
        if (produto.nome == produtos[i].nome){
            isNew = false;
            i = produtos.size();
        }else{
            isNew = true;
        }
    }
    
    if (isNew){
        writeProdutos(produto);
    }else{
        updateProdutos(produto);
    }

}

string verificaNome(string nome){
    return nome;
}

float verificaPreco(string preco_str){
    for (int i = 0; i < preco_str.length(); i++){
        if (preco_str[i] == ','){
            preco_str[i] = '.';
        }
    }
    float preco = stof(preco_str);
    return preco;
}

float verificaQtd(string qtd_str){
    for (int i = 0; i < qtd_str.length(); i++){
        if (qtd_str[i] == ','){
            qtd_str[i] = '.';
        }
    }
    float qtd = stof(qtd_str);
    return qtd;
}


//Funções de tela.
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

    string nome, preco, qtd_estoque;

    Produto produto;
    cout << "Cadastro de produto selecionado" << endl;
    cout << "Digite os dados do produto a ser cadastrado..."<< endl;
    cout << "Nome: "<< endl;
    cin >> nome;
    cout << "Preço: "<< endl;
    cin >> produto.preco;
    cout << "Quantidade: "<< endl;
    cin >> produto.qtd_estoque;

    handleProdutos(produto);
    
    // string teste = "produtos.txt";
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