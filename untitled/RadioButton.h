//
// Created by admin on 04/03/2024.
//

#ifndef UNTITLED_RADIOBUTTON_H
#define UNTITLED_RADIOBUTTON_H
#include "StyleButton.h"

// Définition d'une structure Radio_Button qui représente un bouton radio personnalisé avec des propriétés spécifiques.
typedef struct
{
    GtkWidget *Button;  // Pointeur vers le widget du bouton
    GtkWidget *pere;    // Pointeur vers le widget parent
    gchar *titre;       // Titre du bouton
    dimension dim;      // Structure dimension pour stocker la taille du bouton
    coordonnees cord;     // Structure cordonnee pour stocker les cordonnées du bouton
    gint mnemonic;      // Indicateur prenant la valeur 0 ou 1
    GSList *group;      // Liste de groupe pour les boutons radio
    gboolean checked;   // Indicateur pour spécifier si le bouton doit être coché
} Radio_Button;



// Fonction pour initialiser une structure Radio_Button avec des valeurs par défaut
Radio_Button *init_buttonRadio(GtkWidget *pere, gchar *title, GSList *group,
                          gint mnemonic,coordonnees cord, dimension dim, gboolean checked)
{
    Radio_Button *B;

    B = (Radio_Button *)malloc(sizeof(Radio_Button));
    if (!B)
    {
        printf("Erreur d'allocation !!");
        exit(-1);
    }

    if (title)
    {
        B->titre = (gchar *)malloc(strlen(title) + 1);
        if (!B->titre)
        {
            printf("Erreur d'allocation de titre !!");
            exit(-1);
        }
        strcpy(B->titre, title);
    }

    if (pere)
    {
        B->pere = pere;
    }

    B->cord.x = cord.x;
    B->cord.y = cord.y;
    B->dim.height = dim.height;
    B->dim.width = dim.width;
    B->mnemonic = mnemonic;
    B->group = group;
    B->checked = checked;

    return ((Radio_Button *)B);
}

// Fonction pour créer un bouton radio en fonction des paramètres spécifiés dans la structure Radio_Button
Radio_Button *creer_button_radio(Radio_Button *Mb)
{
    if (Mb->titre)
    {
        switch (Mb->mnemonic)
        {
            case 0:
                Mb->Button = gtk_radio_button_new_with_label(Mb->group, Mb->titre);
                break;
            case 1:
                Mb->Button = gtk_radio_button_new_with_mnemonic(Mb->group, Mb->titre);
                break;
        }
    }
    else
    {
        Mb->Button = gtk_radio_button_new(Mb->group);
    }

    if (Mb->checked)
    {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(Mb->Button), TRUE);
    }

    gtk_widget_set_size_request(Mb->Button, Mb->dim.width, Mb->dim.height);

    return Mb;
}

// Fonction pour ajouter un bouton radio à la liste existante
Radio_Button *ajouter_bouton_radio(GtkWidget *pere, gchar *title, GSList **group, gboolean checked)
{
    // Création d'un nouveau bouton radio avec les paramètres spécifiés
    Radio_Button *nouveau_bouton = init_buttonRadio(pere, title, *group, 0, (coordonnees){0, 0}, (dimension){0, 0}, checked);
    nouveau_bouton = creer_button_radio(nouveau_bouton);

    // Ajout du bouton radio à la liste
    *group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(nouveau_bouton->Button));

    // Ajout du bouton radio au conteneur parent, s'il est spécifié
    if (pere)
    {
        gtk_box_pack_start(GTK_BOX(pere), nouveau_bouton->Button, FALSE, FALSE, 0);
    }

    // Retourne le nouveau bouton radio
    return ((Radio_Button*)nouveau_bouton);
}

// Exemple d'utilisation des boutons radio avec l'option "checked"
int mainradio(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Groupe de Boutons Radio");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    GSList *group = NULL;

    Radio_Button *radio_button1 = ajouter_bouton_radio(box, "Option 1", &group, FALSE);
    gtk_box_pack_start(GTK_BOX(box), radio_button1->Button, FALSE, FALSE, 0);

    Radio_Button *radio_button2 = ajouter_bouton_radio(box, "Option 2", &group, FALSE);
    gtk_box_pack_start(GTK_BOX(box), radio_button2->Button, FALSE, FALSE, 0);

    Radio_Button *radio_button3 = ajouter_bouton_radio(box, "Option 3", &group, TRUE);
    gtk_box_pack_start(GTK_BOX(box), radio_button3->Button, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), box);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
#endif //UNTITLED_RADIOBUTTON_H
