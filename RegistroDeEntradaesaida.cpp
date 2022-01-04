#include <iostream>
#include <string.h>
using namespace std;

struct RegistroEntrada // struct de um registro
{
    char nome[101];
    char cpf[12];
    char local[51];
    int hora[2];       // vetor de 2 casas (1 entrada e 1 saida)
    int min[2];        // vetor de 2 casas (1 entrada e 1 saida)
    int dia[2];        // vetor de 2 casas (1 entrada e 1 saida)
    int mes[2];        // vetor de 2 casas (1 entrada e 1 saida)
    int ano[2];        // vetor de 2 casas (1 entrada e 1 saida)
    bool saiu = false; // basicamente diz se a pessoa já saiu ou não
};

int op;                                                 //operador do menu
int cregistros = 0;                                     // cria a variavel mestra da quantidade de registros.
RegistroEntrada *reg = new RegistroEntrada[cregistros]; // cria uma variável ponteiro que aponta para um novo array de registros com [cregistros]

int menu();                                                        //declara a funçao menu
int deletarregistro(int cregistros, RegistroEntrada *&reg);        //funçao eletar registro
int addregistro(int cregistros, RegistroEntrada *&reg);            //funçao adicionar registros que recebe de parametros o cregistros e o ponteiro reg
void listarregistros(int cregistros, RegistroEntrada *reg);        // função que lista os registros
void addbancodedados();                                            //funçao pra ajudar a explicação e adicionar varios registros de uma vez pelo control c + control v do notepad
void addsaida(RegistroEntrada *reg);                               // adicionar saída a um registro existente
void listarregistroespecifico(int registro, RegistroEntrada *reg); //printar o registro que quiser (pra não precisar digitar um cout <<...... cada vez que for printar um certo registro)
void buscarregistro(RegistroEntrada *reg);                         //menu buscar registro
void pesquisar(RegistroEntrada *reg, int j);                       // funçao pesquisar
void listarpordata(int cregistros, RegistroEntrada *reg);          // listar por ordem de data
void listarporcpf(int cregistros, RegistroEntrada *reg);           // listar por ordem de cpf
void listarpornome(int cregistros, RegistroEntrada *&reg);         //listar por ordem de nome

main() //main
{

    system("CLS"); // limpa a tela
    do             // inicia o menu
    {
        op = menu(); //pega o operador da função menu o que o usuario escolheu
        switch (op)
        {
        case 1:
            system("CLS");
            cregistros = addregistro(cregistros, reg);
            break;
        case 2:
            if (cregistros == 0)
            {
                system("CLS");
                cout << "Primeiro adicione um registro para poder adicionar uma saida. " << endl;
                break;
            }
            else
                system("CLS"); //caso o operador for 2 adicionar saida
            addsaida(reg);
            break;

        case 3:
            if (cregistros == 0)
            {
                system("CLS"); //limpa a tela
                cout << "Primeiro adicione um registro para Listar os Registros. " << endl;
                break;
            }
            else
                system("CLS"); //limpa a tela
            system("CLS");
            listarregistros(cregistros, reg);
            break;
        case 4:
            if (cregistros == 0)
            {
                system("CLS"); //limpa a tela
                cout << "Primeiro adicione um registro para Buscar um Registros " << endl;
                break;
            }
            else
                system("CLS"); //caso operador for 4 Buscar Registro
            buscarregistro(reg);
            break;
        case 5:
            if (cregistros == 0)
            {
                system("CLS");
                cout << "Primeiro adicione um registro para poder deletar um" << endl;
                break;
            }
            else
                system("CLS"); //caso operador for 5 limpar registro
            cregistros = deletarregistro(cregistros, reg);
            break;
        case 6:
            return 0; // caso for 6 encerrar o programa.
        case 9:
            addbancodedados();
        default:
            cout << "Escolha outra opcao!" << endl;
            break;
        }
    } while (op != 6);
    return 0;
}

