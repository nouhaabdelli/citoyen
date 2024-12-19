#ifndef citoyen_H
#define citoyen_H
#include <gtk/gtk.h>
// Définition de la structure ProfilCitoyen
typedef struct {
     char cin[20];               // CIN (Carte d'Identité Nationale)
     char nomComplet[100]; 
     char email[100];
     char numeroTelephone[20];
     char id[200];
    char region[50];
    char marqueVoiture[50];
    char matriculeVoiture[50];
    char methodePaiement[50];
     int genre;
    int jour;
    int mois;
    int annee; 
    int recevoirNotification[2];// recevoirNotification[0] = email, [1] = SMS

} Profilecitoyen;

// Structure pour stocker une réservation
typedef struct {
    int id_citoyen;
    int id_reservation;
    int id_parking;
    int jour;
    int mois;
    int annee;
} Reservation;

// Structure pour stocker les informations de parking
typedef struct {
    int id_parking;
    float prix_par_jour;
} Parking;


// Prototypes des fonctions
int verifierCIN(const char *cin);
int verifierNumeroTelephone(const char *numeroTelephone);
int ajouterProfil(const char *nomFichier, Profilecitoyen profil);
int modifierProfil(const char *nomFichier, const char *cin, Profilecitoyen nouvProfil);
int supprimerProfil(char *nomFichier, const char *cin);
int chercherProfil(char *nomFichier, const char *cin, Profilecitoyen* profil) ;
void afficher_service_dans_treeview(Profilecitoyen service, GtkTreeView *treeview) ;


/// fonctions supplementaires:
void creerFichierReservation();
void creerFichierParking();
void calculerFacture(int id_citoyen, int mois, int annee) ;

#endif















