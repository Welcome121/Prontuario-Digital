/**
* @file lista_consultas.c
* @brief Arquivo com as funções referentes a lista de consultas
* @author Gabriel Benvindo Begnami
* @date 14/07/2021
*/

#include "lista_consultas.h"
#include <stdio.h>
#include <stdlib.h>


Lista* cria_lista()
{
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    if (lista != NULL) *lista = NULL;
    return lista;
}

void libera_lista(Lista* lista)
{
    consulta_t* aux;

    while(*lista != NULL)
    {
        aux = *lista;
        *lista = (*lista)->proximo;
        free(aux);

    }
    free(lista);
}

//Insere no início da lista
int insere_consulta(Lista* lista, data_t* data, char obs[])
{
    if(lista == NULL) return 1;
    consulta_t* novo = (consulta_t*)malloc(sizeof(consulta_t));
    if(novo == NULL) return 1;

    novo->data = (data_t*)malloc(sizeof(data_t));

    novo->data = data;
    strcpy(novo->obs, obs);
    novo->proximo = *lista;
    *lista = novo;
    return 0;
}


void imprime_lista(Lista* lista)
{
    consulta_t* aux = *lista;

    while(aux != NULL)
    {
        fprintf(stdout, "Data: %d/%d/%d\n", aux->data->dia, aux->data->mes, aux->data->ano);
        fprintf(stdout, "Observacao:\n-->%s\n", aux->obs);
        aux = aux->proximo;
    }
}

int tamanho_lista(Lista* lista)
{
    int tamanho = 0;
    if(lista_vazia(lista)) return tamanho;
    consulta_t* aux = *lista;
    while(aux != NULL)
    {
        tamanho++;
        aux = aux->proximo;
    }
    return tamanho;
}

int lista_vazia(Lista* lista)
{
    return (lista == NULL || *lista == NULL);
}