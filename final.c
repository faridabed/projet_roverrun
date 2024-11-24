#include "tree.h"
#include "final.h"
#include <stdlib.h>
#include <stdio.h>
#include "loc.h"

void findBase(t_map map, int x, int y, t_orientation orientation){
    t_nnode* tree = NULL;
    int isBase = 0;
    int regverif = 0;

    do {
        tree = creerarbre(0, map, x, y, orientation, 9, 6, regverif);
        t_nnode *bestleaf = NULL;

        bestleaf = trouverCoutMinFeuille(tree);

        if (bestleaf != NULL) {
            printf("\n\n%d coord x : %d y : %d\n\n", bestleaf->cost, bestleaf->loca.pos.x, bestleaf->loca.pos.y);
            dispMvmt(bestleaf);
        } else {
            printf("\n\nAucune feuille valide trouvée.\n\n");
        }

        //dispMvmt(bestleaf);

        if (bestleaf != NULL) {
            bestleaf->base = isBaseFound(bestleaf, map);
            if (bestleaf->cost == 0 || bestleaf->base == 1) {
                isBase = 1;
            }
        }

        x = bestleaf->loca.pos.x;
        y = bestleaf->loca.pos.y;
        orientation = bestleaf->loca.ori;
        regverif = bestleaf->regcount;

    }while(isBase == 0);

    printf("Base Atteinte \n");

}
