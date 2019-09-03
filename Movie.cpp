/*
 * Estructura de Dades. Laboratori.
 * Pràctica 3: Arbres binaris
 */

/* 
 * File:    Movie.cpp
 * Authors: Carla Morral, Oscar Lacasta
 */

#include <iomanip>
#include <string>
#include <sstream>

#include "Movie.h"

using namespace std;


// Constructor per defecte
Movie::Movie() {
    this->movieID = 0;
    this->title = "";
    this->rating = 0;
}

// Constructor amb paràmetres
Movie::Movie(int movieID, string title, float rating) {
    this->movieID = movieID;
    this->title = title;
    this->rating = rating;
}

// Constructor de còpia
Movie::Movie(const Movie& orig) {
    this->movieID = orig.movieID;
    this->title = orig.title;
    this->rating = orig.rating;
}

// Destructor
Movie::~Movie() {
    
}


/*
 * Consultors
 */

// Retorna el ID de la Movie
int Movie::getMovieID() const {
    return movieID;
}

// Retorna el títol de la Movie
string Movie::getTitle() const {
    return title;
}

// Retorna la puntuació de la Movie
float Movie::getRating() const {
    return rating;
}

// Retorna la puntuació de la Movie, amb la precisió decimal especificada, com un string
string Movie::getRating(int i) const {
    stringstream r;
    r << fixed << setprecision(i) << rating;
    return r.str();
}

// Retorna un string amb el contingut de la Movie
string Movie::toString() const {
    string str = "";
    str += to_string(movieID) + "::" + title + "::" + getRating(2);
    return str;
}


/*
 * Modificadors
 */

// Permet canviar el ID de la Movie
void Movie::setMovieID(int movieID) {
    this->movieID = movieID;
}

// Permet canviar el títol de la Movie
void Movie::setTitle(string title) {
    this->title = title;
}

// Permet canviar la puntuació de la Movie
void Movie::setRating(float rating) {
    this->rating = rating;
}


/*
 * Altres
 */

// Sobrecarreguem l'operador per tal de poder imprimir un objecte Movie amb "std::cout" 
ostream& operator<<(ostream& out, const Movie& orig) {
    return out << orig.toString();
}
