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

    printf("a: %d, b: %d, operation: %d\n", a, b, operation);

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
}

void createMatrix(int n) {
    int *array;
    array = (int *) malloc(n * n * sizeof(int));

    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            *(array + i * n + j) = rand() & 0xff;
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%3d\t\t", *(array + i * n + j));
        }
        printf("\n");
    }
}

void runBinaryFormat() {
    int value;
    printf("enter value: ");
    scanf("%d", &value);
    printBinaryFormat(value);
}

void runHexFormat() {
    int value;
    printf("enter value: ");
    scanf("%d", &value);
    printHexFormat(value);
}

void runOptionOpCode() {
    int value;
    printf("enter value: ");
    scanf("%d", &value);
    int result = runOpCode(value);
    printf("%d\n", result);


}

void runCreateMatrix() {
    int value;
    printf("enter value: ");
    scanf("%d", &value);
    createMatrix(value);
}

int main() {
    int flag = 1;
    unsigned short value;

    while (flag == 1) {
        printf("Select a program to run: \n"
               "0) exit\n"
               "1) print binary format\n"
               "2) print hex format\n"
               "3) opCode\n"
               "4) createMatrix\n"
        );

        printf("enter option: ");
        scanf("%d", &value);

//        if (value == 0) {
//            flag = 0;
//        } else if (value == 1) {
//            runBinaryFormat();
//        } else if (value == 2) {
//            runBinaryFormat();
//        } else if (value == 3) {
//            runBinaryFormat();
//        } else if (value == 4) {
//            runBinaryFormat();
//        } else {
//            printf("Option wasn't recognized\n");
//        }

        switch (value) {
            case 0:
                flag = 0;
                break;
            case 1:
                runBinaryFormat();
                break;
            case 2:
                runHexFormat();
                break;
            case 3:
                runOptionOpCode();
                break;
            case 4:
                runCreateMatrix();
                break;
            default:
                printf("Option wasn't recognized\n");
                break;
        }
        printf("\n");


    }


//    printf("size of integer value: %lu bits\n", sizeof(unsigned int) * 8);
//    printf("size of short value: %lu bits\n", sizeof(unsigned short) * 8);

    return 0;
}