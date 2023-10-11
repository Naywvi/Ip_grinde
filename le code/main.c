#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void decimalToBinary(int num)
{
    for (int i = 7; i >= 0; i--)
    {
        int bit = (num >> i) & 1;
        printf("%d", bit);
    }
    printf(" ");
}
int main(void)
{
    char ip[16];
    char mask[16];

    printf("IP (max 16) : ");
    fgets(ip, 16, stdin);
    printf("\nMask (max 16) : ");
    fgets(mask, 16, stdin);

    // Calcul de la longueur de la ip
    size_t lengthIp = strlen(ip);
    size_t lengthMask = strlen(mask);

    //>>>>>>>>> IP <<<<<<<<<<<<

    int octetsIP[4]; // Pour stocker chaque octet de l'IP sous forme d'entier
    int i = 0;       // Indice pour parcourir le tableau d'octets
    char *tokenIP;   // Pour stocker chaque octet en tant que token
    // Verifier s'il y a plus de trois points (quatre octets)

    int pointCountIP = 0;
    for (int j = 0; ip[j]; j++)
    {
        if (ip[j] == '.')
        {
            pointCountIP++;
        }
    }

    if (pointCountIP != 3)
    {
        printf("Error : Need ip valid.\n");
        return 1;
    }

    // Diviser l'adresse IP en tokens bases sur les points
    tokenIP = strtok(ip, ".");
    while (tokenIP != NULL && i < 4)
    {
        octetsIP[i] = atoi(tokenIP); // Convertir le token en entier
        if (octetsIP[i] < 0 || octetsIP[i] > 255)
        {
            printf("Error : octet %d invalid\n", i);
            return 1;
        }
        tokenIP = strtok(NULL, ".");
        i++;
    }

    // Afficher les octets
    for (i = 0; i < 4; i++)
    {
        printf("Octet %d : %d\n", i + 1, octetsIP[i]);
    }

    //>>>>>>>>> IP <<<<<<<<<<<<

    //>>>>>>>>> MASK <<<<<<<<<<<<
    int octetsM[4]; // Pour stocker chaque octet du masque en tant qu'entier
    int a = 0;      // Indice pour parcourir le tableau d'octets
    char *tokenM;   // Pour stocker chaque octet en tant que token

    int pointCountM = 0;

    for (int j = 0; mask[j]; j++)
    {
        if (mask[j] == '.')
        {
            pointCountM++;
        }
    }

    if (pointCountM != 3)
    {
        printf("Erreur : Le masque de sous-reseau doit contenir quatre octets.\n");
        return 1;
    }

    // Diviser le masque de sous-reseau en tokens bases sur les points
    tokenM = strtok(mask, ".");

    while (tokenM != NULL && a < 4)
    {
        octetsM[a] = atoi(tokenM); // Convertir le token en entier

        if (octetsM[a] < 0 || octetsM[a] > 255)
        {
            printf("Erreur : L'octet %d est invalide. Il doit etre compris entre 0 et 255.\n", a + 1);
            return 1;
        }
        tokenM = strtok(NULL, ".");
        a++;
    }

    if (a != 4)
    {
        printf("Erreur : Le masque de sous-reseau doit contenir quatre octets.\n");
        return 1;
    }
    a = 0; // Reset a car plus haut check des values non attribué
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
                        return 1;
                    }
                    k++;
                }
                // printf("Erreur : L'octet %d doit etre superieur à l'octet precedent.\n", a + 1);
                // return 1;
            }
            else
            {
                printf("Erreur : L'octet %d doit etre superieur à l'octet precedent.\n", a + 1);
                return 1;
            }
        }
        a++;
    }

    printf("Masque de sous-reseau valide :\n");
    for (i = 0; i < 4; i++)
    {
        printf("Octet %d : %d\n", i + 1, octetsM[i]);
    }
    //>>>>>>>>> MASK <<<<<<<<<<<<

    //>>>>>>>>> CONVERT TO BINARY <<<<<<<<<<<<
    int sizeBIP = sizeof(octetsIP) / sizeof(octetsIP[0]); // << Ici je le fais que pour l'ip
    for (int i = 0; i < sizeBIP; i++)
    {
        decimalToBinary(octetsIP[i]);
    }
    //>>>>>>>>> CONVERT TO BINARY <<<<<<<<<<<<

    //>>>>>>>>> CONVERT TO HEXA <<<<<<<<<<<<
    int sizeHexaIp = sizeof(octetsIP) / sizeof(octetsIP[0]); // << Ici je le fais que pour l'ip
    for (int i = 0; i < sizeHexaIp; i++)
    {
        printf("%X ", octetsIP[i]);
    }

    //>>>>>>>>> CONVERT TO HEXA <<<<<<<<<<<<
    return 0;
}

// recuperation de l'ip
// verification de l'ip
// envoie de l'ip
// idem pour mask
// return ip + mask
// possibilite notaion cidr
// regex
