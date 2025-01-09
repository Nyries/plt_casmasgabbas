# Rapport de Projet Logiciel Transverse : CLUEDO

![Boite_CLUEDO](Images_rapport/boite_CLUEDO.png)

[Louis-Mathis MASSIN](https://github.com/lmmas), [Cassandre CHANDELIER](https://github.com/CassandreChandelier), [Cyprien GABORIEAU](https://github.com/Nyries), [Bastien DUQUENNOY](https://github.com/Bastoune9)

## Table des matières : (à compléter)
1. [Présentation générale](##présentation-générale)

   1.1 [Archétype du jeu](###archétype-du-jeu)

   1.2 [Règles du jeu](###règles-du-jeu)

   1.3 [Ressources](###ressources)


## 1. Présentation générale

### 1.1 Archétype du jeu
L'objectif de ce projet est de réaliser le jeu de plateau **CLUEDO** en C++.
Le CLUEDO est un jeu de société classique d'enquête et de déduction, conçu par Anthony E. Pratt en 1943 et publié pour la première fois en 1949.
Jouable de 3 à 6 joueurs, il se déroule dans un manoir victorien fictif, où les participants endossent le rôle de détectives pour résoudre un meurtre mystérieux.

### 1.2 Règles du jeu
Samuel Lenoir est retrouvé mort dans sa demeure… La police a découvert sur place six suspects et six armes disséminées dans les 9 pièces de la maison mais n’a pas pu résoudre le mystère. A vous de mener votre enquête pour trouver la solution !

Pour remporter la partie, vous devez déterminer :
1. Qui a tué Samuel Lenoir ?
2. Avec quelle arme ?
3. Et dans quelle pièce ?

### But du jeu :

- Résoudre le mystère ! Pour gagner, vous devez être le premier joueur à déduire quelles sont les cartes suspect, arme et pièce qui se trouvent dans l’étui confidentiel au centre du plateau.

### Comment jouer :

**Début du jeu :**

- On place chaque pion personnage et arme sur sa case de départ.
- Puis mélange séparément les cartes indices. On en sélectionne secrètement une de chaque que l'on cache dans l'étui mystère, puis on distribue le reste des cartes aux joueurs.
- Chaque joueur doit garder sa main secrète, et il est possible que les joueurs n'aient pas tous le même nombre de cartes.
- Chaque joueur lance ensuite les dés. Celui qui obtient le meilleur score commence à jouer. La partie continue ensuite dans le sens des aiguilles d’une montre.

**A votre tour, lancez les dés et déplacez-vous sur le plateau :**
- Lancez les dés et déplacez votre pion personnage sur le plateau du nombre de cases obtenues avec les dés. 
- Vous pouvez déplacer votre pion verticalement ou horizontalement sur les cases ce couloir, mais jamais en diagonale.
- Lorsqu'un pion personnage atteint une case de porte, le joueur peut choisir d'entrer dans la pièce de la maison associée.
- Vous n’êtes pas obligé d’utiliser la totalité du score indiqué par les dés pour votre déplacement. Dès qu'un joueur entre dans une pièce, il termine sa phase de déplacement.

**Émettez ensuite une hypothèse pour obtenir des réponses :**
- Lorsqu'un joueur entre dans une pièce, il peut émettre une hypothèse avec **un suspect, une arme et la pièce dans laquelle il se trouve.**
  Exemple : après être rentré dans le Garage : « Est-ce Rose avec une Corde dans le Garage ? »
- Déplacez le pion personnage et le pion arme que vous citez dans la pièce où vous vous trouvez.
- Si le pion d'un joueur a été déplacé par un autre joueur depuis votre dernier tour, il peut choisir de ne pas bouger et d’émettre une hypothèse directement.
- Le joueur placé à votre gauche est le premier à répondre à votre hypothèse. S’il possède au moins une des cartes des éléments que vous avez cités, il **doit** vous en montrer une en cachette des autres joueurs. S'il en possède plusieurs, il choisit la carte qu'il révèle.
- S’il ne possède aucune des cartes que vous citez dans votre hypothèse, il doit juste vous dire « Je ne peux pas répondre. » et c’est au joueur situé à sa gauche de répondre. Ainsi de suite jusqu’à ce qu’un joueur vous montre **une carte.**
- Vous ne pouvez pas effectuer une hypothèse dans la même pièce 2 fois de suite. Vous devez d'abord changer de pièce et revenir ensuite.

**4. Enfin, terminez votre tour en cochant les cases sur votre feuilles de détective :**
- Cochez les cases des éléments qui vous ont été montrés pendant ce tour. Si une carte se trouve dans la main d'un adversaire, elle ne se trouve pas dans l'étui mystère et n'est donc pas lié au meurtre !
- **Et si aucun joueur ne vous montre de carte ?** Si une carte ne se trouve ni dans votre main, ni dans celles de vos adversaires, alors elle se trouve dans l'étui mystère ! 
- Laissez les pions personnage et arme là où vous les avez déplacé. Si le pion personnage que vous avez déplacé appartient à un autre joueur, celui-ci repartira de sa nouvelle position lors de son prochain tour.
- Votre tour est maintenant terminé. C’est au joueur situé à votre gauche de jouer.

**5. Portez une accusation (optionnel) :**

A la fin du tour de chaque joueur, celui-ci **peut** tenter de faire une accusation s'il pense connaître les trois cartes présentes dans l'étui secret.

Il porte votre accusation à haute voix :  « J’accuse Olive avec la Barre de Fer dans la Salle à Manger ! ». Puis, à l’abri du regard des autres joueurs, il vérifie le contenu de l’étui confidentiel.

**Avez-vous résolu le mystère ?**

- OUI ! Les trois cartes sont les mêmes que celles de mon accusation !
Félicitations ! Vous remportez la partie !
- NON ! Vous avez commis une erreur : vous êtes éliminé !
- Lorsqu'un joueur est éliminé, il ne peut plus porter d’accusation ni émettre d’hypothèses, mais il continue à montrer des cartes aux autres joueurs lorsqu’ils émettent des hypothèses.
- Si tous les joueurs se trompent , l’affaire reste non résolue.

**Déplacements futés :**
Des passages secrets sont présents dans la maison. Vous pouvez les utiliser pour passer d’une pièce a une autre.


### 1.3 Ressources

**Modélisation du plateau de jeu :**

![Plateau](../ressources/maison_map.png)

**Cartes indices :**

![Cartes_indice](../ressources/allcards/ensemble_cartes.png)

## 2. Description et conception des états

### 2.1 Description des états
Les états du jeu comprennent les informations sur les joueurs, toutes les cases du plateau ainsi que les salles, et toutes les cartes utilisées dans le jeu.

#### Les infos des joueurs
Pour chaque joueur on dispose de leur nom, le suspect associé, leur emplacement, la liste de ses cartes, un booléen le fait que le joueur a lancé une accusation fausse ou pas (cela détermine si le joueur peut continuer à jouer ses tours ou pas).
Ces infos de joueurs sont stockées dans une liste.

#### Les cases du jeu
Les cases du jeu sont stockées dans un tableau 2D. Chacune d'entre elles a un type et des coordonnées, les cases de type "porte" ont une salle associée.

#### Les salles
Les salles ont un nom, la liste de leurs portes, et potentiellement la salle vers laquelle il y a un passage secret.

