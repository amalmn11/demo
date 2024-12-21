//
// Created by admin on 03/03/2024.
//

#ifndef UNTITLED_LABEL_H
#define UNTITLED_LABEL_H

///////////////////////////////////////////////////////////////////////////////////////////////////////
//MonLabel
//structure de donne de label
typedef struct
{
    GtkWidget *Label;    // Pointeur vers le widget du label
    GtkWidget *pere;     // Pointeur vers le widget parent
    gchar *texte;        // Texte du label
    gint mnemonic;       // Indicateur mnémonique
    dimension dim;       // Structure dimension pour stocker la taille du label
    coordonnees cord;      // Structure cordonnee pour stocker les coordonnées du label
    // Style stl;        // Commenté pour éviter les erreurs de compilation
} MonLabel;


//-----> initialisation de Label
// Fonction init_label : initialise une structure MonLabel avec les paramètres spécifiés
MonLabel *init_label(GtkWidget *pere, gchar *title, gchar *texte, gint mnemonic, dimension dim, coordonnees cord)
{
    MonLabel *L;

    // Allocation de mémoire pour la structure MonLabel
    L = (MonLabel *)malloc(sizeof(MonLabel));
    if (!L)
    {
        // En cas d'échec de l'allocation, afficher un message d'erreur et quitter le programme
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(-1);
    }

    // Allocation de mémoire pour le texte du label si spécifié
    if (texte)
    {
        L->texte = (gchar *)malloc(strlen(texte) + 1);
        if (!L->texte)
        {
            // En cas d'échec de l'allocation, afficher un message d'erreur et quitter le programme
            fprintf(stderr, "Erreur d'allocation mémoire pour le texte du label\n");
            exit(-1);
        }
        strcpy(L->texte, texte);
    }

    // Allocation de mémoire pour le widget parent si spécifié
    if (pere)
    {
        L->pere = (GtkWidget *)malloc(sizeof(GtkWidget));
        if (!L->pere)
        {
            // En cas d'échec de l'allocation, afficher un message d'erreur et quitter le programme
            fprintf(stderr, "Erreur d'allocation mémoire pour le conteneur parent\n");
            exit(-1);
        }
        L->pere = pere;
    }

    // Initialisation des autres propriétés de la structure MonLabel avec les valeurs spécifiées
    L->mnemonic = mnemonic;
    L->cord.x = cord.x;
    L->cord.y = cord.y;
    L->dim.height = dim.height;
    L->dim.width = dim.width;

    // Retourner un pointeur vers la structure MonLabel
    return ((MonLabel *)L);
}


//---------> Creation de Label
// Fonction creer_label : crée un label avec les propriétés spécifiées dans la structure MonLabel
MonLabel *creer_label(MonLabel *Mb)
{
    // Vérifier si un texte est spécifié dans la structure MonLabel
    if (Mb->texte)
    {
        // Vérifier si un mnemonic est spécifié dans la structure MonLabel
        if (Mb->mnemonic)
        {
            // Créer un label avec mnemonic
            Mb->Label = gtk_label_new_with_mnemonic(Mb->texte);
        }
        else
        {
            // Créer un label sans mnemonic
            Mb->Label = gtk_label_new(Mb->texte);
        }
    }

    // Définir la taille du label avec les dimensions spécifiées dans la structure MonLabel
    gtk_widget_set_size_request(Mb->Label, Mb->dim.width, Mb->dim.height);

    // Retourner un pointeur vers la structure MonLabel mise à jour avec le label créé
    return ((MonLabel *)Mb);
}
#endif //UNTITLED_LABEL_H
