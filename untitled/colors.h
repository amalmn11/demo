//
// Created by admin on 03/03/2024.
//

#ifndef UNTITLED_COLORS_H
#define UNTITLED_COLORS_H

///////////////////////////////////////////////////////////////////////////////////////////////////////
//Color
//--------> Stcructure de la Couleur
typedef struct
{
    GdkRGBA color; // Objet GdkRGBA représentant la couleur RGBA
    double red;    // Composante rouge (entre 0.0 et 1.0)
    double green;  // Composante verte (entre 0.0 et 1.0)
    double blue;   // Composante bleue (entre 0.0 et 1.0)
    double alpha;   // Composante alpha (transparence)
}Color;

//-----------> fonction  initialisation de type Color
/*************************************************************
Nom          : init_color()
Entrée       : Un pointeur vers une structure de type Color
               valeur (double) de la composante rouge/verte/blue et alpha de la couleur
Sortie       : Objet Color initialisé
Description  : utilisée pour initialiser une structure de type Color avec les valeurs spécifiées
*************************************************************/
Color* init_color(Color *myColor, double red, double green, double blue, double alpha)
{
    myColor->color.red = red;
    myColor->color.green = green;
    myColor->color.blue = blue;
    myColor->color.alpha = alpha;
}//Fin de la fontion init_color()

///////////////////////////////////////////////////////////////////////////////////////////////////////
//hexa_color
//------------> structure hexa_color
typedef struct
{
    GdkRGBA color;   // Objet GdkRGBA représentant la couleur RGBA
    gchar hexa_color[30]; // Chaîne de caractères représentant la couleur en format hexadécimal
}hexa_color;

//----> fonction d'initialisation de hexa_color
/*************************************************************
Nom          : init_hexa_color()
Entrée       : Un pointeur vers une structure de type hexa_color
               Un pointeur vers une chaîne représentant le code hexadécimal
               de la couleur
Sortie       : un pointeur vers la structure hexa_color initialisée
Description  : est utilisée pour initialiser une structure hexa_color
avec les informations passées en argument
*************************************************************/
hexa_color* init_hexa_color(hexa_color *myColor, gchar *hex_code)
{
    // Allocation de mémoire pour myColor s'il n'est pas déjà alloué
    if (myColor == NULL)
    {
        myColor = malloc(sizeof(hexa_color));
        if (myColor == NULL) {
            // Gestion de l'échec de l'allocation mémoire
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            return NULL;
        }
    }
    // Copie de la couleur hexadécimale dans la structure
    g_strlcpy(myColor->hexa_color, hex_code,
              sizeof(myColor->hexa_color));
    // Conversion de la couleur hexadécimale en GdkRGBA
    gdk_rgba_parse(&(myColor->color), myColor->hexa_color);
    // Retour de la structure initialisée
    return myColor;
}//Fin fonction init_hexa_color()

#endif //UNTITLED_COLORS_H
