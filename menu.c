/**
* @file menu.c
* @brief Arquivo que apresenta todas as funções do menu
* @author Gabriel Benvindo Begnami
* @date 15/07/2021
*/


#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCESSO 0

void imprime_titulo()
{
    (void)fprintf(stdout,"\t ____   _____   _____   __  __   ______   __  __   _____ / _____   __    _____\n"
    "\t|  _ \\ |  _  \\ /     \\ |  \\|  | |_    _| |  ||  | /  _  \\ |  _  \\ |  |  /     \\\n"
    "\t|  __/ |     / |  |  | |      |   |  |   |  `'  | |  _  | |     / |  |  |  |  |\n"
    "\t|__|   |__|__\\ \\_____/ |__|\\__|   |__|    \\____/  \\_/ \\_/ |__|__\\ |__|  \\_____/\n"
    "\t ____    __   _____   __   ______   _____   __\n"
    "\t|    \\  |  | /  ___\\ |  | |_    _| /  _  \\ |  |\n"
    "\t|  |  | |  | |  \\_ \\ |  |   |  |   |  _  | |  |__\n"
    "\t|____/  |__| \\_____/ |__|   |__|   \\_/ \\_/ |_____|\n");
}

void imprime_desenho()
{
    (void)fprintf(stdout,
        "\t\t           .----.\n"
        "\t\t          ===(_)==\n"
        "\t\t         // 6  6 \\\\\n"
        "\t\t         (    7   )\n"
        "\t\t          \\ '--' /\n"
        "\t\t           \\_ ._/\n"
        "\t\t          __)  (__\n"
        "\t\t        /    V/    \\\n"
        "\t\t       /     Y  |_| \\\n"
        "\t\t      /      |       \\\n");
}

void menu()
{
    Arvore* arvore = cria_arvore();
    int option_menu;
    char lixo;
    do
    {
        system("cls");
        imprime_titulo();        
        imprime_desenho();
        
        (void)fprintf(stdout, "\t\t ----------MENU---------- \n"
        "\t\t| [1] Consultar paciente |\n"
        "\t\t| [2] Consultar data     |\n"
        "\t\t| [3] Inserir consulta   |\n"
        "\t\t| [4] Remover prontuario |\n"
        "\t\t| [0] Sair               |\n"
        "\t\t ------------------------ \n"
        "\t\t >>>> Opcao: ");
        (void)fscanf(stdin, "%d%c", &option_menu, &lixo);

        switch (option_menu)
        {
        case 1:
            consultar_paciente(arvore);
            break;
        case 2:
            consultar_data(arvore);
            break;
        case 3:
            inserir_consulta(arvore);
            break;
        case 4:
            remover_prontuario(arvore);
            break;
        case 0:
             sair(arvore);
             return;

            break;
        default:
            (void)fprintf(stdout, "\n[ERRO] Opcao invalida!\n");
            break;
        }

        system("pause");
    } while (option_menu != 0); 
    return;
}

void consultar_paciente(Arvore* arv_prontuarios)
{
    system("cls");
    imprime_titulo();
    char nome[TAM_MAX_NOME];
    (void)fprintf(stdout, "<Funcao 1> Consultar paciente\n\n");
    (void)fprintf(stdout, "Nome do paciente: ");
    (void)fgets(nome, TAM_MAX_NOME, stdin);

    consultar_nome_arvore(arv_prontuarios, nome);

    (void)fprintf(stdout, "Funcao realizada com sucesso! (^.^)\n");
    return;
}

void consultar_data(Arvore* arv_prontuarios)
{
    system("cls");
    imprime_titulo();

    char lixo;
    data_t* data = (data_t*)malloc(sizeof(data_t));
    if (data == NULL)
    {
        (void)fprintf(stderr, "Erro de memoria! :(");
        return;
    }
    (void)fprintf(stdout, "<Funcao 2> Consultar data\n\n");
    (void)fprintf(stdout, "Data (DD/MM/AAAA): ");
    (void)fscanf(stdin, "%d/%d/%d%c", &(data->dia), &(data->mes), &(data->ano), &lixo);
    valida_data(data);

    consultar_data_arvore(arv_prontuarios, data);

    free(data);

    return;
}

