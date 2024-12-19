#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "string.h"
#include "citoyen.h"

int xx,yy,zz;
int mm,nn,ll;

void
on_ajouternouha_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GdkColor color;

 GtkWidget *entry_id, *entry_Nomcomplet, *entry_email, *entry_telephone,
             *entry_cin,*entry_marque, *entry_matricule, *label_status;
    GtkWidget *radiobutton_h, *radiobutton_f,*combobox_region , *combobox_paiement;
    GtkWidget *check_mail, *check_SMS;
    GtkWidget *spinbutton_jour, *spinbutton_mois, *spinbutton_annee;

GtkWidget *label = lookup_widget(GTK_WIDGET(button), "titre1nouha");
gtk_label_set_markup(GTK_LABEL(label), "<span font='15' underline='single'><b>Formulaire d'ajout du citoyen</b></span>");


   
    // Déclarez la variable 'c' de type ProfilCitoyen
    Profilecitoyen c;
    char filename[] = "citoyens.txt";

    // Récupération des widgets via lookup_widget
    entry_cin = lookup_widget(GTK_WIDGET(button), "cinnouha");
    entry_Nomcomplet = lookup_widget(GTK_WIDGET(button), "nomnouha");
    entry_email = lookup_widget(GTK_WIDGET(button), "emailnouha");
    entry_telephone = lookup_widget(GTK_WIDGET(button), "telephonenouha");
    entry_id = lookup_widget(GTK_WIDGET(button), "idnouha");
    entry_marque= lookup_widget(GTK_WIDGET(button), "marquenouha");
    entry_matricule = lookup_widget(GTK_WIDGET(button), "matriculenouha");
    label_status = lookup_widget(GTK_WIDGET(button), "label_statusnouha");
    radiobutton_h = lookup_widget(GTK_WIDGET(button), "radiobutton1nouha");
    radiobutton_f = lookup_widget(GTK_WIDGET(button), "radiobutton2nouha");
    check_mail = lookup_widget(GTK_WIDGET(button), "checkbutton1nouha");
    check_SMS = lookup_widget(GTK_WIDGET(button), "checkbutton2nouha");
    spinbutton_jour = lookup_widget(GTK_WIDGET(button), "spinbutton1nouha");
    spinbutton_mois = lookup_widget(GTK_WIDGET(button), "spinbutton2nouha");
    spinbutton_annee = lookup_widget(GTK_WIDGET(button), "spinbutton3nouha");
    combobox_paiement = lookup_widget(GTK_WIDGET(button), "combo2nouha"); 
    combobox_region = lookup_widget(GTK_WIDGET(button), "combo1nouha"); 
 // Gestion des boutons radio - Sexe
 c.genre = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton_h)) ? 0: 1;

//check
   c.recevoirNotification[0] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_mail));
   c.recevoirNotification[1] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_SMS));
      


    // Récupérer les valeurs des champs    

    strcpy(c.cin, gtk_entry_get_text(GTK_ENTRY(entry_cin)));
    strcpy(c.nomComplet, gtk_entry_get_text(GTK_ENTRY(entry_Nomcomplet)));  
    strcpy(c.email, gtk_entry_get_text(GTK_ENTRY(entry_email)));
    strcpy(c.numeroTelephone, gtk_entry_get_text(GTK_ENTRY(entry_telephone)));    
    strcpy(c.id, gtk_entry_get_text(GTK_ENTRY(entry_id)));
    strcpy(c.marqueVoiture, gtk_entry_get_text(GTK_ENTRY(entry_marque)));
    strcpy(c.matriculeVoiture, gtk_entry_get_text(GTK_ENTRY(entry_matricule)));

//spinnn
    
    c.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_jour));
    c.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_mois));
    c.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_annee));

    // Validation générale des champs obligatoires
    if (strlen(c.id) == 0 || 
        strlen(c.nomComplet) == 0 || 
        strlen(c.email) == 0 ||
       strlen(c.numeroTelephone) == 0 ||
        strlen(c.marqueVoiture) == 0 || 
        strlen(c.matriculeVoiture) == 0) {
        gdk_color_parse("green",&color);
	gtk_widget_modify_fg(label_status,GTK_STATE_NORMAL,&color);
gtk_label_set_text(GTK_LABEL(label_status), "Données manquantes. \n Veuillez remplir tout les champs!");
    }


