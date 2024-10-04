#include <stdio.h>
#include <string.h>

typedef struct {
    int day;
    int month;
    int year;
} date;

typedef struct {
    char nom[100];
    char prenom[100];
    char tel[11];
    int age; 
    char status[100]; /* "validé", "reporté", "annulé", "traité" */
    char reference[100];
    date reservation_date;
} reservation;

reservation r[100];
int reservation_count = 0;

void afficherMenu();
void ajouterReservation();
void modifierReservation();
void supprimerReservation();
void afficherReservation();
void rechercheReservation();
void defaultReservations();
void generateReference(char *ref);
void rechercheParReference();
void rechercheParNom();
void rechercheParDate();
void afficherDetailsReservation(int index);
void triReservations();
void statistiques();


int main() {
    int x = 0;

    defaultReservations(); 

    do {
    	here:
        afficherMenu();
        scanf("%d", &x);
    } while (x < 1 || x > 7);

    switch (x) {
        case 1:
            ajouterReservation();
            goto here;
            break;
        case 2:
            modifierReservation();
            goto here;
            break;
        case 3:
            supprimerReservation();
            goto here;
            break;
        case 4:
            afficherReservation();
            goto here;
            break;
        case 5:
            triReservations();
            goto here;
            break;
        case 6:
            rechercheReservation();
            goto here;
            break;
        case 7:
            statistiques();
            goto here;
            break;
        default:
            printf("Option invalide!\n");
            goto here;
    }

    return 0;
}

void afficherMenu() {
    printf("*********************************************************\n");
    printf("*\t1. Ajouter une reservation. \t\t\t\t\t\t*\n");
    printf("*\t2. Modifier une reservation. \t\t\t\t\t\t*\n");
    printf("*\t3. Supprimer une reservation. \t\t\t\t\t\t*\n");
    printf("*\t4. Afficher les details d'une reservation. \t\t\t*\n");
    printf("*\t5. Tri des reservations. \t\t\t\t\t\t\t*\n");
    printf("*\t6. Recherche des reservations. \t\t\t\t\t\t*\n");
    printf("*\t7. Statistiques. \t\t\t\t\t\t\t\t\t*\n");
    printf("*********************************************************\n");
    printf("\tChoisissez une option:\n");
}

void ajouterReservation() {
    printf("Nom : ");
    scanf("%s", r[reservation_count].nom);
    
    printf("Prénom : ");
    scanf("%s", r[reservation_count].prenom);
    
    printf("Téléphone : ");
    scanf("%s", r[reservation_count].tel);
    
    printf("Âge : ");
    scanf("%d", &r[reservation_count].age);
    
    printf("Statut (validé/reporté/annulé/traité) : ");
    scanf("%s", r[reservation_count].status);
    
    printf("Date (dd-mm-yyyy)\n");
    printf("Jour : ");
    scanf("%d", &r[reservation_count].reservation_date.day);
    printf("Mois : ");
    scanf("%d", &r[reservation_count].reservation_date.month);
    printf("Année : ");
    scanf("%d", &r[reservation_count].reservation_date.year);

    
    generateReference(r[reservation_count].reference);
    printf("Réservation ajoutée avec succès!\n");
    printf("Référence: %s\n", r[reservation_count].reference);
    
    reservation_count++; 
}

void modifierReservation() {
    char ref[100];
    int found = -1;
    int i = 0 ;

    printf("Entrez la référence de la réservation à modifier: ");
    scanf("%s", ref);

    for(i = 0; i < reservation_count; i++) {
        if (strcmp(r[i].reference, ref) == 0) {
            found = i;
            break;
        }
    }
    if (found != -1) {
        printf("Réservation trouvée. Que voulez-vous modifier?\n");
        printf("1. Nom\n2. Prénom\n3. Téléphone\n4. Âge\n5. Statut\n6. Date\n");
        int x;
        scanf("%d", &x);

        switch (x) {
            case 1:
                printf("Entrez le nouveau nom: ");
                scanf("%s", r[found].nom);
                break;
            case 2:
                printf("Entrez le nouveau prénom: ");
                scanf("%s", r[found].prenom);
                break;
            case 3:
                printf("Entrez le nouveau téléphone: ");
                scanf("%s", r[found].tel);
                break;
            case 4:
                printf("Entrez le nouvel âge: ");
                scanf("%d", &r[found].age);
                break;
            case 5:
                printf("Entrez le nouveau statut (validé, reporté, annulé, traité): ");
                scanf("%s", r[found].status);
                break;
            case 6:
                printf("Entrez la nouvelle date (dd-mm-yyyy)\n");
                printf("Jour: ");
                scanf("%d", &r[found].reservation_date.day);
                printf("Mois: ");
                scanf("%d", &r[found].reservation_date.month);
                printf("Année: ");
                scanf("%d", &r[found].reservation_date.year);
                break;
            default:
                printf("Choix invalide.\n");
                return;
        }

        printf("Modification réussie!\n");

    } else {
        printf("Référence introuvable!\n");
    }
}

