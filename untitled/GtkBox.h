//
// Created by admin on 03/03/2024.
//

#ifndef UNTITLED_GTKBOX_H
#define UNTITLED_GTKBOX_H


///////////////////////////////////////////////////////////////////////////////////////////////////////
//Mybox
//-------------> structure Mybox
//GTKBox
typedef struct
{
    GtkWidget *box;       // Widget GTK+ représentant la boîte
    gchar nom_class[40];  // Nom de la classe associée à la boîte
    gchar orientation; // Orientation de la boîte (v: verticale / h: horizontale)
    gint space_child; // Espacement entre les enfants de la boîte
    dimension dim;   // Dimensions de la boîte
    gint halign; // Alignement horizontal des enfants (1: début / 2: fin ...)
    gint valign;// Alignement vertical des enfants (CENTER / END / BASELINE)
    hexa_color bgColor; // Couleur de fond de la boîte
    gint homogene; // Homogénéité 0:TRUE or 1:FALSE
}Mybox;

//---------> fonction d'initialisation d'un box
/*************************************************************
Nom          : init_box()
Entrée       : nom_class - Nom de la classe associée à la boîte
               orientation - Orientation de la boîte (v: verticale / h: horizontale)
               space_child - Espacement entre les enfants de la boîte
               dim - Dimensions de la boîte
               halign - Alignement horizontal des enfants (1: début / 2: fin ...)
               valign - Alignement vertical des enfants (CENTER / END / BASELINE)
               bgColor - Couleur de fond de la boîte
               homogene - Homogénéité de l'espacement des enfants (0:TRUE or 1:FALSE)
Sortie       : Un pointeur vers une structure Mybox initialisée
Description  : Initialise une structure Mybox avec les valeurs fournies
*************************************************************/
Mybox* init_box(gchar nom_class[40], gchar orientation,gint space_child,dimension dim,
                gint halign,gint valign,hexa_color bgColor,gint homogene)
{
    // Allocation dynamique de mémoire pour une instance de Mybox
    Mybox * box=NULL;
    box=(Mybox*)malloc(sizeof(Mybox));
    // Vérification de l'allocation de mémoire
    if(!box)
    {
        printf("\nerreur d'allocation de memoire.");
        exit(0);
    }//Fin if(!box)
    // Initialisation des champs de la structure Mybox avec les valeurs fournies
    box->dim=dim;
    box->bgColor=bgColor;
    box->homogene=homogene;
    box->space_child=space_child;
    strcpy(box->nom_class,nom_class);
    box->orientation=orientation;
    box->halign=halign;
    box->valign=valign;
    // Retour de la structure Mybox initialisée
    return ((Mybox*)box);
}//FIN fonction init_box()

//----------> fonction de creation d'un box
/*************************************************************
Nom          : creer_box()
Entrée       : box - Pointeur vers une structure Mybox
Sortie       : -
Description  : Crée une boîte GTK+ en fonction des spécifications
fournies dans la structure Mybox.
*************************************************************/
void creer_box(Mybox *box)
{
    // Création de la boîte GTK+ selon l'orientation spécifiée
    if(box->orientation=='h')
        box->box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, box->space_child);
    else if(box->orientation=='v')
        box->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, box->space_child);
    // Définition de l'alignement horizontal de la boîte
    switch(box->halign)
    {
        case 1:
            gtk_widget_set_halign(box->box,GTK_ALIGN_FILL);
            break;
        case 2:
            gtk_widget_set_halign(box->box,GTK_ALIGN_START);
            break;
        case 3:
            gtk_widget_set_halign(box->box,GTK_ALIGN_END);
            break;
        case 4:
            gtk_widget_set_halign(box->box,GTK_ALIGN_CENTER);
            break;
    }//Fin switch(box->halign)
    // Définition de l'alignement vertical de la boîte
    switch(box->valign)
    {
        case 1:
            gtk_widget_set_valign(box->box,GTK_ALIGN_FILL);
            break;
        case 2:
            gtk_widget_set_valign(box->box,GTK_ALIGN_START);
            break;
        case 3:
            gtk_widget_set_valign(box->box,GTK_ALIGN_END);
            break;
        case 4:
            gtk_widget_set_valign(box->box,GTK_ALIGN_CENTER);
            break;
    }//Fin switch(box->valign)
    // Définir l espacement entre les enfants dans une GtkBoxS
    gtk_box_set_spacing(GTK_BOX(box->box),box->space_child);
    // Définition de la hauteur et de la largeur de la boîte
    gtk_widget_set_size_request(GTK_BOX(box->box),box->dim.width,box->dim.height);
    // Définition de la couleur de fond
    gtk_widget_override_background_color(GTK_BOX(box->box),GTK_STATE_FLAG_NORMAL,&box->bgColor);
    // homogeneté (définir si tous les enfants d'une GtkBox doivent avoir la même taille ou non)
    if(!box->homogene)
        gtk_box_set_homogeneous(GTK_BOX(box->box), FALSE);
    else
        gtk_box_set_homogeneous(GTK_BOX(box->box), TRUE);
    // définir un nom (une classe CSS) pour une GtkBox
    gtk_widget_set_name(box->box, box->nom_class);
}//FIN fonction creer_box()


//-----> ajouter au debut de box
void ajouter_element_debut(GtkWidget *box, GtkWidget *element,gboolean expand,gboolean fill,gint padding)
{
    gtk_box_pack_start(GTK_BOX(box), element, expand, fill, padding);
}

//----> ajouter à la fin de box
void ajouter_element_Fin(GtkWidget *box, GtkWidget *element,gboolean expand,gboolean fill,gint padding)
{
    gtk_box_pack_end(GTK_BOX(box), element, expand, fill, padding);
}


//exemple main
int mainGtkBox(int argc, char *argv[])
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
    hexa_color *myColor2= NULL;
    myColor2 =init_hexa_color(myColor2, "black");
    dimension *dim2;
    dim2=(dimension*)malloc(sizeof(dimension));
    dim2->height=100;
    dim2->width=400;
    Mybox *box= init_box("monBox",'h',50,*dim2,
                         2,3,*myColor2,1);
    creer_box(box);
    ///CREATION DE Button
    GtkWidget *button1 = gtk_button_new_with_label("Bouton 1");
    ajouter_element_Fin(box->box,button1,TRUE,TRUE,30);
    gtk_container_add(GTK_CONTAINER(maFenetre->window), box->box);
    // Afficher tous les widgets
    gtk_widget_show_all(maFenetre->window);
    gtk_main();
    return 0;
}
#endif //UNTITLED_GTKBOX_H