if (strlen(c.cin) != 8 || strspn(c.cin, "0123456789") != 8) {
        gdk_color_parse("green",&color);
	gtk_widget_modify_fg(label_status,GTK_STATE_NORMAL,&color);
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Le CIN doit contenir exactement 8 chiffres.");
        return;
    }

    // Validation spécifique pour le numéro de téléphone (exactement 8 chiffres)
    if (verifierNumeroTelephone(c.numeroTelephone)==1) {
         gdk_color_parse("green",&color);
	gtk_widget_modify_fg(label_status,GTK_STATE_NORMAL,&color);
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Le numéro de téléphone doit contenir exactement 8 chiffres.");
        return;
    }



//combobox
 if (combobox_paiement != NULL) {
        gchar *selected_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_paiement));

        if (selected_text != NULL) {
            // Affiche le genre sélectionné dans la console (debug)
            g_print("Genre sélectionné : %s\n", selected_text);
            // Copie le genre sélectionné dans la structure c
            strcpy(c.methodePaiement, selected_text);
           g_free(selected_text);
        } else {
            // Aucune option sélectionnée dans la combobox
            // Faites quelque chose en conséquence
           zz=0;
        }  }


 if (combobox_region != NULL) {
        gchar *selected_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_region));

        if (selected_text != NULL) {
            // Affiche le genre sélectionné dans la console (debug)
            g_print("Genre sélectionné : %s\n", selected_text);
            // Copie le genre sélectionné dans la structure c
            strcpy(c.region, selected_text);
           g_free(selected_text);
        } else {
            // Aucune option sélectionnée dans la combobox
            // Faites quelque chose en conséquence
           zz=0;
        }}






    // Ajout dans le fichier
    if (ajouterProfil(filename, c)==1) {
         gdk_color_parse("red",&color);
	gtk_widget_modify_fg(label_status,GTK_STATE_NORMAL,&color);
        gtk_label_set_text(GTK_LABEL(label_status), "Citoyen ajouté avec succès !");
    } else {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Échec de l'ajout du citoyen.");
    }


    // Réinitialisation des champs
    gtk_entry_set_text(GTK_ENTRY(entry_id), "");
    gtk_entry_set_text(GTK_ENTRY(entry_cin), "");
    gtk_entry_set_text(GTK_ENTRY(entry_Nomcomplet), "");
    gtk_entry_set_text(GTK_ENTRY(entry_email), "");
    gtk_entry_set_text(GTK_ENTRY(entry_telephone), "");
    gtk_entry_set_text(GTK_ENTRY(entry_marque), "");
    gtk_entry_set_text(GTK_ENTRY(entry_matricule), "");

  
 
}

void
on_checkbutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_checkbutton1nouha_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}

void
on_radiobutton1nouha_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radiobutton2nouha_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}






void
on_affichernouha_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{  

GtkWidget *treeview9, *label_status;
    const char *cin_saisi;
    gboolean found = FALSE;
    const char *filename = "citoyens.txt";

    // Récupérer la valeur saisie dans l'entrée de texte pour le CIN
    GtkWidget *entry_cin = lookup_widget(GTK_WIDGET(button), "entry3");  // Le nom du widget GtkEntry pour CIN
    cin_saisi = gtk_entry_get_text(GTK_ENTRY(entry_cin));

    // Vérification des widgets
    treeview9 = lookup_widget(GTK_WIDGET(button), "treeview1nouha");
    label_status = lookup_widget(GTK_WIDGET(button), "label652nouha");

    // Vérification des widgets
    if (!treeview9 || !label_status) {
        g_print("Erreur : Widgets non trouvés.\n");
        return;
    }


  // Réinitialisation du TreeView (effacement des données actuelles)
   GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview9)));
