#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// structure etudiant
typedef struct Etudiant Etudiant;
struct Etudiant
{
    int id;
    char nom[50];
    char prenom[50];
    float moyenne;
  Etudiant* suivant;
};

// Prototypes des fonctions
void afficherMenu();
Etudiant* creerEtudiant(int id, char *nom, char *prenom, float moyenne);
void ajouterEnTete(Etudiant **etu);
void ajouterApresElement(Etudiant **etu);
void supprimerParId(Etudiant **etu);
void afficherListe(Etudiant *etu);
void afficherMoyenneGenerale(Etudiant *etu);
void supprimerDernier(Etudiant **etu);
void viderListe(Etudiant **etu);
int listeVide(Etudiant *etu);


int main() {
    Etudiant *etu = NULL;
    int choix;
    
    do {
        afficherMenu();
        printf(" Entrer votre choix : ");
        scanf("%d", &choix);
        
        
        switch(choix) {
            case 1:
                ajouterEnTete(&etu);
                break;
            case 2:
                ajouterApresElement(&etu);
                break;
            case 3:
                supprimerParId(&etu);
                break;
            case 4:
                afficherListe(etu);
                break;
            case 5:
                afficherMoyenneGenerale(etu);
                break;
            case 6:
                supprimerDernier(&etu);
                break;
            case 7:
                viderListe(&etu);
                break;
            case 8:
                printf(" Au revoir ! \n");
                viderListe(&etu);
                break;
            default:
                printf("\n Choix invalide !\n");
        }
        
        if(choix != 8) {
            printf("\nAppuyez sur ENTREE pour continuer...");
            
        }
        
    } while(choix != 8);
    
    return 0;
}

// Afficher le menu
void afficherMenu() {
   
    printf("\n*********************************************\n");
    printf("\n*       GESTIONNAIRE D'ÉTUDIANTS            *\n");
    printf("\n*********************************************\n");
    printf("\n1. Ajouter un étudiant en tête\n");
    printf("  2.  Ajouter un étudiant après un élément\n");
    printf("  3.  Supprimer un étudiant par ID\n");
    printf("  4.  Afficher la liste des étudiants\n");
    printf("  5.  Afficher la moyenne générale\n");
    printf("  6.  Supprimer le dernier élément\n");
    printf("  7.  Vider la liste complète\n");
    printf("  8.  Quitter\n");
    printf("\n***********************************************\n");
}

// Créer un nouvel étudiant
Etudiant* creerEtudiant(int id, char *nom, char *prenom, float moyenne) {
    Etudiant *nouveau = (Etudiant*)malloc(sizeof(Etudiant));
    
    if(nouveau == NULL) {
        printf(" Erreur d'allocation mémoire !\n");
        return NULL;
    }
    
    nouveau->id = id;
    strcpy(nouveau->nom, nom);
    strcpy(nouveau->prenom, prenom);
    nouveau->moyenne = moyenne;
    nouveau->suivant = NULL;
    
    return nouveau;
}

// Vérifier si la liste est vide
int listeVide(Etudiant *etu) {
    return (etu == NULL);
}

// 1. Ajouter un étudiant en tête
void ajouterEnTete(Etudiant **etu) {
    int id;
    char nom[50], prenom[50];
    float moyenne;
    
    printf("\n AJOUTER UN ÉTUDIANT EN TÊTE \n");
    printf("ID : ");
    scanf("%d", &id);
    getchar();
    
    printf("Nom : ");
    scanf("%[^\n]",nom);
    
    printf("Prénom : ");
   scanf("%[^\n]",prenom);
    
    printf("Moyenne : ");
    scanf("%f", &moyenne);
    
    Etudiant *nouveau = creerEtudiant(id, nom, prenom, moyenne);
    
    if(nouveau != NULL ) {
        nouveau->suivant = *etu;
        *etu = nouveau;
        printf("\n Étudiant ajouté en tête avec succès !\n");
    }
}


// 2. Ajouter un étudiant après un élément donné
void ajouterApresElement(Etudiant **etu) {
    if(listeVide(*etu)) {
        printf("\n La liste est vide ! Ajoutez d'abord un étudiant.\n");
        return ;
    }
    
    int idRecherche, id;
    char nom[50], prenom[50];
    float moyenne;
    
    printf("\n AJOUTER APRÈS UN ÉLÉMENT \n");
    afficherListe(*etu);
    
    printf("\nID de l'étudiant après lequel ajouter : ");
    scanf("%d", &idRecherche);
    
    
    Etudiant *courant = *etu;
    
    // Rechercher l'étudiant
    while(courant != NULL && courant->id != idRecherche) {
        courant = courant->suivant;
    }
    
    if(courant == NULL) {
        printf("\n Étudiant avec ID %d introuvable !\n", idRecherche);
        return;
    }
    
    printf("\n--- Nouvel étudiant ---\n");
    printf("ID : ");
    scanf("%d", &id);
    getchar();
    
    printf("Nom : ");
    scanf("%[^\n]",nom);
    
    printf("Prénom : ");
    scanf("%[^\n]",prenom);
    
    printf("Moyenne : ");
    scanf("%f", &moyenne);
    
    Etudiant *nouveau = creerEtudiant(id, nom, prenom, moyenne);
    
    if(nouveau != NULL) {
        nouveau->suivant = courant->suivant;
        courant->suivant = nouveau;
        printf("\n Étudiant ajouté après ID %d avec succès !\n", idRecherche);
    }
}


