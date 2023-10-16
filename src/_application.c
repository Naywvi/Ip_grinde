#include "../includes/code.h"
#include <gtk/gtk.h>
//Struct to contain Ip / Mask entry
typedef struct {
    GtkWidget *entryIp;
    GtkWidget *entryM;
    gboolean *binaryCheck;
    gboolean *hexadecimalCheck;
} EntryData;

int binaryChecked;       
int hexadecimalChecked; 

static GtkTextBuffer *text_buffer; // Variable global for text buffer

static GtkWidget *entryMa; // Variable global for mask entry

// Warning dialog popup
void show_warning_dialog(const gchar *message) {
    // Invisible window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_POPUP);

    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_WARNING,
        GTK_BUTTONS_OK,
        message
    );
    // Run the popup
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    gtk_widget_destroy(dialog); // Destroy when the user clicks on the button
}

// Load data from the file & print the list in the GtkTextView
void print_list(){
    const char *filename = "./list.json";
    char **ipArray = NULL;
    char **maskArray = NULL;
    int count = 0;

    load_data(filename, &ipArray, &maskArray, &count);

    if (count > 0) {
        GtkTextIter iter;
        for (int i = 0; i < count; i++) {
            gtk_text_buffer_get_end_iter(text_buffer, &iter);
            gtk_text_buffer_insert(text_buffer, &iter, ipArray[i], -1);
            gtk_text_buffer_insert(text_buffer, &iter, "\n", -1);
            gtk_text_buffer_insert(text_buffer, &iter, maskArray[i], -1);
            gtk_text_buffer_insert(text_buffer, &iter, "\n\n", -1);
        }
    } else show_warning_dialog("No data found in the file.");
    
    free_data(ipArray, maskArray, count);
}

//Empty input2
static void on_ip_entry_changed(GtkWidget *entry, gpointer user_data) {
    const gchar *ip = gtk_entry_get_text(GTK_ENTRY(entry));

    // If the IP entry is empty, disable the mask entry
    if (strlen(ip) == 0) {
        gtk_widget_set_sensitive(entryMa, FALSE);
        gtk_entry_set_text(GTK_ENTRY(entryMa), ""); // Delete the text in the mask entry
    } else {
        gtk_widget_set_sensitive(entryMa, TRUE); // Or enable it
    }
}

// Send text to the GtkTextView
static void send_text(GtkWidget *widget, gpointer user_data) {

    EntryData *data = (EntryData *)user_data;
    const gchar *ip = gtk_entry_get_text(GTK_ENTRY(data->entryIp));
    const gchar *mask = gtk_entry_get_text(GTK_ENTRY(data->entryM));
    const gboolean hexadecimalS = data->hexadecimalCheck;
    const gboolean binaryS = data->binaryCheck;
    gchar *a = g_strdup(ip);
    gchar *b = g_strdup(mask); // Copy the string to avoid overwriting it

    if (strlen(ip) == 0 || strlen(mask) == 0) {
        show_warning_dialog("Please enter a valid ip address and mask");
        return;
    }else{
        if(!run(ip, mask, binaryS, hexadecimalS))
            show_warning_dialog("Please enter a valid ip address and mask");
        else {
            save_L(a,b); // save
            show_warning_dialog("Add to the list");
        }
        gtk_entry_set_text(GTK_ENTRY(entryMa), ""); 
        gtk_entry_set_text(GTK_ENTRY(data->entryIp), "");
    }
}

// Save button
void save_B(GtkWidget *widget, gpointer user_data) {
    EntryData *data = (EntryData *)user_data;
    const gchar *ip = gtk_entry_get_text(GTK_ENTRY(data->entryIp));
    const gchar *mask = gtk_entry_get_text(GTK_ENTRY(data->entryM));
    save(ip,mask); // save
    show_warning_dialog("Saved");
}

//Event quit()
void on_window_destroy(GtkWidget *widget, gpointer user_data) {
    gtk_main_quit();
}

