/*
 * Problema: 2588 - https://www.urionlinejudge.com.br/judge/pt/problems/view/2588
 * Autor: Lucas Campos.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_PALAVRA 1000

void limpaVetor(int v[]);

int main () {

  char palavra[TAMANHO_PALAVRA];

  int letras[200];
  int ocorrencias[200];

  while (1 == 1) {

    if (!gets(palavra)) break;

    int tamanhoPalavra = strlen(palavra);
    if (tamanhoPalavra == 1) {
      printf("0\n");
      continue;
    }

    limpaVetor(&letras[0]);
    limpaVetor(&ocorrencias[0]);

    int i = 0;
    for (; i < tamanhoPalavra; i++) {
      int indicePalavra = palavra[i];
      ocorrencias[indicePalavra]++;
    }

    int totalOcorImp = 0;
    i = 0;
    for (; i < 200; i++) {
      if (ocorrencias[i]%2 != 0) {
        totalOcorImp++;
      }
    }

    if (totalOcorImp > 0) {
      printf("%d\n", totalOcorImp-1);
    } else {
      printf("0\n");
    }

  }
  
  return 0;
}

void limpaVetor(int v[]) {
  int i = 0;
  for (; i < 200; i++) {
    v[i] = 0;
  }
}