//Check Ip protocole
int* checkIp(gchar *ip){
    size_t lengthIp = strlen(ip);
    int* octetsIP = (int*)malloc(4 * sizeof(int)); // Dynamic allocation of memory
    int i = 0;
    char *tokenIP;

    int pointCountIP = 0;
    for (int j = 0; ip[j]; j++)
    {
        if (ip[j] == '.')pointCountIP++;
    }

    if (pointCountIP != 3)return 0; // Bad IP format
    
    // Divide the string into tokens with delimiter as "."
    tokenIP = strtok(ip, ".");
    
    while (tokenIP != NULL && i < 4)
    {
        octetsIP[i] = atoi(tokenIP); // Convert all the tokens to integers
        if (octetsIP[i] < 0 || octetsIP[i] > 255)return 0; // Invalid octet value
        tokenIP = strtok(NULL, ".");
        i++;
    }
    return octetsIP;
}
// Check a.a.a.a