static void on_binary_toggled(GtkToggleButton *button, gpointer user_data) {
    EntryData *data = (EntryData *)user_data;
    data->binaryCheck = gtk_toggle_button_get_active(button);
}

static void on_hexadecimal_toggled(GtkToggleButton *button, gpointer user_data) {
    EntryData *data = (EntryData *)user_data;
    data->hexadecimalCheck = gtk_toggle_button_get_active(button);
}

// Main gtk function
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *button_box;
    GtkWidget *entryIp;
    GtkWidget *entryM;
    GtkWidget *send_button;
    GtkWidget *text_view;
    GtkWidget *scrolled_window; 
    GtkWidget *binary;
    GtkWidget *hexadecimal;
    GtkWidget *save_button;
    GtkWidget *check_button_list;

    // Window configuration
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Ip_grinde - #github.com/Naywvi/Ip_grinde");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL); // event quit()

    // Grid vertical container
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), main_box);

    // Grid horizontal container
    button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(main_box), button_box, FALSE, FALSE, 0);

    // Area for text entry
    entryIp = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryIp), "Example: 192.168.1.1");
    gtk_box_pack_start(GTK_BOX(main_box), entryIp, FALSE, FALSE, 0);

    entryMa = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryMa), "Example: 255.255.255.0");
    gtk_box_pack_start(GTK_BOX(main_box), entryMa, FALSE, FALSE, 0);
    
    gtk_widget_set_sensitive(entryM, FALSE); // Disabled if IP input is empty

    // Init struct for send_text()
    EntryData *data = g_new(EntryData, 1);
    data->entryIp = entryIp;
    data->entryM = entryMa;
    data->binaryCheck = binary;
    data->hexadecimalCheck = hexadecimal;
    data->binaryCheck = 0;
    data->hexadecimalCheck = 0;

    g_signal_connect(entryIp, "changed", G_CALLBACK(on_ip_entry_changed), data); // event disabled field mask

    // Check box binary & hexadecimal
    binary = gtk_check_button_new_with_label("Binary");
    g_signal_connect(G_OBJECT(binary), "toggled", G_CALLBACK(on_binary_toggled), data); // event check binary
    gtk_box_pack_start(GTK_BOX(main_box), binary, FALSE, FALSE, 0);

    hexadecimal = gtk_check_button_new_with_label("Hexadecimal");
    g_signal_connect(G_OBJECT(hexadecimal), "toggled", G_CALLBACK(on_hexadecimal_toggled), data); // event check binary
    gtk_box_pack_start(GTK_BOX(main_box), hexadecimal, FALSE, FALSE, 0);

    // Button for sending text
    send_button = gtk_button_new_with_label("Submit");
    g_signal_connect(send_button, "clicked", G_CALLBACK(send_text), data);
    gtk_box_pack_start(GTK_BOX(main_box), send_button, FALSE, FALSE, 0);

    save_button = gtk_button_new_with_label("Save");
    g_signal_connect(save_button, "clicked", G_CALLBACK(save_B), data);
    gtk_box_pack_start(GTK_BOX(main_box), save_button, FALSE, FALSE, 0);

    //annuaire
    check_button_list = gtk_button_new_with_label("Check list");
    g_signal_connect(check_button_list, "clicked", G_CALLBACK(print_list), data);
    gtk_box_pack_start(GTK_BOX(main_box), check_button_list, FALSE, FALSE, 0);

    // Area view (GtkTextView)
    text_view = gtk_text_view_new();
    gtk_widget_set_sensitive(text_view, FALSE); // Disable text view

    scrolled_window = gtk_scrolled_window_new(NULL, NULL); // Scroll barre
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    gtk_box_pack_start(GTK_BOX(main_box), scrolled_window, TRUE, TRUE, 0);


    // Buffer GtkTextView
    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    
    //Check save
    if(check_save()){
        gtk_entry_set_text(GTK_ENTRY(entryIp), saveIp);
        gtk_entry_set_text(GTK_ENTRY(entryMa), saveM);
    }
    

    // Initialisation of the window
    gtk_widget_show_all(window);
}