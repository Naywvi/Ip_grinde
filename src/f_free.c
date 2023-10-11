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