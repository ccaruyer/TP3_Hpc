#include "Camera.hpp"
#include "Rayon.hpp"
#include <thread>


Camera::Camera(){
  position = Point(0.0, 0.0, 2.0);;
  cible = Point(0.0, 0.0, 0.0);
  distance = 2.0;
}

struct zone {
    int x, y; // coordonnées du coin supérieur gauche de la zone
    int largeur, hauteur; // dimensions de la zone
};

Camera::~Camera(){}

void Camera::genererImage(const Scene& sc, Image& im, int profondeur){

  // Calcul des dimensions d'un pixel par rapport
  // à la résolution de l'image - Les pixels doivent être carrés
  // pour éviter les déformations de l'image.
  // On fixe :
  // - les dimensions en largeur de l'écran seront comprises dans [-1, 1]
  // - les dimensions en hauteur de l'écran soront comprises dans [-H/L, H/L]
  float cotePixel = 2.0/im.getLargeur();

  // Pour chaque pixel
  for(int i=0; i<im.getLargeur(); i++){
    for(int j=0; j<im.getHauteur(); j++){
      
      // calcul des coordonnées du centre du pixel
      float milieuX = -1 + (i+0.5f)*cotePixel;
      float milieuY =  (float)im.getHauteur()/(float)im.getLargeur()
	- (j+0.5f)*cotePixel;
 
      Point centre(milieuX, milieuY, 0);
      
      // Création du rayon
      Vecteur dir(position, centre);
      dir.normaliser();
      Rayon ray(position, dir);
      
      // Lancer du rayon primaire
      Intersection inter;
      if(sc.intersecte(ray, inter)){
	im.setPixel(i, j, inter.getCouleur(sc, position, profondeur));
      }
      else
	im.setPixel(i, j, sc.getFond());

    }// for j

  }// for i
}


ostream& operator<<(ostream& out, const Camera& c){

  out << " position = " << c.position << " - cible = " << c.cible;
  out <<  " - distance = " << c.distance << flush;
  return out;
}


void Camera::genererImageParallele(const Scene& sc, Image& im, int profondeur, int nbThreads){

    //hauteur de l'image = im.getHauteur()/3
    //largeur de l'image = im.getLargeur()
    float cotePixel = 2.0/im.getLargeur();

    double H = im.getHauteur()/nbThreads;

    for (int t = 1; t < nbThreads; t++) {

        // Pour chaque pixel
        for (int i = 0; i < im.getLargeur(); i++) {
            for (int j = 0 ; j < (H * t); j++) {

                // calcul des coordonnées du centre du pixel
                float milieuX = -1 + (i + 0.5f) * cotePixel;
                float milieuY = (float) (im.getHauteur()/nbThreads) / (float) im.getLargeur()
                                - (j + 0.5f) * cotePixel;

                Point centre(milieuX, milieuY, 0);

                // Création du rayon
                Vecteur dir(position, centre);
                dir.normaliser();
                Rayon ray(position, dir);

                // Lancer du rayon primaire
                Intersection inter;
                if (sc.intersecte(ray, inter)) {
                    im.setPixel(i, j, inter.getCouleur(sc, position, profondeur));
                } else
                    im.setPixel(i, j, sc.getFond());

            }// for j

        }// for i
    }
}