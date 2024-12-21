//
// Created by admin on 03/03/2024.
//

#ifndef UNTITLED_GRID_H
#define UNTITLED_GRID_H
#define MAXNAME 60

typedef struct
{
    GtkWidget *grid;//le conteneur grid
    gchar name[MAXNAME];//Nom du grid
    gint halign;//alignement horizontal,
    gint valign;//alignement vertical,
    gint rowspace;//espace entre les colonnes,
    gint colspace;//espace entre les lignes,
    dimension dim;//la hauteur et la longueur de grid
    gint border;//taille de bordure
    hexa_color *bgColor;//Background color
}GridObj;
/*
 * ***********************************************************************************
 * Nom          : initialiser_Grid
 * Entrée       :  *nom de grid,
 *                 *alignement horizontal et vertical de grid :
 *                  0 :pas d'alignement
                    1 : GTK_ALIGN_FILL: Remplit l'espace.
                    2 : GTK_ALIGN_START: Aligné en haut.
                    3 : GTK_ALIGN_END: Aligné en bas.
                    4 :GTK_ALIGN_CENTER: Aligné au centre.
                    *espace entre les colonnes,
                    *espace entre les lignes,
                    *dimension (hauteur,larger),
                    *taille de bordure;
                    *couleur de background,
 * Sortie       : pointeur sur une structure de type GridObj
 * Description  : Cette fonction permet de créer et initialiser la structure de grid
 *  ***********************************************************************************
 */
GridObj*initialiser_Grid(gchar nom[MAXNAME],gint ha,gint va,gint rows,gint cols, dimension dim,gint border,hexa_color *bgColor)
{

    GridObj *grido=NULL;
    //allocation de memoire
    grido=(GridObj*)malloc(sizeof(GridObj));
    if(!grido)
    {
        printf("\nError d'allocation");
        exit(-1);
    }
    //l'ajout de la couleur de bachground s'il exist
    if(bgColor) grido->bgColor=bgColor;
    strcpy(grido->name,nom);
    grido->dim= dim;
    grido->halign=ha;
    grido->valign=va;
    grido->border=border;
    grido->rowspace=rows;
    grido->colspace=cols;
    return (GridObj*) grido;
}
/*
 * ***********************************************************************************
 * Nom          : set_alignement
 * Entrée       :  *Un widget GTK,
                   *alignement horizontal
                   *alignement vertical
 * Description  : Cette fonction permet de définir l'alignement horizontal
                    et vertical d'un widget
 *  ***********************************************************************************
 */
void set_alignement(GtkWidget *w, gint ha, gint va)
{
    //0 :pas d'alignement
    //1 : GTK_ALIGN_FILL: Remplit l'espace .
    //2 : GTK_ALIGN_START: Aligné en haut.
    //3 : GTK_ALIGN_END: Aligné en bas.
    //4 :GTK_ALIGN_CENTER: Aligné au centre .

    switch(ha)
    {
        case 1:gtk_widget_set_halign(w, GTK_ALIGN_FILL);break;
        case 2:gtk_widget_set_halign(w, GTK_ALIGN_START);break;
        case 3:gtk_widget_set_halign(w, GTK_ALIGN_END);break;
        case 4:gtk_widget_set_halign(w, GTK_ALIGN_CENTER);break;
        default:gtk_widget_set_halign(w, GTK_ALIGN_CENTER);break;
    }
    switch(va)
    {
        case 1:
            gtk_widget_set_valign(w, GTK_ALIGN_FILL);break;
        case 2:
            gtk_widget_set_valign(w, GTK_ALIGN_START);break;
        case 3:
            gtk_widget_set_valign(w, GTK_ALIGN_END);break;
        case 4:
            gtk_widget_set_valign(w, GTK_ALIGN_CENTER);break;
        default: gtk_widget_set_valign(w, GTK_ALIGN_CENTER);break;
    }
}
/*
 * ***********************************************************************************
 * Nom          : creer_Grid
 * Entrée       :  *pointeur de type GridObj
 * Description  :  la fct crée le conteneur grid de gtk d'après la structure
 *  ***********************************************************************************
 */
void creer_Grid(GridObj*grido)
{
    //creation du grid
    grido->grid=gtk_grid_new();
    //changement de hauteur et largeur du grid
    gtk_widget_set_size_request(grido->grid,grido->dim.width,grido->dim.height);
    //bordure du grid
    gtk_container_set_border_width(GTK_CONTAINER(grido->grid),grido->border);
    //ajout de nom s'il exist
    if(strlen(grido->name)!=0) gtk_widget_set_name(grido->grid,grido->name);
    //definir l'alignement horizontal et vertical
    set_alignement(grido->grid,grido->halign,grido->valign);
    //ajouter la couleur de background s'elle exist
    if(grido->bgColor)
    {
        gtk_widget_override_background_color(grido->grid, GTK_STATE_FLAG_NORMAL, grido->bgColor);
    }
    // espace entre les colonnes,
    gtk_grid_set_row_spacing(GTK_GRID(grido->grid), grido->rowspace);
    //espace entre les lignes
    gtk_grid_set_column_spacing(GTK_GRID(grido->grid), grido->colspace);
}
/*
 * ***********************************************************************************
 * Nom          : add_to_grid
 * Entrée       :  *pointeur vers le widget grid
                   *pointeur vers le widget fils
                   *coordonnée de fils (x,y)
                   * dimension de fils (longueur , largeur);
 * Description  :  la fct ajout le fils au conteneur grid
 *  ***********************************************************************************
 */
void add_to_grid(GtkWidget*grid,GtkWidget*child,coordonnees cord,dimension dim)
{
    gtk_grid_attach(GTK_GRID(grid), child, cord.x, cord.y, dim.width, dim.height);
}


//fct main de grid (exemple)
int mainGrid(int argc, char *argv[])
{
    // Initialisation de GTK
    gtk_init(&argc, &argv);


    // Création de la fenêtre
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Exemple de conteneur GtkGrid");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);


    // Création du conteneur de type grille (GtkGrid)
    GridObj *newg;
    //creation d'un type color
    hexa_color *myColor = NULL;
    myColor =init_hexa_color(myColor, "pink");


    //creer dimention (height et width)
    dimension *dim ;
    dim=(dimension*)malloc(sizeof(dimension));
    dim->height = 80;
    dim->width = 80;

    //initialiser et creer grid
    newg=initialiser_Grid("testgrid",4,4,0,10,*dim,0,myColor);
    creer_Grid(newg);
    //ajouter le contanier grid dans la fenetre
    gtk_container_add(GTK_CONTAINER(window), newg->grid);

    //ajouter buttons to grid;
    GtkWidget *button1 = gtk_button_new_with_label("Bouton 1");
    GtkWidget *button2 = gtk_button_new_with_label("Bouton 2");
    GtkWidget *button3 = gtk_button_new_with_label("Bouton 3");
    GtkWidget *button4 = gtk_button_new_with_label("Bouton 4");
    //cordonnee
    coordonnees cord;
    cord.x=0;
    cord.y=0;
    dimension dim_child;
    dim_child.width=1;
    dim_child.height=1;
    add_to_grid(newg->grid,button1,cord,dim_child);
    cord.x=0;
    cord.y=1;
    add_to_grid(newg->grid,button2,cord,dim_child);
    cord.x=1;
    cord.y=0;
    add_to_grid(newg->grid,button3,cord,dim_child);
    cord.x=1;
    cord.y=1;
    add_to_grid(newg->grid,button4,cord,dim_child);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;

}


#endif //UNTITLED_GRID_H
