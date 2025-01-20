# Rapport de Projet Logiciel Transverse : CLUEDO

![Boite_CLUEDO](Images_rapport/boite_CLUEDO.png)

[Louis-Mathis MASSIN](https://github.com/lmmas),
[Cassandre CHANDELIER](https://github.com/CassandreChandelier),
[Cyprien GABORIEAU](https://github.com/Nyries),
[Bastien DUQUENNOY](https://github.com/Bastoune9)

## Table des matières : 
## [1. Présentation Générale](#1)
### [1.1 Archétype du jeu](#1.1)
### [1.2 Règles du jeu](#1.2)
### [1.3 Ressources](#1.3)
## [2. Description et conception des états](#2)
### [2.1 Description des états](#2.1)
### [2.2 Conception logiciel](#2.2)
### [2.3 Conception logiciel : extension pour le moteur de jeu](#2.3)
## [3. Rendu: Stratégie et Conception](#3)
### [3.1 Stratégie de rendu d'un état](#3.1)
### [3.2 Conception logiciel](#3.2)
### [3.3 Exemple de rendu](#3.3)
## [4. Règles de changement d'états et moteur de jeu](#4)
### [4.1 Changements extérieurs](#4.1)
### [4.2 Changements autonomes](#4.2)
### [4.3 Conception logiciel](#4.3)
## [5. Intelligence Artificielle](#5)
### [5.1 Stratégies](#5.1)
### [5.2 Conception logiciel](#5.2)

## 1. Présentation générale <a id="1"></a>

### 1.1. Archétype du jeu <a id="1.1"></a>
L'objectif de ce projet est de réaliser le jeu de plateau **CLUEDO** en C++.
Le CLUEDO est un jeu de société classique d'enquête et de déduction, conçu par Anthony E. Pratt en 1943 et publié pour la première fois en 1949.
Jouable de 3 à 6 joueurs, il se déroule dans un manoir victorien fictif, où les participants endossent le rôle de détectives pour résoudre un meurtre mystérieux.

### 1.2. Règles du jeu <a id="1.2"></a>
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
- Si le joueur ne possède aucune des cartes que vous citez dans votre hypothèse, il dit simplement « Je ne peux pas répondre. » et c’est au joueur situé à sa gauche de répondre. On continue de cette façon jusqu’à ce qu’une carte soit dévoilée ou que tous les joueurs aient été interrogés.
- Vous ne pouvez pas effectuer une hypothèse dans la même pièce 2 fois de suite. Vous devez d'abord changer de pièce et revenir ensuite.

**Enfin, terminez votre tour en cochant les cases sur votre feuille de détective :**
- Cochez les cases des éléments qui vous ont été montrés pendant ce tour. Si une carte se trouve dans la main d'un adversaire, elle ne se trouve pas dans l'étui mystère et n'est donc pas lié au meurtre !
- **Et si aucun joueur ne vous montre de carte ?** Si une carte ne se trouve ni dans votre main, ni dans celles de vos adversaires, alors elle se trouve dans l'étui mystère ! 
- Laissez les pions personnage et arme là où vous les avez déplacés. Si le pion personnage que vous avez déplacé appartient à un autre joueur, celui-ci repartira de sa nouvelle position lors de son prochain tour.
- Votre tour est maintenant terminé. C’est au joueur situé à votre gauche de jouer.

**Portez une accusation (optionnel) :**

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


### 1.3. Ressources <a id="1.3"></a>

**Modélisation du plateau de jeu :**

![Plateau](../ressources/maison_map.png)

**Cartes indices :**

![Cartes_indice](../ressources/allcards/ensemble_cartes.png)

## 2. Description et conception des états <a id="2"></a>

### 2.1. Description des états <a id="2.1"></a>
Les états du jeu comprennent toutes les informations nécessaires au bon fonctionnement du moteur du jeu.

Cela inclut toutes les informations sur les joueurs, les cartes indices, et une décomposition de la carte du manoir en salles et en cellules (couloirs & portes).

#### Les joueurs
Un joueur (PlayerState) est caractérisé par son identité (quel suspect il incarne), sa position sur le plateau et sa main (vecteur de cartes indices).
On garde également en mémoire la dernière pièce dans laquelle il a effectué une hypothèse puisqu'il ne peut pas en effectuer plusieurs à la suite au même endroit.
Enfin, on lui associe une valeur booléenne indiquant s'il a effectué une accusation, puisqu'un joueur ayant fait une mauvaise accusation ne prend plus part à la partie.

#### Le plateau de jeu
Les cases du plateau sont stockées dans un tableau.
Une case est caractérisée par des coordonnées et par un type (CORRIDOR, DOOR, ROOM, INACCESSIBLE).
- Une case DOOR est un cas particulier de case CORRIDOR, et possède une référence à la ROOM à laquelle elle mène.
- Une ROOM est caractérisée par son nom, la liste de ses portes, et par une éventuelle autre ROOM qui serait accessible par passage secret.
- On qualifie d'INACCESSIBLE les cases auxquelles les joueurs ne peuvent pas accéder (extérieur du manoir & pièce centrale).

#### Les cartes indice
Chaque carte indice est caractérisée par un type (SUSPECT_CARD, WEAPON_CARD, ROOM_CARD) et par un identifiant.
On renseigne le nom de chaque carte au sein d'un "enum" pour chaque type de carte.

### 2.2 : Conception logiciel <a id="2.2"></a>

![State_dia](Images_rapport/state_dia.png)

Vous trouverez notre diagramme de classes pour les états ci-dessus.

La classe State (en bleu) permet la création initiale des états du jeu.
Son constructeur prend en argument le nombre de joueurs dans la partie et la carte du plateau, fournie sous format JSON.

La classe PlayerState (en blanc) permet la création des joueurs et contient toutes les données utiles au fonctionnement du jeu les concernant.

En orange, on retrouve les classes liées à la création des cartes à jouer, réparties en trois catégories : suspect, arme et salle.
Il y a donc trois classes héritant d'une même classe Card, chacune décrite par un énumérateur.

Enfin, on observe en violet les classes liées au plateau de jeu.
La classe Map crée le plateau de jeu sous la forme d'un tableau à deux dimensions, à partir d'un fichier JSON fourni en argument.
Chaque cellule de ce tableau peut prendre une des 4 valeurs suivantes : CORRIDOR (couloir), DOOR (porte), ROOM (salle) et INACCESSIBLE.

### 2.3. Conception logiciel : extension pour le moteur de jeu <a id="2.3"></a>

La structure TripleClue (en gris sur le diagramme de classes) est utilisée dans le moteur de jeu dans le cadre de la création des hypothèses et des accusations formulées par les joueurs.

## 3. Rendu : stratégie et conception <a id="3"></a>

### 3.1. Stratégie de rendu d'un état <a id="3.1"></a>

...

### 3.2. Conception logiciel <a id="3.2"></a>

...

### 3.3. Exemple de rendu <a id="3.3"></a>

...

## 4. Règles de changement d'état et moteur de jeu <a id="4"></a>

La partie engine de notre jeu permet de modifier les données du state en fonction des éléments ayant eu lieu dans la partie.
Ces changements d’état ne suivent pas d’horloge globale puisque les joueurs ne sont pas limités quant à la durée de leur tour.

### 4.1. Changements extérieurs <a id="4.1"></a>

Les changements extérieurs correspondent aux changements causés par les différentes actions des joueurs.
Cela inclut :

- Les déplacements des joueurs via un lancer de dés.
- Les déplacements des joueurs via l'utilisation d'un passage secret.

### 4.2. Changements autonomes <a id="4.2"></a>

Par opposition à la partie précédente, les changements autonomes désignent les changements effectués automatiquement, sans action des joueurs.
Cela inclut : 

- L'initialisation du jeu
- Le déplacement d'une arme ou d'un suspect non joué à la suite d'une hypothèse.
- La victoire / l'élimination d'un joueur à la suite d'une accusation correcte / incorrecte.

### 4.3. Conception logiciel <a id="4.3"></a>

![Engine_dia](Images_rapport/engine_dia.png)

Le diagramme des classes pour le moteur du jeu est présenté ci-dessus.
L’ensemble du moteur de jeu repose sur le "design pattern" Command, et a pour but la mise en œuvre de commandes extérieures sur l’état du jeu.

Ces commandes correspondent aux différentes actions qu'un joueur peut réaliser pendant son tour : 

- MoveCommand permet de se déplacer vers un lieu considéré comme accessible, comme une cellule adjacente si le joueur se situe dans un CORRIDOR, ou une pièce si le joueur est situé sur une des portes qui y mène.
- SecretPassageCommand permet d'emprunter un passage secret vers une autre pièce si le joueur se trouve dans une salle qui en dispose. Dans le reste des cas, l'option ne sera pas disponible.
- HypothesisCommand permet au joueur d'effectuer une hypothèse s'il se trouve dans une pièce.
- AccusationCommand permet au joueur d'effectuer son accusation unique à la fin de son tour s'il le souhaite.

## 5. Intelligence artificielle <a id="5"></a>

### 5.1. Stratégies <a id="5.1"></a>

#### Intelligence minimale

IA random:
L'IA random est l'IA la moins réfléchie possible. Elle choisit au hasard son action (déplacement, accusation, hypothèse,..) et a donc une chance sur deux de mener une accusation dès le début de la partie.
De plus, elle se déplace de façon complètement aléatoire sur la map et ne note aucune carte montrée par ses adversaires.
Elle a donc très peu de chance de gagner.

#### Intelligence basée sur les euristiques

IA easy:
L'IA easy est une IA random mais avec une certaine logique de fonctionnement. Elle accuse uniquement quand elle est sûre d'avoir trouvé le meurtrier, l'arme du crime et le lieu du crime. De plus, elle note tout ce que ses adversaires lui montre dans des vecteurs (0: inconnue, 1: possédée par un joueur, 2: meurtrier), et choisit ses destinations de façon random lorsque plusieurs destinations sont possibles, ou la plus proche si aucune n'est accessible.
Elle se déplace donc intelligemment selon sa destination finale, pour s'en rapprocher un maximum.
En revanche, ses hypothèses (choix du suspect et de l'arme) sont aléatoires. C'est donc une IA random plus intelligente.

IA medium:
L'IA medium a le même principe que l'IA easy. Elle se déplace intelligemment vers sa destination finale. Mais le choix de la destination finale diffère. En effet, elle cherche les pièces qu'elle n'a pas encore explorées, et elle va aléatoirement dans l'une d'entre elles. Si elle les a toutes explorées, elle se dirige de préférence vers une salle qu'elle possède, ou vers celle du crime. Si elle n'en possède aucune, alors elle ira n'importe quelle salle.
Pour ses hypothèses, elle distingue dans des vecteurs, les cartes qui n'ont pas encore été révélées, de celles qu'elle possède, et de celles possédées par les autres joueurs. (0: inconnue, 1: possédée par le joueur, 2: possédée par un adversaire, 3: meurtrier). Ainsi, elle a un bon suivi pour la suite, et quand elle cherchera la salle du crime, elle pourra demander un suspect ou une arme qu'elle possède ou qui est dans l'enveloppe pour éviter qu'un adversaire lui remontre une carte qu'elle connaîtrait déjà et ne pas gaspiller un tour.
Enfin, elle accuse lorsqu'elle connait les trois cartes de l'enveloppe.

Des tests ont été réalisés: avec autoplay (2 IA easy vs 2 IA medium)
Nous avons observé une victoire écrasante pour les IA medium avec pour valeur environ 85 victoires, contre 15 pour les IA easy.

### 5.2. Conception logiciel <a id="5.2"></a>

(ia.dia + explications)
