//
// Created by admin on 03/03/2024.
//

#ifndef UNTITLED_WINDOW_H
#define UNTITLED_WINDOW_H
#define MAX 60
///////////////////////////////////////////////////////////////////////////////////////////////////////
//window
//-----------> structure de window
typedef struct
{
    GtkWidget *window;    // Widget GTK+ de la fenêtre
    dimension dim;        // Dimensions de la fenêtre
    gint border_size;     // Épaisseur de la bordure de la fenêtre
    gchar title[MAX];     // Titre de la fenêtre (maximum MAX caractères)
    gchar icon_name[MAX]; // Nom de l'icône de la fenêtre
    gint  resisable;      // Indique si la fenêtre est redimensionnable
    // (0: FALSE, 1: TRUE)
    gchar position;       // Position initiale de la fenêtre [c: GTK_WIN_POS_CENTER]
    // ou  [m: GTK_WIN_POS_MOUSE] ...
    coordonnees cord;     // Coordonnées de positionnement de la fenêtre
    // par rapport à l'axe y et x
    hexa_color bgColor;   // Couleur de fond de la fenêtre
    MonImage bgImg;       // Image de fond de la fenêtre
}window;


//------------------------------> fonction d'initialisation
/*************************************************************
Nom          : init_window()
Entrée       : dim - Dimensions de la fenêtre
               border_size - Épaisseur de la bordure de la fenêtre
               title - Titre de la fenêtre
               icon_name - Nom de l'icône de la fenêtre
               resizable - Indique si la fenêtre est redimensionnable (0: non, 1: oui)
               position - Position initiale de la fenêtre (c: centrée, m: au niveau de la souris, ...)
               cord - Coordonnées de positionnement de la fenêtre
               bgColor - Couleur de fond de la fenêtre
               bgImg - Image de fond de la fenêtre
Sortie       : Un pointeur vers une structure window initialisée
Description  : Initialise une structure window avec les valeurs fournies
*************************************************************/
window* init_window(dimension dim,gint border_size,gchar title[MAX],gchar icon_name[MAX],gint  resisable,
                    gchar position,coordonnees cord,hexa_color bgColor,MonImage bgImg)
{
    // Allocation dynamique de mémoire pour une nouvelle instance de window
    window* maFenetre=NULL;
    maFenetre=(window*)malloc(sizeof(window));
    // Vérification de l'allocation de mémoire
    if(!maFenetre)
    {
        printf("\nerreur d'allocation de memoire.");
        exit(0);
    }
    // Initialisation des champs de la structure window avec les valeurs fournies
    maFenetre->dim=dim;
    maFenetre->border_size=border_size;
    strcpy(maFenetre->title,title);
    strcpy(maFenetre->icon_name,icon_name);
    maFenetre->resisable=resisable;
    maFenetre->position=position;
    maFenetre->bgColor=bgColor;
    maFenetre->cord=cord;
    maFenetre->bgImg=bgImg;
    // Retour de la structure window initialisée
    return ((window*)maFenetre);
}//Fin fonction init_window()


//-------------------------------------> fonction de creation de window
/*************************************************************
Nom          : create_window()
Entrée       : maFenetre - Un pointeur vers une structure window représentant la fenêtre à créer
Sortie       : -
Description  : Crée Fenêtre GTK+ en utilisant les valeurs spécifiées dans la structure window fournie.
*************************************************************/
void create_window(window *maFenetre)
{
    // Crée une nouvelle fenêtre GTK+ de type toplevel
    maFenetre->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    // Définit la taille par défaut de la fenêtre en utilisant les dimensions fournies
    gtk_window_set_default_size(GTK_WINDOW(maFenetre->window),maFenetre->dim.width,maFenetre->dim.height);
    // Définit la position initiale de la fenêtre
    gtk_window_set_position(GTK_WINDOW(maFenetre->window), maFenetre->position);
    // Définit le titre de la fenêtre
    gtk_window_set_title(GTK_WINDOW(maFenetre->window), maFenetre->title);
    // Définit l'épaisseur de la bordure de la fenêtre
    gtk_container_set_border_width(GTK_CONTAINER(maFenetre->window), maFenetre->border_size);
    // Définit si la fenêtre est redimensionnable en fonction de la valeur de resizable
    if(!maFenetre->resisable)
        gtk_window_set_resizable(GTK_WINDOW(maFenetre->window),FALSE);
    else
        gtk_window_set_resizable(GTK_WINDOW(maFenetre->window),TRUE);
    // Modifie la couleur de fond de la fenêtre
    gtk_widget_override_background_color(maFenetre->window, GTK_STATE_FLAG_NORMAL,
                                         &maFenetre->bgColor);
    // Déplace la fenêtre aux coordonnées spécifiées dans cord
    gtk_window_move(GTK_WINDOW(maFenetre->window), maFenetre->cord.x,maFenetre->cord.y);
    // Charge l'icône de la fenêtre à partir du chemin donné
    GdkPixbuf *icon=create_icon_from_file(maFenetre->icon_name);
    //appliquer l'icon
    gtk_window_set_icon(GTK_WINDOW(maFenetre->window), icon);
    MonImage *background_image = create_image_widget(maFenetre->bgImg.path,
                                                     maFenetre->bgImg.ImCrd.x, maFenetre->bgImg.ImCrd.y, maFenetre->bgImg.dim);
    // Ajoute le widget d'image à la fenêtre
    //gtk_container_add(GTK_CONTAINER(maFenetre->window), background_image->image);
}//Fin fonction create_window()

