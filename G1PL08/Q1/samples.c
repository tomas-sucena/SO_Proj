#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    // verificar se há argumentos suficientes
    if (argc < 4){
        perror("Error! Not enough arguments");
        return EXIT_FAILURE;
    }

    FILE* fptr = fopen(argv[1], "r");

    // caso haja um erro a encontrar o ficheiro
    if (fptr == NULL){
        char* error_msg = (char*) malloc(64 * sizeof(char));
        sprintf(error_msg, "Error! The file \"%s\" could not be opened", argv[1]);

        perror(error_msg);

        return EXIT_FAILURE;
    }

    srandom(0); // inicializar a seed

    int n = atoi(argv[2]);
    int m = atoi(argv[3]);

    // verificar se os argumentos são válidos
    if (n < 0){
        perror("Error! Number of segments cannot be negative");
        return EXIT_FAILURE;
    }
    else if (m < 0){
        perror("Error! The size of a segment cannot be negative");
        return EXIT_FAILURE;
    }

    // descobrir o tamanho do ficheiro
    fseek(fptr, 0L, SEEK_END);

    long F_SIZE = ftell(fptr); // tamanho do ficheiro

    rewind(fptr);

    // imprimir os fragmentos de texto
    for (int i = 0; i < n; i++){
        long off = random() % (F_SIZE - m); // posição a partir da qual vão ser impressos os caracteres

        fseek(fptr, off, SEEK_SET);
        
        printf(">");
        for (int j = 0; j < m;){
            char c = fgetc(fptr);

            // ignorar as mudanças de linha
            if (c < 32){
                continue;
            }

            printf("%c", c);
            j++;
        }
        printf("<\n");

        rewind(fptr);
    }

    return EXIT_SUCCESS;
}