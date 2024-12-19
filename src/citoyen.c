#include "citoyen.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Fonction pour vérifier si un CIN est valide
int verifierCIN(const char *cin) {
    if (strlen(cin) != 8){
        return 0; // Longueur invalide
    }
    for (int i = 0; i < 8; i++) {
        if (!isdigit(cin[i])) {
            return 0; // Caractère non numérique détecté
        }
    }
    return 1; 
}

// Fonction pour valider un numéro de téléphone (8 chiffres)
int verifierNumeroTelephone(const char *numeroTelephone) {
    if (strlen(numeroTelephone) != 8) {
        return 0; // Longueur invalide
    }
    for (int i = 0; i < 8; i++) {
        if (!isdigit(numeroTelephone[i])) {
            return 0; // Caractère non numérique détecté
        }
    }
    return 1; // Numéro de téléphone valide
}

// Ajouter un profil dans le fichier
int ajouterProfil(const char *nomFichier, Profilecitoyen c) {
    FILE *fichier = fopen(nomFichier, "a"); // Ouvrir le fichier en mode append
    if (fichier != NULL) {
        // Écrire les données dans le fichier, y compris la méthode de paiement
        fprintf(fichier, "%s %s %s %s %s %s %s %s %s %d %02d %02d %04d %d %d\n",c.cin, c.nomComplet, c.email, c.numeroTelephone, 
            c.id, c.region, c.marqueVoiture, c.matriculeVoiture,
            c.methodePaiement, c.genre,
             c.jour,c.mois,c.annee, 
            c.recevoirNotification[0],c.recevoirNotification[1] );            
                
        fclose(fichier);
        return 1; // Profil ajouté avec succès
    } else {
        printf("Erreur d'ouverture du fichier\n");
        return 0; // Échec de l'ajout
    }
}

int modifierProfil (const char *filename, const char *cin , Profilecitoyen nouv) {
    int tr = 0;
  Profilecitoyen c;  
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erreur d'ouverture du fichier d'origine");
        return 0;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        printf("Erreur d'ouverture du fichier temporaire");
        fclose(file);
        return 0;
    }

    // Lecture et écriture ligne par ligne
     while (fscanf(file, "%s %s %s %s %s %s %s %s %s %d %d %d %d %d %d\n",c.cin, c.nomComplet, c.email, c.numeroTelephone, 
            c.id, c.region,  c.marqueVoiture, c.matriculeVoiture,c.methodePaiement,&c.genre,
             &c.jour,&c.mois,&c.annee, 
            &c.recevoirNotification[0], &c.recevoirNotification[1] ) != EOF) {
        // Comparaison des ID
        if (strcmp(c.cin, cin) == 0) {
            // Écrit les nouvelles données si l'ID correspond
            fprintf(tempFile, "%s %s %s %s %s %s %s %s %s %d %d %d %d %d %d\n",
     nouv.cin, nouv.nomComplet, nouv.email, nouv.numeroTelephone, 
      nouv.id, nouv.region, nouv.marqueVoiture, nouv.matriculeVoiture,nouv.methodePaiement,
       nouv.genre,             
       nouv.jour,nouv.mois,nouv.annee,
        nouv.recevoirNotification[0],nouv.recevoirNotification[1]);
            tr = 1;  // Indique que la modification a réussi
        } else {
            // Écrit les données existantes si l'ID ne correspond pas
            fprintf(tempFile, "%s %s %s %s %s %s %s %s %s %d %d %02d %04d %d %d\n",c.cin, c.nomComplet, c.email, c.numeroTelephone, 
            c.id, c.region,  c.marqueVoiture, c.matriculeVoiture,c.methodePaiement,c.genre,
             c.jour,c.mois,c.annee, 
           c.recevoirNotification[0], c.recevoirNotification[1] );
        }
    

    // Fermeture des fichiers
    fclose(file);
    fclose(tempFile);
 remove(filename);
     rename("temp.txt", filename);

    }

    return tr;  // Retourne 1 si modification, 0 sinon
}

