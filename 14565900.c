/*********************************************************************/
/**   ACH2024 - Algoritmos e Estruturas de Dados II                 **/
/**   EACH-USP - Primeiro Semestre de 2024                          **/
/**   Turma 04 - Prof. Luciano Digiampietri                         **/
/**                                                                 **/
/**   Primeiro Exercicio-Programa                                   **/
/**                                                                 **/
/**   Davi Batista de Souza                  14565900               **/
/**                                                                 **/
/*********************************************************************/

// gcc completeERenomeie.c -lm

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int bool;

/* Estrutura para representar nosso grafo usando matriz binaria de adjacencias
 */
typedef struct {
  int numVertices;
  int numArestas;
  bool **matriz;
} Grafo;

/* Funcao auxiliar para o sistema de correcao automatica (nao mexer) */
void printf123() {
  // Funcao usada pelo sistema de correcao automatica (nao mexer)
}

/* Funcao que inicializa o grafo cujo endereco foi passado como parametro.
   Isto e, cria a matriz de adjacencias (preenchida com false),
   e atribui valor para numVertices (recebendo o valor passado por parametro)
   e numArestas igual a zero.
*/
bool inicializaGrafo(Grafo *g, int vertices) {
  if (g == NULL || vertices < 1)
    return false;
  g->numVertices = vertices;
  g->numArestas = 0;
  int x, y;
  g->matriz = (bool **)malloc(sizeof(bool *) * vertices);
  for (x = 0; x < vertices; x++) {
    g->matriz[x] = (bool *)malloc(sizeof(bool) * vertices);
    for (y = 0; y < vertices; y++) {
      g->matriz[x][y] = false;
    }
  }
  return true;
}

/* Funcao que libera a memoria da matriz de adjacencia do grafo cujo endereco
   foi passado como parametro.
*/
bool liberaGrafo(Grafo *g) {
  if (g == NULL)
    return false;
  int x;
  for (x = 0; x < g->numVertices; x++)
    free(g->matriz[x]);
  free(g->matriz);
  g->numVertices = 0;
  g->numArestas = 0;
  g->matriz = NULL;
  return true;
}

/* Funcao que retorna o numero de vertices do grafo apontado por g, caso o
   endereco armazenado em g seja diferente de NULL. Caso contrario, retorna -1.
*/
int numeroDeVertices(Grafo *g) {
  if (g != NULL)
    return g->numVertices;
  else
    return -1;
}

/* Funcao que retorna o numero de arestas do grafo apontado por g, caso o
   endereco armazenado em g seja diferente de NULL. Caso contrario, retorna -1.
*/
int numeroDeArestas(Grafo *g) {
  if (g != NULL)
    return g->numArestas;
  else
    return -1;
}

/* Funcao que retorna o grau do vertice v, caso ele exista.
   Caso contrario, retorna -1.
*/
int retornaGrauDoVertice(Grafo *g, int v) {
  if (!g || v < 0 || v >= g->numVertices)
    return -1;
  int x, grau = 0;
  for (x = 0; x < g->numVertices; x++) {
    if (g->matriz[v][x])
      grau++;
  }
  return grau;
}

/* Funcao que retorna true se o vertice v possui um ou mais
   vertices adjacentes (vizinhos).
*/
bool possuiVizinhos(Grafo *g, int v) {
  if (!g || v < 0 || v >= g->numVertices)
    return false;
  int x;
  for (x = 0; x < g->numVertices; x++)
    if (g->matriz[v][x])
      return true;
  return false;
}

/* Funcao que insere uma nova aresta no grafo.
   Se os vertices passados como parametro forem validos, ha duas possibilidades:
   - a aresta nao existia;
   - a aresta existia.
*/
bool insereAresta(Grafo *g, int v1, int v2) {
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices ||
      v1 == v2)
    return false;
  if (g->matriz[v1][v2] == false) {
    g->matriz[v1][v2] = true;
    g->matriz[v2][v1] = true;
    g->numArestas++;
  }
  return true;
}

