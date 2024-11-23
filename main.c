#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "final.h"


int main() {
    t_map map = createMapFromFile("..\\maps\\training.map");
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

    /*TEST/
    /*
    t_nnode * node1 = NULL;
    node1 = malloc(sizeof(t_nnode));
    node1->cost = 3;
    node1->depth = 5;
    node1->nb_sons = 0;
    t_nnode* comp = NULL;
    comp = findMinCostLeaf(node1);
    printf("\n\n%d coord x : %d y : %d\n\n", comp->cost, comp->loca.pos.x, comp->loca.pos.y);
    findBase(map, comp->loca.pos.x, comp->loca.pos.y, 0);
*/
    /*  t_nnode * node1 = NULL;
      node1 = malloc(sizeof(t_nnode));
      node1->cost = 3;
      node1->depth = 5;
      node1->nb_sons = 0;

      t_nnode* comp = NULL;
      comp = findMinCostLeaf(node1);
      printf("\n\n%d coord x : %d y : %d\n\n", comp->cost, comp->loca.pos.x, comp->loca.pos.y);

     // tree = createTree(0, map, 0, 0, NORTH, 9, 6);
     /* t_localisation pos;
      pos = loc_init(3, 4, NORTH);
      pos = translate(pos, F_30);
      printf("x : %d y : %d ori : %d", pos.pos.x, pos.pos.y, pos.ori);

      t_move* moves = NULL;
      moves = getRandomMoves(9);
      for (int i = 0; i < 9; ++i) {
          printf("%d  ", moves[i]);
      }

    /*  t_nnode* bestleaf = NULL;
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

    /* int idx = 2;
     int local[2];
     int j = 0;
     for (int i = 0; i < 3; i++) {
         if(i == idx){
             continue;
         }
         else {
             local[j] = t[i];
             printf("it %d j = %d val = %d\n", i, j, local[j]);
             j++;
         }
     } */

    // tree = findBase(map);
    return 0;
}
