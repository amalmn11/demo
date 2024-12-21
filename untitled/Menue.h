//
// Created by admin on 04/03/2024.
//

#ifndef UNTITLED_MENUE_H
#define UNTITLED_MENUE_H


typedef struct
{
    GtkWidget *fix;
}fixedObj;
fixedObj*creer_fixed()
{
    fixedObj*fixedo=NULL;
    fixedo=(fixedObj*)malloc(sizeof(fixedObj));
    if(!fixedo)
    {
        printf("\nError d'allocation");
        exit(-1);
    }
    fixedo->fix=gtk_fixed_new();
    return (fixedObj *) fixedo;

}
/*Nom: ajouter_container
 * Entrée: *widget parent, *widget fils
 * Description : Fct pour assigner un widget a une autre
 * */
void ajouter_container(GtkWidget *parent,GtkWidget *fils)
{
    gtk_container_add(GTK_CONTAINER(parent),fils);
}
/* Nom: set_position
 * Entrée: *un pointeur vers le conteneur fixed,
           *widget fils
           *coordonnées (x,y)
 * Description : Fct pour positionner un widget
 * */
void set_position(fixedObj*fixedo, GtkWidget *wid,coordonnees cord)
{
    gtk_fixed_put(GTK_FIXED(fixedo->fix),wid,cord.x,cord.y);
}

// --->Structure de menu
typedef struct {
    GtkWidget *menu;//widget menu
    char libelle[MAXNAME];//son libelle
} MenuObj;

// --->Structure de menu bar
typedef struct {
    GtkWidget *menu_bar; //widget menubar
} MenuBarObj;



//fct d'initialisation de menu
/** ***********************************************************************************
 * Nom          : initialiser_menu
 * Sortie       : pointeur sur la structure MenuObj
 * Description  :  Cette fonction permet de créer et initialiser la structure de  menu
 *  *********************************************************************************** */
MenuObj*initialiser_menu()
{
    MenuObj *menuObj = NULL;
    menuObj= (MenuObj*)malloc(sizeof(MenuObj));
    if(!menuObj)
    {
        printf("\nError d'allocation");
        exit(-1);
    }
    return (MenuObj*) menuObj;
}



// Function to create menu

/** ***********************************************************************************
 * Nom          : creer_menu
 * Entree       : pointeur sur la structure MenuObj
 * Description  :   fonction permet de créer un menu sans libelle
 *  *********************************************************************************** */
void creer_menu(MenuObj*menuObj) {

    menuObj->menu = gtk_menu_new();
}

/** ***********************************************************************************
 * Nom          : creer_menu_avec_libelle
 * Entree       : pointeur sur la structure MenuObj
 * Description  :   fonction permet de créer un menu avec libelle
 *  *********************************************************************************** */
void creer_menu_avec_libelle(MenuObj*menuObj,char libelle[20]) {

    menuObj->menu = gtk_menu_item_new_with_label(libelle);
}

//fct initialiser et creer et associer submenu avec son menu pere

/** ***********************************************************************************
 * Nom          : creer_sub
 * Entree       : pointeur sur la structure MenuObj
 * Sortie       : pointeur sur la structure MenuObj
 * Description  : initialiser , créer et associer submenu avec son menu père
 *  *********************************************************************************** */
MenuObj*creer_sub(MenuObj*pere)
{
    MenuObj*sub=NULL;
    sub=initialiser_menu();
    creer_menu(sub);
    //associer sub a son pere
    gtk_menu_item_set_submenu((GtkMenuItem *) pere->menu, sub->menu);
    return ((MenuObj*)sub);
}

//fct d'initialisation de menubar

/** ***********************************************************************************
 * Nom          : initialiser_menubar
 * Sortie       : pointeur sur la structure MenuBarObj
 * Description  :  Cette fonction permet de créer et initialiser la structure de  menubar
 *  *********************************************************************************** */
