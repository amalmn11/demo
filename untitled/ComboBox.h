//
// Created by admin on 03/03/2024.
//

#ifndef UNTITLED_COMBOBOX_H
#define UNTITLED_COMBOBOX_H

///////////////////////////////////////////////////////////////////////////////////////////////////////
//ComboBox
//----------> structure de donnees de ComboBox
typedef struct
{
    GtkWidget* comboBox; // Widget de combobox GTK+
    dimension dim; //Dimension de comboBox
    coordonnees cord; //Coordonnees sur le conteneur (fixed)
    char nom_class[30]; //Class de combo box
    GtkWidget* conteneur_fixed; // Conteneur fixed auquel la combobox est attachée
}gtkComboBox;

//---------> fonction d'initialisation d'un combo box
/*************************************************************
Nom          : init_comboBox()
Entrée       : Une structure dimension && Une structure coordonnees
               Une chaîne de caractères && Un pointeur vers le widget GTK+ du conteneur fixed
Sortie       : renvoie un pointeur vers une structure gtkComboBox
Description  : Est utilisée pour initialiser une structure gtkComboBox
*************************************************************/
gtkComboBox* init_comboBox(dimension dim,coordonnees cord,char nom_class[30],GtkWidget* conteneur_fixed)
{
    // Allocation de mémoire pour une nouvelle instance de gtkComboBox
    gtkComboBox *myCombo = (gtkComboBox *)malloc(sizeof(gtkComboBox ));
    // Vérification de l'allocation de mémoire
    if (!myCombo)
    {
        // En cas d'échec de l'allocation, affichage d'un message d'erreur
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }//Fin if(!myCombo)
    // Initialisation des champs de la structure gtkComboBox
    myCombo->dim.height=dim.height;
    myCombo->dim.width=dim.width;
    myCombo->cord.x=cord.x;
    myCombo->cord.y=cord.y;
    strcpy(myCombo->nom_class,nom_class);
    myCombo->conteneur_fixed=conteneur_fixed;
    // Retour de la structure gtkComboBox initialisée
    return ((gtkComboBox*)myCombo);
}//Fin fonction init_comboBox()

//--------> fonction de creation d'un combo box
/*************************************************************
Nom          : create_ComboBox()
Entrée       : Un pointeur vers une structure gtkComboBox
Sortie       : -
Description  : Elle prend en entrée un pointeur vers une structure gtkComboBox contenant
les informations nécessaires pour créer et configurer la combobox.
*************************************************************/
void create_ComboBox(gtkComboBox *myCombo)
{
    // Création d'une nouvelle combobox
    myCombo->comboBox = gtk_combo_box_text_new();
    // Attribution d'une classe à la combobox
    gtk_widget_set_name(myCombo->comboBox,myCombo->nom_class);
    // Ajustement de la hauteur et de la largeur de la combobox
    gtk_widget_set_size_request(myCombo->comboBox, myCombo->dim.width,myCombo->dim.height);
    // Positionnement de la combobox sur le conteneur fixed
    gtk_fixed_put(GTK_FIXED(myCombo->conteneur_fixed), myCombo->comboBox,
                  myCombo->cord.x,myCombo->cord.y);
}//Fin fonction create_ComboBox()

//--------> fonction pour ajouter des elements à comboBox
/*************************************************************
Nom          : ajouterElementComboBox()
Entrée       : myCombo - Un pointeur vers une structure gtkComboBox
              id - Identifiant de l'élément à ajouter à la combobox (chaîne de caractères)
              text - Texte de l'élément à ajouter à la combobox (chaîne de caractères)
Sortie       : -
Description  : Ajoute un élément à la combobox spécifiée
*************************************************************/
void ajouterElementComboBox(gtkComboBox *myCombo,char id[50],char text[50])
{
    // Ajout de l'élément à la combobox en utilisant l'identifiant et le texte fournis
    gtk_combo_box_text_prepend(GTK_COMBO_BOX_TEXT(myCombo->comboBox),id, text);
}//Fin fonction ajouterElementComboBox()


//--------> definir l'element active dans le ComboBox
/*************************************************************
Nom          : elementActive()
Entrée       : myCombo - Un pointeur vers une structure gtkComboBox
               index - L'indice de l'élément à rendre actif dans la combobox
Sortie       : -
Description  : Rend l'élément à l'indice spécifié actif dans la combobox.
*************************************************************/
void elementActive(gtkComboBox *myCombo,gint index)
{
    // Rend l'élément à l'indice spécifié actif dans la combobox
    gtk_combo_box_set_active(myCombo->comboBox, index);
}//Fin fonction elementActive()


///////////////////////////////////////////////////////////
//MAIN
int mainComboBox(int argc, char *argv[])
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
    cord->y=100;
    cord->x=100;

    //image de background
    dimension *dim2;
    dim2=(dimension*)malloc(sizeof(dimension));
    dim2->height=0;
    dim2->width=0;
    MonImage *bgImg=create_image_widget("",0,0,*dim2);

    //creation+initialisation
    window *maFenetre= init_window(*dim,3,"fatiha's window","flower.png",0,
                                   GTK_WIN_POS_CENTER,*cord,*myColor,*bgImg);
    create_window(maFenetre);


    //ajouter comboBox
    dimension *dim3;
    dim3=(dimension*)malloc(sizeof(dimension));
    dim3->height=20;
    dim3->width=300;
    GtkWidget *fixed1 = gtk_fixed_new();
    gtkComboBox *comboBox=init_comboBox(*dim3,*cord,"myCombo1",fixed1);
    create_ComboBox(comboBox);
    gtk_combo_box_text_prepend(GTK_COMBO_BOX_TEXT(comboBox->comboBox), "element0", "Élément 0");
    //ajouter des elements au comboBox
    ajouterElementComboBox(comboBox,"element 1","element 1");
    ajouterElementComboBox(comboBox,"element 2","element 2");
    ajouterElementComboBox(comboBox,"element 3","element 3");
    elementActive(comboBox,1);


    gtk_container_add(GTK_CONTAINER(maFenetre->window), fixed1);
    // Afficher tous les widgets
    gtk_widget_show_all(maFenetre->window);
    gtk_main();
    return 0;
}
#endif //UNTITLED_COMBOBOX_H
