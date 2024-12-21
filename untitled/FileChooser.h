//
// Created by admin on 11/03/2024.
//

#ifndef UNTITLED_FILECHOOSER_H
#define UNTITLED_FILECHOOSER_H

typedef struct
{
    GtkWidget *file_chooser; // Widget GtkFileChooser
    gchar *selected_file;    // Chemin du fichier sélectionné
} MonFileChooser;

MonFileChooser* create_file_chooser_widget(const gchar *title, GtkFileChooserAction action)
{
    MonFileChooser *file_chooser = g_new(MonFileChooser, 1);
    file_chooser->file_chooser = gtk_file_chooser_dialog_new(title, NULL, action,
                                                             "_Cancel", GTK_RESPONSE_CANCEL, "_Open",
                                                             GTK_RESPONSE_ACCEPT, NULL);
    file_chooser->selected_file = NULL;

    return file_chooser;
}


void set_file_chooser_file(MonFileChooser *file_chooser, const gchar *file_path)
{
    if (file_chooser == NULL) return;

    gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(file_chooser->file_chooser), file_path);
}

gchar* get_selected_file(MonFileChooser *file_chooser)
{
    if (file_chooser == NULL) return NULL;

    gchar *file_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser->file_chooser));
    if (file_chooser->selected_file != NULL) {
        g_free(file_chooser->selected_file);
    }
    file_chooser->selected_file = g_strdup(file_path);
    return file_path;
}

void destroy_file_chooser_widget(MonFileChooser *file_chooser)
{
    if (file_chooser == NULL) return;

    gtk_widget_destroy(file_chooser->file_chooser);
    g_free(file_chooser->selected_file);
    g_free(file_chooser);
}

#endif //UNTITLED_FILECHOOSER_H
