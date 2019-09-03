/*
 * Estructura de Dades. Laboratori.
 * Pràctica 3: Arbres binaris
 */

/* 
 * File:    BSTMovieFinder.cpp
 * Authors: Carla Morral, Oscar Lacasta
 */

#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "BinarySearchTree.h"
#include "Movie.h"
#include "BSTMovieFinder.h"

using namespace std;


// Constructor
BSTMovieFinder::BSTMovieFinder() {
    this->tree = new BinarySearchTree<Movie>();
}

// Constructor de còpia
BSTMovieFinder::BSTMovieFinder(const BSTMovieFinder& orig) {
    this->tree = new BinarySearchTree<Movie>(*orig.tree);
}

// Destructor
BSTMovieFinder::~BSTMovieFinder() {
    this->tree->~BinarySearchTree();
}


/*
 * Consultors
 */

// Funció que retorna l'objecte Movie associat al ID especificat
const Movie& BSTMovieFinder::findMovie(int movieID) const {
    
    const Movie *movie = tree->getSearch(movieID);
    if (movie != nullptr) {
        return *movie;
    }
    else {
        throw invalid_argument("L'arbre no conté cap Movie amb l'ID " + to_string(movieID));
    }
}

// Funció que retorna un string amb les dades de la Movie associada al ID especificat
string BSTMovieFinder::showMovie(int movieID) const {
    
    try {
        return findMovie(movieID).toString();
    }
    catch (const exception& e) {
        return e.what();
    }
}

// Funció que retorna el títol de la Movie associada al ID especificat
string BSTMovieFinder::findTitleMovie(int movieID) const {
    
    try {
        return findMovie(movieID).getTitle();
    }
    catch (const exception& e) {
        return e.what();
    }
}

// Funció que retorna el rating de la Movie associada al ID especificat
float BSTMovieFinder::findRatingMovie(int movieID) const {
    
    try {
        return findMovie(movieID).getRating();
    }
    catch (const exception& e) {
        return -1; // Si la Movie no es troba en l'arbre
    }
}


/*
 * Modificadors
 */

// Funció que rep el nom d'un fitxer i emmagatzema el seu contingut en un arbre
void BSTMovieFinder::appendMovies(string fileName) {
    
    ifstream file;
    string line, ext = ".txt";
    int movieID; string title; float rating;
    
    if (fileName.empty() || fileName.substr( (fileName.size() - ext.size()) % fileName.size() ) != ext) {
        throw invalid_argument("Invalid file name.");
    }
    
    file.open(fileName);
    if (file.is_open()) {
        while (!file.eof()) {
            getline(file, line);
            if (!line.empty()) {
                // Obtenim les dades de la Movie i la insertem a l'arbre
                parseMovieData(line, movieID, title, rating);
                insertMovie(movieID, title, rating);
            }
        }
        file.close();
    }
    else {
        throw invalid_argument("Could not open the specified file.");
    }
}

// Funció que rep les dades d'una Movie i la inserta a l'arbre
void BSTMovieFinder::insertMovie(int movieID, string title, float rating) {
    
    Movie newMovie(movieID, title, rating);
    try {
        tree->insert(movieID, newMovie);
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }
}


/*
 * Altres
 */

// Funció que retorna l'adreça de l'arbre
BinarySearchTree<Movie>* BSTMovieFinder::getTree() const {
    return tree;
}

// Funció que mostra les Movies de l'arbre per ID en ordre creixent
void BSTMovieFinder::printInorder() const {
    
    if (tree->isEmpty()) {
        cout << "L'arbre està buit. No conté cap Movie." << endl;
    }
    else {
        cout << "Mostrant l'arbre per ID en ordre creixent (InOrdre):" << "\n-----" << endl;
        printInorder(tree->root(), 0);
    }
}


/*
 * Private functions
 */

// Funció recursiva de suport per a mostrar les Movies de l'arbre seguint un recorregut en inordre
int BSTMovieFinder::printInorder(const NodeTree<Movie>* p, int count) const {
    
    if (p->hasLeft()) {
        count = printInorder(p->getleft(), count);
    }
    
    // Quan portem 40 Movies impreses, preguntem a l'usuari si vol continuar
    if (count > 0 && count % 40 == 0) {
        string input;
        cout << "Movies mostrades: " << count << endl;
        cout << "Vols seguir mostrant l'arbre (Y/[N])? "; getline(cin, input);
        if (input != "Y" && input != "y") {
            count = -1;
        }
    }
    
    // Si el count és -1 acabem, sinó, continuem imprimint
    if (count == -1) {
        return -1;
    }
    else {
        cout << p->getValue() << endl;
        count++;
    }
    
    if (p->hasRight()) {
        count = printInorder(p->getright(), count);
    }
    
    // Retornem el nombre de Movies que portem imprimides
    return count;
}

// Funció que tracta un string per extreure'n la dades de la Movie
void BSTMovieFinder::parseMovieData(string data, int& movieID, string& title, float& rating) const {
    vector<string> vect(3);
    string token, delimiter = "::";
    size_t pos = 0;
    
    for (int i = 0; i < 3, pos != data.npos; i++) {
        pos = data.find(delimiter);
        token = data.substr(0, pos);
        vect[i] = token;
        data.erase(0, pos + delimiter.length());
    }
    
    stringstream(vect[0]) >> movieID;
    title = vect[1];
    stringstream(vect[2]) >> rating;
}
