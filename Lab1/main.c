#include <stdio.h>
#include <stdlib.h>

char getCharValue(unsigned char byte) {
    char result = 0;
    if (byte >= 0 && byte < 10) result = 48 + byte;
    else if (byte >= 10 && byte <= 15) result = 65 + (byte - 10);
    return result;
}

void printHexFormat(int value) {
    int sizeInt = sizeof(unsigned int) * 8;
    for (int i = sizeInt - 4; i >= 0; i -= 4) {
        printf("%c", getCharValue((value >> i) & 0b1111));
    }
}

void printBinaryFormat(int value) {
    int sizeInt = sizeof(unsigned int) * 8;
    for (int i = 0; i < sizeInt; i++) {
        printf("%d", (value >> (sizeInt - i - 1)) & 0b1);
    }
}

int runOpCode(unsigned int value) {
    /**
        0000 A + B
        0001 A − B
        0010 B − A
        0011 A + 1
        0100 A − 1
        0101 B + 1
        0110 B − 1
        0111 A × B
        1000 A/B
        1001 A Mod B
        1010 Not A
        1011 Not B
        1100 A And B
        1101 A Or B
        1110 A Xor B
        1111 0
     */
    unsigned int b = value & 0xff;
    unsigned int a = (value >> 8) & 0xff;
    short operation = (value >> 16) & 0b1111;

    switch (operation) {
        case 0:
            return a + b;
        case 1:
            return a - b;
        case 2:
            return b - a;
        case 3:
            return a + 1;
        case 4:
            return a - 1;
        case 5:
            return b + 1;
        case 6:
            return b - 1;
        case 7:
            return a * b;
        case 8:
            return a / b;
        case 9:
            return a % b;
        case 10:
            return !a;
        case 11:
            return !b;
        case 12:
            return a & b;
        case 13:
            return a | b;
        case 14:
            return (!a & b) | (a & !b);
        default:
            return 0;
    }

    printf("a: %d, b: %d, operation: ", a, b);
    printBinaryFormat(operation);
}

void createMatrix(int n) {
    int **array;
    array = (int **) malloc(n * n * sizeof(int));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(*(array + i) + j) = rand();
        }
    }

//    for (int i = 0; i < 10; i++) {
//        for (int j = 0; j < 10; j++) {
//            int value = *(*(array + i) + j);
//            printf("value %d\t", value);
//        }
//        printf("\n");
//    }
}

int main() {
    printf("size of integer value: %lu bits\n", sizeof(unsigned int) * 8);
    printf("size of short value: %lu bits\n", sizeof(unsigned short) * 8);

//    unsigned int value;
//    scanf("%d", &value);
//    printHexFormat(value);

//    unsigned int reference = 460046;
//    runOpCode(reference);

    createMatrix(10);

    return 0;
}