////////////////////////////////////////////////////////////////////////
//------> fonction pour ajouter headerBar au fenêtre au lieur de header ordinaire
////////////////////////////////////////////////////////////////////////

/*************************************************************
Nom          : ajouterHeader()
Entrée       : window *maFenetre- Un pointeur vers la structure de fenêtre (window)
              int headerHeight  - La hauteur souhaitée de la barre d'en-tête
              char titre[60] - Le titre à afficher dans la barre d'en-tête
              char icon[60] - Le chemin d'accès à l'icône
              int iconWidth - La largeur de l'icône.
              int iconHeight - La hauteur de l'icône.
Sortie       : -
Description  : cette fonction personnalise l'apparence de la fenêtre en
ajoutant une barre d'en-tête
*************************************************************/
void ajouterHeader(window *maFenetre,GtkWidget *box,int headerHeight,int headerWidth,char titre[60],char icon[60],int iconWidth,int iconHeight)
{
    gtk_window_set_decorated(GTK_WINDOW(maFenetre->window), FALSE);
    GtkWidget *header_bar = gtk_header_bar_new();
    gtk_widget_set_size_request(header_bar, headerWidth, headerHeight);
    gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), titre);
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
    // Création d'une icône pour la barre d'en-tête
    GtkWidget *icon_image =create_image_widget_from_file(icon);
    set_icon_size(icon_image,iconWidth,iconHeight);
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header_bar), icon_image);
    // Création d'une boîte pour contenir la barre d'en-tête et le contenu
    gtk_container_add(GTK_CONTAINER(box), header_bar);
    //gtk_container_add(GTK_CONTAINER(maFenetre->window), box);
    g_signal_connect(maFenetre->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}//Fin Fonction ajouterHeader()



////////////////////////////////////////////////////////////////////////
//-------> ajouter button à header
void ajouterButtonHeaderDebut(GtkWidget *header_bar,GtkWidget *button)
{
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header_bar), button);
}
void ajouterButtonHeaderFin(GtkWidget *header_bar,GtkWidget *button)
{
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header_bar), button);
}
////////////////////////////////////////////////////////////////////////
//MAIN
int mainWindow(int argc, char *argv[])
{

    gtk_init(&argc, &argv);
    //creation d'un type color
    hexa_color *myColor = NULL;
    myColor =init_hexa_color(myColor, "pink");
    //creation type dimension
    dimension *dim= create_dimension(500,500);

    //creation type coordonees
    coordonnees *cord= create_coordonnees(20,30);

    //image de background
    MonImage *bgImg=create_image_widget("background.jpg",0,0,*dim);

    //creation+initialisation
    window *maFenetre= init_window(*dim,3,"fatiha's window","flower.png",1,
                                   GTK_WIN_POS_CENTER_ALWAYS,*cord,*myColor,*bgImg);
    create_window(maFenetre);


    //----------------> ajouter headerBar
    //ajouterHeader(maFenetre,50,"l'entete","flower.png",
     //             50,50);
    // Afficher tous les widgets
    gtk_widget_show_all(maFenetre->window);
    gtk_main();
    return 0;
}
#endif //UNTITLED_WINDOW_H