/* Funcao que exclui a aresta entre v1 e v2 (caso exista uma aresta valida
   entre v1 e v2) e retorna true; ou retorna false, caso contrario.
*/
bool removeAresta(Grafo *g, int v1, int v2) {
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices ||
      g->matriz[v1][v2] == false)
    return false;
  g->matriz[v1][v2] = false;
  g->matriz[v2][v1] = false;
  g->numArestas--;
  return true;
}

/* Funcao que retorna true se existe uma aresta valida entre v1 e v2
   e false caso contrario.
*/
bool arestaExiste(Grafo *g, int v1, int v2) {
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices ||
      g->matriz[v1][v2] == false)
    return false;
  return true;
}

/* Funcao que cria um grafo com o numero de vertices e
   numero de arestas passados como parametro e retorna seu endereco.
*/
Grafo *criaGrafoAleatorio(int numVertices, int numArestas) {
  printf("################# Criando grafo com %i vertice(s) e com %i "
         "aresta(s). #################\n",
         numVertices, numArestas);
  int x, y, a = 0;
  if (numVertices < 1 || numArestas >= numVertices * (numVertices - 1) / 2) {
    printf("Parametros invalidos, o grafo nao sera gerado.\n");
    return NULL;
  }
  Grafo *g = (Grafo *)malloc(sizeof(Grafo));
  inicializaGrafo(g, numVertices);
  while (a < numArestas) {
    x = rand() % numVertices;
    y = rand() % numVertices;
    if (x != y && g->matriz[x][y] == false) {
      g->matriz[x][y] = true;
      g->matriz[y][x] = true;
      a++;
    }
  }
  g->numArestas = numArestas;
  return g;
}

/* Funcao desenvolvida para exibir um grafo, no formato de uma matriz
   de adjacencia.
*/
void exibeGrafo(Grafo *g) {
  if (!g)
    return;
  int x, y;
  printf("\nImprimindo grafo (vertices: %i; arestas: %i).\n   ", g->numVertices,
         g->numArestas);
  for (x = 0; x < g->numVertices; x++)
    printf(" %3i", x);
  printf("\n");
  for (x = 0; x < g->numVertices; x++) {
    printf("%3i", x);
    for (y = 0; y < g->numVertices; y++)
      printf(" %3i", g->matriz[x][y]);
    printf("\n");
  }
  printf("\n");
}

/* Funcao que exibe os valores de um arranjo de numeros reais */
void exibeArranjoReais(float *arranjo, int n) {
  int x;
  for (x = 0; x < n; x++)
    printf("  v%i\t", x);
  printf("\n");
  for (x = 0; x < n; x++) {
    printf("%3.2f\t", arranjo[x]);
  }
  printf("\n\n");
}

/* Funcao que exibe os valores de um arranjo de numeros inteiros */
void exibeArranjoInteiros(int *arranjo, int n) {
  int x;
  for (x = 0; x < n; x++)
    printf(" v%i\t", x);
  printf("\n");
  for (x = 0; x < n; x++) {
    printf("%3i\t", arranjo[x]);
  }
  printf("\n\n");
}

/* FUNCOES QUE DEVEM SER COMPLETADAS PARA RESOLVER O EP.
   A DESCRICAO DE CADA FUNCAO ESTA NO ENUNCIADO DO EP.
   www.each.usp.br/digiampietri/ACH2024/ep1/ep1.pdf        */

/* Vizinhos em Comum */
void vizinhosEmComum(Grafo *g, int v, int *vizinhos) {
  int i = 0, j = 0;

  for (i = 0; i < g->numVertices; i++)
    vizinhos[i] = 0;

  for (i = 0; i < g->numVertices; i++)
    for (j = 0; j < g->numVertices; j++)
      if (g->matriz[v][j] && g->matriz[i][j])
        vizinhos[i]++;
}

