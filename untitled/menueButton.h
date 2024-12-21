//
// Created by admin on 11/03/2024.
//

#ifndef UNTITLED_MENUEBUTTON_H
#define UNTITLED_MENUEBUTTON_H


// Global list to store checkbox buttons
GList *buttonList = NULL;

void add_checkbox_button_to_list(checkbox_Button *button)
{
    buttonList = g_list_append(buttonList, button);
}
// Function to add a button to the container
void add_button_to_container(GtkWidget *container, gpointer data) {
    checkbox_Button *button = (checkbox_Button *)data;
    gtk_fixed_put(GTK_FIXED(container), button->Button, button->cord.x, button->cord.y);
}

int mainMenueButton(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *pere = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *conteneur = gtk_fixed_new();

    //cordonnee coord = {22, 30};
    dimension dim = {100, 50};

    hexa_color *textColor = init_hexa_color(NULL, "red");
    Style *buttonStyle = init_style_Button(NULL, "Arial", *textColor, 16, 1);

    //creation de le premiere boutton
    checkbox_Button *mon_bouton = init_buttonCheckbox(pere, "Cliquez-moi", 0, (coordonnees){10,10}, dim, 1);
    creer_button_check(mon_bouton);
    appliquer_style_button(buttonStyle, mon_bouton->Button);
    add_checkbox_button_to_list(mon_bouton);


    //creation de la deuxieme boutton
    checkbox_Button *second_button = init_buttonCheckbox(pere, "Nouveau bouton", 0, (coordonnees ){10,40}, dim, 0);
    creer_button_check(second_button);
    appliquer_style_button(buttonStyle, second_button->Button);
    add_checkbox_button_to_list(second_button);


    //creation e la troisieme boutton
    checkbox_Button *third_button = init_buttonCheckbox(pere, "Nouveau bouton", 0, (coordonnees ){10,70}, dim, 0);
    creer_button_check(third_button);
    appliquer_style_button(buttonStyle, third_button->Button);
    add_checkbox_button_to_list(third_button);

    gtk_fixed_put(GTK_FIXED(conteneur), mon_bouton->Button, mon_bouton->cord.x, mon_bouton->cord.y);
    gtk_fixed_put(GTK_FIXED(conteneur), second_button->Button, second_button->cord.x, second_button->cord.y);
    gtk_fixed_put(GTK_FIXED(conteneur), third_button->Button, third_button->cord.x, third_button->cord.y);


    gtk_container_add(GTK_CONTAINER(pere), conteneur);
    gtk_widget_show_all(pere);

    g_signal_connect(pere, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();

    // Free the allocated memory for the button list
    g_list_free_full(buttonList, (GDestroyNotify)free);

    return 0;
}






#endif //UNTITLED_MENUEBUTTON_H
