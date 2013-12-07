PATHOGEN ANNIHILATION


Table des matières
1	Généralités	3
__1.1	Résumé	3
__1.2	Outils de développement	3
2	Contenu sérieux	4
__2.1 Public cible	4
__2.2	Contexte d’utilisation	4
__2.3	Objectifs	4
__2.4	Activités	6
3	Gameplay	7
__3.1 Description résumée	7
__3.2	Objectifs ludiques	8
__3.3	Comment le Gameplay permet-il d’atteindre l’objectif sérieux	8
4	Structure du jeu	10
__4.1	Histoire	10
__4.2	Personnages	10
__4.3	Niveaux	11
5	Etude Comparative	13
__5.1	Leukos War :	13
__5.2	Re-Mission :	14
__5.3	Immune System Defender :	15
__5.4	Immune War :	16
__5.5 Choix effectués dans Pathogen Annihilation :	17








1	Généralités



Titre :	Pathogen Annihilation	Date :	22/10/2013
Auteurs :	Olivier Bartoli, Nassim Rivière	Version :	1.3
UEs :	GMIN324 GMIN317	Collaboration UM3 :	non
Type : 	Learning Game		


1.1	Résumé

Pathogen Annihilation nous fait « incarner » le système immunitaire d’un corps humain qui doit lutter contre les 
différents agents pathogènes qui le menacent. Pour cela, le joueur doit tout d’abord les identifier, puis ensuite 
apporter la réponse adaptée parmi celles qui sont à sa disposition.


1.2	 Outils de développement 

Le projet sera réalisé en parallèle avec l’unité d’enseignement GMIN317 « Moteurs De Jeux ». Nous créerons notre 
propre moteur de jeu. Il sera codé en C++.
Nous utiliserons Github pour la gestion de version ainsi que Visual Studio 2013 pour la programmation.
Les textures seront réalisées à l’aide d’Adobe Photoshop et les modèles 3D de 3D studio Max 2012.



2	Contenu sérieux  

2.1 Public cible 

Pathogen Annihilation visera principalement les élèves de collège. Son contenu sérieux doit pouvoir être appréhendé 
par les joueurs. Ils devront en savoir un minimum sur le fonctionnement et la composition du corps. 
Cela correspond au niveau 5ème.

2.2	Contexte d’utilisation

Le jeu ne nécessite pas d’équipement particulier si ce n’est un ordinateur. Il pourra donc être pratiqué en classe 
ou à la maison.
2.3	 Objectifs

Pathogen Annihilation à pour but de faire connaitre les principales menaces et leur fonctionnement (ce qu’elles 
attaquent, comment elles se reproduisent, les conséquences de leur prolifération)  dans le corps humain.  
Le jeu tend de plus à faire comprendre le mécanisme d’identification, d’adaptation et de réponse du système 
immunitaire au niveau cellulaire.
Nous nous concentrons sur des notions simples :
Menaces : 
- Les virus : se reproduisent grâce au matériel génétique des cellules qu’ils parasitent. Détruisent les cellules infectées.
- Bactéries : se reproduisent par division, provoquent des infections et peuvent corrompre les tissus.
- Cancers : cellules corrompues qui se divisent indéfiniment, provoques des métastases.

Mécanisme d’identification : 
- Les monocytes présentent les agents pathogènes aux lymphocytes.

Mécanisme d‘adaptation :
- Les lymphocytes produisent les anticorps adaptés à la nouvelle menace.
Réponses immunitaires :
- Lymphocytes : combattent les virus et les cancers.
- Monocytes: combattent les bactéries et nettoient les débris qui peuvent être source d’inflammation, participent
au mécanisme d’identification.
- Neutrophiles : combattent les bactéries, sont beaucoup plus nombreux que les monocytes mais laissent des débris 
à leur mort.
Le projet à aussi pour but de faire de la prévention, en décrivant les causes de l’arrivée des menaces dans le corps.


2.4	 Activités

Les activités mises en place pour atteindre ces objectifs sont les suivantes :

 

- Identifier les menaces : l’utilisateur doit identifier visuellement les menaces, en fonction de leur comportement
et de leur apparence.
- Identifier les réponses immunitaires : l’utilisateur doit visuellement identifier les lymphocytes, monocytes ou 
neutrophiles en fonction de ce qu’il sait de leur action et les mettre en relation avec le type de menace qu’ils 
combattent.
- Mettre en place la stratégie de défense du système immunitaire : l’utilisateur, après avoir identifié les menaces 
doit :
- si c’est une infection virale ou un cancer : permettre aux lymphocytes de mémoriser la menace et de fabriquer les
anticorps adaptés.
- se c’est une infection bactérienne : choisir les neutrophiles ou les monocytes selon la virulence.
3	Gameplay

