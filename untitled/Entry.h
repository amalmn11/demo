//
// Created by admin on 03/03/2024.
//

#ifndef UNTITLED_ENTRY_H
#define UNTITLED_ENTRY_H
#include "FixedContainer.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
//myEntry
//-------------> Structure de myEntry
typedef struct
{
    GtkWidget* entry;           // Widget GTK+ de l'entrée
    gchar placeholder_text[50]; // Texte de remplacement (placeholder)
    dimension dim;             // Dimensions de l'entrée
    gint max_nbr_caracteres; // Nombre maximal de caractères autorisés dans l'entrée
    gint visibility;       // Visibilité du texte (0: masqué, 1: visible)
    gint set_frame;      // Cadre autour de l'entrée (0: non, 1: oui)
    gint val_alignement; // Alignement vertical du texte (0: haut, 1: milieu, 2: bas)
    //alignement
    /*
      0, cela signifie que le texte sera aligné complètement à gauche dans le widget
      1, cela signifie que le texte sera aligné complètement à droite dans le widget.
      0.5, cela signifie que le texte sera centré horizontalement dans le widget.
     */
    gchar car_replacement; //caractere de remplacement (pour mot de passe)
    gchar icon_path[30]; // Chemin vers une icône associée
}myEntry;

//------------>fonction d'initialisation
/*************************************************************
Nom          : init_entry()
Entrée       : placeholder_text - Texte de remplacement
               dim - Dimensions de l'entrée
               max_nbr_caracteres - Nombre maximal de caractères autorisés dans l'entrée
               visibility - Visibilité du texte dans l'entrée (0: masqué, 1: visible)
               set_frame - Indique s'il faut afficher un cadre autour de l'entrée (0: non, 1: oui)
               val_alignement - Alignement vertical du texte dans l'entrée (0: haut, 1: milieu, 2: bas)
               car_replacement - Caractère de remplacement
               icon_path - Chemin vers une icône
Sortie       : Un pointeur vers une nouvelle structure myEntry initialisée
Description  : Initialise une structure myEntry avec les valeurs fournies
*************************************************************/
myEntry* init_entry(gchar placeholder_text[50],dimension dim,gint max_nbr_caracteres,
                    gint visibility,gint set_frame,gint val_alignement,
                    gchar car_replacement,gchar icon_path[30])
{
    // Allocation dynamique de mémoire pour une instance de myEntry
    myEntry *Entry=(myEntry*)malloc(sizeof(myEntry));
    // Vérification de l'allocation de mémoire
    if(!Entry)
    {
        printf("\nerreur d'allocation de memoire.");
        exit(0);
    }//Fin if(!Entry)
    // Initialisation des champs de la structure myEntry avec les valeurs fournies
    Entry->dim=dim;
    Entry->car_replacement=car_replacement;
    Entry->max_nbr_caracteres=max_nbr_caracteres;
    strcpy(Entry->icon_path,icon_path);
    Entry->set_frame=set_frame;
    Entry->val_alignement=val_alignement;
    strcpy(Entry->placeholder_text,placeholder_text);
    Entry->visibility=visibility;
    // Retour de la structure myEntry initialisée
    return ((myEntry*)Entry);
}//Fin fonction init_entry()

