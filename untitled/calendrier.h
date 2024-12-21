//
// Created by admin on 11/03/2024.
//

#ifndef UNTITLED_CALENDRIER_H
#define UNTITLED_CALENDRIER_H

/* Titre: Structure Date*/
typedef struct
{
    guint year;   // Année sélectionnée
    guint month;  // Mois sélectionné
    guint day;    // Jour sélectionné
} Date;

// Structure pour stocker les données associées au calendrier
typedef struct
{
    GtkWidget *pere;      // Fenêtre principale
    GtkCalendar *calendar; // Widget Calendrier
    Date date;             // Jour sélectionné
    dimension dim;          // Structure définissant les dimensions du calendrier
    coordonnees cord;      // Structure représentant les coordonnées du calendrier
} Calender;

// Fonction d'initialisation de la structure
/*************************************************************
Nom          : init_calender()
Entrée       : pere - Le widget parent du calendrier
               cord - Les coordonnées du calendrier
               dim  - Les dimensions du calendrier
Sortie       : Calender* - Pointeur vers la structure Calender initialisée
Description  : Cette fonction initialise  l'objet Calender,
 avec les informations spécifiés en parametre
*************************************************************/
Calender *init_calender(GtkWidget *pere,coordonnees cord,dimension dim)
{
    // Allocation de mémoire pour la structure Calender
    Calender *calendrier = malloc(sizeof(Calender));
    // Vérification si l'allocation a réussi
    if (!calendrier)
    {
        printf("Erreur d'allocation !!");
        exit(-1);
    }
    if(pere) calendrier->pere = pere;
    // Initialisation des champs de date à 0
    calendrier->date.year = 0;
    calendrier->date.month = 0;
    calendrier->date.day = 0;
    // Attribution des coordonnées et dimensions spécifiées
    calendrier->cord.x = cord.x;
    calendrier->cord.y = cord.y;
    calendrier->dim.height = dim.height;
    calendrier->dim.width = dim.width;
    // Retour du pointeur vers la structure Calender initialisée
    return ((Calender*)calendrier);
}//FIN fonction init_calender()

// Fonction de rappel appelée lorsqu'un jour est sélectionné dans le calendrier
/*************************************************************
Nom          : on_day_selected()
Entrée       : calendar - Le widget calendrier GTK où la date est sélectionnée
               data     - Pointeur vers la structure Calender contenant les données
Sortie       : -
Description  : Cette fonction est appelée lorsqu'une date est sélectionnée dans
               un widget calendrier GTK. Elle récupère la date sélectionnée à partir
               du widget calendrier et met à jour les champs de la structure Calender
               spécifiée avec cette date. Ensuite,fait l'affichage
*************************************************************/
void on_day_selected(GtkCalendar *calendar, Calender *data)
{
    gtk_calendar_get_date(calendar, &(data->date.year), &(data->date.month), &(data->date.day));
    g_print("Selected Date: %d-%d-%d\n", data->date.year, data->date.month + 1, data->date.day);
}//FIN fonction on_day_selected()

// Fonction de création et de configuration du calendrier
/*************************************************************
Nom          : createCalendar
Entrée       : calendrier - Pointeur vers la structure Calender
Sortie       : -
Description  : Cette fonction crée un widget calendrier
*************************************************************/
void createCalendar(Calender *calendrier)
{
    // Création du widget calendrier GTK
    calendrier->calendar = gtk_calendar_new();
    // Connexion du signal "day-selected" à la fonction de rappel on_day_selected
    g_signal_connect(calendrier->calendar, "day-selected", G_CALLBACK(on_day_selected), calendrier);
}//FIN fonction createCalendar()


int mainCalendar(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    // Création du conteneur
    GtkWidget *conteneur = gtk_fixed_new();

    // Création de la fenêtre principale
    GtkWidget *pere = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pere), "GTK Calendar Example");
    gtk_window_set_default_size(GTK_WINDOW(pere), 300, 200);
    g_signal_connect(pere, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Initialisation de la structure Calender
    Calender *calendrier = init_calender(pere, (coordonnees){0, 0},(dimension){150, 50});

    // Création et configuration du calendrier
    createCalendar(calendrier);

    // Affecter les calendrier  au conteneur
    gtk_fixed_put(GTK_FIXED(conteneur), calendrier->calendar, calendrier->cord.x, calendrier->cord.y);

    // Ajout du calendrier à la fenêtre principale
    gtk_container_add(GTK_CONTAINER(calendrier->pere), conteneur);

    // Affichage des widgets
    gtk_widget_show_all(calendrier->pere);

    //gtk_fixed_put(GTK_FIXED(conteneur), myButton2->Button, myButton2->cord.x, myButton2->cord.y);

    // Affecter le conteneur au parent de bouton
    gtk_container_add(GTK_CONTAINER(pere), conteneur);

    // Exécution de la boucle principale GTK
    gtk_main();

    // Libération de la mémoire allouée pour la structure Calender
    free(calendrier);

    return 0;
}
#endif //UNTITLED_CALENDRIER_H
