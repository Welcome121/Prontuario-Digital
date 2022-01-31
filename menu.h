#pragma once

#ifndef MENU_H
#define MENU_H

#include "Arv_prontuarios.h"

void menu();
void consultar_paciente(Arvore* arv_prontuarios);
void consultar_data(Arvore* arv_prontuarios);
void inserir_consulta(Arvore* arv_prontuarios);
void remover_prontuario(Arvore* arv_prontuarios);
void sair(Arvore* arvore);

void valida_data(data_t* data);

#endif