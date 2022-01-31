/**
* @file Arv_prontuarios.c
* @brief Arquivo com as funções referentes aos prontuarios e as árvores
* @author Gabriel Benvindo Begnami
* @date 15/07/2021
*/

#include "Arv_prontuarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Arvore* cria_arvore()
{
    Arvore* raiz = (Arvore*)malloc(sizeof(Arvore));
    if (raiz != NULL) *raiz = NULL;
    return raiz;
}
prontuario_t* cria_prontuario()
{
    prontuario_t* prontuario = (prontuario_t*)malloc(sizeof(prontuario_t));
    if (prontuario != NULL)
    {
        Lista* lista = cria_lista();
        if(lista != NULL) prontuario->inicio_lista = lista;
    }
    return prontuario;
}

void libera_prontuario(prontuario_t* prontuario)
{
    libera_lista(prontuario->inicio_lista);
    free(prontuario);
}

void libera_vertice(vertice_t* vertice)
{
    if (vertice == NULL) return;
    libera_vertice(vertice->esq);
    libera_vertice(vertice->dir);

    free((*vertice->prontuario->inicio_lista)->data);
    libera_prontuario(vertice->prontuario);
    free(vertice);
}

void libera_arvore(Arvore* arvore)
{
    if (arvore == NULL) return;
    libera_vertice((*arvore));
    free(arvore);
}

int inserir_vertice(Arvore* arvore, prontuario_t* prontuario)
{
    if (arvore == NULL)
    {
        (void)fprintf(stdout, "ERRO Arvore nao alocada [o_o]");
        return 1;
    }
    vertice_t* novo = (vertice_t*)malloc(sizeof(vertice_t));
    if (novo == NULL) return 1;

    novo->prontuario = prontuario;
    novo->esq = NULL;
    novo->dir = NULL;

    if (*arvore == NULL) 
    {
        *arvore = novo;
        return 0;
    }

    vertice_t* atual = *arvore;
    vertice_t* pai = NULL;

    while (atual != NULL)
    {
        pai = atual;
        if (strcmp(prontuario->nome, atual->prontuario->nome) == 0)
        {
            insere_consulta(atual->prontuario->inicio_lista, (*prontuario->inicio_lista)->data, (*prontuario->inicio_lista)->obs);
            libera_lista(novo->prontuario->inicio_lista);
            free(novo);
            return 0;
        }
        if (strcmp(prontuario->nome, atual->prontuario->nome) > 0) atual = atual->dir;
        else atual = atual->esq;
    }

    if(strcmp(prontuario->nome, pai->prontuario->nome) > 0) pai->dir = novo;
    else pai->esq = novo;

    return 0;
}

int remove_vertice_arvore(Arvore* arvore, char nome[])
{
    if (arvore_vazia(arvore))
    {
        (void)fprintf(stdout, "ERRO o sistema ainda nao apresenta prontuarios [o_o]");
        return 1;
    }
    vertice_t *pai = NULL, *atual = *arvore;

    while(atual != NULL)
    {
        if (strcmp(nome, atual->prontuario->nome) == 0)
        {
            if (atual == *arvore) *arvore = remove_vertice(atual);

            else
            {
                if (pai->dir == atual) pai->dir = remove_vertice(atual);
                else pai->esq = remove_vertice(atual);
            }
            (void)fprintf(stdout, ">> Prontuario de %s   foi removido com sucesso! (^.^)\n\n", nome);
            return 0;
        }
        pai = atual;
        if (strcmp(nome, atual->prontuario->nome) > 0) atual = atual->dir;
        else atual = atual->esq;
    }
    (void)fprintf(stdout, ">> %s Nao apresenta um prontuario. [o_o]", nome);
    return 0;

}

