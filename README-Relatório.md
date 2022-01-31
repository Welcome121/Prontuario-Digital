# Prontuário-Digital
Introdução
	O objetivo do trabalho em questão foi desenvolver uma aplicação que insere, remove e pesquisa prontuários de pacientes. Esses prontuários possuem um nome e uma lista das consultas, e são armazenados em uma árvore binária, que é organizada a partir dos nomes dos pacientes.

Estruturas de dados
  Fiz a implementação das structs em diferentes arquivos de cabeçário - buscando sempre uma boa organização individual - sendo eles a Arv_prontuarios.h (onde implementei a struct dos prontuários e do vértice) e a lista_consultas.h (onde foram feitas a struct da data e da consulta). O uso de structs é de suma importância, pois através delas é possível organizar diferentes variáveis de diferentes tipos, possibilitando a “criação” de um tipo de dado.

  Na struct data_s, foram inseridos as variáveis dia, mes e ano, todas do tipo int. 
  Agora, na struct consulta_s, que nada mais é que um elemento da lista de consultas foram inseridas 3 variáveis: uma do tipo data_t*, responsável por apontar para a data, um vetor de char terminado em barra zero para guardar a observação médica (ela apresenta um limite de 140 caracteres) e uma do tipo struct consulta_s* para guardar o endereço da próxima consulta.
O tipo de dado consulta_t*, por fim, tem o nome redefinido, para Lista, e guarda o primeiro elemento da lista de consultas.

  Já na struct prontuario_s apresenta duas variáveis, uma do tipo char para guardar o nome do paciente e outra do tipo Lista*, para guardar o endereço do espaço na memória que aponta para o início da lista de consultas.
	Por fim, no tipo de dado criado, vertice_t, temos uma variável do tipo prontuario_t* que guarda o endereço de um prontuário e duas outras variáveis do tipo struct vertice_s* responsáveis por guardar os endereços seguintes da árvore binária (à esquerda e à direita).
	O tipo de dado vertice_t* tem o nome redefinido para Arvore e é responsável por apontar para a raiz da árvore.

Funcionamento do programa
  A aplicação desenvolvida apresenta 5 funções principais que foram criadas em uma biblioteca própria, denominada menu.h			
	Essas “funções mães” realizam a captação dos dados necessários para seu funcionamento e chamam às funções das outras bibliotecas desenvolvidas (Arv_prontuarios.h e lista_consultas.h) que trabalham sobre a estrutura árvore e lista respectivamente. Tirando algumas funções que foram desenvolvidas no mesmo arquivo, sendo elas, a função imprime_titulo(), imprime_desenho() e analisa_data(data_t* data).
	Há também neste arquivo uma função denominada menu().
  
- void menu()
  A função void menu() é aquela chamada na main, todas as demais funções são chamadas nela. Ela realiza a criação da raiz da árvore e realiza a interação com o usuário, imprimindo os recursos gráficos e captando a opção escolhida pelo mesmo, realizando-a caso seja uma opção válida.
 
- void inserir_consulta (Arvore* arv_prontuarios)
  função inserir_consulta cria um novo prontuário e preenche suas variáveis com as informações digitadas pelo usuário, o nome por meio de um fgets e a consulta por meio da função insere_consulta, que recebe o início da lista do prontuario, cria um novo elemento, atribui a suas variáveis as informações digitadas pelo usuário (recebidas como parâmetro) e a insere no início da lista de consultas. Na função inserir_vertice, esse prontuário preenchido e passado como parâmetro juntamente com a árvore e uma pesquisa é feita na árvore binária, caso haja um nome igual ao digitado, a função insere_consulta é chamada novamente porém com a lista do prontuário já presente na árvore (incluindo assim mais uma consulta a lista de consultas desse determinado prontuário) e a memória alocada ao novo prontuário e ao novo elemento da lista de consultas são liberadas. Caso o nome não esteja presente na árvore, um vértice criado dentro da função recebe o prontuário.

- void consultar_paciente(Arvore* arv_prontuarios)
  Essa função permite ao usuário digitar um nome que será passado como parâmetro juntamente com a árvore para a função consultar_nome_arvore, nela será feita uma busca pela árvore binária tendo como “referência” o nome presente em cada prontuário, caso encontre algum nome, ela irá imprimir todo o prontuário do paciente, ou seja, seu nome e sua lista de consultas. No caso de não encontrar ninguém, o programa possibilita ao usuário digitar outra string, caso queira.
  
 - void consultar_data(Arvore* arv_prontuarios)
   A função consultar_data cria um ponteiro do tipo data_t, lê a data escrita pelo usuário e chama a função consultar_data_arvore que recebe a árvore e a data como parâmetro, nela a lista de consultas de cada vértice é analisada, caso a data de alguma consulta lida seja igual a presente em alguma consulta o programa imprime o nome do prontuário cuja verificação de igualdade é verídica. Caso não encontre ninguém cuja data de consulta seja a mesma da data digitada, o programa imprime “nenhum”.

- void remover_prontuario(Arvore* arv_prontuarios)
  A função remover_prontuario lê uma string digitada pelo usuário e a passa como parâmetro juntamente com a árvore para função remove_vertice_arvore, que percorre a árvore binária por meio do nome lido, caso ele seja igual ao nome presente em algum prontuário o vértice é removido da árvore. Isso ocorre  liberando a memória alocada para a data, a lista de consultas e o prontuário, respectivamente.

- void sair (Arvore* arvore)
  A função sair, acionada quando o usuário digita 0 no menu, é responsável por liberar toda a memória alocada na construção da árvore. Ela chama a função libera_arvore que percorre toda a árvore, utilizando o método de pós-ordem, liberando a data, a lista de consultas, o prontuário e por fim o vértice, respectivamente.
