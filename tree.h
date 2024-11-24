#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include "map.h"
#include "moves.h"
#include "tree.h"
#include "moves.h"
#include "map.h"
#include "loc.h"

typedef struct s_nnode{
    t_move move;
    int cost;
    int soils;
    int pathcost;
    int erg;
    int regcount;
    int depth;
    int nb_sons;
    int base;
    t_move* avails;
    t_move totmove[5];
    t_localisation loca;
    struct s_nnode** sons;
} t_nnode;

t_nnode* creernoeud(t_nnode* prev, int dpth, t_move* avails, int idx, t_localisation* loc, t_map map, int dpmax);

t_nnode* creerarbre(int dpth, t_map map, int x, int y, t_orientation ori, int nbsons, int dpmax, int regverif);

t_nnode* creerracine(int dpth, int nbsons);

void bestLeaf(t_nnode** nodemin, t_nnode* comp, int dpmax);

t_nnode* trouverCoutMinFeuille(t_nnode* node);

int isBaseFound(t_nnode* node, t_map map);

int getCost(t_localisation* loc, t_map map);

int getSoils(t_localisation* loc, t_map map);

t_localisation moveErg(t_localisation loc, t_move move);

void movements(t_localisation* loc, t_move move);

void dispMvmt(t_nnode* node);

void afficherArbre(t_nnode* node, int profondeur);

void afficherChemin(t_nnode* feuille);

void displayMenu();

#endif //UNTITLED1_TREE_H