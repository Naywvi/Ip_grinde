// Global variables
static int* ip;
static int* mask;
static int** ipBin;
static int** maskBin;
static char** hexIP;

int run(gchar *ipG, gchar *maskG)
{
    printf("IP: %s\n", ipG);
    printf("Mask: %s\n", maskG);
   
    ip = checkIp(ipG); // MOMO
    mask = checkMask(maskG); // RUBEN
    if(!ip||!mask)return 0; // Invalid IP or mask

    ipBin = loopDecimal(ip); // MOMO
    maskBin = loopDecimal(mask); 
    hexIP = loopDecimalToHex(ip); // RUBEN

    freeArrays(); // Free memory
    return 1;
}