// 3. Supprimer un étudiant par ID
void supprimerParId(Etudiant **etu) {
    if(listeVide(*etu)) {
        printf("\n La liste est vide !\n");
        return;
    }
    
    int idSuppr;
    
    printf("\n SUPPRIMER UN ÉTUDIANT \n");
    afficherListe(*etu);
    
    printf("\nID de l'étudiant à supprimer : ");
    scanf("%d", &idSuppr);
    
    Etudiant *courant = *etu;
    Etudiant *precedent = NULL;
    
    // Rechercher l'étudiant
    while(courant != NULL && courant->id != idSuppr) {
        precedent = courant;
        courant = courant->suivant;
    }
    
    if(courant == NULL) {
        printf("\n Étudiant avec ID %d introuvable !\n", idSuppr);
        return ;
    }
    
    // Suppression en tête
    if(precedent == NULL) {
        *etu = courant->suivant;
    } else {
        precedent->suivant = courant->suivant;
    }
    
    printf("\n Étudiant %s %s (ID: %d) supprimé !\n", 
           courant->prenom, courant->nom, courant->id);
    free(courant);
}

// 4. Afficher la liste des étudiants
void afficherListe(Etudiant *etu) {
    if(listeVide(etu)) {
        printf("\n La liste est vide !\n");
        return;
    }
    
    printf("************************************************************\n");
    printf("*                   LISTE DES ÉTUDIANTS                    *\n");
    printf("************************************************************\n");
    printf("* ID  *      NOM     *     PRÉNOM     *    MOYENNE         *\n");
    printf("************************************************************\n");
    
    Etudiant *courant = etu;
    
    while(courant != NULL) {
        printf("* %-3d * %-15s *    %-15s  *    %.2f       *\n",
               courant->id, courant->nom, courant->prenom, courant->moyenne);
        courant = courant->suivant;
    }
    
    printf("************************************************************\n");
}

// 5. Afficher la moyenne générale
void afficherMoyenneGenerale(Etudiant *etu) {
    if(listeVide(etu)) {
        printf("\n  La liste est vide !\n");
        return;
    }
    
    float somme = 0;
    int compteur = 0;
    Etudiant *courant = etu;
    
    while(courant != NULL) {
        somme += courant->moyenne;
        compteur++;
        courant = courant->suivant;
    }
    
    float moyenneGenerale = somme / compteur;
    
    printf("\n****************************************\n");
    printf("\n*           STATISTIQUES               *\n");
    printf("\n****************************************\n");
    printf("\n* Nombre d'étudiants : %d              *\n", compteur);
    printf("\n* Moyenne générale   : %.2f            *\n", moyenneGenerale);
    printf("******************************************\n");
}

// 6. Supprimer le dernier élément
void supprimerDernier(Etudiant **etu) {
    if(listeVide(*etu)) {
        printf("\n  La liste est vide !\n");
        return;
    }
    
    // Si un seul élément
    if((*etu)->suivant == NULL) {
        printf("\n Dernier étudiant %s %s supprimé !\n", 
               (*etu)->prenom, (*etu)->nom);
        free(*etu);
        *etu = NULL;
        return;
    }
    
    Etudiant *courant = *etu;
    Etudiant *precedent = NULL;
    
    // Aller jusqu'à l'avant-dernier
    while(courant->suivant != NULL) {
        precedent = courant;
        courant = courant->suivant;
    }
    
    precedent->suivant = NULL;
    printf("\n Dernier étudiant %s %s supprimé !\n", 
           courant->prenom, courant->nom);
    free(courant);
}

// 7. Vider la liste complète
void viderListe(Etudiant **etu) {
    if(listeVide(*etu)) {
        printf("\n La liste est déjà vide !\n");
        return;
    }
    
    Etudiant *courant = *etu;
    Etudiant *suivant;
    int compteur = 0;
    
    while(courant != NULL) {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;
        compteur++;
    }
    
    *etu = NULL;
    printf("\n Liste vidée ! %d étudiant(s) supprimé(s).\n", compteur);
}