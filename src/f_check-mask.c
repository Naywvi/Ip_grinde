int* checkMask(gchar *mask){
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