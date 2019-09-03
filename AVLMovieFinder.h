/*
 * Estructura de Dades. Laboratori.
 * Pràctica 3: Arbres binaris
 */

/* 
 * File:    BSTMovieFinder.h
 * Authors: Carla Morral, Oscar Lacasta
 */

#ifndef AVLMOVIEFINDER_H
#define AVLMOVIEFINDER_H

#include <string>


#include "BalancedBST.h"
#include "Movie.h"

using namespace std;


class AVLMovieFinder {
    
public:
    AVLMovieFinder();
    AVLMovieFinder(const AVLMovieFinder& orig);
    virtual ~AVLMovieFinder();
    
    // Consultors
    const Movie& findMovie(int) const;
    string showMovie(int) const;
    string findTitleMovie(int) const;
    float findRatingMovie(int) const;
    
    // Modificadors
    void appendMovies(string);
    void insertMovie(int, string, float);
    
    // Altres
    BalancedBST<Movie>* getTree() const;
    void printInorder() const;
    
private:
    int printInorder(const NodeTree<Movie>*, int) const;
    void parseMovieData(string, int&, string&, float&) const;
    
    // Atributs
    BalancedBST<Movie> *tree;
    
};


#endif /* AVLMOVIEFINDER_H */
