# SGF avec tags   

<img alt="C" src="https://img.shields.io/badge/c%20-%2300599C.svg?&style=flat-square&logo=c&logoColor=white"/>     

*Projet réalisé en binôme dans le cadre du cours "Programmation Système"*   
**Auteurs : [Joël Hamilcaro](https://github.com/Joel-Hamilcaro/) et [Jie Tu](https://github.com/jie-tu)**   

Le but de ce projet est d'implémenter un système de gestion de fichiers avec tags (SGF), en surcouche d'un système d'exploitation de type UNIX. Le tests sont à réaliser sur une machine virtuelle.

## Architecture

### Stratégie choisie pour répondre au sujet.

Pour répondre à ce sujet, nous avons décidé de traiter les tags de la même
manière que sont traités les répertoires dans les systèmes de fichiers.

En effet, cela nous permet d'implémenter notre hiérarchie de tags, sous-tags, ... (tout
comme une hiérarchie de répertoires, sous-répertoires ... etc).

Concernant les tags "parallèles" (c'est-à-dire les tags distincts n'appartenant
pas à la même hiérarchie), leur fonctionnement est similaire à celui des liens, de répertoires différents, qui pointent vers un même fichier.

### Choix adoptés

- Le système de tags nécessite une installation de l'utilisateur mais n'a pas d'influence
sur les autres comptes utilisateurs.
- L'installation ne nécessite pas de d'accès au compte "root".
- Une fois installé, le système de tags perdure.
- Bien que l'installation ait été pensée comme irréversible pour l'utilisateur,
il est, en pratique, possible de revenir au système initial en supprimant, ou modifiant à la main, certains fichiers.

### Comment les tags sont mis à jour ?

Les tags sont mis à jour à la demande de l'utilisateur via les commandes du shell.
Les commandes sont précisées en détail dans la partie "Détail des nouvelles commandes".

### Structures de données et algorithmes implémentés

Après l'installation, un dossier tags/ est créé dans le dossier home ( ~/ ) de l'utilisateur .  Ce dossier contient tout ce qui est nécessaire à la gestion de notre système de tags.
Il contient en particulier des fichiers C et les fichiers compilés correspondants (l'installation a compilé les programmes C). Il contient aussi des sous-répertoires.

#### Les fichiers compilés

Les fichiers compilés sont exécutés via les commandes du shell (précisées dans README.md).
Des alias ont été introduits dans ./bashrc (via l'installation) pour exécuter ces programmes
facilement depuis n'importe quel répertoire. Nous avons également fait des alias
pour des commandes déjà existantes (comme cp, mv) pour qu'elles exécutent ces programmes qui tiennent en compte le système de tags (comme indiqué dans le sujet).

#### Les sous-répertoires

Ces sous-répertoires permettent de stocker nos tags suivant la stratégie expliquée en I.

Exemple : Soit un fichier "fic" dans ~/Images ayant les tags suivants :
- 'color' , 'blue' (sous-tag de color)
- 'shape' , 'square' (sous-tag de shape)
- 'image'

Alors nous aurons cette hiérarchie de sous-répertoire dans tags/ :

- tags/.tags/color/blue/fic
- tags/.tags/shape/square/fic
- tags/.tags/image/fic

Ces trois chemins correspondent, tous à un lien symbolique vers le même fichier ~/Images/fic.

Ainsi, pour chaque fichier auquel on a ajouté un tag, nous ajoutons un lien symbolique dans
l'arboresence de racine .tags/.

Il y a également un sous-répertoire .file/ qui fonctionne de manière similaire. Néanmoins, les répertoires racines correspondent à des fichiers. Cela permet d'optimiser certains de nos algorithmes (comme celui qui liste tous les tags d'un fichier).

## Installation

Après avoir cloné le projet dans la machine virtuelle, taper la commande :

```
sh lancer.sh
```

Pour compiler tous les fichiers et créer des tags sur des fichiers exemples,
il faut relancer un terminal, puis taper la commande :
```
setupTags
```

## Détail des nouvelles commandes

MkTags : créer les tags:
```
mkTags tags1 tags2 tags3 ...
```
dropTags " supprimer un sous-tags
```
dropTags color/green color/blue
```
addTags : ajouter un tags à un fichier
```
addTags fichier color/red
```

lsFile : lister tous les fichiers qui ont un tag particulier
```
lsFile color/red
```
lsFic : selectioner les fichier avec tags
on utilise ^ pour ET, ! pour NON
```
lsFic system ^ l3 ! 2019
lsFic system ^ l3 ! 2020
```
lsTags : afficher tous les tags pour le fichier
```
lsTags filename
```
rmTags : effacer un tags pour un fichier
```
rmTags filename color/red
```
cp : copier le fichier avec tags
```
cp fic fic2
```
mv : deplacer le fichier avec tags
```
mv fic fic2
```
