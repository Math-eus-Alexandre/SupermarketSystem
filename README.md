# Sistema de Supermercado

**Alunos:** 
Matheus Alexandre Santos
Carlos Deucher
Carlos Eduardo

---

## Descrição do Projeto

Este projeto foi desenvolvido como parte da avaliação do curso de **Ciência da Computação**, turma 2025/I, da Universidade do Vale do Itajaí (Univali), campus Itajaí. A disciplina é ministrada pelo Professor Poffo.

O objetivo é criar um sistema de gerenciamento para um supermercado, permitindo o cadastro e a venda de produtos de forma contínua, com persistência de dados em arquivo.

---

## Funcionalidades Principais

O sistema opera em um loop contínuo, retornando sempre ao menu principal após a conclusão de uma operação (cadastro ou venda), simulando o funcionamento durante um expediente completo.

### 1. Cadastro de Produtos

Ao selecionar a opção de cadastro, o sistema solicitará as seguintes informações sobre o produto:

* **Nome do produto:** Identificação textual do item.
* **Quantidade:** Número de unidades a serem adicionadas ao estoque.
* **Valor de venda:** Preço unitário do produto.

**Regra de Negócio:** Antes de cadastrar um novo item, o sistema verifica se o produto já existe no estoque (utilizando `structs` para a modelagem dos dados).
* **Se o produto já existe:** A quantidade em estoque será atualizada (somando a quantidade existente com a nova) e o valor de venda será substituído pelo valor mais recente informado.
* **Se o produto não existe:** Um novo item será criado e adicionado ao inventário.

### 2. Venda de Produtos

Nesta seção, o usuário pode simular o caixa de uma venda.

* O usuário informa o nome do produto e a quantidade desejada (que pode ser fracionada, como em vendas por quilo).
* O sistema permite adicionar múltiplos produtos ao mesmo carrinho de compras.
* Ao finalizar a seleção de produtos, o valor total da compra é exibido.

#### Formas de Pagamento

Após a apresentação do valor total, o usuário deve escolher uma das seguintes formas de pagamento:

1.  **À vista:** Concede um desconto de 5% sobre o valor total.
2.  **Parcelado em até 3x:** O valor total é dividido em até 3 parcelas sem juros.
3.  **Parcelado em até 12x:** O valor total é acrescido de 10% de juros e dividido em até 12 parcelas.

Ao final, o sistema exibirá o detalhamento dos pagamentos, incluindo o valor de cada parcela e a respectiva data de vencimento, calculada a partir da data atual do sistema.

---

## Requisitos Técnicos e Observações

* **Persistência de Dados:** O programa carrega os dados de produtos de um arquivo `.txt` ao ser iniciado e salva as atualizações (após cadastros ou vendas) de volta no mesmo arquivo para garantir que as informações não sejam perdidas.
* **Navegação e Usabilidade:** A interface é construída com menus claros e oferece opções para o usuário cancelar uma operação a qualquer momento, retornando ao menu principal.
* **Operação Contínua:** O sistema foi projetado para permanecer em execução, voltando ao menu inicial após cada operação finalizada, seja ela um cadastro ou uma venda.
* **Atenção aos Prazos:** Este projeto deve ser entregue na data estipulada na avaliação.

# Supermarket System

**Students:** 
Matheus Alexandre Santos
Carlos Deucher
Carlos Eduardo

---

## Project Description

This project was developed as an assignment for the **Computer Science** course, class of 2025/I, at the University of Vale do Itajaí (Univali), Itajaí campus, under the supervision of Professor Poffo.

The goal is to create a management system for a supermarket, allowing for continuous product registration and sales, with data persistence in a file.

---

## Main Features

The system operates in a continuous loop, always returning to the main menu after an operation (registration or sale) is completed, simulating its use throughout a full workday.

### 1. Product Registration

When the registration option is selected, the system will ask for the following product information:

* **Product name:** The text identifier for the item.
* **Quantity:** The number of units to be added to the stock.
* **Sale price:** The unit price of the product.

**Business Rule:** Before registering a new item, the system checks if the product already exists in the inventory (using `structs` for data modeling).
* **If the product already exists:** The stock quantity will be updated (by adding the existing amount to the new one), and the sale price will be replaced with the most recent price provided.
* **If the product does not exist:** A new item will be created and added to the inventory.

### 2. Product Sales

In this section, the user can simulate a sales checkout process.

* The user provides the product name and the desired quantity (which can be a fractional number, for items sold by weight).
* The system allows multiple products to be added to the same shopping cart.
* After finalizing the product selection, the total purchase amount is displayed.

#### Payment Methods

After the total amount is presented, the user must choose one of the following payment methods:

1.  **Upfront:** Grants a 5% discount on the total amount.
2.  **Installments up to 3x:** The total amount is divided into up to 3 interest-free installments.
3.  **Installments up to 12x:** A 10% interest fee is added to the total amount, which is then divided into up to 12 installments.

Finally, the system will display the payment breakdown, including the amount of each installment and its corresponding due date, calculated based on the current system date.

---

## Technical Requirements and Notes

* **Data Persistence:** The program loads product data from a `.txt` file upon startup and saves updates (after registrations or sales) back to the same file to ensure no information is lost.
* **Navigation and Usability:** The interface is built with clear menus and provides options for the user to cancel an operation at any time, returning to the main menu.
* **Continuous Operation:** The system is designed to run indefinitely, returning to the main menu after each completed operation, whether it's a registration or a sale.
* **Attention to Deadlines:** This project must be submitted by the date specified in the assignment.