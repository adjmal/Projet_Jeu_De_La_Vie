// UE LAngage C - DM 1- 2017
// Numero étudiant :36006038
// Nom :BOURHANE
// Prenom :Adjmal
// Filiere :L2 informatique

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// *******************************************************
// Representation des cellules

// Type enumere pour representer l'etat d'une cellule


typedef enum etatCellule {actif, inactif} TEtat;

typedef struct cellule {
    TEtat etat;         // etat courant
    TEtat etatSuivant;  // etat au prochain cycle
} TCellule;

// *******************************************************
// Representation du monde


#define MAXLIG 50   // nombre maximum de lignes
#define MAXCOL 50   // nombre maximum de colonnes

typedef struct monde {
    int cycle;              // numero du cycle courant
    int nbLignes;           // dimensions du monde
    int nbColonnes;
    int nbCellulesActives;  // nombres de cellules actives
    TCellule grille[MAXLIG][MAXCOL]; // le tableau des cellules
} TMonde;

// *******************************************************
// On définit une variable globale qui est le monde qu'on va manipuler


TMonde LeMonde;

// ==================================================================================
// Ecrivez le code des fonctions suivantes. Les détails sont donnés en commentaire
// avant chaque fonction
// ==================================================================================


// nouvelleCellule
// Entree : rien
// Sortie : une TCellule dont l'etat et l'etat suivant sont inactif
TCellule nouvelleCellule(){
    TCellule newc={inactif,inactif};
    return newc;

}

// initMonde
// Entree : le nombre de lignes et de colonnes utilises
// Sortie : rien
// Effet de bord : la variable globale LeMonde est modifiée de la facon suivante
//     - le nombre de cycle est initialise a zero
//     - le nombre de lignes prend la valeur lig
//     - le nombre de colonnes prend la valeur col
//     - la partie du tableau grille correspondant aux nombres de lignes et de colonnes donnes est
//       remplie de nouvelles cellules inactives
//     - le nombre de cellules actives est initialise a 0
void initMonde(int lig,int col){
    int x;
    int y;
    LeMonde.cycle=0;
    LeMonde.nbLignes=lig;
    LeMonde.nbColonnes=col;
    TCellule grille[MAXLIG][MAXCOL];
    for(x=0;x<lig;x++){
        for(y=0;y<col;y++){
               LeMonde.grille[x][y]=nouvelleCellule();
            }
    }
    LeMonde.nbCellulesActives=0;
}

// nbCellulesActivesAutour
// Entree : les coordonnes x et y d'une cellule du monde
// Sortie : le nombre de cellules actives autour de la cellule situee en (x,y)
// Attention : le monde est torique, ce qui veut dire qu'un cellule situee sur un bord
//             du monde a des cellules voisines sur le bord oppose ...

int nbCellulesActivesAutour(int x, int y){
    int nbcell=0;
    int i;
    int j;
    for (i=(x-1);i<=(x+1);i++){
        for (j=(y-1);j<=(y+1); j++)
        {
            if (LeMonde.grille[(i+LeMonde.nbLignes)%LeMonde.nbLignes][(j+LeMonde.nbColonnes)%LeMonde.nbColonnes].etat ==actif)
            {
                nbcell++;
            }
        }

         }
    if (LeMonde.grille[x][y].etat==actif) {
        nbcell--;
    }
    return nbcell;
}

// activeCelluleEn
// Entree : les coordonnes x et y d'une cellule du monde
// Sortie : rien
// Effet de bord : l'etat de la cellule du monde situee en (x,y) devient actif
void activeCelluleEn(int x, int y){
            LeMonde.grille[x][y].etat = actif;
    }

// desacativeCelluleEn
// Entree : les coordonnes x et y d'une cellule du monde
// Sortie : rien
// Effet de bord : l'etat de la cellule du monde situee en (x,y) devient inactif

void desacativeCelluleEn(int x, int y){

            LeMonde.grille[x][y].etat = inactif;
    }
// activeEtatSuivantEn
// Entree : les coordonnes x et y d'une cellule du monde
// Sortie : rien
// Effet de bord : l'etat suivant de la cellule du monde situee en (x,y) devient actif

void activeEtatSuivantEn(int x, int y){

            LeMonde.grille[x][y].etatSuivant =actif;
}
// desactiveEtatSuivantEn
// Entree : les coordonnes x et y d'une cellule du monde
// Sortie : rien
// Effet de bord : l'etat suivant de la cellule du monde situee en (x,y) devient inactif

void desactiveEtatSuivantEn(int x, int y){
            LeMonde.grille[x][y].etatSuivant = inactif;
}
// passeALetatSuviant
// Entree : les coordonnes x et y d'une cellule du monde
// Sortie : rien
// Effet de bord : l'etat de la cellule situee en (x, y) prend comme valeur son etat suivant

void passeALetatSuivant(int x, int y){
             LeMonde.grille[x][y].etat= LeMonde.grille[x][y].etatSuivant;
}
// calculEtatSuivant
// Entree : rien
// Sortie : rien
// Effet ede bord : calcule l'etat suivant de toutes les cellules du monde
//                  met à jour le nombre de cellules actives du monde