if (!store) {
    store = gtk_list_store_new(15,  
        G_TYPE_STRING,  // CIN
        G_TYPE_STRING,  // Nom complet
        G_TYPE_STRING,  // Email
        G_TYPE_STRING,  // Numéro de téléphone
        G_TYPE_STRING,  // ID
        G_TYPE_STRING,  // Région
        G_TYPE_STRING,  // Marque voiture
        G_TYPE_STRING,  // Matricule voiture
        G_TYPE_STRING,  // Méthode de paiement
        G_TYPE_INT,     // Genre
        G_TYPE_INT,     // Jour
        G_TYPE_INT,     // Mois
        G_TYPE_INT,     // Année
        G_TYPE_INT,     // Notification email
        G_TYPE_INT);
 gtk_tree_view_set_model(GTK_TREE_VIEW(treeview9), GTK_TREE_MODEL(store));
    g_object_unref(store);     
}
gtk_list_store_clear(store);

    // Lecture des citoyens dans le fichier et affichage selon le CIN
    FILE *file = fopen(filename, "r");
    if (file) {
        Profilecitoyen temp;
        char line[512];

        while (fgets(line, sizeof(line), file)) {
            // Extraction des informations du citoyen depuis la ligne du fichier
           if (sscanf(line, "%s %s %s %s %s %s %s %s %s %d %d %d %d %d %d\n",
           temp.cin, temp.nomComplet, temp.email, temp.numeroTelephone, temp.id, 
           temp.region, temp.marqueVoiture, temp.matriculeVoiture, temp.methodePaiement,
           &temp.genre, &temp.jour, &temp.mois, &temp.annee, 
           &temp.recevoirNotification[0], &temp.recevoirNotification[1]) == 15) {
  

                // Filtrage par CIN
                if (strcmp(temp.cin, cin_saisi) == 0) {
                    afficher_service_dans_treeview(temp, GTK_TREE_VIEW(treeview9));
                    found = TRUE;
                }
            }
        }
        fclose(file);
    }

    // Mise à jour du label
    if (found) {
        gtk_label_set_text(GTK_LABEL(label_status), "Citoyen trouvé et affiché.");
    } else {
        gtk_label_set_text(GTK_LABEL(label_status), "Aucun citoyen trouvé avec ce CIN.");
    }

}


