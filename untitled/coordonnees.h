//
// Created by admin on 03/03/2024.
//

#ifndef UNTITLED_COORDONNEES_H
#define UNTITLED_COORDONNEES_H

///////////////////////////////////////////////////////////////////////////////////////////////////////
//coordonnees
//-------> structure coordonnees
typedef struct {
    gint x; // Abscisse (position horizontale)
    gint y; // Ordonnée (position verticale)
}coordonnees;


//------> fonction de creation de coordonnees
/*************************************************************
Nom          : create_coordonnees()
Entrée       : gint x - l'abscisse (position horizontale)
               gint y - l'ordonnée (position verticale)
Sortie       : coordonnees* - un pointeur vers une structure coordonnees initialisée
Description  : Alloue et initialise dynamiquement une nouvelle structure coordonnees
*************************************************************/
coordonnees* create_coordonnees(gint x, gint y)
{
    // Allocation dynamique de mémoire
    coordonnees *cord = (coordonnees*)malloc(sizeof(coordonnees));
    if (cord == NULL)
    {
        // Gestion de l'échec d'allocation mémoire
        perror("Erreur lors de l'allocation de la structure coordonnees");
        exit(EXIT_FAILURE);
    }
    cord->x = x;
    cord->y = y;
    // Retourne un pointeur vers la structure coordonnees initialisée
    return cord;
}//Fin fonction create_coordonnees()



#endif //UNTITLED_COORDONNEES_H