int supprimerProfil(char *fichier,const char *cin) {
    FILE *file = fopen(fichier, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    

    Profilecitoyen c;
    int supprime = 1;

    while (fscanf(file, "%s %s %s %s %s %s %s %s %s %d %d %d %d %d %d\n",c.cin, c.nomComplet, c.email, c.numeroTelephone, 
   c.id, c.region, c.marqueVoiture, c.matriculeVoiture,c.methodePaiement, &c.genre,&c.jour,&c.mois,&c.annee, &c.recevoirNotification[0],
      &c.recevoirNotification[1] ) != EOF){

        if (strcmp(c.cin, cin) != 0) {
            fprintf(tempFile,"%s %s %s %s %s %s %s %s %s %d %d %d %d %d %d\n",c.cin, c.nomComplet, c.email, c.numeroTelephone, 
   c.id, c.region, c.marqueVoiture, c.matriculeVoiture,c.methodePaiement, c.genre,c.jour,c.mois,c.annee, c.recevoirNotification[0],
      c.recevoirNotification[1] );
        } else {
            supprime = 0;
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(fichier);
    rename("temp.txt", fichier);

    return supprime;
}

// Fonction pour rechercher un citoyen
int chercherProfil(char *nomFichier, const char *cin, Profilecitoyen* c) {
    FILE *file = fopen(nomFichier, "r");
    if (file == NULL) return 0;  // Retourne 0 si le fichier ne peut pas être ouvert

    while (fscanf(file, "%s %s %s %s %s %s %s %s %s %d %02d %02d %04d %01d %01d\n",c->cin, c->nomComplet, c->email, c->numeroTelephone, 
   c->id, c->region, c->marqueVoiture, c->matriculeVoiture,c->methodePaiement, &c->genre,&c->jour,&c->mois,
&c->annee, &c->recevoirNotification[0],
      &c->recevoirNotification[1] ) != EOF) {
        if (strcmp(c->cin, cin) == 0) {
            fclose(file);
            return 1;  // Retourne 1 si le profil est trouvé
        }
    }

    fclose(file);
    return 0;  // Retourne 0 si le profil n'est pas trouvé
}





/////////////////////////////
void afficher_service_dans_treeview(Profilecitoyen c, GtkTreeView *treeview) {
  

    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

     renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("CIN", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(treeview, column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom ", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(treeview, column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(treeview, column);


        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Numero de telephone", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(treeview, column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("id ", renderer,"text", 4, NULL);
        gtk_tree_view_append_column(treeview, column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Région", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(treeview, column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("MarqueVoiture ", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(treeview, column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("MatriculeVoiture", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(treeview, column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Methode de Paiement", renderer, "text", 8, NULL);
        gtk_tree_view_append_column(treeview, column);


       renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("genre", renderer, "text", 9, NULL);
        gtk_tree_view_append_column(treeview, column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("jour", renderer, "text", 10, NULL);
        gtk_tree_view_append_column(treeview, column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("mois", renderer, "text", 11, NULL);
        gtk_tree_view_append_column(treeview, column);


renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("annee ",renderer,"text", 12, NULL);
        gtk_tree_view_append_column(treeview, column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Notification1",renderer,"text", 13, NULL);
        gtk_tree_view_append_column(treeview, column);


        column = gtk_tree_view_column_new_with_attributes("Notification2",renderer,"text", 14, NULL);
        gtk_tree_view_append_column(treeview, column);

GtkListStore *creer_model_treeview() {
    GtkListStore *store = gtk_list_store_new(15,  
        G_TYPE_STRING,  // CIN
        G_TYPE_STRING,  // Nom 
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
        G_TYPE_INT);    // Recevoir notification (SMS) (entier)

    return store;}

GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));

    GtkTreeIter iter;

    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       0, c.cin,
                           1, c.nomComplet,
                           2, c.email,
                           3, c.numeroTelephone,
                           4, c.id,
                           5, c.region,
                           6, c.marqueVoiture,
                           7, c.matriculeVoiture,
                           8, c.methodePaiement,
                           9, c.genre,       // Entier pour le genre
                           10, c.jour,       // Entier pour le jour
                           11, c.mois,       // Entier pour le mois
                           12, c.annee,      // Entier pour l'année
                           13, c.recevoirNotification[0],  // Entier pour recevoir notification (email)
                           14, c.recevoirNotification[1],  // Entier pour recevoir notification (SMS)
                           -1);
}


//fonction supplem


// Fonction pour créer un fichier reservation.txt avec des délimiteurs de virgule
void creerFichierReservation() {
    FILE *fichier = fopen("reservation.txt", "w");
    if (fichier == NULL) {
        perror("Erreur lors de la création du fichier reservation.txt");
        return;
    }
    fprintf(fichier, "ID_Citoyen,ID_Reservation,ID_Parking,Jour,Mois,Annee\n");
    fprintf(fichier, "123456789,1,101,1,1,2024\n");
    fprintf(fichier, "123456789,2,102,3,1,2024\n");
    fprintf(fichier, "987654321,3,101,5,1,2024\n");
    fclose(fichier);
    printf("Fichier reservation.txt créé avec succès.\n");
}

// Fonction pour créer un fichier parking.txt avec des délimiteurs de virgule
void creerFichierParking() {
    FILE *fichier = fopen("parking.txt", "w");
    if (fichier == NULL) {
        perror("Erreur lors de la création du fichier parking.txt");
        return;
    }
    fprintf(fichier, "ID_Parking,Prix_Par_Jour\n");
    fprintf(fichier, "101,10.00\n");
    fprintf(fichier, "102,15.50\n");
    fprintf(fichier, "103,12.75\n");
    fclose(fichier);
    printf("Fichier parking.txt créé avec succès.\n");
}
// Fonction pour calculer la facture d'un citoyen pour un mois et une année donnés
void calculerFacture(int id_citoyen, int mois, int annee) {
    FILE *fichier_res = fopen("reservation.txt", "r");
    FILE *fichier_park = fopen("parking.txt", "r");

    if (fichier_res == NULL || fichier_park == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    float facture = 0.0;
    char ligne[100];
    Reservation res;
    Parking park;

    // Sauter la première ligne (en-tête) dans les fichiers
    fgets(ligne, sizeof(ligne), fichier_res);
    fgets(ligne, sizeof(ligne), fichier_park);

    printf("Recherche des réservations pour le citoyen %d, mois: %d, année: %d\n", id_citoyen, mois, annee);

    // Lire chaque réservation dans reservation.txt
    while (fgets(ligne, sizeof(ligne), fichier_res) != NULL) {
        sscanf(ligne, "%d,%d,%d,%d,%d,%d", 
               &res.id_citoyen, &res.id_reservation, &res.id_parking, 
               &res.jour, &res.mois, &res.annee);

        if (res.id_citoyen == id_citoyen && res.mois == mois && res.annee == annee) {
            printf("Réservation trouvée pour le citoyen %d, parking %d, date: %d/%d/%d\n", 
                   res.id_citoyen, res.id_parking, res.jour, res.mois, res.annee);

            // Revenir au début de parking.txt pour chaque recherche de parking
            rewind(fichier_park);
            fgets(ligne, sizeof(ligne), fichier_park);  // Ignorer l'en-tête à chaque fois

            int found = 0;
            while (fgets(ligne, sizeof(ligne), fichier_park) != NULL) {
                sscanf(ligne, "%d,%f", &park.id_parking, &park.prix_par_jour);

                if (park.id_parking == res.id_parking) {
                    printf("Prix trouvé pour le parking %d : %.2f\n", park.id_parking, park.prix_par_jour);
                    facture += park.prix_par_jour;
                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("Aucun prix trouvé pour le parking %d\n", res.id_parking);
            }
        }
    }

    fclose(fichier_res);
    fclose(fichier_park);

    printf("La facture pour le citoyen %d pour %d/%d est : %.2f\n", id_citoyen, mois, annee, facture);
}