MenuBarObj*initialiser_menubar()
{
    MenuBarObj *menuBarO = NULL;
    menuBarO =(MenuBarObj*)malloc(sizeof(MenuBarObj));
    if(!menuBarO)
    {
        printf("\nError d'allocation");
        exit(-1);
    }
    return (MenuBarObj*) menuBarO;

}
// Function to create menu bar
/** ***********************************************************************************
 * Nom          : creer_menu_bar
 * Sortie       : pointeur sur la structure MenuBarObj
 * Description  :  Cette fonction permet de créer un  menubar
 *  *********************************************************************************** */
void creer_menu_bar( MenuBarObj *menuBarO)
{
    menuBarO->menu_bar = gtk_menu_bar_new();
}

// Function to add an item to a submenu that already created and associated with its menu

/** ***********************************************************************************
 * Nom          : add_item_to_submenu
 * Entree       : pointeur sur la structure MenuObj, libelle de son item
 * Description  : ajouter un élément à un sous-menu déjà créé et associé à son menu parent
 *  *********************************************************************************** */
void add_item_to_submenu(MenuObj *menuObj,  gchar label[20]) {
    GtkWidget *item = gtk_menu_item_new_with_label(label);
    gtk_menu_shell_append(GTK_MENU_SHELL(menuObj->menu), item);
}

// Function to add an item to the menu bar

/** ***********************************************************************************
 * Nom          : add_menu_to_menu_bar
 * Entree       : pointeur sur la structure MenuBarObj,
                  pointeur sur la structure MenuObj.
 * Description  : ajouter un menu à la barre de menu
 *  *********************************************************************************** */
void add_menu_to_menu_bar(MenuBarObj *menu_bar_obj,  MenuObj *menu) {
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar_obj->menu_bar), menu->menu);
}


// Callback function for menu item activation
void menu_item_activated(GtkMenuItem *item, gpointer user_data) {
    g_print("Item activated: %s\n", gtk_menu_item_get_label(item));
}

//exemple

int mainMENUHORIZONTAL(int argc, char *argv[]) {
    // Initialisation de GTK
    gtk_init(&argc, &argv);


    // Création de la fenêtre
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Exemple de conteneur GtkGrid");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    //ajouter menubar dans la fenetre
    fixedObj *fixedo = NULL;
    fixedo = creer_fixed();
    gtk_container_add(GTK_CONTAINER(window), fixedo->fix);

    //menubaree
    //creer un menu bar
    MenuBarObj *menu_bar;
    menu_bar = initialiser_menubar();
    creer_menu_bar(menu_bar);

    //-->creer hbox et attacher le a fixed
    dimension *dim2;
    dim2 = (dimension *) malloc(sizeof(dimension));
    dim2->height = 50;
    dim2->width = 100;
    hexa_color *myColor2 = NULL;
    myColor2 =init_hexa_color(myColor2, "pink");
    Mybox *hbox = init_box("monBox", 'h', 50, *dim2,
                           2, 3, *myColor2, 1);
    creer_box(hbox);
    coordonnees cord;
    cord.x = 0;
    cord.y = 0;
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

    gtk_widget_show_all(window);
    gtk_main();


    return 0;
}



