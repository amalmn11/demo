//
// Created by admin on 03/03/2024.
//

#ifndef UNTITLED_DIMENSION_H
#define UNTITLED_DIMENSION_H


///////////////////////////////////////////////////////////////////////////////////////////////////////
//Dimension
//-------> structure dimension
typedef struct
{
    gint height; // Hauteur de l'objet
    gint width;  // Largeur de l'objet
} dimension;

//------> fonction de creation de dimension
/*************************************************************
Nom          :  create_dimension()
Entrée       : gint height - la hauteur de l'objet
               gint width - la largeur de l'objet
Sortie       : dimension* - un pointeur vers une structure dimension initialisée
Description  : Alloue et initialise dynamiquement une nouvelle structure dimension
*************************************************************/
dimension* create_dimension(gint height, gint width)
{
    // Allocation dynamique de mémoire
    dimension *dim = (dimension*)malloc(sizeof(dimension));
    if (dim == NULL)
    {
        // Gestion de l'échec d'allocation mémoire
        perror("Erreur lors de l'allocation de la structure dimension");
        exit(EXIT_FAILURE);
    }
    dim->height = height;
    dim->width = width;
    return ((dimension*)dim);
}//FIN fonction create_dimension()
#endif //UNTITLED_DIMENSION_H