int find_region_index(const char *region) {
    const char *regions[] = {"Tunis",
"Ben Arous","Bizerte","Nabeul","Beja","Kebili","Sfax","Sidi bou zid","Kef","Kasserine","Manouba",
"Jendouba","Mahdia" ,"Tataouine","Siliana","Medenine","Monastir","Ariana","Kairouan","Gabes","Sousse", "Gafsa"
};
    int size = sizeof(regions) / sizeof(regions[0]);
    for (int i = 0; i < size; i++) {
        if (strcmp(region, regions[i]) == 0) {
            return i; // Retourne l'index si trouvé
        }
    }
    return -1; // Non trouvé
}
void
on_cherchernouha_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{ 
GtkWidget *entry_id, *entry_Nomcomplet, *entry_email, *entry_telephone,
             *entry_cin,*entry_marque, *entry_matricule, *label_status;
    GtkWidget *radiobutton_h, *radiobutton_f,*combobox_region , *combobox_paiement;
    GtkWidget *check_mail, *check_SMS;
    GtkWidget *spinbutton_jour, *spinbutton_mois, *spinbutton_annee;

//ini
entry_cin = lookup_widget(GTK_WIDGET(button), "cinnouha1");
    entry_Nomcomplet = lookup_widget(GTK_WIDGET(button), "nomnouha1");
    entry_email = lookup_widget(GTK_WIDGET(button), "emailnouha1");
    entry_telephone = lookup_widget(GTK_WIDGET(button), "telephonenouha1");
    entry_id = lookup_widget(GTK_WIDGET(button), "idnouha1");
    entry_marque= lookup_widget(GTK_WIDGET(button), "marquenouha1");
    entry_matricule = lookup_widget(GTK_WIDGET(button), "matriculenouha1");
    label_status = lookup_widget(GTK_WIDGET(button), "label_statusnouha1");
    radiobutton_h = lookup_widget(GTK_WIDGET(button), "radiobutton1nouha1");
    radiobutton_f = lookup_widget(GTK_WIDGET(button), "radiobutton2nouha1");
    check_mail = lookup_widget(GTK_WIDGET(button), "checkbutton1nouha1");
    check_SMS = lookup_widget(GTK_WIDGET(button), "checkbutton2nouha1");
    spinbutton_jour = lookup_widget(GTK_WIDGET(button), "spinbutton1nouha1");
    spinbutton_mois = lookup_widget(GTK_WIDGET(button), "spinbutton2nouha1");
    spinbutton_annee = lookup_widget(GTK_WIDGET(button), "spinbutton3nouha1");
    combobox_paiement = lookup_widget(GTK_WIDGET(button), "combo2nouha1"); 
    combobox_region = lookup_widget(GTK_WIDGET(button), "combo1nouha1"); 

// Récupérer le cin saisi par l'utilisateur
    const char *search_cin = gtk_entry_get_text(GTK_ENTRY(entry_cin));
    if (!search_cin  || strlen(search_cin ) == 0) {
        gtk_label_set_text(GTK_LABEL(label_status), "Veuillez saisir un identifiant valide.");
        return;
    }
 // Recherche dans le fichier des feedbacks
    Profilecitoyen c;
    

    if (chercherProfil("citoyens.txt", search_cin , &c)) { // Feedback trouvé
       
        gtk_entry_set_text(GTK_ENTRY(entry_Nomcomplet), c.nomComplet);
        gtk_entry_set_text(GTK_ENTRY(entry_email), c.email);
        gtk_entry_set_text(GTK_ENTRY(entry_telephone), c.numeroTelephone);
        gtk_entry_set_text(GTK_ENTRY(entry_id), c.id);
       
        int region_index = find_region_index(c.region);
        if (region_index >= 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox_region), region_index);
        } else {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox_region), -1); // Pas de sélection
        }
        gtk_entry_set_text(GTK_ENTRY(entry_marque), c.marqueVoiture);
        gtk_entry_set_text(GTK_ENTRY(entry_matricule), c.matriculeVoiture);
      
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton_h), c.genre == 1);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton_f), c.genre == 2);

       gtk_combo_box_set_active(GTK_COMBO_BOX(combobox_paiement), atoi(c.methodePaiement)); // Conversion de l'urgence 
   

        
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton_jour), c.jour);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton_mois), c.mois);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton_annee), c.annee);


        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_mail), c.recevoirNotification[0]);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_SMS), c.recevoirNotification[1]);
       



        gtk_label_set_text(GTK_LABEL(label_status), "Entrée trouvée avec succès !");
    } else { // Feedback non trouvé
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Entrée introuvable.");
    }


     
}

void
on_radiobutton2nouha1_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radiobutton1nouha1_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_checkbutton1nouha1_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_checkbutton2nouha1_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_modifiernouha_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *entry_id, *entry_Nomcomplet, *entry_email, *entry_telephone,
             *entry_cin,*entry_marque, *entry_matricule, *label_status;
    GtkWidget *radiobutton_h, *radiobutton_f,*combobox_region , *combobox_paiement;
    GtkWidget *check_mail, *check_SMS;
    GtkWidget *spinbutton_jour, *spinbutton_mois, *spinbutton_annee;


    Profilecitoyen c ;
    char filename[] = "citoyens.txt";


