//
// Created by admin on 03/03/2024.
//

#ifndef UNTITLED_FIXEDCONTAINER_H
#define UNTITLED_FIXEDCONTAINER_H

///////////////////////////////////////////////////////////////////////////////////////////////////////
//FixedContainer
//-------> structure de donnees (conteneurFixed)
typedef struct
{
    GtkWidget *container;         // Le widget Fixed Container GTK
    dimension dim;                // Dimension du conteneur
    gchar name[60];               // Nom du conteneur
}FixedContainer;

//---------> fonction d'initialisation de FixedContainer
FixedContainer* init_FixedContainer(dimension dim,gchar name[60])
{
    // Allocation dynamique de mémoire pour une instance de boiteDialogue
    FixedContainer * fixed=NULL;
    fixed=(FixedContainer*)malloc(sizeof(FixedContainer));
    if(!fixed)
    {
        printf("\nerreur d'allocation de memoire.");
        exit(0);
    }//Fin if(!fixed)
    // Initialisation des champs de la structure FixedContainer
    fixed->dim=dim;
    strcpy(fixed->name,name);
    // Retourne un pointeur vers la structure FixedContainer initialisée
    return ((FixedContainer*)fixed);
}//FIN fonction init_FixedContainer()

//--------> fonction de creation d'une instance de boiteDialogue
void create_FixedContainer(FixedContainer *fixed)
{
    // Creation of the fixed container
    fixed->container = gtk_fixed_new();
    // Set the name of the fixed container
    gtk_widget_set_name(fixed->container, fixed->name);
    // Set the size request of the fixed container
    gtk_widget_set_size_request(fixed->container, fixed->dim.width, fixed->dim.height);
}//FIN fonction create_FixedContainer()

//-------> ajouter au debut
void ajouter_element_fixed(GtkFixed *fixed, GtkWidget *widget, int x, int y)
{
    gtk_fixed_put(fixed, widget, x, y);
}

//MAIN
int mainFixedContainer(int argc, char *argv[])
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
    dimension *dim3= create_dimension(50,100);
    FixedContainer *fixed=init_FixedContainer(*dim3,"myFixed");
    create_FixedContainer(fixed);
    //1) ajouter bouton
    GtkWidget *button1 = gtk_button_new_with_label("Bouton 1");
    ajouter_element_fixed(fixed->container,button1,190,20);
    //2) ajouter label
    hexa_color *textColor=NULL;
    textColor = init_hexa_color(textColor, "blue");
    Style *labelStyle;
    labelStyle = init_style("Arial", *textColor, 10, 1);
    MonLabel *mon_label = init_label(fixed->container, "MonLabel",
                                     "Bienvenue !", 0, *dim3, *cord);
    creer_label(mon_label);
    appliquer_style(labelStyle, mon_label);
    ajouter_element_fixed(fixed->container,mon_label->Label,190,90);
    gtk_container_add(GTK_CONTAINER(maFenetre->window),fixed->container);
    // Afficher tous les widgets
    gtk_widget_show_all(maFenetre->window);
    gtk_main();
    return 0;
}
#endif //UNTITLED_FIXEDCONTAINER_H
