/*
 * Estructura de Dades. Laboratori.
 * Pràctica 3: Arbres binaris
 */

/* 
 * File:    BinarySearchTree.h
 * Authors: Carla Morral, Oscar Lacasta
 */

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <stdexcept>

#include "NodeTree.h"

using namespace std;


template <class Type>
class BinarySearchTree {
    
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& orig);
    virtual ~BinarySearchTree();
    
    /* Consultors */
    int size() const;
    int getHeight() const;
    NodeTree<Type>* root() const;
    const Type* getSearch(int key) const;
    bool isEmpty() const;
    bool search(int key) const;
    void printInorder() const;
    void printPreorder() const;
    void printPostorder() const;
    
    /* Modificadors */
    void insert(int key, const Type& value);
    void mirror();
    
private:
    int size(NodeTree<Type>* p) const;
    int getHeight(NodeTree<Type>* p) const;
    void printPreorder(NodeTree<Type>* p) const;
    void printPostorder(NodeTree<Type>* p) const;
    void printInorder(NodeTree<Type>* p) const;
    void postDelete(NodeTree<Type>* p);
    void mirror(NodeTree<Type>* p);
    
    /* Altres funcions de suport */
    NodeTree<Type>* recursiveCopy(const NodeTree<Type>* arrel, NodeTree<Type>* pivot) const;
    NodeTree<Type>* searchParent(NodeTree<Type>* parent, int key) const;
    void changeChildren(NodeTree<Type>* p);
    
    /* Atributs */
    NodeTree<Type>* pRoot;
    
};


// Constructor
template <class Type>
BinarySearchTree<Type>::BinarySearchTree() {
    
    pRoot = nullptr;
    cout << "Arbre binari creat" << endl;
}


// Constructor de còpia (recorrem l'arbre original en preordre)
template <class Type>
BinarySearchTree<Type>::BinarySearchTree(const BinarySearchTree& orig) {
    
    cout << "Constructor de còpia (Arbre binari)" << endl;
    
    if (orig.isEmpty()) {
        pRoot = nullptr;
    }
    else {
        pRoot = recursiveCopy(orig.pRoot, nullptr);
    }
}


// Destructor (recorrem l'arbre en postordre)
template <class Type>
BinarySearchTree<Type>::~BinarySearchTree() {
    
    if (!isEmpty()) {
        postDelete(pRoot);
    }
    cout << "Arbre binari destruït" << endl;
}



/*
 * Consultors
 */


// Funció que retorna el nombre de nodes que hi ha a l'arbre binari
template <class Type>
int BinarySearchTree<Type>::size() const {
    
    return size(pRoot);
}


// Funció que retorna l'alçada de l'arbre
template <class Type>
int BinarySearchTree<Type>::getHeight() const {
    
    if (isEmpty()) {
        return -1; // Ja que l'alçada és 0 si només hi ha el node arrel
    }
    else {
        return getHeight(pRoot);
    }
}


// Funció que retorna l'adreça del root
template <class Type>
NodeTree<Type>* BinarySearchTree<Type>::root() const {
    
    return pRoot;
}


// Funció que cerca un element en l'arbre i el retorna
template <class Type>
const Type* BinarySearchTree<Type>::getSearch(int key) const {
    
    if (isEmpty()) {
        return nullptr;
    }
    NodeTree<Type> *match = searchParent(pRoot, key);
    return (match->getKey() == key)? &match->getValue() : nullptr;
}


// Funció que retorna cert si l'arbre binari està buit
template <class Type>
bool BinarySearchTree<Type>::isEmpty() const {
    
    return pRoot == nullptr;
}


// Funció que cerca un element en l'arbre i retorna cert si el troba
template <class Type>
bool BinarySearchTree<Type>::search(int key) const {
    
    if (isEmpty()) {
        return false;
    }
    return searchParent(pRoot, key)->getKey() == key;
}


