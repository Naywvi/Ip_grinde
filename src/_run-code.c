void run(gchar *ipG, gchar *maskG)
{
    //Reset l'espace ==> free(ip) free(mask) et si tableau le faire aussi depuis son index
    int* ip = checkIp(ipG);
 
    int* mask = checkMask(maskG);

    int** ipBin = loopDecimal(ip);
    int** maskBin = loopDecimal(mask);
    char** hexIP = loopDecimalToHex(ip);

    //freeArrays(ip, mask, ipBin, maskBin, hexIP);
}