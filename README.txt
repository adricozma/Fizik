Projet de Programmation 
Alexandre Nozet (PH) et Adrian Cozma (PH)

Nous avons fait presque tous les exercices obligatoires (Sauf testIntégrateur 1), et implementé plusieurs extensions.
En moyenne nous avons passé passé 8h/semaine/personne sur ce projet.
Nous avons une version graphique avec Qt.

Comment se déplacer?:
Poour se déplacer, il suffit d'utiliser la souris et les touches, "W,A,S,D"  pour les translations et
"Q,E" pour les rotations.

Comment simuler un Système?: 

- Tout d'abbord ouvrir le répertoire projet_final dans le terminal: (cd "")
- Une fois dans ce répertoire écrire la commande: "qmake"
- Une fois la commande "qmake" effectuée les differents "makefile" sont géneres automtiquement 
  donc il ne reste plus qu'à ouvrir le répertoire désiré pour la simulation désirée:
	- "text" pour la simulation textuelle.
	- "Qt_GL" pout la simulation "3D"
- Et ensuite écrire la commande "make"
	- Pour lancer la simulation textuelle écrire "./Simulations_text"
	- Pour lancer la simulation "3D"  écrire "./Simulations"
	Ce sont les noms des applications respectives.

  De base, les données de la simulation textuelle s'affichent dans le terminal "cout", mais il est
  possible de les afficher dans un "ficier.txt" qui se trouvera dans le répertoire "text/gnuplot"
  La façon de changer de manière d'affichage est expliquée dans le "main_text.cc" qui se trouve
  aussi dans le répertoire "text".
  Dans "main_text.cc" il y plusieurs scènes differents qu'il suffit de commenter ou décommenter.
  Tous les fichiers nécessaires à la simmulation textuelle se trouvent dans ce repertoire.
  
- De même pour la simmulation "3D" pour changer de scène, il faut commenter ou décommenter les scènes 
  qui se trouvent dans "Qt_GL/main_qt_gl.cc"
  Toutes les classes propres à cette simmulation sont contenues dans ce même répertoire "Qt_GL"
  Dès que vous lancez la simmulation de Terrain mettez sur "pause" et déplacez vous au niveau de la montagne.

- Le répertoire "general" contient toutes les classes qui ne dependent pas d'un mode de simulation spécifique.
  Vous trouverez là dedans tous les "ObjetsMobile", "Obstacle", "ChampForces", "ObjetCompose", "Dessinable", "SupportADessin".
  (dans leur ".cc" et ".h" respectifs)
 
- Le répertoire "height_data" contient les "fichier.txt" contenant les données d'altitude pour la simulation des "Terrain".
  Il contient aussi un autre répertoire "data_non_projete" avec les données d'altitude brutes extraites d'internet, sans la projection.
  Vous pouvez utiliser le programme "Projection.cc" pour tester les projections. Encore une fois tout est expliqué dans ce même fichier.
  Il suffit de le compiler et de l'executer.
  
Pour créer d'autres simulations, dans les "main_text.cc" et "main_qt_gl.cc" il y à un espace vide libre à vous de simuler ce que vous voulez.
Les construc
  
Complement:
	Pour les simulation "3D", il y a deux façons d'afficher les "Terrain", il faut jutste aller dans le repértoire 		"Qt_GL" et ouvrir le fichier "vue_open_gl.cc",trouver la fonction "dessine(Terrain)" et commenter ou 		décommenter une partie du code. Il y a le choix entre mesh ou points. Se sont deux façons 
	difféerentes d'afficher les terrains.
Tous les fichiers Tests se trouvent dans le répertoire "general".
