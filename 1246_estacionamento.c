/*
 * Problema: 1246 - https://www.urionlinejudge.com.br/judge/pt/problems/view/1246
 * Autor: Lucas Campos.
 */


#include <stdio.h>

#define SIZE_MAX_PARKING 1000
#define SIZE_CARS 9000

int main() {

    // Armazena o tamanho do carro caso esteja no estacionamento. Se "0" então o carro(placa) não está no estacionamento.
    int sizeCars[SIZE_CARS];
    // Indica a posição inicial do carro(placa) no estacionamento.
    int positionCars[SIZE_CARS];
    // Contém as posições do tamanho do estacionamento. 
    int parking[SIZE_MAX_PARKING];

    // Variáveis para recuperar o tamanho do estacionamento e o total de entradas e saídas.
    int parkingSpace = 0;
    int numberEvents = 0;

    // Variáveis para recuperar uma entrada ou saída do estacionamento, veiculo e seu tamanho.
    char typeEvent;
    int placa;
    int size;

    int index;
    int valueTotal;

    while (1) {

        // Inicializa as estruturas para uma nova instância do problema
        for (index = 0; index < SIZE_MAX_PARKING; index++) {
            sizeCars[index] = 0;
            positionCars[index] = -1;
            parking[index] = -1;
        }
        for (; index < SIZE_CARS; index++) {
            sizeCars[index] = 0;
            positionCars[index] = -1;
        }
        valueTotal = 0;

        scanf(" %d %d*c", &parkingSpace, &numberEvents);
        if (feof(stdin)) {
            break;
        }

        while (numberEvents > 0) {

            scanf(" %c*c", &typeEvent);
            if (typeEvent == 'C') {
                scanf(" %d %d*c", &placa, &size);

                // Caso o carro não esteja no estacionamento.
                if (positionCars[placa - 1000] == -1) {

                    // Verificar se existe um lugar no estacionamento
                    index = 0;
                    for (; index < parkingSpace; index++) {

                        // Encotra a primeira posição livre do estacionamento.
                        while (parking[index] != -1 && index < parkingSpace) {
                            index++;
                        }
                        if (index < parkingSpace) {
                            int count = 0; 
                            while (parking[index] == -1 && count < size && index < parkingSpace) {
                                index++;
                                count++;
                            }

                            // Encontrou a primeira vaga que cabe o carro
                            if (count == size) {
                                while (count > 0) {
                                    parking[index-count] = placa - 1000;
                                    count--;
                                }

                                positionCars[placa - 1000] = index-size;
                                sizeCars[placa - 1000] = size;

                                valueTotal += 10;
                                break;
                            }
                        }
                    }
                }

            } else {
                scanf(" %d*c", &placa);
                if (positionCars[placa - 1000] != -1) {
                    index = positionCars[placa - 1000];
                    int positionFinal = index + sizeCars[placa - 1000];
                    for (; index < positionFinal; index++) {
                        parking[index] = -1;
                    }

                    positionCars[placa - 1000] = -1;
                    sizeCars[placa - 1000] = 0;
                }
            }
            numberEvents--;
        }
        printf("%d\n", valueTotal);
    }
    return 0;
}