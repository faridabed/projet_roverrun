#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "final.h"

int main() {
    t_map map = createMapFromFile("..\\maps\\example1.map");
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);

    findBase(map, 2, 2, 0);

/*TEST FONCTION TROUVERCOUTMINFEUILLE

    t_nnode * node1 = NULL;
    node1 = malloc(sizeof(t_nnode));
    node1->cost = 3;
    node1->depth = 5;
    node1->nb_sons = 0;
    t_nnode* comp = NULL;
    comp = trouverCoutMinFeuille(node1);
    printf("\n\n%d coord x : %d y : %d\n\n", comp->cost, comp->loca.pos.x, comp->loca.pos.y);
    findBase(map, comp->loca.pos.x, comp->loca.pos.y, 0);
*/

    /*SIMULATION DE TRANSLATION

      t_localisation pos;
      pos = loc_init(3, 4, NORTH);
      pos = translate(pos, F_30);
      printf("x : %d y : %d ori : %d", pos.pos.x, pos.pos.y, pos.ori);

     //GENARATION ALEATOIRE DE MOUVEMENTS

      t_move* moves = NULL;
      moves = getRandomMoves(9);
      for (int i = 0; i < 9; ++i) {
          printf("%d  ", moves[i]);
      }

    /* RECHERCHE DE LA MEILLEURE FEUILLE
     t_nnode* bestleaf = NULL;
     // bestleaf = malloc(sizeof(t_nnode));
     // bestleaf->cost = 100000;
     // bestLeaf(&bestleaf, tree, 4);
     //printf("%d\n", bestleaf->cost);

      free(bestleaf);
      bestleaf = NULL;

    // int t[3] = {1,2,3};
    /* t_stack* stck = NULL;
     stck = createStack(3);
      for (int i = 0; i < 3; ++i) {
          push(stck, t[i]);
      }

      printf("nbelts =  %d\n", stck->nbElts);
      printf("top val est %d \n", top(stck));
      printf("nbelts =  %d\n", stck->nbElts); */

    //t_nnodetest* test = NULL;
    //test = TESTcreateTree(0, t);

    // tree = findBase(map);

    /*
     * // Test Sortie de la carte
     int x_max = 5;
     int y_max = 5;

     t_position positions[] = {
         {2, 2},  // Position valide
         {0, 0},  // Coin supérieur gauche (valide)
         {4, 4},  // Coin inférieur droit (valide)
         {5, 3},  // Hors limites (x dépasse x_max)
         {-1, 2}, // Hors limites (x négatif)
         {3, 6},  // Hors limites (y dépasse y_max)
         {3, -1}  // Hors limites (y négatif)
     };

     int n_positions = sizeof(positions) / sizeof(positions[0]);

     printf("Test de sortie de la carte :\n");
     for (int i = 0; i < n_positions; i++) {
         t_position pos = positions[i];
         int valid = isValidLocalisation(pos, x_max, y_max);
         printf("Position (%d, %d) : %s\n", pos.x, pos.y, valid ? "Valide" : "Invalide");
     }*/

    /*//TEST PASSAGE SUR CREVASSE
    t_position positions[] = {
        {2, 2},  // Une position potentiellement valide
        {0, 0},  // Coin supérieur gauche (normalement valide)
        {3, 1},  // Une position qui pourrait être une crevasse
        {1, 4},  // Une autre position sur la carte
        {5, 5}   // Une position qui pourrait être hors de la carte
    };

    int n_positions = sizeof(positions) / sizeof(positions[0]);

    printf("Test de passage sur une crevasse :\n");
    for (int i = 0; i < n_positions; i++) {
        t_position pos = positions[i];

        // Vérifier si la position est dans les limites de la carte
        if (isValidLocalisation(pos, map.x_max, map.y_max)) {
            // Identifier le type de terrain avec getSoils
            int soil = map.soils[pos.y][pos.x];

            // Afficher le résultat
            printf("Position (%d, %d) : ", pos.x, pos.y);
            if (soil == 4) {
                printf("Crevasse (danger !)\n");
            } else {
                printf("Terrain sur (type %d)\n", soil);
            }
        } else {
            printf("Position (%d, %d) : Hors des limites de la carte\n", pos.x, pos.y);
        }
    }*/
    return 0;
}
