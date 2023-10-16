// Check mask protocole
int* check_mask(gchar *mask){
    size_t lengthMask = strlen(mask);
    int* octetsM = (int*)malloc(4 * sizeof(int)); // Dynamic allocation of memory
    int i = 0;
    int a = 0;
    int j = 0;
    char *tokenM;
    int pointCountM = 0;

    for (j ; mask[j]; j++)
    {
        if (mask[j] == '.') pointCountM++;
    }

    if (pointCountM != 3)return 0; // Bad mask format

    // Divide the string into tokens with delimiter as "."
    tokenM = strtok(mask, ".");

    while (tokenM != NULL && a < 4)
    {
        octetsM[a] = atoi(tokenM); // Convertir le token en entier
        if (octetsM[a] < 0 || octetsM[a] > 255)return 0; // Invalid octet value
        tokenM = strtok(NULL, ".");
        a++;
    }

    if (a != 4)return 0; // Bad mask format

    a = 0; // Reset a to 0
    while (tokenM != NULL && a < 4)
    {
        if (a > 0 && octetsM[a] < octetsM[a - 1] && octetsM[a] != octetsM[3])
        {
            if (octetsM[a] == 0)
            {
                for (int k = a + 1; k < 4 - a; k++)
                {
                    if (octetsM[k] != 0)return 0; // Invalid mask equal to 0
                    k++;
                }
            }
            else return 0; // Invalid mask value [0] < [1]
        }
        a++;
    }
    return octetsM;
}