int addregistro(int cregistros, RegistroEntrada *&reg) // FUNÇÃO ADICIONAR REGISTRO
{
    int i;
    RegistroEntrada *temp = new RegistroEntrada[cregistros + 1]; // cria uma variavel temporaria para o registro com a capacidade do registro atual +1
    for (i = 0; i < cregistros; i++)
    {
        temp[i] = reg[i]; // cria um for pegando TUDO que a nossa variável já tinha e põe dentro da temporária
    }
    cout << "Digite o nome da pessoa (sem espacos): " << endl;
    cin >> temp[cregistros].nome; // lê as entradas
    cout << "Digite o CPF: " << endl;
    cin >> temp[cregistros].cpf; // lê as entradas
    cout << "Digite o local: " << endl;
    cin >> temp[cregistros].local; // lê as entradas
    cout << "Digite a hora e os minutos de entrada (xx xx): " << endl;
    while (cin >> temp[cregistros].hora[0] >> temp[cregistros].min[0]) //enquanto o while não for quebrado ele fica tentando ler o que é digitado
    {
        if (temp[cregistros].hora[0] > 23 || temp[cregistros].min[0] > 59)                                 // se a hora digitada for inválida faz
            cout << "Infelizmente ainda nao moramos em outro planeta, Digite um horario valido! " << endl; //isso.
        else
            break; // caso esteja tudo certo ele quebra o while.
    }
    cout << "Digite a Data de Entrada (xx xx xxxx): " << endl;
    while (cin >> temp[cregistros].dia[0] >> temp[cregistros].mes[0] >> temp[cregistros].ano[0])
    {
        if (temp[cregistros].dia[0] > 31 || temp[cregistros].mes[0] > 12)
            cout << "Infelizmente ainda nao moramos em outro planeta, digite uma data valida!" << endl;
        else
            break;
    }
    system("CLS"); // limpa a tela
    cout << "Registro criado com sucesso!" << endl;
    delete[] reg; // limpa a nossa variavel original pra não gerar memory leak
    reg = temp;   // joga a variável temporária na original;

    return cregistros + 1; // retorna a quantidade de registros aumentada.
}

void listarregistros(int cregistros, RegistroEntrada *reg) // MENU LISTAR REGISTROS
{
    int i;
    int op;
    cout << "Listar em que ordem?" << endl;
    cout << "1...Ordem De Adicionado" << endl;
    cout << "2...Ordem Alfabetica" << endl;
    cout << "3...Ordem de CPF" << endl;
    cout << "4...Ordem de Data" << endl;
    cout << "5...Listar Registro Especifico" << endl;
    cout << "6...Voltar" << endl;
    cin >> op;
    switch (op)
    {
    case 1:
        system("CLS");
        cout << "     NOME    CPF     LOCAL" << endl;
        for (i = 0; i < cregistros; i++)
        {
            listarregistroespecifico(i, reg);
        }

        break;
    case 2:
        system("CLS");
        cout << "     NOME    CPF     LOCAL" << endl;
        listarpornome(cregistros, reg);
        break;
    case 3:
        system("CLS");
        cout << "     NOME    CPF     LOCAL" << endl;
        listarporcpf(cregistros, reg);
        break;
    case 4:
        system("CLS");
        cout << "     NOME    CPF     LOCAL" << endl;
        listarpordata(cregistros, reg);
        break;
    case 5:
        system("CLS");
        int f;
        cout << "Digite o numero do registro" << endl;
        cin >> f;
        f--;
        system("CLS");
        cout << "     NOME    CPF     LOCAL" << endl;
        listarregistroespecifico(f, reg);
        break;
    case 6:
        system("CLS");
        break;
    }
}

int menu()
{
    int operador;
    cout
        << "MENU" << endl
        << "1...Adicionar Entrada" << endl
        << "2...Adicionar Saida" << endl
        << "3...Listar Registro" << endl
        << "4...Buscar Registro" << endl
        << "5...Deletar Registro" << endl
        << "9...Carregar Banco de Dados" << endl
        << "6...SAIR" << endl;
    cin >> operador;
    return operador;
}