//ini
entry_cin = lookup_widget(GTK_WIDGET(button), "cinnouha1");
    entry_Nomcomplet = lookup_widget(GTK_WIDGET(button), "nomnouha1");
    entry_email = lookup_widget(GTK_WIDGET(button), "emailnouha1");
    entry_telephone = lookup_widget(GTK_WIDGET(button), "telephonenouha1");
    entry_id = lookup_widget(GTK_WIDGET(button), "idnouha1");
    entry_marque= lookup_widget(GTK_WIDGET(button), "marquenouha1");
    entry_matricule = lookup_widget(GTK_WIDGET(button), "matriculenouha1");
    label_status = lookup_widget(GTK_WIDGET(button), "label_statusnouha1");
    radiobutton_h = lookup_widget(GTK_WIDGET(button), "radiobutton1nouha1");
    radiobutton_f = lookup_widget(GTK_WIDGET(button), "radiobutton2nouha1");
    check_mail = lookup_widget(GTK_WIDGET(button), "checkbutton1nouha1");
    check_SMS = lookup_widget(GTK_WIDGET(button), "checkbutton2nouha1");
    spinbutton_jour = lookup_widget(GTK_WIDGET(button), "spinbutton1nouha1");
    spinbutton_mois = lookup_widget(GTK_WIDGET(button), "spinbutton2nouha1");
    spinbutton_annee = lookup_widget(GTK_WIDGET(button), "spinbutton3nouha1");
    combobox_paiement = lookup_widget(GTK_WIDGET(button), "combo2nouha1"); 
    combobox_region = lookup_widget(GTK_WIDGET(button), "combo1nouha1"); 



    // Récupérer les données modifiées
    const char *cin_text = gtk_entry_get_text(GTK_ENTRY(entry_cin));
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(entry_id));
    const char *Nomcomplet_text = gtk_entry_get_text(GTK_ENTRY(entry_Nomcomplet));
    const char *email_text = gtk_entry_get_text(GTK_ENTRY(entry_email));
    const char *telephone_text = gtk_entry_get_text(GTK_ENTRY(entry_telephone));
    const char *marque_text = gtk_entry_get_text(GTK_ENTRY(entry_marque));
    const char *matricule_text = gtk_entry_get_text(GTK_ENTRY(entry_matricule));
    const char *region_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_region));
    const char *paiement_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_paiement));

    int jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_jour));
    int mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_mois));
    int annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_annee));
   
    // Vérification des champs obligatoires
    if (strlen(id_text) == 0 || strlen(cin_text) == 0 || strlen(Nomcomplet_text) == 0 || strlen(telephone_text) == 0) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Tous les champs obligatoires doivent être remplis.");
        return;
    }

    // Remplir la structure Feedback
    strcpy(c.id, id_text);
    strcpy(c.cin, cin_text);
    strcpy(c.nomComplet, Nomcomplet_text);
    strcpy(c.marqueVoiture, marque_text);
    strcpy(c.matriculeVoiture, matricule_text);
    strcpy(c.numeroTelephone, telephone_text);
    c.genre = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton_h)) ? 0 : 1;
    strcpy(c.email, email_text);
    strcpy(c.region , paiement_text);
    strcpy(c.methodePaiement , region_text);
    c.jour = jour;
    c.mois = mois;
    c.annee = annee;
    
// Traitement de l'urgence
region_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_region));
if (region_text != NULL && strlen(region_text) > 0) {
    strcpy(c.region, region_text);  // Copier la chaîne entière
} else {
    c.region[0] = '\0';  // Valeur par défaut si aucune option n'est sélectionnée
}


    // Traitement de la réclamation

    c.recevoirNotification[0] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_mail));
    c.recevoirNotification[1] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_SMS));
    
    // Sauvegarde dans le fichier
    int result = modifierProfil(filename, cin_text, c);
    if (result == 1) {
        gtk_label_set_text(GTK_LABEL(label_status), "Modification réussie.");
    } else {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur lors de la modification.");
    }
}



int mode_suppression_actif = 0;

void
on_Supprimeraficherr_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{ mode_suppression_actif = 1;  // Activer le mode suppression
    GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label652nouha");
    gtk_label_set_text(GTK_LABEL(label_status), "Sélectionnez un service à supprimer.");
}


void
on_treeview1nouha_cursor_changed       (GtkTreeView     *treeview,
                                        gpointer         user_data)
{
 if (!mode_suppression_actif) return;  // Ne rien faire si le mode suppression est désactivé

    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
    GtkTreeModel *model;
    GtkTreeIter iter;

    // Vérifier si une ligne est sélectionnée
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        char cin[20];  // Variable pour stocker le CIN

        // Récupérer le CIN de la ligne sélectionnée
        gtk_tree_model_get(model, &iter, 0, &cin, -1);
 int suppr = supprimerProfil("citoyens.txt", cin);
        // Supprimer le profil du fichier
        if ( suppr==1){
        g_print("Erreur : Widgets non trouvés.\n");
            // Supprimer la ligne du TreeView
            GtkListStore *store = GTK_LIST_STORE(model);
            gtk_list_store_remove(store, &iter);

            // Afficher un message de confirmation
            GtkWidget *label_status = lookup_widget(GTK_WIDGET(treeview), "label652nouha");
            gtk_label_set_text(GTK_LABEL(label_status), "Service supprimé avec succès.");
        } else {
            // Afficher un message d'erreur
            GtkWidget *label_status = lookup_widget(GTK_WIDGET(treeview), "label652nouha");
            gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Impossible de supprimer le service.");

        }

        // Désactiver le mode suppression après traitement
        mode_suppression_actif = 0;
    }
}


