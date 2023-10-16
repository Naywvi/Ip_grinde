char *hexdecimal_convert(int *ipArray) {
    char *hexString = (char *)malloc(9);
    snprintf(hexString, sizeof(hexString), "%02X%02X%02X%02X", ipArray[0], ipArray[1], ipArray[2], ipArray[3]);
    return hexString; // Return the first character of the hexadecimal string
}