//-------------> fonction creer_entry()
/*************************************************************
Nom          :  creer_entry()
Entrée       : entry - Un pointeur vers une structure myEntry
Sortie       : -
Description  : Crée un widget d'entrée en utilisant les valeurs spécifiées
dans la structure myEntry fournie.
*************************************************************/
void creer_entry(myEntry* entry)
{
    // Crée un nouveau widget d'entrée GTK+
    entry->entry=gtk_entry_new();
    // Définit le texte de l'entrée en utilisant le texte de remplacement spécifié
    gtk_entry_set_text(GTK_ENTRY(entry->entry), entry->placeholder_text);
    // Définit la taille de l'entrée en utilisant les dimensions spécifiées
    gtk_widget_set_size_request(entry->entry, entry->dim.width,  entry->dim.height);
    // Définit le nombre maximal de caractères autorisés dans l'entrée
    gtk_entry_set_max_length(GTK_ENTRY(entry->entry), entry->max_nbr_caracteres);
    // Définit la visibilité du texte dans l'entrée
    if(!entry->visibility)
        gtk_entry_set_visibility(GTK_ENTRY(entry->entry),FALSE);
    else
        gtk_entry_set_visibility(GTK_ENTRY(entry->entry),TRUE);
    // Définit si l'entrée doit avoir un cadre autour d'elle
    if(!entry->set_frame)
        gtk_entry_set_has_frame(GTK_ENTRY(entry->entry), FALSE);
    else
        gtk_entry_set_has_frame(GTK_ENTRY(entry->entry), TRUE);
    // Définit l'alignement du texte dans l'entrée
    gtk_entry_set_alignment(GTK_ENTRY(entry->entry), entry->val_alignement);
    // Charge l'icône à partir du chemin spécifié
    GdkPixbuf *pixbuf =  create_icon_from_file(entry->icon_path);
    gtk_entry_set_icon_from_pixbuf(GTK_ENTRY(entry->entry), GTK_ENTRY_ICON_PRIMARY, pixbuf);
    // Définit le caractère de remplacement
    gtk_entry_set_invisible_char(GTK_ENTRY(entry->entry), entry->car_replacement);
}//Fin fonction creer_entry()


/////////////////////////////////////////////////////////////////////////////////////////////
//MAIN
int mainEntry(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    //creation d'un type color
    hexa_color *myColor = NULL;
    myColor =init_hexa_color(myColor, "pink");
    //creation type dimension
    dimension *dim;
    dim=(dimension*)malloc(sizeof(dimension));
    dim->height=400;
    dim->width=500;

    //creation type coordonees
    coordonnees *cord=(coordonnees*)malloc(sizeof(coordonnees));
    cord->y=0;
    cord->x=0;

    //image de background
    MonImage *bgImg=create_image_widget("background.png",0,0,*dim);

    //creation+initialisation
    window *maFenetre= init_window(*dim,3,"fatiha's window","flower.png",0,
                                   GTK_WIN_POS_CENTER_ALWAYS,*cord,*myColor,*bgImg);
    create_window(maFenetre);

    /////////////////////////////
    ///CREATION DE GTKBox
    dimension *dim3= create_dimension(50,300);
    FixedContainer *fixed=init_FixedContainer(*dim3,"myFixed");
    create_FixedContainer(fixed);
    //1) ajouter Entry
    dimension *dim2= create_dimension(40,50);
    //entry
    myEntry *entry= init_entry("text par defaut",*dim3,30,0,
                               1,0,'*',"lock.png");
    creer_entry(entry);
    //entry2
    myEntry *entry2= init_entry("Nom",*dim3,30,1,
                                1,0,'-',"woman.png");
    creer_entry(entry2);
    //entry3
    myEntry *entry3= init_entry("Prenom",*dim3,30,1,
                                1,0,'-',"woman.png");
    creer_entry(entry3);
    //entry4
    myEntry *entry4= init_entry("adresse",*dim3,30,1,
                                1,0,'-',"adresse.png");
    creer_entry(entry4);
    ajouter_element_fixed(fixed->container,entry->entry,100,20);
    ajouter_element_fixed(fixed->container,entry2->entry,100,80);
    ajouter_element_fixed(fixed->container,entry3->entry,100,140);
    ajouter_element_fixed(fixed->container,entry4->entry,100,200);
    gtk_container_add(GTK_CONTAINER(maFenetre->window),fixed->container);
    // Afficher tous les widgets
    gtk_widget_show_all(maFenetre->window);
    gtk_main();
    return 0;
}


#endif //UNTITLED_ENTRY_H