void
on_afficherpaiementnouha_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{ GtkWidget *image = gtk_image_new_from_file("/home/nom_utilisateur/Téléchargements/nana.jpeg");

    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeviewpaiement");
    GtkTreeIter iter;
    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;

    // Récupérer le CIN entré par l'utilisateur
    GtkWidget *entry_cin = lookup_widget(GTK_WIDGET(button), "cinavance");
    const char *cin = gtk_entry_get_text(GTK_ENTRY(entry_cin));

    // Vérifier que le TreeView a un modèle ou le créer
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));

    if (!store) {
        store = gtk_list_store_new(8,  
            G_TYPE_STRING,  // CIN
            G_TYPE_INT,     // Jour
            G_TYPE_INT,     // Mois
            G_TYPE_INT,     // Année
            G_TYPE_INT,     // ID Parking
            G_TYPE_FLOAT,   // Prix par heure
            G_TYPE_INT,     // Heures
            G_TYPE_FLOAT);  // Paiement

        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
        g_object_unref(store);
    }

    // Effacer les anciennes lignes
    gtk_list_store_clear(store);

   
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("CIN", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        // Jour
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Jour", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        // Mois
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Mois", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        // Année
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Année", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        // ID Parking
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID Parking", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        // Prix
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Prix", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        // Heures
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Heures", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        // Paiement
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Paiement", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    

    // Ouvrir les fichiers
    FILE *file_reservation = fopen("reservation.txt", "r");
    FILE *file_parking = fopen("parking.txt", "r");

    if (!file_reservation || !file_parking) {
        if (file_reservation) fclose(file_reservation);
        if (file_parking) fclose(file_parking);
        g_print("Erreur : Impossible d'ouvrir les fichiers.\n");
        return;
    }

    char cinFile[20];
    int jour, mois, annee, idParking, heures;
    float prix, paiement;
    int cin_found = 0;

    // Parcourir le fichier reservation.txt pour trouver les réservations pour ce CIN
    while (fscanf(file_reservation, "%s %d %d %d %d %d\n", cinFile, &jour, &mois, &annee, &idParking, &heures) != EOF) {
        if (strcmp(cinFile, cin) == 0) {
            cin_found = 1;

            // Parcourir le fichier parking.txt pour obtenir le prix du parking selon l'ID
            rewind(file_parking);  // Revenir au début du fichier parking.txt
            int temp_idParking;
            float temp_prix;
            while (fscanf(file_parking, "%d %f\n", &temp_idParking, &temp_prix) != EOF) {
                if (temp_idParking == idParking) {  // Vérifie si l'ID parking correspond
                    // Calculer le paiement pour ce jour
                    paiement = heures * temp_prix;

                    // Ajouter les données dans le GtkListStore
                    gtk_list_store_append(store, &iter);
                    gtk_list_store_set(store, &iter,
                                       0, cinFile,
                                       1, jour,
                                       2, mois,
                                       3, annee,
                                       4, idParking,   // ID Parking
                                       5, temp_prix,    // Prix par heure
                                       6, heures,      // Nombre d'heures
                                       7, paiement,    // Paiement total (dernier colonne)
                                       -1);
                    break;  // Sortir du while interne
                }
            }
        }
    }

    fclose(file_reservation);
    fclose(file_parking);

    if (!cin_found) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "CIN invalide ou inexistant.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }


}

