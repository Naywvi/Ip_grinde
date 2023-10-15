//Free all arrays
void freeArrays() {
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