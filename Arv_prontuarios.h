#pragma once

#ifndef ARV_PRONTUARIOS_H
#define ARV_PRONTUARIOS_H

#define TAM_MAX_NOME (39 + 1)

#include "lista_consultas.h"

#define KEEP 0
#define RESET 1

typedef struct prontuario_s
{
    char nome[TAM_MAX_NOME];
    Lista* inicio_lista;
}prontuario_t;

typedef struct vertice_s
{
    prontuario_t* prontuario;
    struct vertice_s* esq;
    struct vertice_s* dir;
}vertice_t;

typedef vertice_t* Arvore;

Arvore* cria_arvore();
prontuario_t* cria_prontuario();
void libera_prontuario(prontuario_t* prontuario);
void libera_vertice(vertice_t* vertice);
void libera_arvore(Arvore* arvore);
int inserir_vertice(Arvore* arvore, prontuario_t* prontuario);
int remove_vertice_arvore(Arvore* arvore, char nome[]);
vertice_t* remove_vertice(vertice_t* vertice);
void consultar_nome_arvore(Arvore* arvore, char nome[]);
void consultar_data_arvore(Arvore* arvore, data_t* data);
void percorre_arvore(vertice_t* vertice, data_t* data);
void avalia_data_lista(vertice_t* vertice, data_t* data);
int avalia_se_data_encontrada(int x);
void imprime_vertice(prontuario_t* prontuario);
int arvore_vazia(Arvore* arvore);

#endif