3.1 Description résumée

Dans Pathogen Annihilation, le joueur dirige un mobile qui représente le système immunitaire. Il peut se déplacer
en 2D dans un environnement 3D vu de dessus.

L’environnement représente un endroit quelconque du corps humain à l’échelle cellulaire. Des cellules sont en
suspension dans ce milieu, elles peuvent se reproduire par division cellulaire. Des menaces de différents types 
apparaissent au cours du temps et se développent.
Le joueur doit les combattre en choisissant parmi différentes actions :

- envoyer des monocytes pour marquer la menace et à leur retour fabriquer des anticorps.
- détruire la menace en envoyant des lymphocytes chargés d’anticorps.
- détruire la menace en envoyant des neutrophiles.

Pour ce faire, le joueur doit choisir le bon type de munition, viser puis tirer. Le nombre de munitions de chaque 
type est limité mais elles se régénèrent au cours du temps.

	Il y a 3 types de menaces :

- Les bactéries : en suspension, elles se reproduisent jusqu'à atteindre un nombre critique.

- Les virus : infectent les cellules et se reproduisent à partir de leur matériel génétique, elles sont alors 
considérées comme détruites.

- Les cancers : cellules corrompues qui se reproduisent à l’infini et s’agglomèrent pour former des métastases.
	
	Ces trois classes sont elles mêmes divisée par couleur selon leur virulence.
	
De plus les débris déposés par les combats ralentissent les déplacements du joueur dans une zone dont la taille 
varie en fonction du nombre de débris agglomérés (inflammation).	

	Les munitions ont des comportements différents :

- les monocytes se déplacent lentement, font peu de dégâts aux bactéries mais lorsqu’ils sont en contact avec 
des virus ou des cellules cancéreuses reviennent vers le joueur. Cette action active les lymphocytes pour être 
efficaces contre ce type/couleur d’ennemi précis. Ils nettoient aussi les débris.
- Les lymphocytes on besoin d’être activés selon un type/couleur d’ennemi pour pouvoir être efficaces. Ils ne 
font pas de dégâts aux bactéries mais détruisent les virus et cellules cancéreuses.

- Les neutrophiles se déplacent rapidement et sont très efficaces contre les bactéries, ils laissent cependant
des débris.  

Au  début de chaque mission, un écran de briefing présente les menaces et décrit la réponse à fournir. De plus,
le joueur devra choisir un bonus de régénération d’un type de leucocytes en fonction de la menace prépondérante 
du niveau. 

Les niveaux sont tout d’abord thématiques suivant un seul type de menace. D’autres types sont ajoutés au fur et 
à mesure des niveaux.

3.2	Objectifs ludiques

Il faudra faire en sorte que l’hôte du système immunitaire que « contrôle » le joueur survive pour atteindre le 
niveau suivant. Et ainsi de suite jusqu’à la fin du jeu. C’est un jeu d’adresse, le joueur doit apprendre à viser
et tirer au bon moment, il doit aussi gérer son stock de munitions. Prioriser la destruction des types d’ennemis
en fonction de la situation.
Conditions de défaite :

- le mobile entre en contact avec une menace de tout type : le système immunitaire est infecté.
- Aucune cellule saine ne reste dans l’environnement : le milieu est détruit, les menaces se propagent dans le 
reste du corps.
- Le milieu est totalement métastasé : le cancer se répand.
- Les bactéries ont atteint un trop grand nombre.

Conditions de victoire :

- Toutes les menaces sont éradiquées : le système est à nouveau sain.

De plus, on pourra mesurer la réussite en comptant les points pour chaque ennemi abattu, pour chaque leucocyte
adapté « tiré » avec succès. Le nombre de succès d’affilé etc.

3.3	Comment le Gameplay permet il d’atteindre l’objectif sérieux 

Le gameplay permet de mettre en place les activités et de réaliser les objectifs sérieux vus précédemment de la
façon suivante : 

Connaitre/Identifier les menaces : 

Les menaces sont décrites visuellement en début de niveau à l’aide d’une image et d’un texte descriptif, elles 
sont aussi mises en relation avec leur visuel dans le jeu qui s’inspire de leur apparence réelle. 

Leur comportement, basé sur la réalité est lui aussi décrit à l’aide de schémas lors de cette phase de briefing.


