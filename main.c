#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "final.h"

int main() {
    t_map map = createMapFromFile("..\\maps\\training.map");
    printf("Map creer avec les dimensions %d x %d\n", map.y_max, map.x_max);
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

    return 0;
}
