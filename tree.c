#include "moves.h"
#include "tree.h"
#include "loc.h"
#include "map.h"

#include <stdlib.h>
#include <stdio.h>

int isBaseFound(t_nnode* node, t_map map){
    if(isValidLocalisation(node->loca.pos, 5, 6) == 0){
        return 0;
    }

    int verif = 0;
    int base;

    base = getSoils(&node->loca, map);

    if(base == 0){
        verif = 1;
    }

    return verif;
}

t_nnode* creernoeud(t_nnode* prev, int dpth, t_move* avails, int idx, t_localisation* loc, t_map map, int dpmax){
    if(dpth == dpmax){
        return NULL;
    }

    t_nnode* new = NULL;
    new = malloc(sizeof(t_nnode));
    if(new == NULL){
        exit(EXIT_FAILURE);
    }

    new->nb_sons = prev->nb_sons - 1;
    new->depth = dpth;
    new->move = avails[idx];

    new->loca.pos.x = loc->pos.x;
    new->loca.pos.y = loc->pos.y;
    new->loca.ori = loc->ori;
    new->loca.translatefail = 0;

    new->soils = getSoils(&new->loca, map);
    new->cost = getCost(&new->loca, map);
    /* new->pathcost = prev ->pathcost + new->cost;*/

    if(prev->soils == 2){
        new->erg = 1;
    } else if(new->soils == 4){
        free(new);
        return NULL;
    }
    else{
        new->erg = 0;
    }

    if(new->move >= 0 && new->move <= 3){
        if(new->erg == 1){
            new->loca = moveErg(new->loca, new->move);
        }
        else {
            new->loca = translate(new->loca, new->move);
        }
    }
    else{
        if(new->erg == 1){
            new->loca = moveErg(new->loca, new->move);
        }
        else {
            new->loca.ori = rotate(new->loca.ori, new->move);
        }
    }

    if(new->loca.translatefail == 1){
        free(new);
        return NULL;
    }

    new->soils = getSoils(&new->loca, map);
    new->cost = getCost(&new->loca, map);
    new->base = isBaseFound(new, map);

    if(isValidLocalisation(new->loca.pos, 5, 6) == 0){
        free(new);
        return NULL;
    }else if(new->soils == 4){
        free(new);
        return NULL;
    }


    t_move local[prev->nb_sons];
    int j = 0;
    for (int i = 0; i < prev->nb_sons + 1; ++i) {
        if(i == idx){
            continue;
        }
        else{
            local[j] = avails[i];
            j++;
        }
    }

    if(dpth == 1){
        new->totmove[0] = new->move;
    }
    else {
        for (int i = 0; i < prev->depth; ++i) {
            new->totmove[i] = prev->totmove[i];
        }
        new->totmove[new->depth - 1] = new->move;
    }

    if (new->depth == 5) {
        new->nb_sons = 0;
    }

    if(new->base == 1){
        new->nb_sons = 0;
        new->depth = dpth;
        return new;
    }

    if(new->soils == 3){
        new->regcount = 1;
    }

    new->sons = malloc(new->nb_sons * sizeof(t_nnode*));
    if(new->sons == NULL){
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < new->nb_sons; ++i) {
        new->sons[i] = creernoeud(new, new->depth+1, local,i, &new->loca, map, dpmax);
    }

    return new;
}



t_nnode* creerracine(int dpth, int nbsons){
    t_nnode* root = NULL;
    root = malloc(sizeof(t_nnode));
    if(root == NULL){
        exit(EXIT_FAILURE);
    }

    root->nb_sons = nbsons;
    root->depth = dpth;
    root->pathcost = 0;

    root->sons = malloc(root->nb_sons * sizeof(t_nnode*));
    if(root->sons == NULL){
        exit(EXIT_FAILURE);
    }

    printf("root\n");

    return root;
}

t_nnode* creerarbre(int dpth, t_map map, int x, int y, t_orientation ori, int nbsons, int dpmax, int regverif){
    t_move* phase = NULL;
    phase = getRandomMoves(nbsons);

    t_localisation l;
    l = loc_init(x, y, ori);
    t_localisation* loc = NULL;
    loc = &l;

    t_nnode* root = NULL;
    root = creerracine(dpth, nbsons);
    root->soils = getSoils(loc, map);

    if(regverif == 1){
        dpmax = 5;
    }
    else{
        dpmax = 6;
    }

    for (int i = 0; i < root->nb_sons; ++i) {
        root->sons[i] = creernoeud(root, root->depth+1, phase, i, loc, map, dpmax);
    }

    printf("tree\n");

    return root;
}


