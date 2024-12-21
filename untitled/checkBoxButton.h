//
// Created by admin on 04/03/2024.
//

#ifndef UNTITLED_CHECKBOXBUTTON_H
#define UNTITLED_CHECKBOXBUTTON_H

// Structure pour définir un bouton personnalisé avec différentes propriétés
typedef struct
{
    GtkWidget *Button;  // Widget du bouton
    GtkWidget *pere;    // Fenêtre parente du bouton
    gchar *titre;       // Texte du bouton
    dimension dim;      // Dimensions du bouton
    gint mnemonic;      // Mnemonic du bouton (0 ou 1)
    coordonnees cord;     // Coordonnées du bouton
    int checked;        // État initial du bouton (coché ou non)
}checkbox_Button;

/***************************************************************************************************
 Nom            : init_button()
 Entrée         : pere - Pointeur vers le widget parent
                  title - Pointeur vers le titre associé à la checkbox
                  mnemonic - Mnémonique associé à la checkbox
                  cord - Coordonnées de la checkbox
                  dim - Dimensions de la checkbox
                  check - État initial de la checkbox (coché ou non)
 Sortie         : Un pointeur vers la structure checkbox_Button initialisée
 Description    : Initialise la structure checkbox_Button avec les paramètres spécifiques.
 ***************************************************************************************************/
checkbox_Button *init_buttonCheckbox(GtkWidget *pere, gchar *title, gint mnemonic, coordonnees cord, dimension dim, int check)
{
    checkbox_Button *B;

    // Allocation de mémoire pour la structure checkbox_Button
    B = (checkbox_Button *)malloc(sizeof(checkbox_Button));

    // Vérifie si l'allocation a réussi
    if (!B)
    {
        // En cas d'échec de l'allocation, afficher un message d'erreur et quitter le programme
        printf("Erreur d'allocation !!");
        exit(-1);
    }

    // Allocation de mémoire pour le titre si spécifié
    if (title)
    {
        B->titre = (gchar *)malloc(strlen(title) + 1);
        if (!B->titre)
        {
            // En cas d'échec de l'allocation, afficher un message d'erreur et quitter le programme
            printf("Erreur d'allocation de titre !!");
            exit(-1);
        }
        strcpy(B->titre, title);
    }

    // Allocation de mémoire pour le widget parent si spécifié
    if (pere)
    {
        B->pere = (GtkWidget *)malloc(sizeof(GtkWidget));
        if (!B->pere)
        {
            // En cas d'échec de l'allocation, afficher un message d'erreur et quitter le programme
            printf("Erreur d'allocation de pere!!");
            exit(-1);
        }
        B->pere = pere;
    }

    // Initialisation des autres propriétés de la structure checkbox_Button avec les valeurs spécifiées
    B->cord.x = cord.x;
    B->cord.y = cord.y;
    B->dim.height = dim.height;
    B->dim.width = dim.width;
    B->mnemonic = mnemonic;
    B->checked = check;

    // Retourner un pointeur vers la structure checkbox_Button initialisée
    return ((checkbox_Button *)B);
}


/*********************************************************************************************************************
 Nom            : creer_button_check()
 Entrée         : Mb - Pointeur vers la structure checkbox_Button
 Sortie         : Un pointeur vers la structure checkbox_Button mise à jour avec le bouton check créé
 Description    : Crée un bouton check en fonction des paramètres spécifiés dans la structure checkbox_Button
*********************************************************************************************************************/
checkbox_Button *creer_button_check(checkbox_Button *Mb)
{
    // Vérifier si un titre est spécifié dans la structure checkbox_Button
    if (Mb->titre)
    {
        // Selon la valeur de mnemonic, créer un bouton check avec ou sans marquage
        switch (Mb->mnemonic)
        {
            case 0:
                Mb->Button = gtk_check_button_new_with_label(Mb->titre);
                break;
            case 1:
                Mb->Button = gtk_check_button_new_with_mnemonic(Mb->titre);
                break;
        }
    }
    else
    {
        // Si aucun titre n'est spécifié, créer un simple bouton check
        Mb->Button = gtk_check_button_new();
    }

    // Définition de l'état initial à "coché"
    if (Mb->checked == 1)
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(Mb->Button), TRUE);

    // Retourner un pointeur vers la structure checkbox_Button mise à jour avec le bouton check créé
    return ((checkbox_Button *)Mb);
}

/* check_button : fonction qui permet d'activer ou désactiver un bouton selon la valeur variable a
                  valeur 0: désactiver le bouton;
                  valeur 1: activer le bouton;
*/
checkbox_Button *check_button(checkbox_Button *Mb, int a)
{
    // Activer ou désactiver le bouton en fonction de la valeur de a
    if (a == 1)
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(Mb->Button), TRUE);
    else
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(Mb->Button), FALSE);

    // Retourner un pointeur vers la structure MaBoutton mise à jour
    return ((checkbox_Button *)Mb);
}


/////////////////////////////////////////////////////////////////////////////////////////////
//MAIN
// Fonction principale du programme
int mainCheckBox(int argc, char *argv[])
{
    // Démarrer la boucle principale GTK
    gtk_init(&argc, &argv);

    // Création de la fenêtre parente
    GtkWidget *pere = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // Création du conteneur
    GtkWidget *conteneur = gtk_fixed_new();

    // Initialisation des propriétés pour un bouton
    coordonnees coord = {22, 30};
    dimension dim = {100, 50};

    // Initialisation de la couleur du texte pour le bouton
    hexa_color *textColor;
    textColor = init_hexa_color(textColor, "red");

    // Initialisation du style du bouton
    StyleButton *buttonStyle;
    buttonStyle = init_style_Button(buttonStyle, "Arial", *textColor, 16,1);

    // Initialisation de la structure MaBoutton pour le bouton
    checkbox_Button *mon_bouton = init_buttonCheckbox(pere, "Cliquez-moi", 0, coord, dim, 1);

    // Création et configuration du bouton check
    creer_button_check(mon_bouton);

    // Application du style au bouton
    appliquer_style_button(buttonStyle, mon_bouton->Button);

    // Test pour activer et désactiver un bouton
    // mon_bouton = check_button(mon_bouton, 0);

    // Affecter le bouton au conteneur
    gtk_fixed_put(GTK_FIXED(conteneur), mon_bouton->Button, mon_bouton->cord.x, mon_bouton->cord.y);

    // Affecter le conteneur au parent de bouton
    gtk_container_add(GTK_CONTAINER(mon_bouton->pere), conteneur);

    // Afficher la fenêtre parente
    gtk_widget_show_all(mon_bouton->pere);

    // Connecter le signal "destroy" au callback de fermeture
    g_signal_connect(mon_bouton->pere, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Fin de la boucle principale GTK
    gtk_main();

    // Retourner 0 en fin de programme
    return 0;
}
#endif //UNTITLED_CHECKBOXBUTTON_H