Connaitre/identifier les réponses immunitaires : 

De la même manière que les menaces, les réponses immunitaires sont décrites en début de niveau. De plus, on 
s’assurera de sa compréhension en lui faisant choisir le bonus de régénération de munition qui correspondra 
à la menace qui aura la fréquence d’apparition la plus importante. 


On retrouve le comportement et l’apparence des agents décrits dans le briefing lors de la phase de combat. 
Le joueur peut donc les identifier.

On prendra soin de n’introduire qu’une seule menace/réponse par niveau, pour éviter de rebuter le joueur par 
des explications trop nombreuses.

Durant la phase de combat, le joueur ne peut tirer qu’un seul type de munition à la fois. Pour s’assurer qu’il a
bien comprit la relation entre les menace et les réponses, les stocks de munitions sont limités.

Mettre en place une stratégie de défense :

Après avoir identifié les menaces, le joueur doit être capable d’élaborer une stratégie de défense :
	
- Si c’est une bactérie : choisir monocyte ou neutrophiles en fonction de la virulence. Les neutrophiles vont 
réduire rapidement l’infection bactérienne mais vont laisser des débris provoquant l’inflammation lors de leur 
action. Les monocytes vont réduire lentement mais proprement l’infection.

- Si c’est un virus ou un cancer : envoyer un monocyte qui fera un aller retour pour marquer puis activer les 
lymphocytes pour combattre ce type d’ennemi. Il faut ensuite utiliser les lymphocytes pour détruire la menace.

Ce sont les stratégies mises en place dans la réalité par le système immunitaire. Si le joueur est capable de 
les reproduire dans le jeu à partir des informations qui sont mises à sa disposition lors des briefings, on peut
les considérer comme acquises. Elles valident la connaissance des menaces et réponses immunitaires.

Toute autre stratégie est soit inopérante soit inefficace et peut conduire à la défaite selon le niveau.
4	Structure du jeu

4.1	Histoire

Un jeune système immunitaire prend soin paisiblement d’un corps sain, les problèmes sont rares et souvent bénins,
sa vie est sans histoire.
 
Un jour, alors que la crise financière fait rage, sont hôte perd son travail et se voit contraint de vivre dans la rue.
S’ensuit alors une longue descente aux enfers qui mettra notre pauvre système immunitaire à rude épreuve. 

Nourriture infectée trouvée dans les poubelles, abus de substances nocives, morsures de parasites contagieux…
Toutes les menaces auxquelles le système devra faire face lui permettront, s’il s’en sort victorieux, 
d’apprendre à se protéger et de permettre à son hôte reconnaissant de retrouver le chemin de la rédemption.

4.2	Personnages

On distinguera 6 personnages ou types de personnages : 
- Le système immunitaire : contrôlé par le joueur. C’est le héros.
- L’hôte : c’est le corps humain dans lequel se passe le jeu. 
- Les cellules : éléments neutres que doit protéger le système immunitaire. Elles sont susceptibles de devenir 
cancéreuses et/ou d’être parasitées par des virus.
- Les bactéries : ennemis qui se divisent et endommagent les cellules.
- Les virus : ennemis qui infectent les cellules pour se reproduire.
- Les cancers : ennemis, cellules corrompues qui se dupliquent et s’agglomèrent pour former des métastases.
Les types d’ennemis seront présents ou non suivant le niveau.



4.3	Niveaux

Niveau 1 : 

Description :
Niveau d’apprentissage, il est destiné à la prise en main des contrôles par le joueur. Il présente la menace 
bactérienne et ses remèdes.
Histoire : 
L’hôte souffre d’une intoxication alimentaire due à la consommation de nourriture impropre. Un grand nombre de 
bactéries se développent dans son estomac et commencent à proliférer. 
Ennemis :
Bactéries.

Niveau 2 : 

Description :
Le joueur connait les contrôles. On le met en présence d’un ennemi différent.
Histoire : 
Après plusieurs nuits passées dehors, l’hôte s’est affaibli et à capté un virus émis par un de ses congénères. 
Il faut l’anéantir avant qu’il ne se développe et contamine tout le corps.
Ennemis :
Virus.

Niveau 3 : 

Description :
Augmentation du challenge. On met le joueur en présence de deux types d’ennemis. Il va devoir choisir  les types 
de leucocytes à projeter.

Histoire : 
Cela fait une année maintenant que l’hôte n’a plus de domicile. L’hiver et l’inaction lui ont donné de mauvaises 
habitudes. A force de fumer et de boire de l’alcool l’hôte commence à tousser, son larynx le brûle. 
Des cellules cancéreuses commencent à se développer. De plus, des bactéries se sont invitées à la fête.
Ennemis :
Cancer, bactéries.

