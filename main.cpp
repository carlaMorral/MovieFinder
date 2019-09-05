#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "AVLMovieFinder.h"
#include "BSTMovieFinder.h"

using namespace std;

/*Get data*/
void seleccionarFitxer(BSTMovieFinder* bst, string nomFitxer) {
    clock_t t;
    
    cout << "Reading " << nomFitxer << " ..." << endl;
    
    try {
        t = clock();
        bst->appendMovies(nomFitxer);
        t = (clock() - t);
        cout << "Temps d'inserció en BST: " << ((float)t)/CLOCKS_PER_SEC << " segons" << endl;
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }
}

/*Get data*/
void seleccionarFitxer(AVLMovieFinder* avl, string nomFitxer) {
    clock_t t;
    
    cout << "Reading " << nomFitxer << " ..." << endl;
    
    try {
        t = clock();
        avl->appendMovies(nomFitxer);
        t = (clock() - t);
        cout << "Temps d'inserció en AVL: " << ((float)t)/CLOCKS_PER_SEC << " segons" << endl;
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }
}

/*Read data*/
void llegirFitxerCerca(const BSTMovieFinder& bst) {
    ifstream file;
    string line, fileName = "data/cercaPelicules.txt";
    clock_t t;
    int movieID, count = 0;
    
    file.open(fileName);
    if (file.is_open()) {
        t = clock();
        while (!file.eof()) {
            getline(file, line);
            if (!line.empty()) {
                stringstream(line) >> movieID;
                if (bst.getTree()->search(movieID)) {
                    count++;
                }
            }
        }
        t = (clock() - t);
        file.close();
        cout << "Search time using BST: " << ((double)t)/CLOCKS_PER_SEC << " seconds" << endl;
        cout << "Number of found movies: " << count << endl;
    }
    else {
        cout << "Could not open the specified file." << endl;
    }
}

/*Read data*/
void llegirFitxerCerca(const AVLMovieFinder& avl) {
    ifstream file;
    string line, fileName = "data/cercaPelicules.txt";
    clock_t t;
    int movieID, count = 0;
    
    file.open(fileName);
    if (file.is_open()) {
        t = clock();
        while (!file.eof()) {
            getline(file, line);
            if (!line.empty()) {
                stringstream(line) >> movieID;
                if (avl.getTree()->search(movieID)) {
                    count++;
                }
            }
        }
        t = (clock() - t);
        file.close();
        cout << "Search time using AVL: " << ((double)t)/CLOCKS_PER_SEC << " seconds" << endl;
        cout << "Number of found movies: " << count << endl;
    }
    else {
        cout << "Could not open the specified file." << endl;
    }
}


/*
 * Main function
 */
int main(int argc, char** argv) {
    
    cout << "OPERATIONS WITH SMALL FILE: " << endl;
    cout << endl;
    
    BSTMovieFinder* bst = new BSTMovieFinder();
    AVLMovieFinder* avl = new AVLMovieFinder();

    seleccionarFitxer(bst, "data/movie_rating_small.txt");
    seleccionarFitxer(avl, "data/movie_rating_small.txt");

    cout << endl;

    llegirFitxerCerca(*bst);
    llegirFitxerCerca(*avl);

    delete bst;
    delete avl;
    
    cout << endl;
    cout << "OPERATIONS WITH BIG FILE: " << endl;
    cout << endl;
    
    BSTMovieFinder* bst2 = new BSTMovieFinder();
    AVLMovieFinder* avl2 = new AVLMovieFinder();    
    
    seleccionarFitxer(bst2, "data/movie_rating.txt");
    seleccionarFitxer(avl2, "data/movie_rating.txt");
    
    cout << endl;
    
    llegirFitxerCerca(*bst2);
    llegirFitxerCerca(*avl2);
    
    delete bst2;
    delete avl2;
    
    return 0;
}