void calculEtatSuivant(){
    int i;
    int j;
    for ( i=0; i<LeMonde.nbLignes;i++){
        for (j=0;j<LeMonde.nbColonnes;j++)
        {
            int nbCellulesActives = nbCellulesActivesAutour(i,j);
            if (LeMonde.grille[i][j].etat==inactif && nbCellulesActives==3)
                {
                    activeEtatSuivantEn(i,j);
                }

            if ((LeMonde.grille[i][j].etat==actif) && (nbCellulesActives>=2) && (nbCellulesActives<=3) )
                {
                    activeEtatSuivantEn(i,j);
                }
            if (nbCellulesActives>3 || nbCellulesActives<2){
               desactiveEtatSuivantEn(i,j);

            }
    }

}
}
// passeAuCycleSuivant
// Entree : rien
// Sortie : rien
// Effet de bord : toutes les cellules du monde passe dans leur etat suivant
void passeAuCycleSuivant(){
    int x,y;
    for(x=0;x<LeMonde.nbLignes;x++){
            for(y=0;y<LeMonde.nbColonnes;y++){
                   passeALetatSuivant(x,y);
}
    }
}
// afficheMonde
// Entree : rien
// Sortie : rien
// Effet de bord : le nombre de cycle, le nombre de cellule actives puis
//                 affiche les nblignes et nbColonnes de la grille du monde a l'ecran
//                 en affichant un espace pour chaque cellule inactive
//                 et une * pour chaque cellule active

void afficheMonde(){

    int i;
    int j;

    printf("******************************\n");
    printf(("       JEUX DE LA VIE        \n"));
    printf("******************************\n\n\n");

    printf("\n cycle : %d \n", LeMonde.cycle);
    LeMonde.nbCellulesActives = 0;


    for(i=0; i< LeMonde.nbColonnes; i++ ){
        printf("\n");
        for(j=0; j<LeMonde.nbLignes; j++){

                if(LeMonde.grille[j][i].etat == inactif){
                    printf(" ");

               }
                else{
                    printf(" * ");
                    LeMonde.nbCellulesActives += 1;
                }}
        }
    printf("\n \n nombre de cellule active : %d \n \n", LeMonde.nbCellulesActives);;
}

// activeAleatoirementNbCellules
// Entree : le nombre nb de cellule a rendre active dans LeMonde
// Sortie : rien
// Effet de bord : affecte aleatoirement l'etat d'exactement nb cellules du monde a actif

void activeAleatoirementNbCellules(int nb){
    srand(time(NULL));
    int i=0;
        while(i<nb){
        int ax = rand()%LeMonde.nbLignes;
        int ay = rand()%LeMonde.nbColonnes;
        if(LeMonde.grille[ax][ay].etat == actif){
            i+= actif;
        }
        else{
            LeMonde.grille[ax][ay].etat = actif;
            i+= 1;
        }
        }

}
//pour la ressaisie des information
void buffer(void)
{
    int c;
    while((c=getchar()) != EOF && c != '\n');

}

// main
// Demande la saisie des dimensions du monde a utiliser (sans depasser les valeurs maximum)
// Initialise le monde
// Demande combien de cellules il faut activer et les actives aleatoirement
// Demande le nombre de cycles qu'on veut calculer
// Effectue le nombre de cycles demandes. Un cycle consiste a :
//        - afficher le monde
//        - calculer l'etat du monde au cycle suivant
//        - faire passer toutes les cellules dans leur etat suivant

int main(){
    printf("******************************\n");
    printf(("       JEUX DE LA VIE        \n"));
    printf("******************************\n\n\n");
    int lig;
    int col;
    int nb;
    int v1 =1;
    int v2 =1;
    int v4 =1;
    int nbcycle=0;
    do{ //vérification du nombre de ligne et de colonne
                printf("Veuillez donnez le nombre de ligne (inferieur a 50):");
                v1=scanf("%d",&lig);
                buffer();
                printf("Veuillez donnez le nombre de colonne (inferieur a 50):");
                v2=scanf("%d",&col);
                buffer();
            if ((lig>MAXLIG) || (col>MAXCOL) || (v1==0)||(v2==0))
                {
                    printf("Donner uniquement des nombres (inferieur a 50) pour le nombre de ligne et de colonne\n");
                }
    }while(v1!=1 || v2!= 1 || (lig>MAXLIG) || (col>MAXCOL) );

    initMonde(lig,col);
    int v3 =1;
    do{ //vérification nombre de cellule
        printf("Combien de cellule souhaitez vous activer?(inferieur a %d):",lig*col);
        v3=scanf("%d",&nb);
        buffer();
            if(v3==0 || nb>lig*col){
                printf("veuillez resaisir un nombre inferieur a %d:\n",lig*col);
            }
    }while(v3 != 1 || nb>lig*col );

    activeAleatoirementNbCellules(nb);

    do{ //vérification nombre de cycle
            printf("Combien de cycle souhaitez vous calculer:");
            v4 = scanf("%d",&nbcycle);
            buffer();
            if(v4==0 || nbcycle<=0){
                printf("saisissez au moins un cycle\n");
            }

                        }while(v4 !=1 || nbcycle<=0 );
        printf("\n\n");

    for (LeMonde.cycle=0;LeMonde.cycle<nbcycle+1;LeMonde.cycle++){
        system("cls");
        afficheMonde();
        calculEtatSuivant();
        passeAuCycleSuivant();

    }
    return 0;
}














