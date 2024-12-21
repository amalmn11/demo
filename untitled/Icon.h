//
// Created by admin on 03/03/2024.
//

#ifndef UNTITLED_ICON_H
#define UNTITLED_ICON_H

////////////////////////////////////////////////////////////////////////////////////////////////
//icon
//--------> fonction de creation d'un icon
GdkPixbuf* create_icon_from_file(const gchar file_path[50])
{
    GdkPixbuf *icon;
    GError *error = NULL;
    icon = gdk_pixbuf_new_from_file(file_path, &error);
    if (error != NULL)
    {
        // Affichage de l'erreur en cas d'échec du chargement de l'icône
        g_printerr("Erreur lors du chargement de l'icône : %s\n", error->message);
        g_error_free(error);
        return NULL;
    }//FIn if (error != NULL)
    return icon;
}//FIN fonction create_icon_from_file()

///////////////////////////////////////////////////////////////////////////////////////////
GtkWidget* create_image_widget_from_file(const gchar *file_path) {
    GdkPixbuf *pixbuf;
    GtkWidget *image_widget;

    // Charger l'image à partir du fichier spécifié
    pixbuf = gdk_pixbuf_new_from_file(file_path, NULL);
    if (!pixbuf) {
        // Afficher une erreur si le chargement de l'image échoue
        g_printerr("Erreur lors du chargement de l'image : %s\n", file_path);
        return NULL;
    }
    // Créer un widget GtkImage à partir de l'image chargée
    image_widget = gtk_image_new_from_pixbuf(pixbuf);
    g_object_unref(pixbuf);  // Libérer la mémoire utilisée par le pixbuf, car le widget GtkImage le détient désormais
    return image_widget;
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void set_icon_size(GtkWidget *image_widget, int width, int height) {
    GdkPixbuf *pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(image_widget));
    if (pixbuf != NULL) {
        GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_BILINEAR);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image_widget), scaled_pixbuf);
        g_object_unref(scaled_pixbuf);  // Free the scaled pixbuf after use
    }
}
#endif //UNTITLED_ICON_H
