
#include <stdio.h>
static int* ipInt;

int* convert_ip(const char* ipString) {
    int* octetsIP = (int*)malloc(4 * sizeof(int));
    int i = 0;
    char *tokenIP;

    tokenIP = strtok(ipString, ".");

    while (tokenIP != NULL && i < 4) {
        octetsIP[i] = atoi(tokenIP);
        tokenIP = strtok(NULL, ".");
        i++;
    }

    return octetsIP;
}

static GtkTextBuffer *text_buffer;
//Generate range on buffer & check check box
void generate_subnet(unsigned int ip, unsigned int mask, gboolean binaryS, gboolean hexadecimalS) {
    unsigned int subnetAddress = ip & mask;
    unsigned int broadcastAddress = ip | ~mask;
    char **binaryIP; 
    char ipString[16];
    char *hexString;
    
    GtkTextIter iter;
    for (unsigned int i = subnetAddress + 1; i < broadcastAddress; i++) {
        snprintf(ipString, sizeof(ipString), "%u.%u.%u.%u", (i >> 24) & 0xFF, (i >> 16) & 0xFF, (i >> 8) & 0xFF, i & 0xFF);
        char ok[16];
        strcpy(ok, g_strdup(ipString));
        ipInt = convert_ip(ok);
        gtk_text_buffer_get_end_iter(text_buffer, &iter);
        gtk_text_buffer_insert(text_buffer, &iter, ipString, -1);
        gtk_text_buffer_insert(text_buffer, &iter, "\n", -1);
        
        if (binaryS) {
            binaryIP = binary_convert_loop(ipInt); // Convertir en binaire
            for (int j = 0; j < 4; j++) {
                gtk_text_buffer_insert(text_buffer, &iter, binaryIP[j], -1); // Insérer la chaîne binaire
                gtk_text_buffer_insert(text_buffer, &iter, " ", -1); // Ajouter un espace entre les octets binaires
            }
            gtk_text_buffer_insert(text_buffer, &iter, "\n", -1);
            for (int j = 0; j < 4; j++) {
                free(binaryIP[j]);
            }
            free(binaryIP);
        }
        
        if (hexadecimalS) {// Convert hexa
            hexString = hexdecimal_convert(ipInt);
            gtk_text_buffer_insert(text_buffer, &iter, hexString, -1);
            gtk_text_buffer_insert(text_buffer, &iter, "\n", -1);
            free(hexString);
        }
        gtk_text_buffer_insert(text_buffer, &iter, "\n", -1);
    }
}


//Convert & calculate range main function
void calculate_range(int *ip, int *mask, gboolean binaryS, gboolean hexadecimalS) {
    unsigned int ipE = (ip[0] << 24) | (ip[1] << 16) | (ip[2] << 8) | ip[3];
    unsigned int maskE = (mask[0] << 24) | (mask[1] << 16) | (mask[2] << 8) | mask[3];
    generate_subnet(ipE, maskE, binaryS, hexadecimalS);
    return;
}
