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
   
    ip = checkIp(ipG);
    mask = checkMask(maskG);
    if(!ip||!mask)return 0; // Invalid IP or mask

    ipBin = loopDecimal(ip);
    maskBin = loopDecimal(mask);
    hexIP = loopDecimalToHex(ip);

    freeArrays(ip, mask, ipBin, maskBin, hexIP); // Free memory
    return 1;
}
//192.168.1.9
//255.255.255.0