/*
 ////////////////////////////////////////////////////////////////////////
//MAIN EXEMPLE DEMO
void menu_item_clicked(GtkWidget *widget, gpointer data) {
    g_print("Menu item clicked.\n");
}

int main(int argc, char *argv[]) {
    // Initialisation de GTK
    gtk_init(&argc, &argv);
    //creation d'un type color
    hexa_color *myColor = NULL;
    myColor =init_hexa_color(myColor, "pink");
    //creation type dimension
    dimension *dim= create_dimension(600,900);


    //creation type coordonees
    coordonnees *cord_w= create_coordonnees(20,30);
    //image de background

    MonImage *image=create_image_widget("ILISI.jpg",10,30,*dim);
    //creation+initialisation
    window *window= init_window(*dim,3,"fatiha's window","flower.png",1,
                                GTK_WIN_POS_CENTER_ALWAYS,*cord_w,*myColor,*image);
    create_window(window);

    //ajouter menubar dans la fenetre
    fixedObj *fixedo = NULL;
    fixedo = creer_fixed();
    gtk_container_add(GTK_CONTAINER(window->window), fixedo->fix);
    ////////////////
    ///header Bar
    hexa_color *myColor4 = NULL;
    myColor4 =init_hexa_color(myColor4, "pink");
    dimension *dimBox= create_dimension(20,900);
    Mybox *box= init_box("monBox",'h',0,*dimBox,
                         1,3,*myColor4,0);
    creer_box(box);
    ajouterHeader(window,box->box,50,900,"Exemple Demo",
                  "flower.png",50,50);
    //ajouter le box a fixed
    coordonnees *cordd= create_coordonnees(0,0);
    set_position(fixedo,box->box,*cordd);
    ////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    //MENU VERTICALE
    //menubaree
    MenuBarObj *m_b;
    m_b=initialiser_menubar();
    creer_menu_bar(m_b);
    //creer des menus
    MenuObj *menu4, *menu5, *menu6;
    menu4 = initialiser_menu();
    menu5 = initialiser_menu();
    menu6 = initialiser_menu();
    creer_menu_avec_libelle(menu4, "  menu4");
    creer_menu_avec_libelle(menu5, "  menu5");
    creer_menu_avec_libelle(menu6, "menu \ndéroulant");
    //asocier menu 6 a un menubar
    add_menu_to_menu_bar(m_b, menu6);
    //-->creer vbox et attacher le a fixed
    dimension *dim3= create_dimension(50,50);
    hexa_color *myColor3 = NULL;
    myColor3 =init_hexa_color(myColor3, "#728cb0");
    Mybox *vbox = init_box("monBox", 'v', 10, *dim3,
                           2, 3, *myColor3, 1);
    creer_box(vbox);
    coordonnees cord;
    cord.x = 10;
    cord.y = 140;
    set_position(fixedo, vbox->box, cord);
    //******
    //ajouter les menubar dans un hbox
    ajouter_container(vbox->box, menu4->menu);
    ajouter_container(vbox->box, menu5->menu);
    ajouter_container(vbox->box, m_b->menu_bar);
    //creer un submenu pour chacun des menus en haut
    MenuObj *sub_menu6;
    sub_menu6 = creer_sub(menu6);
    //ajouter le contenu des submenus
    //>sub1
    add_item_to_submenu(sub_menu6, "item1");
    add_item_to_submenu(sub_menu6, "item2");
    //FIN DE MENU VERTICALE
    ////////////////////////////////////////////////////////////////////////////////////////
    //MENU HORIZONTALE

    //menubaree
    //creer un menu bar
    MenuBarObj *menu_bar;
    menu_bar = initialiser_menubar();
    creer_menu_bar(menu_bar);

    //-->creer hbox et attacher le a fixed
    dimension *dim2= create_dimension(50,100);
    hexa_color *myColor2 = NULL;
    myColor2 =init_hexa_color(myColor2, "#728cb0");
    Mybox *hbox = init_box("monBox", 'h', 50, *dim2,
                           2, 3, *myColor2, 1);
    creer_box(hbox);
    //coordonnees cord;
    cord.x = 100;
    cord.y = 90;
    set_position(fixedo, hbox->box, cord);
    //******
    //ajouter les menubar dans un hbox
    ajouter_container(hbox->box, menu_bar->menu_bar);
    //creer listes des menu de menubar
    MenuObj *menu1, *menu2, *menu3;
    menu1 = initialiser_menu();
    menu2 = initialiser_menu();
    menu3 = initialiser_menu();
    creer_menu_avec_libelle(menu1, "menu1");
    creer_menu_avec_libelle(menu2, "menu2");
    creer_menu_avec_libelle(menu3, "menu3");
    //associer les menus au menubar
    add_menu_to_menu_bar(menu_bar, menu1);
    add_menu_to_menu_bar(menu_bar, menu2);
    add_menu_to_menu_bar(menu_bar, menu3);

    //creer un submenu pour chacun des menus en haut
    MenuObj *sub_menu1, *sub_menu2, *sub_menu3;
    sub_menu1 = creer_sub(menu1);
    sub_menu2 = creer_sub(menu2);
    sub_menu3 = creer_sub(menu3);

    //ajouter le contenu des submenus
    //>sub1
    add_item_to_submenu(sub_menu1, "item1");
    add_item_to_submenu(sub_menu1, "item2");
    //>sub2
    add_item_to_submenu(sub_menu2, "item1");
    add_item_to_submenu(sub_menu2, "item2");
    //>sub3
    add_item_to_submenu(sub_menu3, "item1");
    add_item_to_submenu(sub_menu3, "item2");


    //FIN MENU HORIZONTALE
    ///////////////////////////////////////////////////////////////////////
    //IMAGE
    dim3->height=40;
    dim3->width=70;

    //image
    MonImage *bgImg=create_image_widget("ILISI.jpg",11,90,*dim3);
    cord.x=bgImg->ImCrd.x;
    cord.y=bgImg->ImCrd.y;
    set_position(fixedo, bgImg->image, cord);
    //////////////////////////////////////////////////////////////////////
    //Entry
    dim3->height=30;
    dim3->width=90;
    myEntry *entry= init_entry("text par defaut",*dim3,30,0,
                               1,0,'*',"lock.png");
    creer_entry(entry);
    //entry2
    myEntry *entry2= init_entry("Nom",*dim3,30,1,
                                1,0,'-',"woman.png");
    creer_entry(entry2);
    //entry3
    myEntry *entry3= init_entry("Prenom",*dim3,30,1,
                                1,0,'-',"woman.png");
    creer_entry(entry3);
    //entry4
    myEntry *entry4= init_entry("adresse",*dim3,30,1,
                                1,0,'-',"adresse.png");
    creer_entry(entry4);

    cord.x = 140;
    cord.y = 150;
    set_position(fixedo,entry->entry,cord);
    cord.y = 200;
    set_position(fixedo,entry2->entry,cord);
    cord.y = 250;
    set_position(fixedo,entry3->entry,cord);
    cord.y =300;
    set_position(fixedo,entry4->entry,cord);


    /////////////////////////////////////
    //ajouter label et ComboBox
    hexa_color *textColor=NULL;
    textColor = init_hexa_color(textColor, "#0098c3");
    Style *labelStyle;
    labelStyle = init_style("Arial", *textColor, 10, 1);
    coordonnees cordLabel = {400, 100};
    MonLabel *mon_label = init_label(window->window, "MonLabel",
                                     "choisir un element", 0, *dim3,cordLabel);
    creer_label(mon_label);
    appliquer_style(labelStyle, mon_label);
    set_position(fixedo,mon_label->Label,cordLabel);
    //
    coordonnees *crdd= create_coordonnees(400,140);
    dimension *dimComboBox= create_dimension(30,190);
    //premier ComboBox
    gtkComboBox *comboBox=init_comboBox(*dimComboBox,*crdd,"myCombo1",fixedo->fix);
    create_ComboBox(comboBox);
    gtk_combo_box_text_prepend(GTK_COMBO_BOX_TEXT(comboBox->comboBox), "element0", "Élément 0");
    //ajouter des elements au comboBox
    ajouterElementComboBox(comboBox,"element 1","element 1");
    ajouterElementComboBox(comboBox,"element 2","element 2");
    ajouterElementComboBox(comboBox,"element 3","element 3");
    elementActive(comboBox,1);
    //deuxieme ComboBox
    coordonnees *crdd2= create_coordonnees(400,200);
    gtkComboBox *comboBox2=init_comboBox(*dimComboBox,*crdd2,"myCombo2",fixedo->fix);
    create_ComboBox(comboBox2);
    gtk_combo_box_text_prepend(GTK_COMBO_BOX_TEXT(comboBox2->comboBox), "choix1", "choix2");
    //ajouter des elements au comboBox
    ajouterElementComboBox(comboBox2,"element 1","element 1");
    ajouterElementComboBox(comboBox2,"element 2","element 2");
    ajouterElementComboBox(comboBox2,"element 3","element 3");
    elementActive(comboBox2,2);

    /////////////////////////////////////////////////////////////////////
    gtk_widget_show_all(window->window);
    gtk_main();


    return 0;
}

 */

