#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

void clearScreen(){
    system("cls"); // Windows
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

    for (int c = 0; c < preco_str.length(); c++){
        char ch = preco_str[c];
        if (!isdigit(ch) && ch != '.' && ch != ','){
            clearScreen();
            cout << "O preco digitado é invalido!" << endl;
            return 0;
        }
    }

    for (int i = 0; i < preco_str.length(); i++){
        if (preco_str[i] == ','){
            preco_str[i] = '.';
        }
    }
    float preco = stof(preco_str);
    return preco;
}

float verificaQtd(string qtd_str){

    for (int c = 0; c < qtd_str.length(); c++){
        char ch = qtd_str[c];
        if (!isdigit(ch) && (ch != '.' && ch != ',')){
            clearScreen();
            cout<<"A quantidade digitada e invalida!"<<endl;
            return 0;
        } ;
    }

    for (int i = 0; i < qtd_str.length(); i++){
        if (qtd_str[i] == ','){
            qtd_str[i] = '.';
        }
    }
    float qtd = stof(qtd_str);
    return qtd;
}

int verificaOpcMenu(string opc_menu){
    for (int c = 0; c < opc_menu.length(); c++){
        char ch = opc_menu[c];
        if (!isdigit(ch)){
            return 0;
        }
    }
    clearScreen();
    cout<<"A opcao digitada e invalida!"<<endl;
    return stoi(opc_menu);
}

void printaProdutos(){
    vector<Produto> produtos;
    produtos = readProdutos();

    for (int i = 0; i < produtos.size(); i++){
        cout << produtos[i].nome << " - R$ " << produtos[i].preco << " x " << produtos[i].qtd_estoque << endl;
    }

    cout << "Pressione enter para continuar..." << endl;
    
    cin.get();

    cin.ignore(1000, '\n');

    clearScreen();
}

struct ItemVenda
{
    Produto produto;
    int qtd_vendida;
};

struct Venda {
    vector<ItemVenda> carrinho;
    float total = 0;

    int verificaEscolha(string escolha){
    for (int c = 0; c < escolha.length(); c++){
        char ch = escolha[c];
        if (!isdigit(ch)){
            clearScreen();
            return 0;
        }
    }
    return stoi(escolha);
}

    void exibirListaProdutos(){
        vector<Produto> produtos = readProdutos();
        for (int i = 0; i < produtos.size(); i++){
            cout << i + 1 << ". " << produtos[i].nome << endl;
        }
        cout << endl;
        cout << "pressione enter para voltar.";
        return;
    }

    void adicionarProduto(){
        vector<Produto> produtos = readProdutos();
        string busca;
        Produto produtoSelecionado;

        vector<Produto> resultados;
        do{
            clearScreen();
            cout << "Busque um produto pelo nome: ";
            cin.ignore();
            getline(cin, busca);

            for (int i = 0; i < produtos.size(); i++){
                if (produtos[i].nome.find(busca) != string::npos)
                {
                    resultados.push_back(produtos[i]);
                }
            }

            if (resultados.empty()){
            cout << "Nenhum produto encontrado. Tente novamente.\n";
            }

        } while (resultados.empty());
        
        cout << endl << "\nProdutos encontrados:\n";
        for (int i = 0; i < resultados.size(); i++){
            cout << i + 1 << ". " << resultados[i].nome << " - R$ " << resultados[i].preco << " Estoque: " << resultados[i].qtd_estoque << endl;
        }

        string escolha_str;
        int escolha = 0;
        while (true) {
            cout << "Digite o numero do produto ou 0 para buscar novamente: ";
            cin >> escolha_str;
            escolha = verificaEscolha(escolha_str);

            if (escolha == 0) {
                resultados.clear(); 
                return;
            } 
            else if (escolha > 0 && escolha <= resultados.size()) {
                produtoSelecionado = resultados[escolha - 1];
                break;
            } 
            else {
                cout << "Escolha invalida. Tente novamente.\n";
            }
        }

        //cin validado da quantidade a ser vendida do item.
        string qtd_vendida_str;
        float qtd_vendida_fl = 1;
        do {
            if (qtd_vendida_fl == 0) cout << "Quantidade digitada invalida!" << endl;
            cout << "Digite a quantidade a ser vendida (Estoque disponivel: " << produtoSelecionado.qtd_estoque << "): ";

            cin >> qtd_vendida_str;
            qtd_vendida_fl = verificaQtd(qtd_vendida_str);
            
            clearScreen();
        } while(qtd_vendida_fl == 0);
        
        //prepara o estoque do produto para ser atualizado com a função updateTabela()
        produtoSelecionado.qtd_estoque -= produtoSelecionado.qtd_estoque + qtd_vendida_fl;

        //monta o ItemVenda e adiciona ao carrinho
        ItemVenda item;
        item.produto = produtoSelecionado;
        item.qtd_vendida = qtd_vendida_fl;
        carrinho.push_back(item);
        cout << "Produto adicionado ao carrinho.\n";
    };

