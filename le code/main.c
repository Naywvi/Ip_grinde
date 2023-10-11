#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Free all arrays
void freeArrays(int* ip, int* mask, int** ipBin, int** maskBin, char** hexIP) {
    free(ip);
    free(mask);

    for (int i = 0; i < 4; i++) {
        free(ipBin[i]);
        free(maskBin[i]);
        free(hexIP[i]);
    }

    free(ipBin);
    free(maskBin);
    free(hexIP);
}

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
char** lopDecimalToHex(int* ip) {
    char** hexIP = (char**)malloc(4 * sizeof(char*));
    
    if (hexIP == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour le tableau d'octets hexadécimaux.\n");
        exit(1);
    }

    for (int i = 0; i < 4; i++) {
        hexIP[i] = decimalToHex(ip[i]);
    }

    return hexIP;
}

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
int** lopDecimal(int* ip) {
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


//Check Ip
int* checkIp(){
    printf("IP (max 16) : ");
    char ip[16];
    fgets(ip, 16, stdin);
    ip[strcspn(ip, "\n")] = '\0'; // Supprime le caractère de nouvelle ligne
    size_t lengthIp = strlen(ip);

    int* octetsIP = (int*)malloc(4 * sizeof(int));// Tableau dynamique pour stocker chaque octet de l'adresse IP en tant qu'entier
    int i = 0;       // Indice pour parcourir le tableau d'octets
    char *tokenIP;   // Pour stocker chaque octet en tant que token
    // Verifier s'il y a plus de trois points (quatre octets)

    int pointCountIP = 0;
    for (int j = 0; ip[j]; j++)
    {
        if (ip[j] == '.')pointCountIP++;
        
    }

    if (pointCountIP != 3)
    {
        printf("Error : Need ip valid.\n");
        exit(1);
    }

    // Diviser l'adresse IP en tokens bases sur les points
    tokenIP = strtok(ip, ".");
    while (tokenIP != NULL && i < 4)
    {
        octetsIP[i] = atoi(tokenIP); // Convertir le token en entier
        if (octetsIP[i] < 0 || octetsIP[i] > 255)
        {
            printf("Error : octet %d invalid\n", i);
            exit(1);
        }
        tokenIP = strtok(NULL, ".");
        i++;
    }
    return octetsIP;
}
int* checkMask(){
    printf("\nMask (max 16) : ");
    char mask[16];
    fgets(mask, 16, stdin);
    mask[strcspn(mask, "\n")] = '\0';
    size_t lengthMask = strlen(mask);
    int* octetsM = (int*)malloc(4 * sizeof(int));
    int i = 0;
    int a = 0;      // Indice pour parcourir le tableau d'octets
    char *tokenM;   // Pour stocker chaque octet en tant que token

    int pointCountM = 0;

    for (int j = 0; mask[j]; j++)
    {
        if (mask[j] == '.') pointCountM++;
    }

    if (pointCountM != 3)
    {
        printf("Erreur : Le masque de sous-reseau doit contenir quatre octets.\n");
        exit(1);
    }

    // Diviser le masque de sous-reseau en tokens bases sur les points
    tokenM = strtok(mask, ".");

    while (tokenM != NULL && a < 4)
    {
        octetsM[a] = atoi(tokenM); // Convertir le token en entier
        if (octetsM[a] < 0 || octetsM[a] > 255)
        {
            printf("Erreur : L'octet %d est invalide. Il doit etre compris entre 0 et 255.\n", a + 1);
            exit(1);
        }
        tokenM = strtok(NULL, ".");
        a++;
    }

    if (a != 4)
    {
        printf("Erreur : Le masque de sous-reseau doit contenir quatre octets.\n");
        exit(1);
    }

    a = 0; // Reset to verify if octet is 0
    while (tokenM != NULL && a < 4)
    {
        if (a > 0 && octetsM[a] < octetsM[a - 1] && octetsM[a] != octetsM[3])
        {
            if (octetsM[a] == 0)
            {

                for (int k = a + 1; k < 4 - a; k++)
                {
                    if (octetsM[k] != 0)
                    {
                        printf("Erreur : L'octet %d doit etre egal a 0.\n", a + 1);
                        exit(1);
                    }
                    k++;
                }
            }
            else
            {
                printf("Erreur : L'octet %d doit etre superieur à l'octet precedent.\n", a + 1);
                exit(1);
            }
        }
        a++;
    }
    return octetsM;
}
int main(void)
{
    //Reset l'espace ==> free(ip) free(mask) et si tableau le faire aussi depuis son index
    int* ip = checkIp();
    int* mask = checkMask();
    int** ipBin = lopDecimal(ip);
    int** maskBin = lopDecimal(mask);
    char** hexIP = lopDecimalToHex(ip);

    freeArrays(ip, mask, ipBin, maskBin, hexIP);
    return 0;
}

// possibilite notation cidr
// regex