/* Coeficiente de Jaccard */
void coeficienteDeJaccard(Grafo *g, int v, float *coeficientes) {
  float numVizinhosIguais, numVizinhosUnidos, vizinhosY, vizinhosX;

  for (int c = 0; c < g->numVertices; c++)
    coeficientes[c] = 0;

  for (int i = 0; i < g->numVertices; i++) {
    numVizinhosIguais = 0, numVizinhosUnidos = 0, vizinhosX = 0, vizinhosY = 0;

    for (int j = 0; j < g->numVertices; j++) {
      if (g->matriz[v][j] && g->matriz[i][j])
        numVizinhosIguais++;
      if (g->matriz[v][j])
        vizinhosX++;
      if (g->matriz[i][j])
        vizinhosY++;
    }

    numVizinhosUnidos = vizinhosX + vizinhosY - numVizinhosIguais;

    if (numVizinhosUnidos == 0)
      coeficientes[i] = -1;

    float coeficienteJC = numVizinhosIguais / numVizinhosUnidos;
    if (numVizinhosUnidos != 0)
      coeficientes[i] = (coeficienteJC);
  }
}

/* Medida Adamic Adar */
void AdamicAdar(Grafo *g, int v, float *coeficientes) {
  int i = 0, j = 0, k = 0, l = 0, n = g->numVertices;
  int numVizinhosComum[n];
  int vizinhos[n];
  float coeficienteVizinho = 0;
  for (i = 0; i < n; i++) {
    numVizinhosComum[i] = 0;
    coeficientes[i] = 0;
    vizinhos[i] = 0;
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      for (k = 0; k < n; k++)
        if (g->matriz[v][k] && g->matriz[i][k])
          vizinhos[k] = 1;

    for (j = 0; j < n; j++)
      if (numVizinhosComum[j] == 1) {
        coeficientes[j] = -1;
      } else if (vizinhos[j]) {
        for (k = 0; k < n; k++) {
          if (g->matriz[j][k])
            numVizinhosComum[j]++;
        }
      }

    for (j = 0; j < n; j++) {
      if (numVizinhosComum[j] > 0)
        coeficienteVizinho += 1.0 / log(numVizinhosComum[j]);
    }
    if (coeficienteVizinho == INFINITY) coeficientes[i] = -1;
    else coeficientes[i] = coeficienteVizinho;

    coeficienteVizinho = 0;

    for (l = 0; l < n; l++) {
      numVizinhosComum[l] = 0;
      vizinhos[l] = 0;
    }
  }
}

/* Alocacao de Recursos */
void alocacaoDeRecursos(Grafo *g, int v, float *coeficientes) {
  int i = 0, j = 0, k = 0, l = 0, n = g->numVertices;
  float coeficienteVizinho = 0;
  int numVizinhosComum[n];
  int vizinhos[n];
  for (i = 0; i < n; i++) {
    numVizinhosComum[i] = 0;
    coeficientes[i] = 0;
    vizinhos[i] = 0;
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      for (k = 0; k < n; k++)
        if (g->matriz[v][k] && g->matriz[i][k])
          vizinhos[k] = 1;

    for (j = 0; j < n; j++)
      if (vizinhos[j]) {
        for (k = 0; k < n; k++) {
          if (g->matriz[j][k])
            numVizinhosComum[j]++;
        }
      }

    for (j = 0; j < n; j++) {
      if (numVizinhosComum[j] > 0)
        coeficienteVizinho += 1.0 / (numVizinhosComum[j]);
    }
    coeficientes[i] = coeficienteVizinho;
    coeficienteVizinho = 0;

    for (l = 0; l < n; l++) {
      numVizinhosComum[l] = 0;
      vizinhos[l] = 0;
    }
  }  
}

/* Similaridade Cosseno */
void similaridadeCosseno(Grafo *g, int v, float *coeficientes) {
  int i = 0, j = 0, numY = 0, numX = 0;
  int n = g->numVertices;
  int *vizinhosComuns = (int*) malloc(sizeof(int) * n);
  for (i = 0; i < n; i++) {
    coeficientes[i] = 0;
    vizinhosComuns[i] = 0;
  }

  vizinhosEmComum(g, v, vizinhosComuns);

  for(i = 0; i < n; i++) {
    for(j = 0; j < n; j++) {
      if(g->matriz[v][j]) numY++;
      if(g->matriz[i][j]) numX++;
    }
    if (sqrt(numX * numY) == 0)
      coeficientes[i] = -1;
    else 
      coeficientes[i] = (float) vizinhosComuns[i] / sqrt(numX * numY);
    numX = 0;
    numY = 0;
  }
}