void addsaida(RegistroEntrada *reg) // FUNÇÃO ADICIONAR SAÍDA
{
    int registro;
    cout << "Digite o numero do Registro que voce quer adicionar uma saida (utilize como base o identificador por ordem de adicionado)" << endl
         << "Digite 0 para voltar" << endl;
    cin >> registro;
    if (registro == 0) // se for 0 volta ao menu
    {
        system("CLS"); // limpa a tela
        return;        // volta ao menu
    }
    else
        system("CLS");                       // limpa a tela
    registro--;                              // -1 registro pra nao precisar digitar registro 0 (frescura minha)
    listarregistroespecifico(registro, reg); //printa o registro escolhido pra facilitar a visualização do usuario
    reg[registro].saiu = true;
    cout << endl
         << "Digite a data da saida: " << endl;
    while (cin >> reg[registro].dia[1] >> reg[registro].mes[1] >> reg[registro].ano[1]) //enquanto o while não for quebrado ele fica tentando ler o que é digitado
    {
        if (reg[registro].mes[1] > 12 || reg[registro].dia[1] > 31)
            cout << "Infelizmente ainda nao moramos em outro planeta, digite uma data valida!" << endl;
        else if (reg[registro].ano[1] < reg[registro].ano[0])                                                          // se a hora digitada for inválida faz
            cout << "a nao ser que voce tenha uma maquina do tempo, e impossivel sair anos antes de entrar. " << endl; //isso.
        else if (reg[registro].ano[1] == reg[registro].ano[0] && reg[registro].mes[1] < reg[registro].mes[0])
            cout << "a nao ser que voce tenha uma maquina do tempo, e impossivel sair meses antes de entrar. " << endl; //isso.
        else if (reg[registro].ano[1] == reg[registro].ano[0] && reg[registro].mes[1] == reg[registro].mes[0] && reg[registro].dia[1] < reg[registro].dia[0])
            cout << "a nao ser que voce tenha uma maquina do tempo, e impossivel sair dias antes de entrar. " << endl; //isso.
        else
            break; // caso esteja tudo certo ele quebra o while.
    }
    cout << "Digite a Hora e o minuto da saida: " << endl;
    while (cin >> reg[registro].hora[1] >> reg[registro].min[1]) //enquanto o while não for quebrado ele fica tentando ler o que é digitado
    {
        if (reg[registro].hora[1] > 23 || reg[registro].min[1] > 59) // se a hora digitada for invalida                                                                                                                                                                     // se a hora digitada for inválida faz
            cout << "Infelizmente ainda nao moramos em outro planeta, Digite um horario valido! " << endl;
        else if (reg[registro].hora[1] < reg[registro].hora[0] && reg[registro].dia[1] <= reg[registro].dia[0] && reg[registro].mes[1] <= reg[registro].mes[0] && reg[registro].ano[1] <= reg[registro].ano[0]) // testa se a hora e a data são válidas
            cout << "a nao ser que voce tenha uma maquina do tempo, e impossivel sair antes de entrar. " << endl;
        else if (reg[registro].min[1] < reg[registro].min[0] && reg[registro].hora[1] <= reg[registro].hora[0] && reg[registro].dia[1] <= reg[registro].dia[0] && reg[registro].mes[1] <= reg[registro].mes[0] && reg[registro].ano[1] <= reg[registro].ano[0]) // testa se os minutos e a data são validos
            cout
                << "a nao ser que voce tenha uma maquina do tempo, e impossivel sair minutos antes de entrar. " << endl; //isso.
        else
            break; // caso esteja tudo certo ele quebra o while.
    }

    system("CLS"); // limpa a tela
    cout << "Registro de saida adicionado com sucesso!" << endl;
}

void addbancodedados() //funçao pra ajudar a explicação e adicionar varios registros de uma vez pelo control c + control v do notepad
{
    int r;
    cout << "Qual o numero de registros a serem adicionados?" << endl;
    cin >> r;
    for (int i = 0; i < r; i++)
    {
        cregistros = addregistro(cregistros, reg);
    }
}

void listarregistroespecifico(int registro, RegistroEntrada *reg) // FUNÇÃO LISTAR REGISTRO ESPECIFICO
{
    cout << registro + 1 << "- " << reg[registro].nome << " " << reg[registro].cpf << " " << reg[registro].local << endl
         << "Entrada: ";
    if (reg[registro].hora[0] < 10) // se o valor for menor q 10 ele printa um 0 na frente (pra nao ficar por exemplo 2:7 e sim 02:07)
    {
        cout << "0";
    }
    cout << reg[registro].hora[0] << ":";
    if (reg[registro].min[0] < 10) // se o valor for menor q 10 ele printa um 0 na frente (pra nao ficar por exemplo 2:7 e sim 02:07)
    {
        cout << "0";
    }
    cout << reg[registro].min[0] << " - " << reg[registro].dia[0] << "/" << reg[registro].mes[0] << "/" << reg[registro].ano[0] << endl;
    if (reg[registro].saiu == true) // se o registro contem uma saida ele printa as informações da saída, caso saiu == false, ele printa ----> saída: nao saiu ainda
    {
        cout << "Saida: ";
        if (reg[registro].hora[1] < 10) // se o valor for menor q 10 ele printa um 0 na frente (pra nao ficar por exemplo 2:7 e sim 02:07)
        {
            cout << "0";
        }
        cout << reg[registro].hora[1] << ":";
        if (reg[registro].min[1] < 10) // se o valor for menor q 10 ele printa um 0 na frente (pra nao ficar por exemplo 2:7 e sim 02:07)
        {
            cout << "0";
        }
        cout << reg[registro].min[1] << " - " << reg[registro].dia[1] << "/" << reg[registro].mes[1] << "/" << reg[registro].ano[1] << endl;
    }
    else
        cout << "Saida: Nao saiu ainda" << endl; //isso aqui
}

