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

// Copy Constructor
BSTMovieFinder::BSTMovieFinder(const BSTMovieFinder& orig) {
    this->tree = new BinarySearchTree<Movie>(*orig.tree);
}

// Destructor
BSTMovieFinder::~BSTMovieFinder() {
    this->tree->~BinarySearchTree();
}


/*
 * Consultants
 */

// Returns the movie object associeted to the specified id
const Movie& BSTMovieFinder::findMovie(int movieID) const {
    
    const Movie *movie = tree->getSearch(movieID);
    if (movie != nullptr) {
        return *movie;
    }
    else {
        throw invalid_argument("L'arbre no conté cap Movie amb l'ID " + to_string(movieID));
    }
}

// Returns a string with the data of the associated movie to the specified id. 
string BSTMovieFinder::showMovie(int movieID) const {
    
    try {
        return findMovie(movieID).toString();
    }
    catch (const exception& e) {
        return e.what();
    }
}

// Returns the title of the associated movie to the specified id. 
string BSTMovieFinder::findTitleMovie(int movieID) const {
    
    try {
        return findMovie(movieID).getTitle();
    }
    catch (const exception& e) {
        return e.what();
    }
}

// Returns the rating of the associated movie to the specified id.  
float BSTMovieFinder::findRatingMovie(int movieID) const {
    
    try {
        return findMovie(movieID).getRating();
    }
    catch (const exception& e) {
        return -1; 
    }
}

//Receives a file name and saves its content in a tree
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

void BSTMovieFinder::insertMovie(int movieID, string title, float rating) {
    
    Movie newMovie(movieID, title, rating);
    try {
        tree->insert(movieID, newMovie);
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }
}

//Returns the adress of the tree
BinarySearchTree<Movie>* BSTMovieFinder::getTree() const {
    return tree;
}

//Prints the movies of the tree by id
void BSTMovieFinder::printInorder() const {
    
    if (tree->isEmpty()) {
        cout << "Empty tree" << endl;
    }
    else {
        cout << "Printing the tree:" << "\n-----" << endl;
        printInorder(tree->root(), 0);
    }
}


/*
 * Private functions
 */

int BSTMovieFinder::printInorder(const NodeTree<Movie>* p, int count) const {
    
    if (p->hasLeft()) {
        count = printInorder(p->getleft(), count);
    }
    
    //When 40 movies are printed we ask the user if he wants to continue.
    if (count > 0 && count % 40 == 0) {
        string input;
        cout << "Movies mostrades: " << count << endl;
        cout << "Vols seguir mostrant l'arbre (Y/[N])? "; getline(cin, input);
        if (input != "Y" && input != "y") {
            count = -1;
        }
    }

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