int mainVERTICAL(int argc, char *argv[]) {
    // Initialisation de GTK
    gtk_init(&argc, &argv);


    // Création de la fenêtre
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Exemple de conteneur GtkGrid");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //menubaree
    //creer des menus
    MenuObj *menu4, *menu5, *menu6;
    menu4 = initialiser_menu();
    menu5 = initialiser_menu();
    menu6 = initialiser_menu();
    creer_menu_avec_libelle(menu4, "menu4");
    creer_menu_avec_libelle(menu5, "menu5");
    creer_menu_avec_libelle(menu6, "menu6");

    //ajouter menubar dans la fenetre
    fixedObj *fixedo = NULL;
    fixedo = creer_fixed();
    gtk_container_add(GTK_CONTAINER(window), fixedo->fix);
    //-->creer hbox et attacher le a fixed
    dimension *dim3;
    dim3 = (dimension *) malloc(sizeof(dimension));
    dim3->height = 30;
    dim3->width = 100;
    hexa_color *myColor3 = NULL;
    myColor3 =init_hexa_color(myColor3, "pink");
    Mybox *vbox = init_box("monBox", 'v', 0, *dim3,
                           2, 3, *myColor3, 1);
    creer_box(vbox);
    coordonnees cord;
    cord.x = 0;
    cord.y = 0;
    set_position(fixedo, vbox->box, cord);
    //******
    //ajouter les menubar dans un hbox
    ajouter_container(vbox->box, menu4->menu);
    ajouter_container(vbox->box, menu5->menu);
    ajouter_container(vbox->box, menu6->menu);



    //creer un submenu pour chacun des menus en haut
    MenuObj *sub_menu6;
    sub_menu6 = creer_sub(menu6);


    //ajouter le contenu des submenus
    //>sub1
    add_item_to_submenu(sub_menu6, "item1");
    add_item_to_submenu(sub_menu6, "item2");


    //menubarrefin
    gtk_widget_show_all(window);
    gtk_main();


    return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
///////////////////////////////
void menu_item_clicked_MENUE(GtkWidget *widget, gpointer data)
{
    g_print("Menu item clicked.\n");
}

int mainMENUE(int argc, char *argv[]) {
    // Initialisation de GTK
    gtk_init(&argc, &argv);
    //creation d'un type color
    hexa_color *myColor = NULL;
    myColor =init_hexa_color(myColor, "pink");
    //creation type dimension
    dimension *dim;
    dim=(dimension*)malloc(sizeof(dimension));
    dim->height=500;
    dim->width=800;

    //creation type coordonees
    coordonnees *cord_w= create_coordonnees(20,30);

    //image de background

    MonImage *image=create_image_widget("ILISI.png",10,30,*dim);
    //creation+initialisation
    window *window= init_window(*dim,3,"fatiha's window","flower.png",1,
                                GTK_WIN_POS_CENTER_ALWAYS,*cord_w,*myColor,*image);
    create_window(window);


    //ajouter menubar dans la fenetre
    fixedObj *fixedo = NULL;
    fixedo = creer_fixed();
    gtk_container_add(GTK_CONTAINER(window->window), fixedo->fix);
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
    dimension *dim3;
    dim3 = (dimension *) malloc(sizeof(dimension));
    dim3->height = 100;
    dim3->width = 100;
    hexa_color *myColor3 = NULL;
    myColor3 =init_hexa_color(myColor3, "pink");
    Mybox *vbox = init_box("monBox", 'v', 10, *dim3,
                           2, 3, *myColor3, 1);
    creer_box(vbox);
    coordonnees cord;
    cord.x = 10;
    cord.y = 90;
    set_position(fixedo, vbox->box, cord);
    //**
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
    dimension *dim2;
    dim2 = (dimension *) malloc(sizeof(dimension));
    dim2->height = 100;
    dim2->width = 100;
    hexa_color *myColor2 =NULL;
    myColor2 =init_hexa_color(myColor2, "pink");
    Mybox *hbox = init_box("monBox", 'h', 50, *dim2,
                           2, 3, *myColor2, 1);
    creer_box(hbox);
    //coordonnees cord;
    cord.x = 120;
    cord.y = 20;
    set_position(fixedo, hbox->box, cord);
    //**
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

    //image de background

    MonImage *bgImg=create_image_widget("ILISI.jpg",10,30,*dim3);
    cord.x=bgImg->ImCrd.x;
    cord.y=bgImg->ImCrd.y;
    set_position(fixedo, bgImg->image, cord);

    //////////////////////////////////////////////////////////////////////

    gtk_widget_show_all(window->window);
    gtk_main();


    return 0;
}
#endif //UNTITLED_MENUE_H
