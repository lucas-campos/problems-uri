
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 51
#define MAXCHAR 256

typedef struct {
    int initialPosition;
    int length;
} Standard;

typedef struct {
    int sizeSubString;
    int sizeSet;
    Standard *elements;
} StandardSet;

// ---------------------------------------------------------------------------------------------------------
// FUNÇÕES QUE IMPLEMENTAM O PADRÃO DE PROCESSAMENTO DE CARACTERES BOYER-MOORE-HORSPOOL-SUNDAY -------------
// ---------------------------------------------------------------------------------------------------------

void BMHS(StandardSet *standardSet, char *string, char *textStandard, int lengthStandard);

int execBMHS(char *string, int lengthString, char *textStandard, Standard *standard);

// ---------------------------------------------------------------------------------------------------------
// Demais Funções do programa principal. -------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------

// Limpa o vetor de caracteres, setando '\0' para cada posição.
void clearText(char *text, short int size);

// Retorna o tamanho do texto válido.
short int lengthText(char *text);

// Compara o tamanho dos textos A e B e define a texto e o padrao a ser encontrado.
void defineStringAndStandard(char *textA, char *textB, char **string, char **standard);

// Define o conjunto de vetores
void defineStandardSet(StandardSet **standardSet, char *standard);

// Define os elementos do conjunto de padrões.
void defineElements(Standard *elements, short int lengthStandard, short int lengthNewStandard);

int main() {

    // Define as variáveis e as inicializa.
    char text1[MAX_SIZE];
    char text2[MAX_SIZE];
    clearText(&text1[0], MAX_SIZE);
    clearText(&text2[0], MAX_SIZE);

    while (1 == 1) {
        
        if (!gets(text1) || !gets(text2)) {
            break;
        };

        // Resolve o problema

        // Define o texto e o padrao principal.
        char *string, *standard;
        defineStringAndStandard(&text1[0], &text2[0], &string, &standard);

        // Define o vetor de StandardSet
        StandardSet* standardSet = (StandardSet*) malloc(lengthText(&standard[0]) * sizeof(StandardSet));

        // Define o Conjunto com todos os padrões possíveis.
        defineStandardSet(&standardSet, &standard[0]);

        // Método que executa o algoritmo BMHS para o conjunto de padrões.
        BMHS(standardSet, &string[0], &standard[0], lengthText(&standard[0]));

        // Limpa as variaveis para a proxima instancia do problema.
        clearText(&text1[0], MAX_SIZE);
        clearText(&text2[0], MAX_SIZE);

        // Limpa a estrutura.
        free(standardSet);
    }

    return 0;

}

void clearText(char *text, short int size) {

    int i = 0;
    for (; i < size; i++) {
        text[i] = '\0';
    }
}

short int lengthText(char *text) {

    short int index = 0;
    while (text[index] != '\0') {
        index++;
    }
    return index;
}

void defineStringAndStandard(char *textA, char *textB, char **string, char **standard) {

    short int lengthA = lengthText(&textA[0]);
    short int lengthB = lengthText(&textB[0]);

    if (lengthA > lengthB) {
        *string = &textA[0];
        *standard = &textB[0];
    } else {
        *string = &textB[0];
        *standard = &textA[0];
    }
}

void defineStandardSet(StandardSet **standardSet, char *standard) {

    int lengthStandard = lengthText(&standard[0]);
    int lengthNewStandard = lengthStandard;
    int index = 0;
    for (; index < lengthStandard; index++) {
        (*standardSet)[index].sizeSubString = lengthNewStandard;
        (*standardSet)[index].sizeSet = index+1;
        (*standardSet)[index].elements = malloc(sizeof(Standard) * (index+1));
        // Define todos os elementos do conjunto.
        defineElements((*standardSet)[index].elements, lengthStandard, --lengthNewStandard);
    }
}

void defineElements(Standard *elements, short int lengthStandard, short int lengthNewStandard) {

    int beginIndex = 0;
    int index = lengthNewStandard;

    for (; index < lengthStandard; index++) {
        elements[beginIndex].initialPosition = beginIndex;
        elements[beginIndex].length = lengthNewStandard+1;
        beginIndex++;
    }
}

void BMHS(StandardSet *standardSet, char *string, char *textStandard, int lengthStandard) {

    int lengthString = lengthText(&string[0]);
    int resultFinal = 0;

    int index = 0;
    while (index < lengthStandard) {

        int sizeSet = 0;
        int result = 0;

        while (sizeSet < standardSet[index].sizeSet && result == 0) {
            result = execBMHS(&string[0], lengthString, &textStandard[0], &(standardSet[index].elements[sizeSet]));
            sizeSet++;
        }
        if (result == 1) {
            printf("%d\n", standardSet[index].elements[sizeSet-1].length);
            resultFinal = 1;
            break;
        }
        index++;        
    }
    if (resultFinal == 0) {
        printf("0\n");
    }
}

int execBMHS(char *string, int lengthString, char *textStandard, Standard *standard) {

    int length = lengthText(&string[0]);
    int table[MAXCHAR +1];

    int i = 0;
    for (; i <= MAXCHAR; i++) {
        table[i] = standard -> length + 1;
    }
    
    int positionStandard;
    int j = 1;
    for (; j <= standard -> length; j++) {
        positionStandard = j-1+(standard->initialPosition);

        int value = textStandard[positionStandard];
        table[value] = (standard -> length - j + 1);
    }

    int indexAux;
    int index = standard -> length;
    while (index <= lengthString) {
        indexAux = index;
        j = standard -> length + standard -> initialPosition;
        while (indexAux > 0 && j > standard -> initialPosition && string[indexAux-1] == textStandard[j-1]) {
            indexAux--;
            j--;
        }
        if (j == standard -> initialPosition) {
            return 1;
        }
        index += (table[(int)string[index]]);
    }
    return 0;

}