// Convert decimal to binary and store the binary representation in an array
int* decimalToBinary(int num) {
    int* binaryArray = (int*)malloc(8 * sizeof(int));
    
    if (binaryArray == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour le tableau binaire.\n");
        exit(1);
    }

    for (int i = 0; i < 8; i++) {
        binaryArray[i] = (num >> (7 - i)) & 1;
    }

    return binaryArray;
}

// Convert each octet of the IP address to binary and store in an array 
int** loopDecimal(int *ip) {
    int** binaryIP = (int**)malloc(4 * sizeof(int*));
    if (binaryIP == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour le tableau d'octets binaires.\n");
        exit(1);
    }

    for (int i = 0; i < 4; i++) {
        binaryIP[i] = decimalToBinary(ip[i]);
    }

    return binaryIP;
}