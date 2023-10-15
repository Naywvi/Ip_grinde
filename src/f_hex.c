// Convert decimal to hexadecimal and store the hexadecimal representation in a string
char* decimalToHex(int num) {
    char* hexString = (char*)malloc(3 * sizeof(char)); // 2 characters for the hexadecimal digits + 1 for the null terminator
    
    if (hexString == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la chaîne hexadécimale.\n");
        exit(1);
    }

    snprintf(hexString, 3, "%02X", num); // Convert decimal to hexadecimal

    return hexString;
}

// Convert each octet of the IP address to hexadecimal and store in an array of strings
char** loopDecimalToHex(int* ip) {
    char** hexIP = (char**)malloc(4 * sizeof(char*));
    
    if (hexIP == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour le tableau d'octets hexadécimaux.\n");
        //exit(1);
    }

    for (int i = 0; i < 4; i++) {
        hexIP[i] = decimalToHex(ip[i]);
    }

    return hexIP;
}