void buscarregistro(RegistroEntrada *reg) //menu de busca
{

    int i;
    int op; //mesma coisa do outro menu, um switch e cada um leva a uma função...
    cout << "Pesquisar" << endl;
    cout << "1...Pesquisar por Nome" << endl;
    cout << "2...Pesquisar por CPF" << endl;
    cout << "3...Pesquisar por Local" << endl;
    cout << "4...Pesquisar por Data" << endl;
    cout << "5...Voltar" << endl;
    cin >> op;
    switch (op)
    {
    case 1:
        system("CLS");
        pesquisar(reg, 1);
        break;
    case 2:
        system("CLS");
        pesquisar(reg, 2);
        break;
    case 3:
        system("CLS");
        pesquisar(reg, 3);
        break;
    case 4:
        system("CLS");
        pesquisar(reg, 4);
        break;
    case 5:
        system("CLS");
        break;
    }
}

void pesquisar(RegistroEntrada *reg, int j)
{
    string pesquisa;
    if (j == 1)
    {
        int a = 0;
        cout << "Digite o nome a ser pesquisado: " << endl;
        cin >> pesquisa;

        for (int i = 0; i < cregistros; i++)
        {
            if (reg[i].nome == pesquisa)
            {
                listarregistroespecifico(i, reg);
                a = 1;
            }
        }
        if (a != 1)
            cout << "Nenhum Registro foi encontrado." << endl;
    }
    if (j == 2)
    {
        int a = 0;
        cout << "Digite o CPF a ser pesquisado: " << endl;
        cin >> pesquisa;

        for (int i = 0; i < cregistros; i++)
        {
            if (reg[i].cpf == pesquisa)
            {
                listarregistroespecifico(i, reg);
                a = 1;
            }
        }
        if (a != 1)
            cout << "Nenhum Registro foi encontrado." << endl;
    }
    if (j == 3)
    {
        cout << "Digite o Local a ser pesquisado: " << endl;
        cin >> pesquisa;

        int a = 0; //variavel pra dizer se achou alguma coisa

        for (int i = 0; i < cregistros; i++)
        {
            if (reg[i].local == pesquisa)
            {
                listarregistroespecifico(i, reg);
                a = 1;
            }
        }
        if (a != 1)
            cout << "Nenhum Registro foi encontrado." << endl;
    }
    if (j == 4)
    {
        int dia, mes, ano;
        int a = 0; //variavel pra dizer se achou alguma coisa
        cout << "Digite a Data a ser pesquisada: " << endl;
        cin >> dia >> mes >> ano;

        for (int i = 0; i < cregistros; i++)
        {
            if ((dia == *reg[i].dia) && (mes == *reg[i].mes) && (ano == *reg[i].ano))
            {
                listarregistroespecifico(i, reg);
                a = 1;
            }
        }
        if (a != 1)
            cout << "Nenhum Registro foi encontrado." << endl;
    }
}

