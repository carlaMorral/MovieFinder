/*
 * Estructura de Dades. Laboratori.
 * Pràctica 3: Arbres binaris
 */

/* 
 * File:    BSTMovieFinder.h
 * Authors: Carla Morral, Oscar Lacasta
 */

#ifndef BSTMOVIEFINDER_H
#define BSTMOVIEFINDER_H

#include <string>

#include "BinarySearchTree.h"
#include "Movie.h"

using namespace std;


class BSTMovieFinder {
    
public:
    BSTMovieFinder();
    BSTMovieFinder(const BSTMovieFinder& orig);
    virtual ~BSTMovieFinder();
    
    // Consultors
    const Movie& findMovie(int) const;
    string showMovie(int) const;
    string findTitleMovie(int) const;
    float findRatingMovie(int) const;
    
    // Modificadors
    void appendMovies(string);
    void insertMovie(int, string, float);
    
    // Altres
    BinarySearchTree<Movie>* getTree() const;
    void printInorder() const;
    
private:
    int printInorder(const NodeTree<Movie>*, int) const;
    void parseMovieData(string, int&, string&, float&) const;
    
    // Atributs
    BinarySearchTree<Movie> *tree;
    
};


#endif /* BSTMOVIEFINDER_H */
