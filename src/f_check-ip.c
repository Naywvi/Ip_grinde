//Check Ip protocole
int* checkIp(gchar *ip){
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