void listarpordata(int cregistros, RegistroEntrada *reg) // ORDEM POR DATA
{
    int i, j;
    RegistroEntrada temp;                                     //cria um registro temporario
    RegistroEntrada *temp2 = new RegistroEntrada[cregistros]; //cria um ponteiro array temporário (similar ao da função de adicionar produto)

    // fiz isso de criar uma temporaria de novo para manter o meu array principal reg quieto, assim eu posso usar a ordem de adicionado por padrão(usar o index dela para adicionar uma saída, por exemplo...)

    for (i = 0; i < cregistros; i++)
    {
        temp2[i] = reg[i]; //joga todos os registros dentro desse ponteiro array novo temporaria
    }

    for (i = 0; i < cregistros - 1; i++) // selection sort
    {
        for (j = i + 1; j < cregistros; j++)
        {
            if ((*temp2[i].ano < *temp2[j].ano) || (*temp2[i].ano == *temp2[j].ano && *temp2[i].mes < *temp2[j].mes) || (*temp2[i].ano == *temp2[j].ano && *temp2[i].mes == *temp2[j].mes && *temp2[i].dia < *temp2[j].dia)) //checa se uma data é menor que a outra
            {
                temp = temp2[i];
                temp2[i] = temp2[j];
                temp2[j] = temp;
            }
        }
    }
    for (i = 0; i < cregistros; i++)
    {
        listarregistroespecifico(i, temp2); //printa a variavel temporaria ordenada...
    }
    delete[] temp2; //deleta a variavel temporaria para evitar memory
}

void listarporcpf(int cregistros, RegistroEntrada *reg) // ORDEM POR CPF
{
    int i, j;
    RegistroEntrada temp;                                     //cria um registro temporario
    RegistroEntrada *temp2 = new RegistroEntrada[cregistros]; //cria um ponteiro array temporário (similar ao da função de adicionar produto)

    for (i = 0; i < cregistros; i++)
    {
        temp2[i] = reg[i];
    }

    for (i = 0; i < cregistros - 1; i++) // selection sort
    {
        for (j = i + 1; j < cregistros; j++)
        {
            if (*temp2[i].cpf < *temp2[j].cpf) //checa se o cpf é maior que o outro.
            {
                temp = temp2[i];
                temp2[i] = temp2[j];
                temp2[j] = temp;
            }
        }
    }
    for (i = 0; i < cregistros; i++)
    {
        listarregistroespecifico(i, temp2); //printa a variavel temporaria ordenada...
    }
    delete[] temp2; //deleta a variavel temporaria para limpara memória...
}

void listarpornome(int cregistros, RegistroEntrada *&reg) // ORDEM POR NOME
{
    int i, j;
    RegistroEntrada temp;                                     //cria um registro temporario
    RegistroEntrada *temp2 = new RegistroEntrada[cregistros]; //cria um ponteiro array temporário (similar ao da função de adicionar produto)

    for (i = 0; i < cregistros; i++)
    {
        temp2[i] = reg[i];
    }

    for (i = 0; i < cregistros - 1; i++) // selection sort
    {
        for (j = i + 1; j < cregistros; j++)
        {

            if (strcmp(temp2[i].nome, temp2[j].nome) > 0) //checa a ordem dos nomes
            {
                temp = temp2[i];
                temp2[i] = temp2[j];
                temp2[j] = temp;
            }
        }
    }
    for (i = 0; i < cregistros; i++)
    {
        listarregistroespecifico(i, temp2); //printa a variavel temporaria ordenada...
    }
    delete[] temp2; //deleta a variavel temporaria para evitar memory leak...
}

int deletarregistro(int cregistros, RegistroEntrada *&reg) //deletar registro
{
    int removido, i;
    cout << "Qual Registro voce quer deletar? (utilize como base o identificador da lista por ordem de adicionado)" << endl
         << "Digite 0 para voltar" << endl;
    while (cin >> removido)
    {
        if (removido > cregistros)
            cout << "Esse Registro nao existe. " << endl;
        else
            break;
    }
    if (removido != 0)
    { // se o input for 0 ele volta ao menu
        removido--;
        RegistroEntrada *temp = new RegistroEntrada[cregistros]; // cria uma variavel temporaria para o registro com a capacidade do registro atual -1
        for (i = 0; i < cregistros; i++)                         //coloca todos os registros nessa temporaria
        {
            temp[i] = reg[i];
        }
        for (i = removido; i < cregistros; i++) // troca todos os registros a partir do removido por um da frente (ex: reg 4 pelo 5, reg 5 pelo 6....) para REORGANIZAR a lista
        {
            temp[i] = temp[i + 1];
        }
        delete[] reg;  //deleta o registro atual
        reg = temp;    //joga a temporaria dentro do registro
        system("CLS"); // limpa a tela
        cout << "Registro Deletado com sucesso!" << endl;
        return cregistros - 1; //diminui a quantidade geral do registro
    }
    else
        system("CLS");
    return cregistros;
}
