//
// Created by admin on 03/03/2024.
//

#ifndef UNTITLED_STYLE_H
#define UNTITLED_STYLE_H

//##################################################################################
//Style
//////////////////////////////////////
//---------->Structure de style
typedef struct
{
    //police du text
    gchar police[50];
    //couleur de text
    hexa_color color;
    //taille du text
    gint taille;
    //texte gras
    gint gras; // 0 --> vrai | 1--> faux
}Style;

//------->initialisation de style
/*************************************************************
Nom          : init_style()
Entrée       : Une chaîne de caractères représentant le nom de la police à utiliser.
               Une structure hexa_color
               Un entier représentant la taille de la police.
               Un entier représentant si le texte doit être en gras
Sortie       : un pointeur vers une structure Style
Description  : prend en entrée les paramètres nécessaires pour initialiser
structure Style
*************************************************************/
Style* init_style(gchar police[50],hexa_color color,gint taille,gint gras)
{
    // Allocation de mémoire pour la structure Style
    Style *monStyle=(Style*)malloc(sizeof(Style));
    // Vérification de l'allocation mémoire
    if(!monStyle)
    {
        // En cas d'échec de l'allocation
        printf("\nerreur d'allocation de memoire.");
        exit(0);
    }
    strcpy(monStyle->police,police);  // Copie de la police dans la structure Style
    monStyle->color=color;                         // Copie de la couleur dans la structure Style
    monStyle->taille=taille;                      // Affectation de la taille de police dans la structure Style
    monStyle->gras=gras;                         // Affectation du gras dans la structure Style
    return ((Style*)monStyle);  // Retour de la structure Style initialisée
}//Fin Fonction init_style()

//---------> creation de style
/*************************************************************
Nom          : appliquer_style()
Entrée       : Un pointeur vers une structure Style
               Un pointeur vers une structure MonLabel
Sortie       : -
Description  : Est utilisée pour appliquer un style au text d'un label
*************************************************************/
void appliquer_style(Style *monStyle,MonLabel *label)
{
    // Création d'une description de police Pango
    PangoFontDescription *font_desc = pango_font_description_new();
    // Définition de la famille de police
    pango_font_description_set_family(font_desc, monStyle->police);
    // Définition de la taille de police
    pango_font_description_set_size(font_desc, monStyle->taille * PANGO_SCALE);
    gtk_widget_override_font(label->Label, font_desc);
    // Libération de la mémoire allouée
    pango_font_description_free(font_desc);
    // Vérification si le style doit être en gras
    if(monStyle->gras==1)
    {
        const gchar *bold_text = g_strdup_printf("<b>%s</b>",
                                                 gtk_label_get_text(GTK_LABEL(label->Label)));
        gtk_label_set_markup(GTK_LABEL(label->Label), bold_text);
        g_free(bold_text);
    }//Fin if(monStyle->gras==1)
    // Application de la couleur personnalisée
    GdkRGBA color;
    gdk_rgba_parse(&color, monStyle->color.hexa_color);
    gtk_widget_override_color(label->Label, GTK_STATE_FLAG_NORMAL, &color);
}//Fin fonction appliquer_style()


///////////////////////////////////////////////////////////////////////////////////////////////////////
////////// fonction pour charger le fichier CSS
/*************************************************************
Nom          : charger_fichier_css()
Entrée       : filename - Chemin du fichier CSS à charger
Sortie       : -
Description  : Charge un fichier CSS
*************************************************************/
void charger_fichier_css(const char *filename)
{
    // Déclaration d'un fournisseur de CSS GTK
    GtkCssProvider *provider;
    GdkScreen *screen;
    GError *error = NULL;
    provider = gtk_css_provider_new();
    screen = gdk_screen_get_default();
    // Tentative de chargement du fichier CSS
    if (!gtk_css_provider_load_from_file(provider, g_file_new_for_path(filename), &error))
    {
        // Affichage de l'erreur en cas d'échec du chargement
        g_error("Failed to load CSS file: %s\n", error->message);
        // Libération de la mémoire de l'erreur
        g_clear_error(&error);
        // Libération de la mémoire du fournisseur de CSS
        g_object_unref(provider);
        return;
    }//FIN if
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);
}//FIN fonction charger_fichier_css()

#endif //UNTITLED_STYLE_H
