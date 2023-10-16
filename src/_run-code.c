// Global variables
static int* ip;
static int* mask;

// Loop code ip / mask / binary / hexadecimal / widget / user_data
int run(gchar *ipG, gchar *maskG, gboolean binaryS, gboolean hexadecimalS)
{
    ip = check_ip(ipG); // MOMO
    mask = check_mask(maskG); // RUBEN
    if(!ip||!mask)return 0; // Invalid IP or mask

    calculate_range(ip, mask, binaryS, hexadecimalS);
 
    freeArrays(ip, mask); // Free memory
    return 1;
}