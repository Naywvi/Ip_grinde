#include <gtk/gtk.h>

static GtkTextBuffer *text_buffer; // Variable global

static void send_text(GtkWidget *widget, gpointer data)
{
    GtkWidget *entry = GTK_WIDGET(data);
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(entry));

    // Recuperation of text data
    g_print("send => : %s\n", text);

    // Add to buffer
    GtkTextIter iter;
    gtk_text_buffer_get_end_iter(text_buffer, &iter);     // The end of the buffer
    gtk_text_buffer_insert(text_buffer, &iter, text, -1); // Add to the end
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button_box;
    GtkWidget *entry;
    GtkWidget *send_button;
    GtkWidget *text_view;

    // Window configuration
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Grid vertical container
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), main_box);

    // Grid horizontal container
    button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(main_box), button_box, FALSE, FALSE, 0);

    // Area for text entry
    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Add valid ip address");
    gtk_box_pack_start(GTK_BOX(main_box), entry, FALSE, FALSE, 0);

    // Button for sending text
    send_button = gtk_button_new_with_label("Submit");
    g_signal_connect(send_button, "clicked", G_CALLBACK(send_text), entry);
    gtk_box_pack_start(GTK_BOX(main_box), send_button, FALSE, FALSE, 0);

    // Area view (GtkTextView)
    text_view = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(main_box), text_view, TRUE, TRUE, 0); // Param TRUE, TRUE => Expand, Fill

    // Buffer GtkTextView
    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    // Initialisation of the window
    gtk_widget_show_all(window);
}