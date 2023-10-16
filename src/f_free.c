//Free all arrays
void freeArrays(int* ip, int* mask) {
    free(ip);
    free(mask);
}

// Json data
void free_data(char **ipArray, char **maskArray, int count) {
    for (int i = 0; i < count; i++) {
        free(ipArray[i]);
        free(maskArray[i]);
    }
    free(ipArray);
    free(maskArray);
}