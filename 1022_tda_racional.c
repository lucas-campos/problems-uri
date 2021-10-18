
/*
 * Problema: 1022 - https://www.urionlinejudge.com.br/judge/pt/problems/view/1022
 * Descrição: Um ponto relevante foi a sacada de descobrir uma forma simples de simplificar a fração utilizando o cálculo do MDC pelo algoritmo de Euclides
 * Autor: Lucas Campos.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int numerator;
  int denominator;
} RationalNumber;

RationalNumber *newRationalNumber(int numerator, int denominator);
void deleteRationalNumber(RationalNumber *rationalNumber);
RationalNumber *performCalulation(RationalNumber *first, RationalNumber *second, char operation);
RationalNumber *performAdditionNumber(RationalNumber *first, RationalNumber *second);
RationalNumber *performSubtractionNumber(RationalNumber *first, RationalNumber *second);
RationalNumber *performMultiplicationNumber(RationalNumber *first, RationalNumber *second);
RationalNumber *performDivisionNumber(RationalNumber *first, RationalNumber *second);
RationalNumber *performSimplificaton(RationalNumber *rationalNumber);
int calculateMDC(int first, int second);

void printResult(RationalNumber *numberCalculation, RationalNumber *numberSimplification) {
  printf("%d/%d = %d/%d\n",
    numberCalculation->numerator, numberCalculation->denominator,
    numberSimplification->numerator, numberSimplification->denominator);
}

int main() {

  int totalCases = 0;
  int firstNumerator, firstDenominator, secondNumerator, secondDenominator;
  char operation;

  scanf("%d", &totalCases);

  while (totalCases > 0) {
    totalCases--;

    scanf("%d / %d %c %d / %d", &firstNumerator, &firstDenominator, &operation, &secondNumerator, &secondDenominator);

    RationalNumber *firstRationalNumber = newRationalNumber(firstNumerator, firstDenominator);
    RationalNumber *secondRationalNumber = newRationalNumber(secondNumerator, secondDenominator);
    RationalNumber *calculationResult = performCalulation(firstRationalNumber, secondRationalNumber, operation);
    RationalNumber *simplificationResult = performSimplificaton(calculationResult);

    printResult(calculationResult, simplificationResult);

    deleteRationalNumber(firstRationalNumber);
    deleteRationalNumber(secondRationalNumber);
    deleteRationalNumber(calculationResult);
    deleteRationalNumber(simplificationResult);

  }
  return 0;
}

RationalNumber *newRationalNumber(int numerator, int denominator) {
  RationalNumber *rationalNumber = malloc(sizeof(RationalNumber));
  rationalNumber -> numerator = numerator;
  rationalNumber -> denominator = denominator;
  return rationalNumber;
}

void deleteRationalNumber(RationalNumber *rationalNumber) {
  free(rationalNumber);
}

RationalNumber *performCalulation(RationalNumber *first, RationalNumber *second, char operation) {
  switch (operation) {
    case '+':
      return performAdditionNumber(first, second);
    case '-':
      return performSubtractionNumber(first, second);
    case '*':
      return performMultiplicationNumber(first, second);
    case '/':
      return performDivisionNumber(first, second);
  }
}

RationalNumber *performAdditionNumber(RationalNumber *first, RationalNumber *second) {
  int numerator = (first->numerator * second->denominator) + (second->numerator * first->denominator);
  int denominator = first->denominator * second->denominator;
  return newRationalNumber(numerator, denominator);
}

RationalNumber *performSubtractionNumber(RationalNumber *first, RationalNumber *second) {
  int numerator = (first->numerator * second->denominator) - (second->numerator * first->denominator);
  int denominator = first->denominator * second->denominator;
  return newRationalNumber(numerator, denominator);
}

RationalNumber *performMultiplicationNumber(RationalNumber *first, RationalNumber *second) {
  int numerator = first->numerator * second->numerator;
  int denominator = first->denominator * second->denominator;
  return newRationalNumber(numerator, denominator); 
}

RationalNumber *performDivisionNumber(RationalNumber *first, RationalNumber *second) {
  int numerator = first->numerator * second->denominator;
  int denominator = second->numerator * first->denominator;
  return newRationalNumber(numerator, denominator);
}

RationalNumber *performSimplificaton(RationalNumber *rationalNumber) {
  int mdc = calculateMDC(rationalNumber->numerator, rationalNumber->denominator);
  mdc = (mdc < 0) ? mdc* (-1) : mdc;
  
  int numerator = rationalNumber->numerator / mdc;
  int denominator = rationalNumber->denominator / mdc;
  return newRationalNumber(numerator, denominator);
}

int calculateMDC(int first, int second) {
  int rest = first % second;
  if (rest == 0) {
    return second;
  }
  return calculateMDC(second, rest);
}
