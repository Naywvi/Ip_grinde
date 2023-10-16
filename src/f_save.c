
static char *saveIp;
static char *saveM;

//Load Data for print list
void load_data(const char *filename, char ***ipArray, char ***maskArray, int *count) {
    *ipArray = NULL;
    *maskArray = NULL;
    *count = 0;

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening the file for reading");
        return;
    }

    json_t *root = json_loadf(file, 0, NULL);
    fclose(file);

    if (!root || !json_is_object(root)) {
        fprintf(stderr, "Invalid JSON data in the file.\n");
        return;
    }

    json_t *ipJson = json_object_get(root, "ip");
    json_t *maskJson = json_object_get(root, "mask");

    if (json_is_array(ipJson) && json_is_array(maskJson)) {
        *count = json_array_size(ipJson);
        *ipArray = (char **)malloc(sizeof(char *) * *count);
        *maskArray = (char **)malloc(sizeof(char *) * *count);

        for (int i = 0; i < *count; i++) {
            json_t *ipItem = json_array_get(ipJson, i);
            json_t *maskItem = json_array_get(maskJson, i);

            if (json_is_string(ipItem) && json_is_string(maskItem)) {
                const char *ipStr = json_string_value(ipItem);
                const char *maskStr = json_string_value(maskItem);

                (*ipArray)[i] = strdup(ipStr);
                (*maskArray)[i] = strdup(maskStr);
            }
        }
    }

    json_decref(root);
}

//Create json list
void save_L(const gchar *ip, const gchar *mask) {
    if(!ip||!mask)return; // Invalid IP or mask

    const char *filename = "./list.json";
    FILE *file = fopen(filename, "r");
    json_t *root = NULL;

    if (file) {
        root = json_loadf(file, 0, NULL);
        fclose(file);
    } else {
        root = json_object();
    }

    // Get the "ip" and "mask" arrays from the JSON object
    json_t *ipArray = json_object_get(root, "ip");
    json_t *maskArray = json_object_get(root, "mask");

    if (!ipArray) {
        ipArray = json_array();
        json_object_set_new(root, "ip", ipArray);
    }
    if (!maskArray) {
        maskArray = json_array();
        json_object_set_new(root, "mask", maskArray);
    }

    // Add the provided values to the arrays
    json_array_append_new(ipArray, json_string(ip));
    json_array_append_new(maskArray, json_string(mask));

    file = fopen(filename, "w");
    if (file) {
        json_dumpf(root, file, JSON_INDENT(4));
        fclose(file);
    } else {
        perror("Error opening the file for writing");
    }

    json_decref(root);
}


// Save IP and mask in a JSON file if quit() event
void save(const gchar *ip, const gchar *mask) {

    json_t *root = json_object(); // Créer un objet JSON

    // Ajouter les données à l'objet JSON
    json_object_set_new(root, "ip", json_string(ip));
    json_object_set_new(root, "mask", json_string(mask));

    // Ouvrir un fichier pour écriture
    const char *filename = "./config.json";
    FILE *file = fopen(filename, "w");
    if (file) {
        // Écrire l'objet JSON dans le fichier
        json_dumpf(root, file, JSON_INDENT(4));
        fclose(file);
    } else {
        perror("Erreur lors de l'ouverture du fichier pour écriture");
    }

    json_decref(root); // Libérer la mémoire de l'objet JSON
}

//Check if the file exist
int check_save() {
    // Open Json
    const char *filename = "./config.json";
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    // Load JSON
    json_t *root;
    json_error_t error;
    root = json_loadf(file, 0, &error);
    fclose(file);

    if (!root) {
        fprintf(stderr, "Error loading file: %s\n", error.text);
        return 0;
    }

    // Extract IP and mask values
    json_t *ip = json_object_get(root, "ip");
    json_t *mask = json_object_get(root, "mask");

    if (!json_is_string(ip) || !json_is_string(mask)) {
        fprintf(stderr, "Bad format values.\n");
        json_decref(root); // Free memory before exit
        return 0;
    }

    const char *ip_str = json_string_value(ip);
    const char *mask_str = json_string_value(mask);
   
    saveIp = strdup(ip_str);
    saveM = strdup(mask_str);

    // Free memory
    json_decref(root);

    return 1;
}