// Funció que mostra el contingut de l’arbre seguint un recorregut en preordre
template <class Type>
void BinarySearchTree<Type>::printPreorder() const {
    
    if (isEmpty()) {
        cout << "L'arbre està buit. No conté cap element" << endl;
    }
    else {
        cout << "Preordre = {";
        printPreorder(pRoot);
        cout << "\b\b" << "}" << endl;
    }
}


// Funció que mostra el contingut de l’arbre seguint un recorregut en postordre
template <class Type>
void BinarySearchTree<Type>::printPostorder() const {
    
    if (isEmpty()) {
        cout << "L'arbre està buit. No conté cap element" << endl;
    }
    else {
        cout << "Postordre = {";
        printPostorder(pRoot);
        cout << "\b\b" << "}" << endl;
    }
}


// Funció que mostra el contingut de l’arbre seguint un recorregut en inordre
template <class Type>
void BinarySearchTree<Type>::printInorder() const {
    
    if (isEmpty()) {
        cout << "L'arbre està buit. No conté cap element" << endl;
    }
    else {
        cout << "Inordre = {";
        printInorder(pRoot, 0);
        cout << "\b\b" << "}" << endl;
    }
 }



/*
 * Modificadors
 */


// Funció que permet afegir un nou node a l'arbre binari
template <class Type>
void BinarySearchTree<Type>::insert(int key, const Type& value) {
    
    // Si l'arbre està buit, afegim l'arrel
    if (isEmpty()) {
        NodeTree<Type> *arrel = new NodeTree<Type>(key, value);
        pRoot = arrel;
    }
    else {
        NodeTree<Type> *parent = searchParent(pRoot, key);
        
        // Si l'element ja es troba dins de l'arbre, llançem una excepció
        if (parent->getKey() == key) {
            throw invalid_argument("EXCEPTION: L'arbre ja conté un element amb l'ID " + to_string(key));
        }
        
        // Creem el nou node i li assignem el seu pare
        NodeTree<Type> *nouNode = new NodeTree<Type>(key, value);
        nouNode->setParent(parent);
        
        // Assignem el nou node com a fill del pare
        if (key < parent->getKey()) {
            parent->setLeft(nouNode);
        }
        else {
            parent->setRight(nouNode);
        }
        
        // Assignem l'altura del nou node
        nouNode->setHeight(parent->getHeight() + 1);
        
    }
}


// Funció que intercanvia els fills (el dret per l'esquerra) de cada node intern de l'arbre
template <class Type>
void BinarySearchTree<Type>::mirror() {
    
    if (isEmpty()) {
        throw invalid_argument("EXCEPTION: L'arbre està buit");
    }
    mirror(pRoot);
    cout << "Arbre mirall creat" << endl;
}



/*
 * Private functions
 */


// Funció recursiva de suport per a calcular el nombre de nodes que té l'arbre binari
template <class Type>
int BinarySearchTree<Type>::size(NodeTree<Type>* p) const {
    
    if (p == nullptr) {
        return 0;
    }
    else {
        return 1 + size(p->getleft()) + size(p->getright());
    }
}


// Funció recursiva de suport per a trobar l'alçada de l'arbre
template <class Type>
int BinarySearchTree<Type>::getHeight(NodeTree<Type>* p) const {
    
    int left = 0, right = 0;
    
    if (!p->isExternal()) {
        if (p->hasLeft()) {
            left = 1 + getHeight(p->getleft());
        }
        if (p->hasRight()) {
            right = 1 + getHeight(p->getright());
        }
        return max(left, right);
    }
    
    return 0;
}


// Funció de suport per a mostrar el contingut de l’arbre seguint un recorregut en preordre
template <class Type>
void BinarySearchTree<Type>::printPreorder(NodeTree<Type>* p) const {
    
    cout << p->getValue() << ", ";
    
    if (p->hasLeft()) {
        printPreorder(p->getleft());
    }
    if (p->hasRight()) {
        printPreorder(p->getright());
    }
}


