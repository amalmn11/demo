//
// Created by admin on 03/03/2024.
//

#ifndef UNTITLED_IMAGE_H
#define UNTITLED_IMAGE_H

///////////////////////////////////////////////////////////////////////////////////////////////////////
//MonImage
//--------> structure d'image
typedef struct
{
    GtkWidget *image;   // Objet image GTK
    gchar *path;        // Chemin d'accès à l'image
    coordonnees ImCrd; // Position de l'image
    dimension dim; //largeur et hauteur
}MonImage;
//--------> fonction pour changer la la heuteur et largeur d'image
/*************************************************************
Nom          : change_image_size()
Entrée       : Un pointeur vers un widget GTK+ qui affiche une image
              La nouvelle largeur/hauteur de l'image
Sortie       : -
Description  : permet de changer la taille d'une image affichée dans un widget GTK+
*************************************************************/
void change_image_size(GtkWidget *image_widget, int width, int height)
{
    GdkPixbuf *pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(image_widget));
    // Vérification si le GdkPixbuf est valide
    if (pixbuf != NULL)
    {
        // Redimensionnement du GdkPixbuf à la taille spécifiée
        GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, width,
                                                           height, GDK_INTERP_BILINEAR);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image_widget), scaled_pixbuf);
        // Libération de la mémoire allouée pour le GdkPixbuf
        g_object_unref(scaled_pixbuf);
    }//fin if(pixbuf != NULL)
}//Fin Fonction change_image_size()

//--------> fonction de creation d'image
/*************************************************************
Nom          : create_image_widget()
Entrée       : image_path - chemin d'accès à l'image
               x - position horizontale de l'image
               y - position verticale de l'image
               dim - dimensions de l'image
Sortie       : MonImage* - pointeur vers la structure MonImage créée
Description  : Elle initialise une structure MonImage.
*************************************************************/
MonImage* create_image_widget(const gchar *image_path, gint x, gint y,dimension dim)
{
    // Allocation de mémoire pour la structure MonImage
    MonImage *my_image = g_new(MonImage, 1);
    // Création d'un widget image GTK à partir du fichier image spécifié
    my_image->image = gtk_image_new_from_file(image_path);
    // Copie du chemin d'accès à l'image dans la structure MonImage
    my_image->path = g_strdup(image_path);
    // Attribution de la position horizontale et verticale de l'image dans la structure MonImage
    my_image->ImCrd.x = x;
    my_image->ImCrd.y = y;
    // Attribution des dimensions de l'image dans la structure MonImage
    my_image->dim.width=dim.width;
    my_image->dim.height=dim.height;
    // Changement de la taille de l'image en fonction des dimensions spécifiées
    change_image_size(my_image->image,my_image->dim.width,my_image->dim.height);
    return my_image;
}//Fin fonction create_image_widget()

#endif //UNTITLED_IMAGE_H