void supprimerReservation() {
    char ref[100];
    int found = -1;
    int i = 0;

    printf("Entrez la référence de la réservation à supprimer: ");
    scanf("%s", ref);

    for (i = 0; i < reservation_count; i++) {
        if (strcmp(r[i].reference, ref) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        for ( i = found; i < reservation_count - 1; i++) {
            r[i] = r[i + 1];
        }

        reservation_count--; 

        printf("Réservation avec référence %s a été supprimée.\n", ref);
    } else {
        printf("Référence introuvable!\n");
    }
}

void afficherReservation() {
    char ref[100];
    int found = -1;
    int i = 0;

    printf("Entrez la référence de la réservation à afficher: ");
    scanf("%s", ref);
    for ( i = 0; i < reservation_count; i++) {
        if (strcmp(r[i].reference, ref) == 0) {
            found = i;
            break;
        }
    }
    if (found != -1) {
        printf("\n--- Détails de la réservation ---\n");
        printf("Référence: %s\n", r[found].reference);
        printf("Nom: %s\n", r[found].nom);
        printf("Prénom: %s\n", r[found].prenom);
        printf("Téléphone: %s\n", r[found].tel);
        printf("Âge: %d\n", r[found].age);
        printf("Statut: %s\n", r[found].status);
        printf("Date: %02d-%02d-%d\n", r[found].reservation_date.day, r[found].reservation_date.month, r[found].reservation_date.year);
    } else {
        printf("Réservation avec la référence '%s' introuvable!\n", ref);
    }
}

void rechercheReservation() {
    int x;
    printf("Choisissez un critère de recherche:\n");
    printf("1. Par Référence\n");
    printf("2. Par Nom\n");
    printf("3. Par Date\n");
    scanf("%d", &x);

    switch (x) {
        case 1:
            rechercheParReference();
            break;
        case 2:
            rechercheParNom();
            break;
        case 3:
            rechercheParDate();
            break;
        default:
            printf("Choix invalide.\n");
    }
}

void rechercheParReference() {
    char ref[100];
    int found = -1;
    int i = 0;

    printf("Entrez la référence de la réservation: ");
    scanf("%s", ref);

    for ( i = 0; i < reservation_count; i++) {
        if (strcmp(r[i].reference, ref) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        afficherDetailsReservation(found);
    } else {
        printf("Réservation avec la référence %s introuvable.\n", ref);
    }
}

void rechercheParNom() {
    char nom[100];
    int found = -1;
    int i = 0;

    printf("Entrez le nom de la réservation: ");
    scanf("%s", nom);

    for (i = 0; i < reservation_count; i++) {
        if (strcmp(r[i].nom, nom) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        afficherDetailsReservation(found);
    } else {
        printf("Réservation au nom de %s introuvable.\n", nom);
    }
}

void rechercheParDate() {
    int day, month, year;
    int found = -1;
    int i = 0;

    printf("Entrez la date de réservation (dd mm yyyy): ");
    scanf("%d %d %d", &day, &month, &year);

    for (i = 0; i < reservation_count; i++) {
        if (r[i].reservation_date.day == day && 
            r[i].reservation_date.month == month && 
            r[i].reservation_date.year == year) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        afficherDetailsReservation(found);
    } else {
        printf("Aucune réservation trouvée pour la date %02d-%02d-%d.\n", day, month, year);
    }
}

void afficherDetailsReservation(int index) {
    printf("\nDétails de la réservation:\n");
    printf("Référence: %s\n", r[index].reference);
    printf("Nom: %s\n", r[index].nom);
    printf("Prénom: %s\n", r[index].prenom);
    printf("Téléphone: %s\n", r[index].tel);
    printf("Âge: %d\n", r[index].age);
    printf("Statut: %s\n", r[index].status);
    printf("Date: %02d-%02d-%d\n", r[index].reservation_date.day, r[index].reservation_date.month, r[index].reservation_date.year);
}

void defaultReservations() {
	int i = 0;
    for (i = 0; i < 10; i++) {
        sprintf(r[i].nom, "Nom%d", i + 1);
        sprintf(r[i].prenom, "Prenom%d", i + 1);
        sprintf(r[i].tel, "06%d", i + 100000000);
        r[i].age = 20 + i;
        sprintf(r[i].status, "validé");
        r[i].reservation_date.day = i + 1;
        r[i].reservation_date.month = 10;
        r[i].reservation_date.year = 2024;
        generateReference(r[i].reference);
    }

    reservation_count = 10;
}

void generateReference(char *ref) {
    sprintf(ref, "REF%d", reservation_count + 1);
}

void triReservations(){
    
}
void statistiques(){
    
}