/* Coeficiente de Dice */
void coeficienteDeDice(Grafo *g, int v, float *coeficientes) {
  int i = 0, j = 0, numX = 0, numY = 0, n = g->numVertices;
  int *vizinhosComuns = (int*) malloc(sizeof(int) * n);
  for (i = 0; i < g->numVertices; i++) {
    coeficientes[i] = 0;
    vizinhosComuns[i] = 0;
  }

  vizinhosEmComum(g, v, vizinhosComuns);

  for(i = 0; i < n; i++) {
    for(j = 0; j < n; j++) {
      if(g->matriz[v][j]) numY++;
      if(g->matriz[i][j]) numX++;
    }
    if (numX + numY == 0)
      coeficientes[i] = -1;
    else 
      coeficientes[i] = (float) 2 * vizinhosComuns[i] / (numX + numY);
    numX = 0;
    numY = 0;
  }

  /* Complete o codigo desta funcao */
}

/* Hub Promoted Index */
void HPI(Grafo *g, int v, float *coeficientes) {
  int i = 0, j = 0, numX = 0, numY = 0, menor = 0, n = g->numVertices;
  int *vizinhosComuns = (int*) malloc(sizeof(int) * n);

  for (i = 0; i < g->numVertices; i++) {
    coeficientes[i] = 0;
    vizinhosComuns[i] = 0;
  }

  vizinhosEmComum(g, v, vizinhosComuns);

  for(i = 0; i < n; i++) {
    for(j = 0; j < n; j++) {
      if(g->matriz[v][j]) numY++;
      if(g->matriz[i][j]) numX++;
    }
    if (numX == 0 || numY == 0)
      coeficientes[i] = -1;
    else {
      if (numY < numX)
        menor = numY;
      else 
        menor = numX;
      
      coeficientes[i] = (float) vizinhosComuns[i] / menor;
    }

    numX = 0, numY = 0, menor = 0;
  }
}

/* Hub Depressed Index */
void HDI(Grafo *g, int v, float *coeficientes) {
  int i = 0, j = 0, numX = 0, numY = 0, maior = 0, n = g->numVertices;
  int *vizinhosComuns = (int*) malloc(sizeof(int) * n);

  for (i = 0; i < g->numVertices; i++) {
    coeficientes[i] = 0;
    vizinhosComuns[i] = 0;
  }

  vizinhosEmComum(g, v, vizinhosComuns);

  for(i = 0; i < n; i++) {
    for(j = 0; j < n; j++) {
      if(g->matriz[v][j]) numY++;
      if(g->matriz[i][j]) numX++;
    }
    if ((numX == 0 && numY == 0))
      coeficientes[i] = -1;
    else {
      if (numY > numX)
        maior = numY;
      else 
        maior = numX;
      
      coeficientes[i] = (float) vizinhosComuns[i] / maior;
    }

    numX = 0, numY = 0, maior = 0;
  }
}