// Funció de suport per a mostrar el contingut de l’arbre seguint un recorregut en postordre
template <class Type>
void BinarySearchTree<Type>::printPostorder(NodeTree<Type>* p) const {
    
    if (p->hasLeft()) {
        printPostorder(p->getleft());
    }
    if (p->hasRight()) {
        printPostorder(p->getright());
    }
    
    cout << p->getValue() << ", ";
}


// Funció de suport per a mostrar el contingut de l’arbre seguint un recorregut en inordre
template <class Type>
void BinarySearchTree<Type>::printInorder(NodeTree<Type>* p) const {
    
    if (p->hasLeft()) {
        printInorder(p->getleft());
    }
    
    cout << p->getValue() << ", ";
    
    if (p->hasRight()) {
        printInorder(p->getright());
    }
}


// Funció de suport per al destructor de l'arbre
template <class Type>
void BinarySearchTree<Type>::postDelete(NodeTree<Type>* p) {
    
    if (p->hasLeft()) {
        postDelete(p->getleft());
    }
    
    if (p->hasRight()) {
        postDelete(p->getright());
    }
    
    // Eliminem el node (és extern, no té fills)
    delete p;
}


// Funció de suport per a l'operació mirall de l'arbre
template <class Type>
void BinarySearchTree<Type>::mirror(NodeTree<Type>* p) {
    
    changeChildren(p);
    
    if (p->hasLeft()) {
        mirror(p->getleft());
    }
    if (p->hasRight()) {
        mirror(p->getright());
    }
}



/*
 * Private functions (Altres)
 */


// Funció recursiva de suport per al constructor de còpia de l'arbre
template <class Type>
NodeTree<Type>* BinarySearchTree<Type>::recursiveCopy(const NodeTree<Type>* arrel, NodeTree<Type>* pivot) const {
    
    // Creem un nou node idèntic al node, apuntat per "arrel", de l'arbre a copiar
    NodeTree<Type> *nouNode = new NodeTree<Type>(*arrel);
    
    // Assignem l'adreça de "pivot", que apunta a l'últim node afegit al nou arbre, com a pare del nou node
    nouNode->setParent(pivot);
    
    // Si el nou node no és el root, assignem el nou node com a fill del node pare
    if (!nouNode->isRoot()) {
        if (nouNode->getKey() <  pivot->getKey()) {
            pivot->setLeft(nouNode);
        }
        else {
            pivot->setRight(nouNode);
        }
    }
    
    // Actualitzem l'adreça de "pivot"
    pivot = nouNode;
    
    // Tornem a cridar a la funció per als nodes fills de "arrel"
    if (arrel->hasLeft()) {
        recursiveCopy(arrel->getleft(), pivot);
    }
    if (arrel->hasRight()) {
        recursiveCopy(arrel->getright(), pivot);
    }
    
    // Retornem l'adreça del node creat
    return nouNode;
}


// Funció recursiva de suport per a buscar el node pare quan volem inserir un element a l'arbre
// També serà utilitzada per les funcions search() i getSearch()
// No permetem duplicats: si l'element ja es troba dins de l'arbre, la funció retorna la direcció del node que el conté
template <class Type>
NodeTree<Type>* BinarySearchTree<Type>::searchParent(NodeTree<Type>* parent, int key) const {
    
    // Tenint en compte que el fill esquerre és més petit que el pare i que el fill dret és més gran que el pare,
    // anem buscant mentre el node tingui fills i no l'haguem trobat
    if (parent->isExternal() || parent->getKey() == key) {
        return parent;
    }
    else if (key < parent->getKey()) {
        return (parent->getleft() == nullptr)? parent : searchParent(parent->getleft(), key);
    }
    else {
        return (parent->getright() == nullptr)? parent : searchParent(parent->getright(), key);
    }
}


// Funció de suport per a l'operació mirall que intercanvia el fill dret d'un node pel seu fill esquerre
template <class Type>
void BinarySearchTree<Type>::changeChildren(NodeTree<Type>* p) {
    
    if (!p->isExternal()) {
        NodeTree<Type> *left = p->getleft();
        p->setLeft(p->getright());
        p->setRight(left);
    }
}


#endif /* BINARYSEARCHTREE_H */