Niveau 4 : 

Description :
Augmentation du challenge. On met le joueur en présence de trois types d’ennemis. Il va devoir choisir efficacement 
les types de leucocytes à projeter.
Histoire : 
Malgré la victoire remportée dans le niveau précédent, un autre foyer cancéreux c’est déclaré plus profondément dans 
la gorge de l’hôte. Et se ne sont plus seulement des cellules cancéreuses et des bactéries mais aussi des virus 
qui ont rejoint la bataille.
Ennemis :
Cancer, bactéries, virus.

Niveau 5: 

Description :
Augmentation du challenge. En plus des trois types d’ennemis il y a un temps limité pour terminer le niveau.
Histoire : 
C’est la dernière ligne droite, l’hôte est parvenu à trouver un logement et un travail. Seulement, les dommages 
que lui a infligé cette vie de misère sont très importants. Il faut se presser si on ne veut pas échouer si près du but. 
Ennemis :
Cancer, bactéries, virus.

5	Etude Comparative

Critères de comparaison :
Dans cette étude, nous présenterons rapidement 4 jeux sérieux, tous basés sur la thématique du fonctionnement du 
système immunitaire, puis nous ferons la comparaison de ces jeux aux choix faits pour le développement de notre jeu 
selon les critères suivants :
- Quel est le public cible ? Est-il vraiment en mesure d'appréhender le contenu sérieux du jeu ?
- Comment sont amenées les connaissances à enseigner ?
- La jouabilité est-elle adaptée au jeu et au public cible ?
- L’univers graphique permet-il d’immerger suffisamment le joueur dans le jeu pour le garder concentré et lui 
donner envie de continuer à jouer ?


5.1	Leukos War 

Leukos War est un jeu ludo-éducatif créé par une équipe d’étudiants de l’école isart digital.
C’est un jeu flash d’action-aventure qui a pour but de sensibiliser les adolescents et jeunes adultes sur l’importance 
du don de sang, de plaquettes, de moelle osseuse ou d’organes.

Histoire :
Le petit Bob joue sur la plage. Il est pris d’un malaise et tombe essoufflé.
Il est atteint de leucémie et doit trouver un donneur très vite.
On incarne l’escadron du général Leukos, en charge du maintien de l’ordre à l’intérieur du corps de Bob et notre 
objectif est de lutter contre la maladie qui vient de se déclarer et de l’anéantir.

Design:
Leukos war est un jeu 2D. Il reconstitue l’intérieur du corps humain de manière simple, coloré et stylisé toon afin 
de dédramatiser le sujet et l’aborder de manière amusante mais compréhensible.

Gameplay :
La partie se déroule sous forme de missions. Entre chaque mission le général Leukos explique les différents rôles 
des “héros”.
En fonction des missions, le joueur incarnera :
-Le globule rouge qui tire des bulles d'oxygène pour réoxigéner l’organisme.
-La plaquette qui permet de cautériser les plaies de l’organisme.

5.2	Re-Mission 

Re-Mission est un jeu sérieux sorti en 2006 qui cible les adolescents et jeunes adultes atteints de cancer. Il a 
pour objectif de conduire les patients à avoir un comportement positif et ainsi améliorer l’efficacité des traitements 
contre le cancer.

Histoire :
Le joueur commande un nanobot qui s’appelle Roxxi et qui voyage dans les corps de patient ayant le cancer. Ce nanobot
permet de détruire les cellules cancéreuses, combattre les infections bactériennes et gérer les effets secondaires 
du traitement contre le cancer.

Design:
Re-mission est un jeu 3D où le corps humain est représenté de manière assez réaliste ce qui permet au joueur de 
s’immerger encore plus dans le jeu.



Gameplay :
Re-Mission est un TPS (Third-Person Shooters). Le joueur combat les infections grâce à un choix d’arme varié comme 
le “chemoblaster”, le “radiation gun” et “l’antibiotic rocket”.
Il doit aussi vérifier la santé du patient et reporter chaque symptôme au docteur West. 
Chacun des 20 niveaux a été créé de manière à informer le patient sur toute une liste de traitements variés, leurs
modes de fonctionnement, et l’importance de maintenir un suivi strict de ces traitements.

5.3	Immune System Defender 

Immune System Defender est un jeu éducatif où l’on incarne un soldat des forces de défense du système immunitaire.
Son rôle est de défendre un être humain contre une infection bactérienne. 

