#include <gtk/gtk.h>
#include "../includes/code.h"

//Struct to contain Ip / Mask entry
typedef struct {
    GtkWidget *entryIp;
    GtkWidget *entryM;
} EntryData;

static GtkTextBuffer *text_buffer; // Variable global for text buffer
static GtkWidget *entryMa; // Variable global for mask entry

static void on_ip_entry_changed(GtkWidget *entry, gpointer user_data) {
    const gchar *ip = gtk_entry_get_text(GTK_ENTRY(entry));

    // Si l'adresse IP est vide, désactivez l'entrée du masque
    if (strlen(ip) == 0) {
        gtk_widget_set_sensitive(entryMa, FALSE);
        gtk_entry_set_text(GTK_ENTRY(entryMa), ""); // Effacez le contenu de l'entrée du masque
    } else {
        gtk_widget_set_sensitive(entryMa, TRUE); // Sinon, activez l'entrée du masque
    }
}

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

// Send text to the GtkTextView
static void send_text(GtkWidget *widget, gpointer user_data) {
    EntryData *data = (EntryData *)user_data;
    const gchar *ip = gtk_entry_get_text(GTK_ENTRY(data->entryIp));
    const gchar *mask = gtk_entry_get_text(GTK_ENTRY(data->entryM));
    gchar *a = g_strdup(ip);
    gchar *b = g_strdup(mask); // Copy the string to avoid overwriting it

    if (strlen(ip) == 0 || strlen(mask) == 0) {
        //show_warning_dialog("Please enter a valid ip address and mask");
        return;
    }else{
        //Reset inputs
        if(run(ip, mask)){
            // Add to view with buffer
            GtkTextIter iter;
            gtk_text_buffer_get_end_iter(text_buffer, &iter); // End buffer
            gtk_text_buffer_insert(text_buffer, &iter, a, -1); // Add at the end
            gtk_text_buffer_insert(text_buffer, &iter, "\n", -1); // Add new line
            gtk_text_buffer_insert(text_buffer, &iter, b, -1); // Add at the end
            gtk_text_buffer_insert(text_buffer, &iter, "\n", -1); // Add new line
        }else{
            show_warning_dialog("Please enter a valid ip address and mask");
        }
        gtk_entry_set_text(GTK_ENTRY(entryMa), ""); 
        gtk_entry_set_text(GTK_ENTRY(data->entryIp), "");
    }
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *button_box;
    GtkWidget *entryIp;
    GtkWidget *entryM;
    GtkWidget *send_button;
    GtkWidget *text_view;
    GtkWidget *binary;
    GtkWidget *hexadecimal;

    // Window configuration
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Ip_grinde - #github.com/Naywvi/Ip_grinde");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

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

    g_signal_connect(entryIp, "changed", G_CALLBACK(on_ip_entry_changed), entryMa);

    // Init struct for send_text()
    EntryData *data = g_new(EntryData, 1);
    data->entryIp = entryIp;
    data->entryM = entryMa;

    // Check box binary & hexadecimal
    binary = gtk_check_button_new_with_label("Case à cocher 1");
    gtk_box_pack_start(GTK_BOX(main_box), binary, FALSE, FALSE, 0);

    hexadecimal = gtk_check_button_new_with_label("Case à cocher 2");
    gtk_box_pack_start(GTK_BOX(main_box), hexadecimal, FALSE, FALSE, 0);

    // Button for sending text
    send_button = gtk_button_new_with_label("Submit");
    g_signal_connect(send_button, "clicked", G_CALLBACK(send_text), data);
    gtk_box_pack_start(GTK_BOX(main_box), send_button, FALSE, FALSE, 0);

    // Area view (GtkTextView)
    text_view = gtk_text_view_new();
    gtk_widget_set_sensitive(text_view, FALSE);// Disable text view
    gtk_box_pack_start(GTK_BOX(main_box), text_view, TRUE, TRUE, 0); // Param TRUE, TRUE => Expand, Fill
    
    // Buffer GtkTextView
    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    // Initialisation of the window
    gtk_widget_show_all(window);
}