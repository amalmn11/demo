//
// Created by admin on 03/03/2024.
//

#ifndef UNTITLED_BOITEDIALOG_H
#define UNTITLED_BOITEDIALOG_H

///////////////////////////////////////////////////////////////////////////////////////////////////////
//BoiteDialogue
//-------> structure de donnees
typedef struct
{
    GtkWidget *dialog;          // La boîte de dialogue GTK
    gchar titre[60];               // Titre de la boîte de dialogue
    gint modal;             // Indique si la boîte de dialogue est modale ou non
    dimension dim;          //dimension de la boite de dialogue
    coordonnees cord;      //coordonnees de la boite de dialogue
    hexa_color bgColor;   //Couleur de fond de la boite de dialogue
    gchar icon[60];     //chemin d'icon de la boite de dialogue
} BoiteDialogue;

//-------> fonction d'initialisation de BoiteDialogue
/*************************************************************
Nom          : init_BoiteDialogue()
Entrée       : gchar titre[60] - le titre de la boîte de dialogue
               gint modal - indique si la boîte de dialogue est modale (1) ou non (0)
               dimension dim - les dimensions de la boîte de dialogue
               coordonnees cord - les coordonnées de la boîte de dialogue
               hexa_color bgColor - la couleur de fond de la boîte de dialogue
               gchar icon[60] - le chemin de l'icône de la boîte de dialogue
Sortie       : un pointeur vers la structure BoiteDialogue initialisée
Description  :  Initialise une structure BoiteDialogue avec les paramètres spécifiés.
*************************************************************/
BoiteDialogue* init_BoiteDialogue(gchar titre[60],gint modal,dimension dim
        ,coordonnees cord,hexa_color bgColor,gchar icon[60])
{
    // Allocation dynamique de mémoire pour une instance de boiteDialogue
    BoiteDialogue * boiteDialogue=NULL;
    boiteDialogue=(BoiteDialogue*)malloc(sizeof(BoiteDialogue));
    if(!boiteDialogue)
    {
        printf("\nerreur d'allocation de memoire.");
        exit(0);
    }//Fin if(!boiteDialogue)
    // Initialisation des champs de la structure BoiteDialogue
    strcpy(boiteDialogue->titre,titre);
    strcpy(boiteDialogue->icon,icon);
    boiteDialogue->cord=cord;
    boiteDialogue->dim=dim;
    boiteDialogue->bgColor=bgColor;
    boiteDialogue->modal=modal;
    // Retourne un pointeur vers la structure BoiteDialogue initialisée
    return ((BoiteDialogue*)boiteDialogue);
}//FIN fonction init_box()

//-------> fonction Creation de BoiteDialogue
/*************************************************************
Nom          : creer_BoiteDialogue()
Entrée       : BoiteDialogue - contenant les informations de la boîte de dialogue à créer
Sortie       : -
Description  :Crée une boîte de dialogue GTK en fonction des paramètres spécifiés
dans la structure BoiteDialogue
*************************************************************/
void creer_BoiteDialogue(BoiteDialogue *boiteDialogue)
{
    // Création de la boîte de dialogue
    boiteDialogue->dialog=gtk_dialog_new();
    // Titre de la boîte de dialogue
    gtk_window_set_title(GTK_WINDOW(boiteDialogue->dialog),boiteDialogue->titre);
    // Définition de la modalité de la boîte de dialogue
    if(boiteDialogue->modal==1)
        gtk_window_set_modal(GTK_WINDOW(boiteDialogue->dialog), TRUE);
    else if(boiteDialogue->modal==0)
        gtk_window_set_modal(GTK_WINDOW(boiteDialogue->dialog), FALSE);
    // Définition des dimensions de la boîte de dialogue
    gtk_window_set_default_size(GTK_WINDOW(boiteDialogue->dialog),
                                boiteDialogue->dim.width,boiteDialogue->dim.height);
    // Définition des coordonnées de la boîte de dialogue
    gtk_window_move(GTK_WINDOW(boiteDialogue->dialog), boiteDialogue->cord.x, boiteDialogue->cord.y);
    // Définition de la couleur de fond de la boîte de dialogue
    gtk_widget_override_background_color(boiteDialogue->dialog, GTK_STATE_FLAG_NORMAL,
                                         &boiteDialogue->bgColor.color);
    // Définition de l'icône de la boîte de dialogue
    GdkPixbuf *icon = create_icon_from_file(boiteDialogue->icon);
    gtk_window_set_icon(GTK_WINDOW(boiteDialogue->dialog), icon);
}//Fin fonction creer_BoiteDialogue()

//---------------> Run dialogBox
/*************************************************************
Nom          : run_dialog()
Entrée       : *dialog - pointeur vers la structure BoiteDialogue
Sortie       : -
Description  : Exécute la boîte de dialogue spécifiée.
*************************************************************/
void run_dialog(BoiteDialogue *dialog)
{
    // Exécute la boîte de dialogue en utilisant gtk_dialog_run()
    gtk_dialog_run(GTK_DIALOG(dialog->dialog));
}//FIN fonction run_dialog()

//------------>   destroy dialog
/*************************************************************
Nom          : destroy_dialog()
Entrée       : *dialog - un pointeur vers la structure BoiteDialogue
Sortie       : -
Description  : Détruit la boîte de dialogue spécifiée.
*************************************************************/
void destroy_dialog(BoiteDialogue *dialog)
{
    // Détruit la boîte de dialogue en utilisant gtk_widget_destroy()
    gtk_widget_destroy(dialog->dialog);
}//FIN fonction destroy_dialog()

#endif //UNTITLED_BOITEDIALOG_H