    void pagamento(float totalVenda) {
        int opcaoPagamento;
        cout << "\n================== Total ==================\n";
        cout << "\nTotal da compra: R$ " << totalVenda << endl;
        do {
            cout << "\n================== Pagamento ==================\n";
            cout << "Escolha a forma de pagamento:\n";
            cout << "1 - A vista (5\% de desconto)\n";
            cout << "2 - Parcelado em ate 3x sem juros\n";
            cout << "3 - Parcelado em ate 12x com 10\% de juros\n";
            cout << "Opcao: ";
            cin >> opcaoPagamento;
            if (opcaoPagamento < 1 || opcaoPagamento > 3) 
            {
                cout << "Opção invalida. Tente novamente.\n";
            }
        } while (opcaoPagamento < 1 || opcaoPagamento > 3);

        float valorFinal = totalVenda;
        int parcelas = 1;

        switch (opcaoPagamento) {
            case 1:
                valorFinal *= 0.95;
                cout << "Pagamento a vista com 5\% de desconto. Valor final: R$ " << valorFinal << endl;
                parcelas = 1;
                break;

            case 2:
                do {
                    cout << "Numero de parcelas (1 a 3): ";
                    cin >> parcelas;
                    if (parcelas < 1 || parcelas > 3)
                        cout << "Numero de parcelas invalido. Tente novamente.\n";
                } while (parcelas < 1 || parcelas > 3);
                valorFinal = totalVenda;
                break;

            case 3:
                do {
                    cout << "Numero de parcelas (4 a 12): ";
                    cin >> parcelas;
                    if (parcelas < 4 || parcelas > 12)
                        cout << "Numero de parcelas invalido. Tente novamente.\n";
                } while (parcelas < 4 || parcelas > 12);
                valorFinal = totalVenda * 1.10;
                break;
        }

        float valorParcela = valorFinal / parcelas;
        cout << "\n==================Detalhamento do pagamento:==================\n";

        time_t t = time(0);
        tm* dataAtual = localtime(&t);

        for (int i = 0; i < parcelas; i++){
            tm vencimento = *dataAtual;
            vencimento.tm_mon += i;
            mktime(&vencimento); // normaliza data

            string dia = (vencimento.tm_mday < 10 ? "0" : "") + to_string(vencimento.tm_mday);
            string mes = (vencimento.tm_mon + 1 < 10 ? "0" : "") + to_string(vencimento.tm_mon + 1);
            string ano = to_string(vencimento.tm_year + 1900);

            cout << i + 1 << "a parcela: R$ " << valorParcela 
                << " - Vencimento: " << dia << "/" << mes << "/" << ano << endl;
        }
    };

    void finalizarVenda(){
        if(carrinho.size() == 0){
            cout << "Nenhum produto adicionado ao carrinho.\n";
            cout << "Pressione Enter para voltar ao menu...";
            cin.ignore();
            cin.get();
            return;
        }

        float total = 0;

        cout << "\n================== Resumo da Venda ==================\n";
        for (int i = 0; i < carrinho.size(); i++){
            ItemVenda item = carrinho[i];
            updateProdutos(item.produto);
            float subtotal = item.produto.preco * item.qtd_vendida;
            total += subtotal;
            cout << item.produto.nome << " - R$ " << item.produto.preco << " x " << item.qtd_vendida << " = R$ " << subtotal << endl;
        }
        pagamento(total);
        cout << "\nPressione Enter para voltar ao menu...";
        cin.ignore();
        cin.get();
    };
};


//Funções de tela.
void setMenuOption(int &opcaoMenu)
{
    string opcao_menu_str;
    do{
        clearScreen();
    
    cout << "===========================================================\n"
         << "|                                                         |\n"
         << "|                    (1) Cadastro                         |\n"
         << "|                    (2) Venda                            |\n"
         << "|                    (3) Sair                             |\n"
         << "|                                                         |\n"
         << "===========================================================\n";

        cout << "Selecione uma das opcoes:  ";
        cin >> opcao_menu_str;
        opcaoMenu = verificaOpcMenu(opcao_menu_str);
    }while(opcaoMenu < 1 || opcaoMenu > 3);
}

void cadastrarProduto(){

    clearScreen();
    int opcaoMenu = -1;
    string nome, preco, qtd_estoque;

    Produto produto;

    do{
    cout << "Cadastro de produto selecionado" << endl;
    cout << "Digite os dados do produto a ser cadastrado..."<< endl;
    cout << "Nome: ";
    getline(cin, nome);
    produto.nome = verificaNome(nome);
    clearScreen();
    }while(produto.nome.length() == 0);
    
    do{
    cout << "Preco:";
    cin >> preco;
    produto.preco = verificaPreco(preco);
    }while(produto.preco == 0);
    clearScreen();

    do{
    cout << "Quantidade: ";
    cin >> qtd_estoque;
    produto.qtd_estoque = verificaQtd(qtd_estoque);
    }while(produto.qtd_estoque == 0);
    clearScreen();

    handleProdutos(produto);

    cout << "Produto " << produto.nome << " cadastrado com sucesso!"<<endl<<endl;
    cout << "Escolha uma opcao: "<< endl;
    cout << "1 - Cadastrar novo produto"<< endl;
    cout << "2 - Voltar para o menu"<<endl;
    cin >> opcaoMenu;

    if (opcaoMenu == 1){
        cadastrarProduto();
    }
}

void venderProduto(){
    Venda venda;
    string opcao_venda;
    int opcao_venda_int;

        do{     

        clearScreen();
        cout << "(1) Exibir lista de produtos"<<endl;
        cout << "(2) Adicionar novo produto"<<endl;
        cout << "(3) Finalizar venda"<<endl;
        cout << "(4) Cancelar venda"<<endl;

        cin >> opcao_venda;
        opcao_venda_int = verificaOpcMenu(opcao_venda);

        switch (opcao_venda_int){
            case 1:
            printaProdutos();
            break;

            case 2:
            venda.adicionarProduto();
            break;

            case 3:
            venda.finalizarVenda();
            break;

            case 4:
            break;
        }
        } while(opcao_venda_int != 3 && opcao_venda_int != 4);
    }   

int main()
{
    int opcaoMenu = -1;
    bool deveFechar = false;

    while (deveFechar == false)
    {
        clearScreen();
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