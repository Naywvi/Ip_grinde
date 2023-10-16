
static char *saveIp;
static char *saveM;

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