Histoire :
Un être humain s’est planté une écharde dans le doigt, l’infection commence à se répandre. Il faut vite l'arrêter.

Design:
Immune System Defender est un jeu 2D plutôt simpliste. On peut voir les cellules se déplacer dans le système sanguin 
du corps humain qui est représenté par un fond rouge.

Gameplay :
Le joueur a 2 missions à compléter : 
- dans la première il devra amener une équipe de granulocytes à combattre contre les bactéries envahissant le système
sanguin.
- dans la seconde mission, le joueur commande, en plus des granulocytes, une armée de macrophages  et cellules 
dendritiques pour stopper l’invasion des bactéries.

A chaque début de mission, le joueur est briefé sur son objectif par le général macrophage et sur le fonctionnement 
des cellules du système immunitaire.

Le déplacement des cellules se fait à la souris : on sélectionne une cellule, puis  sans relâcher le bouton de 
la souris, on la “drag” dans une direction, quand le bouton de la souris est relâché, la cellule est envoyé dans 
la direction inverse.

5.4	Immune War 

Immune War est un jeu éducatif 2D développé par Claude Duprat.
Le but du joueur est d’aider le système immunitaire à vaincre les virus, les bactéries, et les cellules cancéreuses.
Histoire :
Les virus, bactéries et cellules cancéreuses se propagent, il faut les éliminer.

Design :
Immune War est un jeu 2D qui représente un ensemble de cellule et de vaisseau sanguin.

Gameplay :
Le joueur peut à tout moment sélectionner une cellule du système immunitaire pour la diriger.
Il a le choix entre 3 cellules :
1.	Les anticorps : marquent les éléments à détruire pour que les macrophages et les cellules-T puissent intervenir.
2.	Les macrophages : peuvent détruire les virus et les bactéries qui circulent dans les vaisseaux sanguins.
3.	Les cellules-T : peuvent détruire les cellules infestées, et parfois les cellules cancéreuses.


5.5	Choix effectués dans Pathogen Annihilation 

Public cible :
Pour Pathogen Annihilation nous avons décidé de faire un jeu éducatif qui ciblera en particulier, et comme 
tous les jeux cité plus haut, les adolescents. En effet, pour comprendre le fonctionnement, même simplifié, 
du système immunitaire, il faut au minimum quelques bases de biologie qui ne sont enseignées qu’à partir du collège.
Comment sont amenées les connaissances à enseigner
L’objectif sérieux du jeu est de faire connaître les principales menaces et les moyens de défense du système 
immunitaires pour les contrer. Pour atteindre cet objectif, nous avons divisé notre jeu en niveau, et pour 
chaque niveau, le joueur apprendra une nouvelle information à travers un bref briefing qu’il devra utiliser pour
arriver à bout du jeu. On constate que cette stratégie est présente dans Leukos War, Re-Mission et Immune 
System Defender. Seul Immune War n’adopte pas ce système de briefing et plonge directement le joueur dans l’action,
ce dernier peut se retrouver perdu, ne sachant quoi faire et “condamné” à aller lire la documentation du jeu pour 
pouvoir avancer.
La jouabilité est-elle adaptée au jeu et au public cible ?
La jouabilité du jeu est un facteur très important. Dans un jeu comme Immune System Defense, le système de 
déplacement des cellules peut rebuter plus d’un joueur car trop compliqué et trop “lourd” lorsque le joueur doit
déplacer toute une armée de cellule. C’est pourquoi dans Pathogen Annihilation nous avons décidé de développer un
système simple, intuitif et réactif à la façon du jeu geometry wars(non décrit ici car jeu non sérieux) qui devrait
être adapté à n’importe quel joueur du public cible.
L’univers graphique permet-il d’immerger suffisamment le joueur dans le jeu pour le garder concentré et lui donner 
envie de continuer à jouer ?

Notre jeu aura un gameplay 2D, ce choix a été motivé principalement pour simplifier le développement du jeu dû 
à une contrainte de temps. Mais même si un jeu 3D comme Re-Mission permet au joueur une immersion totale grâce 
à une représentation détaillée du corps humain, on remarque qu’un jeu 2D comme Leukos war qui a une réalisation 
soignée n’a rien a lui envier et parvient très bien à faire passer son message sans perdre l’attention du joueur. 
A l’inverse Immune War et Immune Defense System sont des jeux moins poussé au niveau des graphismes et le joueur 
arrive moins à rentrer dans le jeu.
