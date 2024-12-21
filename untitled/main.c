#include <gtk/gtk.h>
#include "Global.h"


void button_clicked(GtkButton *button, MonFileChooser *file_chooser)
{
    // Affichage du sélecteur de fichiers
    gtk_dialog_run(GTK_DIALOG(file_chooser->file_chooser));

    // Récupération du fichier sélectionné
    gchar *selected_file = get_selected_file(file_chooser);
    if (selected_file != NULL) {
        g_print("Fichier sélectionné : %s\n", selected_file);
        g_free(selected_file);
    } else {
        g_print("Aucun fichier sélectionné.\n");
    }
}//Fin fonction button clicked

////////////////////////////////////////////////////////////////////////
//MAIN
void menu_item_clicked(GtkWidget *widget, gpointer data)
{
    g_print("Menu item clicked.\n");
}//Fin fonction menu_item_clicked()

int main(int argc, char *argv[])
{
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
    //////////////// //////////////// //////////////// //////////////// ////////////////
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
    myColor3 =init_hexa_color(myColor3, "#ACC1E5");
    Mybox *vbox = init_box("monBox", 'v', 10, *dim3,
                           2, 3, *myColor3, 1);
    creer_box(vbox);
    coordonnees cord;
    cord.x = 10;
    cord.y = 140;
    set_position(fixedo, vbox->box, cord);
    //////////////////////////////////////////////////////////////////////////////////////
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
    //creer un menu bar
    MenuBarObj *menu_bar;
    menu_bar = initialiser_menubar();
    creer_menu_bar(menu_bar);
    //-->creer hbox et attacher le a fixed
    dimension *dim2= create_dimension(50,100);
    hexa_color *myColor2 = NULL;
    myColor2 =init_hexa_color(myColor2, "#ACC1E5");
    Mybox *hbox = init_box("monBox", 'h', 50, *dim2,
                           2, 3, *myColor2, 1);
    creer_box(hbox);
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
    creer_menu_avec_libelle(menu1, "Fichier");
    creer_menu_avec_libelle(menu2, "aide");
    creer_menu_avec_libelle(menu3, "ajouter");
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

    //////////////////////////////////////////////////////////////////////////
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
    coordonnees cordLabelCal = {700, 100};
    MonLabel *calendar_label = init_label(window->window, "calendrier",
                                     "calendrier", 0, *dim3,cordLabelCal);
    creer_label(calendar_label);
    appliquer_style(labelStyle, calendar_label);
    set_position(fixedo,calendar_label->Label,cordLabelCal);
    //ajouter Calendar
    // Initialisation de la structure Calender
    Calender *calendrier = init_calender(window->window, (coordonnees){0, 0},(dimension){100, 40});
    // Création et configuration du calendrier
    createCalendar(calendrier);
    //ajouter le à fixed
    coordonnees cordCalendar;
    cordCalendar.x = 600;
    cordCalendar.y = 140;
    set_position(fixedo, calendrier->calendar,cordCalendar);

    //ajouter la liste des boutons   ---------> CheckBox
    ////
    dimension dimButton = {100, 50};
    Style *buttonStyle = init_style_Button(NULL, "Arial", *textColor, 11, 1);

    //creation de le premiere boutton
    checkbox_Button *mon_bouton = init_buttonCheckbox(window->window, "Etudiant", 0,
                                                      (coordonnees){0,0},dimButton, 1);
    creer_button_check(mon_bouton);
    appliquer_style_button(buttonStyle, mon_bouton->Button);
    add_checkbox_button_to_list(mon_bouton);
    set_position(fixedo, mon_bouton->Button,(coordonnees ){20,400});

    //creation de la deuxieme boutton
    checkbox_Button *second_button = init_buttonCheckbox(window->window, "Enseignant", 0,
                                                         (coordonnees ){0,0},
                                                         dimButton, 0);
    creer_button_check(second_button);
    appliquer_style_button(buttonStyle, second_button->Button);
    add_checkbox_button_to_list(second_button);
    set_position(fixedo, second_button->Button,(coordonnees ){20,450});

    //creation e la troisieme boutton
    checkbox_Button *third_button = init_buttonCheckbox(window->window, "autre..", 0,
                                                        (coordonnees ){0,0}, dimButton, 0);
    creer_button_check(third_button);
    appliquer_style_button(buttonStyle, third_button->Button);
    add_checkbox_button_to_list(third_button);
    set_position(fixedo, third_button->Button,(coordonnees ){20,500});

    //ajouter la liste des boutons --------> RADIO Button
    ////
    GtkWidget *Monbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GSList *group = NULL;
    Radio_Button *radio_button1 = ajouter_bouton_radio(Monbox, "Option 1", &group, FALSE);
    gtk_box_pack_start(GTK_BOX(Monbox), radio_button1->Button, FALSE, FALSE, 0);

    Radio_Button *radio_button2 = ajouter_bouton_radio(Monbox, "Option 2", &group, FALSE);
    gtk_box_pack_start(GTK_BOX(Monbox), radio_button2->Button, FALSE, FALSE, 0);

    Radio_Button *radio_button3 = ajouter_bouton_radio(Monbox, "Option 3", &group, TRUE);
    gtk_box_pack_start(GTK_BOX(Monbox), radio_button3->Button, FALSE, FALSE, 0);

    //ajouter le a fixed
    set_position(fixedo, Monbox,(coordonnees ){400,400});

    /////////////////////////////////////////
    //Creation de FileChooser
    MonFileChooser *file_chooser = create_file_chooser_widget("Sélectionner un fichier",
                                                              GTK_FILE_CHOOSER_ACTION_OPEN);
    // Création d'un bouton pour lancer le file chooser
    GtkWidget *button = gtk_button_new_with_label("Ouvrir le file chooser");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(button_clicked), file_chooser);
    set_position(fixedo, button,(coordonnees ){550,400});
    //Fin
    gtk_widget_show_all(window->window);
    gtk_main();
    return 0;
}