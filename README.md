Projet: Rover RUN ! réalisé par le GROUPE GBN_5
 Membre du groupe:
- Farida Bedewy
- Maxime Gabouty
- Samuel Sitbon

Résumé du projet:
 Ce projet en langage C implemente une simulation du déplacement d'un rover martien nommé MARC sur une carte 2D. L'objectif est de guider MARC depuis une position initiale jusqu'à une station de base tout en évitant les obstacles et en minimisant les coûts associés aux types de terrains.

 Fonctionnalités principales:
 - Gestion des mouvements du rover : translation, rotation, déplacement sur différents types de terrain (plaine, erg, reg, crevasse).
- Calcul des coûts associés à chaque position sur la carte pour trouver le chemin optimal.
- Génération d’un arbre de décisions N-aire pour explorer les séquences de mouvements possibles.
- Recherche de la feuille avec le coût minimal dans l’arbre.
- Affichage visuel de la carte avec les chemins empruntés.

  Contenu du dépôt:
  - main.c : Initialise la carte et lance la recherche de la station de base.
  - map.c / map.h : Gestion des cartes martiennes. Chargement, affichage et calcul des coûts depuis la station de base.
  - moves.c / moves.h : Implémente les mouvements et rotations du rover en fonction de son orientation et des règles du terrain.
  - tree.c / tree.h : Construction de l’arbre de décisions, recherche des feuilles optimales et gestion des structures dynamiques.
  - loc.c / loc.h : Gestion des positions et vérifications de validité (dans et hors de la carte).
  - stack.c / stack.h et queue.c / queue.h : Structures pour gérer les piles et les files, utilisées dans les calculs.
 
    
lien git : https://github.com/faridabed/projet_roverrun.git

lien fiche dépôt final: https://efrei365net-my.sharepoint.com/:x:/g/personal/maxime_gabouty_efrei_net/EZ8ld68zPD1HhdImZcTxKBgBeDdkKxPdhCQezvuJGUTLTw?e=8lhwie
