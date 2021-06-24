## I - Stratégie choisie pour répondre au sujet.

Pour répondre à ce sujet, nous avons décidé de traiter les tags de la même
manière que sont traités les répertoires dans les systèmes de fichiers.

En effet, cela nous permet d'implémenter notre hiérarchie de tags, sous-tags, ... (tout
comme une hierarchie de répertoires, sous-répertoires ... etc).

Concernant les tags "parallèles" (c'est-à-dire les tags distincts n'appartenant
pas à la même hiérarchie), leur fonctionnement est similaire à celui des liens, de répertoires différents, qui pointent vers un même fichier.

## II - Choix adoptés

- Le système de tags nécessite une installation de l'utilisateur mais n'a pas d'influence
sur les autres comptes utilisateurs.
- L'installation ne nécessite pas de d'accès au compte "root".
- Une fois installé, le système de tags perdure.
- Bien que l'installation ait été pensée comme irréversible pour l'utilisateur,
il est, en pratique, possible de revenir au système initial en supprimant, ou modifiant à la main, certains fichiers.

## III - Comments les tags sont mis à jours

Les tags sont mis à jour à la demande de l'utilisateur via les commandes du shell.
Les commandes sont précisées en détail dans README.md.

## IV Structures de données et algorithmes implémentés

Après l'installation, un dossier tags/ est créé dans le dossier home ( ~/ ) de l'utilisateur .  Ce dossier contient tout ce qui est nécessaire à la gestion de notre système de tags.
Il contient en particulier des fichiers C et les fichiers compilés correspondants (l'installation a compilé les programmes C). Il contient aussi des sous-répertoires.

### Les fichiers compilés

Les fichiers compilés sont exécutés via les commandes du shell (précisées dans README.md).
Des alias ont été introduits dans ./bashrc (via l'installation) pour exécuter ces programmes
facilement depuis n'importe quel répertoire. Nous avons également fait des alias
pour des commandes déjà existantes (comme cp, mv) pour qu'elles exécutent ces programmes qui tiennent en compte le système de tags (comme indiqué dans le sujet).

#### Les sous-répertoires

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

Il y a également un sous-répertoire .file/ qui fonctionne de manière similaire. Sauf qu'ici, les répertoires racines correspondent à des fichiers. Cela permet d'optimiser certains de nos algorithmes (comme celui qui liste tous les tags d'un fichier).

### Algorithmes utilisés

Nous n'avons pas implémenté d'algorithme connu, ou particulièrement innovant.
Nos algorithmes consistent principalement en la manipulation chaînes de caractères (pour les chemins de fichiers / répertoires) et l'utilisation de fonctions C permettant de faire les manipulations nécessaires (opendir() ... etc)

## Remarques

Nous avons fait tous nos tests sur le système ubuntu 18 (celui de l'ISO fourni par le sujet).
Nos tests ont fonctionné sur le PC de chaque membre du binôme. En cas de problème, ou
de pour toute information complémentaire, nous restons à votre disposition.
