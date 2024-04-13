# MaterialBox - une Sandbox en C++ avec la bibliothèque Raylib 

## Auteur : [Najib El khadir](https://github.com/NajibXY)

## 1. Motivations

<img align="right" src="https://github.com/NajibXY/MaterialBox---A-Sandbox-using-CPP-and-Raylib/blob/master/assets/gifs/main.gif">

Dans le cadre de mes expérimentations avec la bibliothèque Raylib et toujours sur le thème des automates cellulaires, j'ai repris mon projet de simulation de jeu de la vie ([Jeu de la vie en C++ avec la bibliothèque Raylib](https://github.com/NajibXY/Game-Of-Life-using-CPP-and-Raylib)) et j'en ai développé un autre projet : celui d'une sandbox interactive où l'utilisateur peut jouer avec différents matériaux. </br></br>
Cette sandbox permet de simuler plusieurs règles physiques et j'ai trouvé un malin plaisir à m'hypnotiser moi-même avec les rendus qu'elle peut proposer.
</br> </br> </br> </br>

## 2. Technologies utilisées

- C++14
- Librairie Raylib pour le développement de jeu vidéo : cela fait quelques temps que je tenais à tester cette librairie simple d'utilisation qui offre de très bon outils pour le développement de jeux (et plus généralement d'interfaces) 2D.
- Le template utilisé pour la configuration du projet Raylib provient de ce dépôt : https://github.com/educ8s/Raylib-CPP-Starter-Template-for-VSCODE-V2

## 3. Règles du jeu

- L'utilisateur peut dessiner en maintenant le bouton gauche de la souris plusieurs matériaux.
- L'utilisateur peut choisir le matériau à dessiner en suivant les indications sur la fenêtre de contrôle.
- Chaque matériau à ses règles d'activités précises et intéragit avec les autres matériaux.

#### Contrôles implémentés 

- Randomisation de la grille (Touche R)
- Nettoyage de la grille (Touche E)
- Accélération et Ralentissement du jeu (Touches S, D & F)
- Mettre en pause / Reprendre le jeu (Touche Espace)
- Jouer une étape de rafraîchissement (Touche G)
- Modifier le matériau choisi (Touche O/P ou Gauche/Droite ou Clics sur les boutons adéquats)
![](https://github.com/NajibXY/MaterialBox---A-Sandbox-using-CPP-and-Raylib/blob/master/assets/gifs/random.gif)

## 4. Matériaux implémentées

### Le sable

- Matériau de base de la simulation
- Se propage comme du sable dans le monde réél
- Se fait bloquer par la pierre et se faufile partout où il peut
- Se dissout progressivement dans l'acide  
![](https://github.com/NajibXY/MaterialBox---A-Sandbox-using-CPP-and-Raylib/blob/master/assets/gifs/sand.gif)

### La pierre

- Forme des blocs statiques sur la grille du dessin 
- Bloque le passage du sable
- Se dissout progressivement au contact de l'acide   
![](https://github.com/NajibXY/MaterialBox---A-Sandbox-using-CPP-and-Raylib/blob/master/assets/gifs/stone.gif)

### L'acide

- Se propage plus facilement que le sable
- Ronge progressivement la pierre
- Dissout progressivement le sable
- Forme des flaques visuellement imprévisibles
- Des règles d'aléatoire simples rendent le comportement de ce matériau particulièrement satisfaisant à observer   
![](https://github.com/NajibXY/MaterialBox---A-Sandbox-using-CPP-and-Raylib/blob/master/assets/gifs/acid.gif)

### Le vide

- Des cases vides peuvent être remises en sélectionnant le matériau "Empty"
- Cela agit sur la simulation indépendamment de si celle-ci est en pause ou non
- Il est d'ailleurs assez fun de mettre en pause la simulation, d'ajouter du vide, puis de relancer la simulation et observer ce qui se passe.
![](https://github.com/NajibXY/MaterialBox---A-Sandbox-using-CPP-and-Raylib/blob/master/assets/gifs/empty.gif)


## 5. Améliorations possibles

- Rajouter plus de matériaux ! Et plus d'intéractions entre eux !!! (Feu, eau, gaz etc.)
- Ajouter des sons lors de la sélection du matériau ; et rendre les boutons de sélection plus interactifs
- Rendre la taille de la grille customizable
- Ajouter une grille de vélocité permettant de donner de l'accélération aux particules des différents matériaux quand cela est pertinent
- Utiliser des Classes et plus de programmation orientée objet au lieu des valeurs utilisées dans la grille principale de la simulation (même si la simulation actuellement est parfaitement conçue pour être fluide et performante)
- Rajouter des compteurs

</br>
</br>

## 6. Exécuter le projet

- Si vous souhaitez vous amuser avec la simulation, vous pouvez télécharger le .exe présent dans le dépôt principal : [materialbox.exe](https://github.com/NajibXY/MaterialBox---A-Sandbox-using-CPP-and-Raylib/blob/master/materialbox.exe)

## Compilation, duplication, amélioration du projet

### Pré-requis 

- Installation de C++ (14 de préférence)
- Installation de Raylib pour C++ : https://www.raylib.com/

### Etapes

- Télécharger ou Forker le projet
- Ouvrir le projet dans VS Code via le fichier main.code-workspace
- F5 pour compiler et exécuter
- A partir de là vous pouvez effectuer toutes les modifications que vous souhaitez sur le fork du projet

  