void inserir_consulta(Arvore* arv_prontuarios)
{
    system("cls");
    imprime_titulo();
    if (arv_prontuarios == NULL) return ;
    int verificador;
    char lixo, obs[TAM_MAX_OBS];
    data_t* data = (data_t*)malloc(sizeof(data_t));
    if (data == NULL)
    {
        (void)fprintf(stderr, "Erro de memoria! :(");
        return;
    }
    prontuario_t* novo = cria_prontuario();
    (void)fprintf(stdout, "<Funcao 3> Inserir consulta\n\n");
    (void)fprintf(stdout, "Data da consulta(DD/MM/AAAA): ");
    (void)fscanf(stdin, "%d/%d/%d%c", &(data->dia), &(data->mes), &(data->ano), &lixo);
    valida_data(data);
   
    (void)fprintf(stdout, "Nome do paciente: ");
    (void)fgets(novo->nome, TAM_MAX_NOME, stdin);

    (void)fprintf(stdout, "Observacao: ");
    (void)fgets(obs, TAM_MAX_OBS, stdin);
    (void)fprintf(stdout, "\n\n");

    verificador = insere_consulta(novo->inicio_lista, data, obs);
    verificador = inserir_vertice(arv_prontuarios, novo);

    if (verificador == 0) fprintf (stdout, "Funcao realizada com sucesso! (^.^)\n");
    else fprintf (stdout, "'inserir_consulta' falhou! [o_o]");

    return;
}

void remover_prontuario(Arvore* arv_prontuarios)
{
    system("cls");
    imprime_titulo();
    if (arv_prontuarios == NULL) return;

    char nome[TAM_MAX_NOME];

    (void)fprintf(stdout, "<Funcao 4> Remover prontuario\n\n"
    "Nome: ");
    (void)fgets(nome, TAM_MAX_NOME, stdin);

    remove_vertice_arvore(arv_prontuarios, nome);

    return;
}

//Encerra o programa, liberando toda a memoria alocada até então
void sair(Arvore* arvore) 
{
    system("cls");
    imprime_titulo();
    libera_arvore(arvore);
    (void)fprintf(stdout, "\nMemoria liberada e programa finalizado\n\n");
    return;
}



//Definições que seram utilizadas na função analisa_data
#define ano_minimo 1900
#define ano_atual 2021
#define janeiro 1
#define fevereiro 2
#define marco 3
#define abril 4
#define maio 5
#define junho 6
#define julho 7
#define agosto 8
#define setembro 9
#define outubro 10
#define novembro 11
#define dezembro 12
void valida_data(data_t* data)
{
    char lixo;
    int avaliador = 0;
    int meses_31_dias [] = {janeiro, marco, maio, julho, agosto, outubro, dezembro};
    int meses_30_dias [] = {abril, junho, setembro, novembro};

    if (data->mes > dezembro || data->mes < janeiro) avaliador++;
    if (data->ano > ano_atual || data->ano < ano_minimo) avaliador++;
    

    for (int i = 0; i <= dezembro; i++)
    {
        if(data->mes == meses_31_dias[i])
        {
            if (data->dia <= 31 && data->dia >= 1) continue;
            else avaliador++;
        }
        else if (data->mes == meses_30_dias[i])
        {
            if(data->dia <= 30 && data->dia >= 1) continue;
            else avaliador++;
        }
        else if (data->mes == fevereiro){
            if (data->dia <= 28 && data->dia >= 1) continue;
            else avaliador++;
        }
        else continue;
    }

    if (avaliador != 0)
    {
        (void)fprintf(stdout, "Data inserida eh invalida! {-_-}\n"
        "Digite novamente (DD/MM/AAAA): ");
        (void)fscanf(stdin, "%d/%d/%d%c", &(data->dia), &(data->mes), &(data->ano), &lixo);
        valida_data(data);
    }
    return;
}