t_nnode* trouverCoutMinFeuille(t_nnode* root) {
    if (root == NULL) {
        return NULL;
    }

    t_nnode *minLeaf = NULL;
    int minCost = 848364;

    if (root->nb_sons == 0) {
        return root;
    }

    for (int i = 0; i < root->nb_sons; i++) {
        t_nnode *candidateLeaf = trouverCoutMinFeuille(root->sons[i]);
        if (candidateLeaf != NULL && candidateLeaf->cost < minCost) {
            minCost = candidateLeaf->cost;
            minLeaf = candidateLeaf;
        }
    }

    return minLeaf;
}


int getCost(t_localisation* loc, t_map map){
    int cost;
    cost = map.costs[loc->pos.y][loc->pos.x];
    return cost;
}

int getSoils(t_localisation* loc, t_map map){
    int soils;
    soils = map.soils[loc->pos.y][loc->pos.x];
    return soils;
}

t_localisation moveErg(t_localisation loc, t_move move){
    int rst = 0;

    t_position res = loc.pos;
    switch (move) {
        case T_RIGHT:
        case T_LEFT:
        case F_10:
        case B_10:
            break;
        case U_TURN:
            rst=3;
            break;
        case F_30:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 2;
                    break;
                case EAST:
                    res.x = loc.pos.x + 2;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 2;
                    break;
                case WEST:
                    res.x = loc.pos.x - 2;
                    break;
                default:
                    break;
            }
            break;
        case F_20:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 1;
                    break;
                case EAST:
                    res.x = loc.pos.x + 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 1;
                    break;
                case WEST:
                    res.x = loc.pos.x - 1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

    if (loc.ori < 0 || loc.ori > 3) {
        printf("Erreur : orientation invalide %d\n", loc.ori);
        exit(EXIT_FAILURE);
    }

    loc.ori = (loc.ori + rst)%4;

    if(isValidLocalisation(res, 5, 6) == 1){
        return loc_init(res.x, res.y, (loc.ori+rst)%4);
    }
    else{
        loc.translatefail = 1;
        return loc;
    }

}

void movements(t_localisation* loc, t_move move){
    int rst = 0;

    switch (move) {
        case T_RIGHT:
            rst = 1;
            break;
        case T_LEFT:
            rst = 3;
            break;
        case F_10:
            switch (loc->ori) {
                case NORTH:
                    loc->pos.y = loc->pos.y - 1;
                    break;
                case EAST:
                    loc->pos.x = loc->pos.x + 1;
                    break;
                case SOUTH:
                    loc->pos.y = loc->pos.y + 1;
                    break;
                case WEST:
                    loc->pos.x = loc->pos.x - 1;
                    break;
                default:
                    break;
            }
            break;
        case B_10:
            switch (loc->ori) {
                case NORTH:
                    loc->pos.y = loc->pos.y + 1;
                    break;
                case EAST:
                    loc->pos.x = loc->pos.x - 1;
                    break;
                case SOUTH:
                    loc->pos.y = loc->pos.y - 1;
                    break;
                case WEST:
                    loc->pos.x = loc->pos.x + 1;
                    break;
                default:
                    break;
            }
            break;
        case U_TURN:
            rst = 2;
            break;
        case F_30:
            switch (loc->ori) {
                case NORTH:
                    loc->pos.y = loc->pos.y - 3;
                    break;
                case EAST:
                    loc->pos.x = loc->pos.x + 3;
                    break;
                case SOUTH:
                    loc->pos.y = loc->pos.y + 3;
                    break;
                case WEST:
                    loc->pos.x = loc->pos.x - 3;
                    break;
                default:
                    break;
            }
            break;
        case F_20:
            switch (loc->ori) {
                case NORTH:
                    loc->pos.y = loc->pos.y - 2;
                    break;
                case EAST:
                    loc->pos.x = loc->pos.x + 2;
                    break;
                case SOUTH:
                    loc->pos.y = loc->pos.y + 2;
                    break;
                case WEST:
                    loc->pos.x = loc->pos.x - 2;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

    if (loc->ori < 0 || loc->ori > 3) {
        printf("Erreur : orientation invalide %d\n", loc->ori);
        exit(EXIT_FAILURE);
    }

    loc->ori = (loc->ori + rst)%4;


}

void dispMvmt(t_nnode* node){
    for (int i = 0; i < node->depth; ++i) {
        switch (node->totmove[i]) {
            case F_10:    printf("F_10   "); break;
            case F_20:    printf("F_20   "); break;
            case F_30:    printf("F_30   "); break;
            case B_10:    printf("B_10   "); break;
            case T_LEFT:  printf("T_LEFT  "); break;
            case T_RIGHT: printf("T_RIGHT  "); break;
            case U_TURN:  printf("U_TURN   "); break;
        }
    }
    printf("\n\n\n");
}
