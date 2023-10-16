// Convert decimal to binary and store the binary representation in a character array
char* binary_convert(int num) {
    char* binaryArray = (char*)malloc(9);  // 8 bits + '\0'

    if (binaryArray == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour le tableau binaire.\n");
        exit(1);
    }

    for (int i = 0; i < 8; i++) {
        binaryArray[i] = ((num >> (7 - i)) & 1) ? '1' : '0';// Fonction ternaire
    }
    binaryArray[8] = '\0';  // Null-terminate the string

    return binaryArray;
}

// Convert each octet of the IP address to binary and store in a character array
char** binary_convert_loop(int *ip) {
    char** binaryIP = (char**)malloc(4 * sizeof(char*));

    if (binaryIP == NULL) { // Ram 100% => exit
        fprintf(stderr, "Erreur d'allocation de mémoire pour le tableau d'octets binaires.\n");
        exit(1);
    }

    for (int i = 0; i < 4; i++) {
        binaryIP[i] = binary_convert(ip[i]);
    }
    return binaryIP;
}