void
on_calculernouha_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeviewpaiement");
    GtkWidget *label_total_paiement = lookup_widget(GTK_WIDGET(button), "prixnouha");
    
    // Récupérer les entrées de mois et d'année
    GtkWidget *entry_mois = lookup_widget(GTK_WIDGET(button), "moisavance");
    GtkWidget *entry_annee = lookup_widget(GTK_WIDGET(button), "anneeavance");
    
    const char *mois_str = gtk_entry_get_text(GTK_ENTRY(entry_mois));
    const char *annee_str = gtk_entry_get_text(GTK_ENTRY(entry_annee));

    int mois = atoi(mois_str);  // Convertir le mois en entier
    int annee = atoi(annee_str); // Convertir l'année en entier

    // Initialiser la somme des paiements
    float total_paiement = 0.0;

    // Récupérer le modèle du TreeView
    GtkListStore *liststore = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    if (!liststore) {
        g_print("Erreur : Le modèle du TreeView n'est pas initialisé.\n");
        return;
    }

    GtkTreeIter iter;
    gboolean valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(liststore), &iter);
    
    // Parcourir le GtkListStore et calculer la somme des paiements pour le mois et l'année donnés
    while (valid) {
        int jour, mois_item, annee_item;
        float paiement;

        // Récupérer les valeurs de la ligne
        gtk_tree_model_get(GTK_TREE_MODEL(liststore), &iter,
                           1, &jour,
                           2, &mois_item,
                           3, &annee_item,
                           7, &paiement,
                           -1);

        // Si le mois et l'année correspondent, ajouter au total
        if (mois == mois_item && annee == annee_item) {
            total_paiement += paiement;
        }

        // Passer à la ligne suivante
        valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(liststore), &iter);
 }

    // Mettre à jour le label avec la somme des paiements
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "Total Paiement: %.2f TND", total_paiement);
    gtk_label_set_text(GTK_LABEL(label_total_paiement), buffer);
}


void
on_affichertous_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *treeview9, *label_status;
    const char *filename = "citoyens.txt";

    // Récupération du TreeView et du label
    treeview9 = lookup_widget(GTK_WIDGET(button), "treeview1nouha");
    label_status = lookup_widget(GTK_WIDGET(button), "label652nouha");

    if (!treeview9 || !label_status) {
        g_print("Erreur : Widgets non trouvés.\n");
        return;
    }

    // Réinitialisation du TreeView
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview9)));
    if (!store) {
        store = gtk_list_store_new(15,  
            G_TYPE_STRING,  // CIN
            G_TYPE_STRING,  // Nom complet
            G_TYPE_STRING,  // Email
            G_TYPE_STRING,  // Numéro de téléphone
            G_TYPE_STRING,  // ID
            G_TYPE_STRING,  // Région
            G_TYPE_STRING,  // Marque voiture
            G_TYPE_STRING,  // Matricule voiture
            G_TYPE_STRING,  // Méthode de paiement
            G_TYPE_INT,     // Genre
            G_TYPE_INT,     // Jour
            G_TYPE_INT,     // Mois
            G_TYPE_INT,     // Année
            G_TYPE_INT,     // Notification email
            G_TYPE_INT);    // Notification SMS
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview9), GTK_TREE_MODEL(store));
        g_object_unref(store);     
    }
    gtk_list_store_clear(store);

    // Lecture du fichier
    FILE *file = fopen(filename, "r");
    if (file) {
        Profilecitoyen temp;
        char line[512];

        while (fgets(line, sizeof(line), file)) {
            if (sscanf(line, "%s %s %s %s %s %s %s %s %s %d %d %d %d %d %d\n",
                       temp.cin, temp.nomComplet, temp.email, temp.numeroTelephone, temp.id, 
                       temp.region, temp.marqueVoiture, temp.matriculeVoiture, temp.methodePaiement,
                       &temp.genre, &temp.jour, &temp.mois, &temp.annee, 
                       &temp.recevoirNotification[0], &temp.recevoirNotification[1]) == 15) {
                afficher_service_dans_treeview(temp, GTK_TREE_VIEW(treeview9));
            }
        }
        fclose(file);

        gtk_label_set_text(GTK_LABEL(label_status), "Tous les citoyens ont été affichés.");
    } else {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Impossible d'ouvrir le fichier.");
    }

}