vertice_t* remove_vertice(vertice_t* vertice)
{
    vertice_t *aux_1, *aux_2;

    if (vertice->esq == NULL)
    {
        aux_2 = vertice->dir;
        free((*vertice->prontuario->inicio_lista)->data);
        libera_prontuario(vertice->prontuario);
        free(vertice);
        return aux_2;
    }

    aux_1 = vertice;
    aux_2 = vertice->esq;

    while(aux_2->dir != NULL)
    {
        aux_1 = aux_2;
        aux_2 = aux_2->dir;
    }

    if(aux_1 != vertice)
    {
        aux_1->dir = aux_2->esq; 
        aux_2->esq = vertice->esq;
    }

    aux_2->dir = vertice->dir;
    free((*vertice->prontuario->inicio_lista)->data);
    libera_prontuario(vertice->prontuario);
    free(vertice);
    return aux_2;
}

void consultar_nome_arvore(Arvore* arvore, char nome[])
{
    if (arvore_vazia(arvore))
    {
        (void)fprintf(stdout, "Nenhum prontuario inserido ainda. [o_o]\n\n");
        return;
    }

    vertice_t* aux = *arvore;

    while(aux != NULL)
    {
        if (strcmp(nome, aux->prontuario->nome) == 0)
        {
            imprime_vertice(aux->prontuario);
            return;
        }
        if (strcmp(nome, aux->prontuario->nome) > 0) aux = aux->dir;
        else aux = aux->esq;
    }

    char sim_ou_nao, lixo;
    (void)fprintf(stdout, "Nome nao encontrado! [o_o]\n"
    "Deseja tentar digitar novamente [S/N]: ");
    (void)fscanf(stdin,"%c%c", &sim_ou_nao, &lixo);
    if (sim_ou_nao == 'S')
    {
        (void)fprintf(stdout, "\nNome: ");
        (void)fgets(nome, TAM_MAX_NOME, stdin);
        consultar_nome_arvore(arvore, nome);
    }
    else if (sim_ou_nao == 'N') return;
    else
    {
        fprintf(stdout, "Caracter invalido, a funcao foi finalizada!");
        return;
    } 
    
}

void consultar_data_arvore(Arvore* arvore, data_t* data)
{
    if (arvore_vazia(arvore))
    {
        (void)fprintf(stdout, "Nenhum prontuario inserido ainda. [o_o]\n\n");
        return;
    }
    (void)fprintf(stdout, "\nNomes econtrados:\n");
    percorre_arvore((*arvore), data);

    //O valor mínimo do verificador é igual a 1, pois a chamada da fulçao count já soma um ao seu verificador local.
    int verificador = avalia_se_data_encontrada(KEEP);
    if (verificador == 1) (void)fprintf(stdout, "- Nenhum [o_o]\n");
    (void)avalia_se_data_encontrada(RESET);
}

void percorre_arvore(vertice_t* vertice, data_t* data)
{
    if (vertice == NULL) return;
    percorre_arvore(vertice->esq, data);
    percorre_arvore(vertice->dir, data);
    avalia_data_lista(vertice, data);
   
}

void avalia_data_lista(vertice_t* vertice, data_t* data)
{
    if (vertice == NULL) return;

    vertice_t* verticeAux = vertice;
    consulta_t* consultaAux = *(vertice->prontuario->inicio_lista);

    while (consultaAux != NULL)
    {
        if ((consultaAux->data->dia == data->dia) && (consultaAux->data->mes == data->mes) && (consultaAux->data->ano == data->ano))
        {
            (void)fprintf(stdout, "- %s", verticeAux->prontuario->nome);
            (void)avalia_se_data_encontrada(KEEP);
        }
        consultaAux = consultaAux->proximo;
    }
}

int avalia_se_data_encontrada(int x)
{
    static int verificador = 0;
    verificador++;
    if (x == RESET) verificador = 0;
    return verificador;
}

void imprime_vertice(prontuario_t* prontuario)
{
    system("cls");
    fprintf(stdout, "Paciente: %s", prontuario->nome);
    fprintf(stdout, "Numero de consutas: %d\n", tamanho_lista(prontuario->inicio_lista));
    imprime_lista(prontuario->inicio_lista);
}

int arvore_vazia(Arvore* arvore)
{
    return (arvore == NULL || *arvore == NULL);
}