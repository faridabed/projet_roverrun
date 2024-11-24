#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "tree.h"
#include "final.h"

int main() {
    int choice = -1;

    printf("========== PROGRAMME INTERACTIF MARC ==========\n");

    while (1) {
        // Afficher le menu
        displayMenu();
        printf("Choisissez une option (0 pour quitter) : ");
        scanf("%d", &choice);

        // Quitter le programme si l'utilisateur entre 0
        if (choice == 0) {
            printf("Au revoir !\n");
            break;
        }

        switch (choice) {
            case 1: {
                printf("\n>>> Chargement et affichage de la carte <<<\n");
                t_map map = createMapFromFile("..\\maps\\example1.map");
                printf("Carte chargée avec dimensions %d x %d\n", map.y_max, map.x_max);
                displayMap(map);
                break;
            }
            case 2: {
                printf("\n>>> Construction et affichage de l'arbre <<<\n");
                t_map map = createMapFromFile("..\\maps\\example1.map");
                t_nnode* tree = creerarbre(0, map, 2, 2, NORTH, 5, 6, 0);

                printf("\n===== ARBRE DES MOUVEMENTS =====\n");
                afficherArbre(tree, 0);
                printf("===============================\n");
                break;
            }
            case 3: {
                printf("\n>>> Test des mouvements <<<\n");
                t_localisation pos = loc_init(2, 2, NORTH);
                printf("Position initiale : (%d, %d), Orientation : %d\n", pos.pos.x, pos.pos.y, pos.ori);
                pos = translate(pos, F_30);
                printf("Après mouvement F_30 : (%d, %d), Orientation : %d\n", pos.pos.x, pos.pos.y, pos.ori);
                break;
            }
            case 4: {
                printf("\n>>> Tester la localisation (sortie de carte) <<<\n");
                t_position positions[] = {
                        {2, 2}, {0, 0},{-1, 2},  {3, -1}
                };
                t_map map = createMapFromFile("..\\maps\\example1.map");

                printf("Test de sortie de la carte :\n");
                for (int i = 0; i < sizeof(positions) / sizeof(positions[0]); i++) {
                    t_position pos = positions[i];
                    int valid = isValidLocalisation(pos, map.x_max, map.y_max);
                    printf("Position (%d, %d) : %s\n", pos.x, pos.y, valid ? "Valide" : "Invalide");
                }
                break;
            }
            case 5: {
                printf("\n>>> Tester le passage sur une crevasse <<<\n");
                t_position positions[] = {
                        {2, 2}, {1, 5}, {5, 5}
                };
                t_map map = createMapFromFile("..\\maps\\example1.map");

                printf("Test de passage sur une crevasse :\n");
                for (int i = 0; i < sizeof(positions) / sizeof(positions[0]); i++) {
                    t_position pos = positions[i];
                    if (isValidLocalisation(pos, map.x_max, map.y_max)) {
                        int soil = map.soils[pos.y][pos.x];
                        printf("Position (%d, %d) : ", pos.x, pos.y);
                        if (soil == 4) {
                            printf("Crevasse (danger !)\n");
                        } else {
                            printf("Terrain sur (type %d)\n", soil);
                        }
                    } else {
                        printf("Position (%d, %d) : Hors des limites de la carte\n", pos.x, pos.y);
                    }
                }
                break;
            }
            case 6: {
                printf("\n>>> Trouver le chemin optimal <<<\n");
                t_map map = createMapFromFile("..\\maps\\example1.map");
                t_nnode* tree = creerarbre(0, map, 2, 2, NORTH, 5, 6, 0);

                t_nnode* best_leaf = trouverCoutMinFeuille(tree);
                if (best_leaf != NULL) {
                    printf("\n===== RESULTATS =====\n");
                    printf("Position finale : (%d, %d)\n", best_leaf->loca.pos.x, best_leaf->loca.pos.y);
                    printf("Coût total : %d\n", best_leaf->cost);

                    printf("\nChemin optimal depuis la racine :\n");
                    afficherChemin(best_leaf);
                } else {
                    printf("Aucun chemin valide trouve.\n");
                }
                break;
            }
            default:
                printf("Option invalide, veuillez reessayer.\n");
        }
    }

    printf("\n========== FIN DU PROGRAMME ==========\n");
    return 0;
}
