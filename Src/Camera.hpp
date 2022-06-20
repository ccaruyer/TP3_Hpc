#ifndef _CAMERA_HPP
#define _CAMERA_HPP

#include <iostream>
using namespace std;

#include "Point.hpp"
#include "Vecteur.hpp"
#include "Scene.hpp"
#include "Image.hpp"

class Camera {
private:
  Point position;/**< Position de la caméra */
  Point cible;/**< Point visé par la caméra. Ce point sera au centre de l'image */
  float distance;/**< distance de l'origine de la caméra au plan image */

public:
  /**
   * Construit une caméra positionnée aux coordonnées (0, 0, 2).
   * Le point visé est l'origine du repère (0, 0, 0) et la distance au plan
   * image est fixée à 2.
   */
  Camera();

  /**
   * Détruit la caméra.
   */
  ~Camera();

  /**
   *  Calcul de l'image d'une scène telle que vue par la caméra. La méthode
   * de calcul est le lancer de rayons récursif.
   * @param sc la scène virtuelle à utiliser pour la génération de l'image
   * @param im l'image à générer par lancer de rayons
   * @param profondeur nombre de réflexions à prendre en compte dans le
   * processus récursif.
   */
  void genererImage(const Scene& sc, Image& im, int profondeur);


  /**
   * Affichage des paramètres d'une caméra sur un flot de sortie,
   * dans un format lisible par un utilisateur humain.
   * @param out le flot de sortie
   * @param c la caméra à afficher
   * @return le flot modifié
   */
  friend ostream& operator<<(ostream& out, const Camera& c);

    /**
   *  Calcul de l'image d'une scène telle que vue par la caméra. La méthode
   * de calcul est le lancer de rayons récursif.
   * @param sc la scène virtuelle à utiliser pour la génération de l'image
   * @param im l'image à générer par lancer de rayons
   * @param profondeur nombre de réflexions à prendre en compte dans le
   * processus récursif.
   * @param nbThreads nombre de thread
   */
    void genererImageParallele(const Scene& sc, Image& im, int profondeur, int nbThreads);

};

#endif
