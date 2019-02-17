# Infographie
Projet d'infographique   
Cage de foot dans un terrain. Animation d'une balle tirée par un joueur. Public dans le stade animé (si possible)

# Utilisation de Objloader.h
***Attention ne prend pas encore en compte les textures sur les objets***  
Permet de charger des fichiers en .obj (Wavefront) dans la scène. 
Comment le faire fonctionner, dans blender:
* Dans blender sélectionner son objet à exporter, aller en mode édition (edit-mode), appuyer sur `u` et sélectionner `Unwarp`. 
* Lorsque tu exporte ton fichier sélectionne l'option `Include UVs`, pour savoir pourquoi aller sur ce [lien](https://blender.stackexchange.com/questions/46260/triangulate-faces-obj-format-problem)  

Dans le code cpp:
* Ne pas oublier d'include `#include "Objloader.h"`
* A l'endroit où vous créez et initialisez vos objets il faut entrer le code suivant pour charger son modèle 3D 
```c++
Objloader obj("chemin vers mon ficher");
Shape mon_objet = obj.getShape()
```
 * Pour initialiser son objet il faut appeler la fonction init soit
 ```c++
obj.init();
```
* Puis dans la boulce principale pour afficher l'objet il faut utiliser la fonction show avec programId du shader
```c++
mon_obj.show(shader->getProgramID());
```

# Liens

[Tutoriel](http://www.opengl-tutorial.org/fr/) complet sur OpenGL.  
[Utiliser](https://guides.github.com/activities/hello-world/) GitHub.  
Un [autre]( https://openclassrooms.com/fr/courses/2342361-gerez-votre-code-avec-git-et-github) tutoriel GitHub en français (OpenClassrooom)
