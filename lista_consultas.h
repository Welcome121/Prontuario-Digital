#pragma once

#ifndef LISTA_CONSULTAS_H
#define LISTA_CONSULTAS_H

#define TAM_MAX_OBS (139 + 1)

typedef struct data_s
{
    int dia;
    int mes;
    int ano;
}data_t;

typedef struct consulta_s
{
    data_t* data;
    char obs[TAM_MAX_OBS];
    struct consulta_s* proximo;
}consulta_t;

typedef consulta_t* Lista;

Lista* cria_lista();
void libera_lista(Lista* lista);
int insere_consulta(Lista* lista, data_t* data, char obs[]);
void imprime_lista(Lista* lista);
int tamanho_lista(Lista* lista);
int lista_vazia(Lista* lista);

#endif