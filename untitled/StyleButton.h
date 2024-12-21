//
// Created by admin on 04/03/2024.
//

#ifndef UNTITLED_STYLEBUTTON_H
#define UNTITLED_STYLEBUTTON_H


// Structure pour définir le style du texte
typedef struct
{
    gchar police[50];  // Police du texte
    hexa_color color;   // Couleur du texte
    gint taille;        // Taille du texte
    gint gras;          // Texte en gras (0 pour vrai, 1 pour faux)
}StyleButton;

// Fonction appliquer_style_button : applique un style spécifié à un bouton
void appliquer_style_button(StyleButton *monStyle, GtkWidget *Mb)
{
    // Création d'une nouvelle description de police Pango
    PangoFontDescription *font_desc = pango_font_description_new();

    // Appliquer la famille de police spécifiée dans le style
    pango_font_description_set_family(font_desc, monStyle->police);

    // Appliquer la taille de police spécifiée dans le style
    pango_font_description_set_size(font_desc, monStyle->taille * PANGO_SCALE);

    // Appliquer la police au widget du bouton
    gtk_widget_override_font(Mb, font_desc);

    // Libérer la mémoire allouée pour la description de police
    pango_font_description_free(font_desc);

    // Appliquer le style gras si spécifié dans le style
    if (monStyle->gras == 1)
    {
        // Récupérer le label du bouton
        GtkWidget *label = gtk_bin_get_child(GTK_BIN(Mb));

        // Récupérer le texte actuel du label
        const gchar *current_label_text = gtk_label_get_text(GTK_LABEL(label));

        // Concaténer le texte avec des balises pour le rendre en gras
        const gchar *bold_text = g_strdup_printf("<b>%s</b>", current_label_text);

        // Appliquer le texte en gras au label
        gtk_label_set_markup(GTK_LABEL(label), bold_text);

        // Libérer la mémoire allouée pour le texte en gras
        g_free(bold_text);
    }

    // Récupérer le label du bouton
    GtkWidget *lab = gtk_bin_get_child(GTK_BIN(Mb));

    // Vérifier si le widget est un label
    if (GTK_IS_LABEL(lab))
    {
        // Modifier la couleur du texte si spécifiée dans le style
        if (monStyle->color.hexa_color[0] != '\0')
        {
            GdkRGBA color;

            // Parse la couleur hexadécimale et l'applique au texte
            gdk_rgba_parse(&color, monStyle->color.hexa_color);
            gtk_widget_override_color(lab, GTK_STATE_FLAG_NORMAL, &color);
        }

        // Modifier la taille de police si spécifiée dans le style
        if (monStyle->taille > 0)
        {
            // Copier la description de police et appliquer la nouvelle taille
            PangoFontDescription *font_desc = pango_font_description_copy(pango_font_description_from_string(monStyle->police));
            gtk_widget_modify_font(lab, font_desc);
            pango_font_description_free(font_desc);
        }
    }
}


//---------> Fonction init_style : initialise une structure de style pour un bouton
StyleButton *init_style_Button(StyleButton *stl, gchar police[50], hexa_color color, gint taille, int gras)
{
    // Vérifier si la structure a déjà été allouée
    if (!stl) {
        // Si non, allouer de la mémoire pour la structure Style
        stl = malloc(sizeof(StyleButton));
        if (!stl) {
            // En cas d'échec de l'allocation, afficher un message d'erreur
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            return NULL;
        }
    }

    // Copier le nom de la police dans la structure Style
    g_strlcpy(stl->police, police, sizeof(stl->police));

    // Copier la couleur hexadécimale dans la structure Style
    stl->color = color;

    // Stocker la taille de la police dans la structure Style
    stl->taille = taille;

    // Stocker l'information sur le gras dans la structure Style
    stl->gras = gras;

    // Retourner un pointeur vers la structure Style
    return (StyleButton*)stl;
}

///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////
/////////////////////


#endif //UNTITLED_STYLEBUTTON_H