/* Funcao main para testar as funcoes implementadas neste EP.
   Esta parte do codigo nao sera usada na correcao do EP e nao contempla
   todos os testes possiveis.
   Fique a vontade para realizar testes adicionais.
*/
int main() {

  int n = 5;
  int *vComum = (int *)malloc(sizeof(int) * n);
  float *coeficientes = (float *)malloc(sizeof(float) * n);

  Grafo g1;

  printf("PRIMEIRO EXEMPLO\n");

  inicializaGrafo(&g1, n);
  insereAresta(&g1, 0, 1);
  insereAresta(&g1, 0, 2);
  insereAresta(&g1, 1, 4);
  insereAresta(&g1, 1, 3);
  insereAresta(&g1, 2, 3);

  exibeGrafo(&g1);

  printf("Vizinhos em Comum de v0:\n");
  vizinhosEmComum(&g1, 0, vComum);
  exibeArranjoInteiros(vComum, n);

  printf("Coeficientes de Jaccard de v0:\n");
  coeficienteDeJaccard(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Adamic-Adar de v0:\n");
  AdamicAdar(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Alocacao de Recursos de v0:\n");
  alocacaoDeRecursos(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Similaridade Cosseno de v0:\n");
  similaridadeCosseno(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  coeficienteDeDice(&g1, 0, coeficientes);
  printf("Coeficiente de Dice de v0:\n");
  exibeArranjoReais(coeficientes, n);

  HPI(&g1, 0, coeficientes);
  printf("Indice HPI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  HDI(&g1, 0, coeficientes);
  printf("Indice HDI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  printf("\n\nSEGUNDO EXEMPLO\n");

  // Excluindo duas arestas do grafo
  removeAresta(&g1, 0, 2);
  removeAresta(&g1, 2, 3);

  exibeGrafo(&g1);

  printf("Vizinhos em Comum de v0:\n");
  vizinhosEmComum(&g1, 0, vComum);
  exibeArranjoInteiros(vComum, n);

  printf("Coeficientes de Jaccard de v0:\n");
  coeficienteDeJaccard(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Adamic-Adar de v0:\n");
  AdamicAdar(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Alocacao de Recursos de v0:\n");
  alocacaoDeRecursos(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Similaridade Cosseno de v0:\n");
  similaridadeCosseno(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  coeficienteDeDice(&g1, 0, coeficientes);
  printf("Coeficiente de Dice de v0:\n");
  exibeArranjoReais(coeficientes, n);

  HPI(&g1, 0, coeficientes);
  printf("Indice HPI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  HDI(&g1, 0, coeficientes);
  printf("Indice HDI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  /* Grafo gerado aleatoriamente - pode ficar diferente
     de acordo com o compilador usado.                 */
  printf("\nTERCEIRO EXEMPLO\n");
  n = 6;
  int arestas = 8;

  free(vComum);
  free(coeficientes);
  vComum = (int *)malloc(sizeof(int) * n);
  coeficientes = (float *)malloc(sizeof(float) * n);

  Grafo *g2 = criaGrafoAleatorio(n, arestas);
  exibeGrafo(g2);

  printf("Vizinhos em Comum de v0:\n");
  vizinhosEmComum(g2, 0, vComum);
  exibeArranjoInteiros(vComum, n);

  printf("Vizinhos em Comum de v1:\n");
  vizinhosEmComum(g2, 1, vComum);
  exibeArranjoInteiros(vComum, n);

  printf("Vizinhos em Comum de v5:\n");
  vizinhosEmComum(g2, 5, vComum);
  exibeArranjoInteiros(vComum, n);

  printf("Coeficientes de Jaccard de v0:\n");
  coeficienteDeJaccard(g2, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Coeficientes de Jaccard de v1:\n");
  coeficienteDeJaccard(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Coeficientes de Jaccard de v5:\n");
  coeficienteDeJaccard(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Adamic-Adar de v0:\n");
  AdamicAdar(g2, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Adamic-Adar de v1:\n");
  AdamicAdar(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Adamic-Adar de v5:\n");
  AdamicAdar(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Alocacao de Recursos de v0:\n");
  alocacaoDeRecursos(g2, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Alocacao de Recursos de v1:\n");
  alocacaoDeRecursos(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Alocacao de Recursos de v5:\n");
  alocacaoDeRecursos(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Similaridade Cosseno de v0:\n");
  similaridadeCosseno(g2, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Similaridade Cosseno de v1:\n");
  similaridadeCosseno(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Similaridade Cosseno de v5:\n");
  similaridadeCosseno(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);

  coeficienteDeDice(g2, 0, coeficientes);
  printf("Coeficiente de Dice de v0:\n");
  exibeArranjoReais(coeficientes, n);

  printf("Coeficiente de Dice de v1:\n");
  coeficienteDeDice(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Coeficiente de Dice de v5:\n");
  coeficienteDeDice(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);

  HPI(g2, 0, coeficientes);
  printf("Indice HPI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  printf("Indice HPI de v1:\n");
  HPI(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Indice HPI de v5:\n");
  HPI(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);

  HDI(g2, 0, coeficientes);
  printf("Indice HDI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  printf("Indice HDI de v1:\n");
  HDI(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Indice HDI de v5:\n");
  HDI(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);

  return 0;
}