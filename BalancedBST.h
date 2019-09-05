#ifndef BALANCEDBST_H
#define BALANCEDBST_H

#include <iostream>
#include <stdexcept>

#include "NodeTree.h"

using namespace std;


template <class Type>
class BalancedBST {
    
public:
    BalancedBST();
    BalancedBST(const BalancedBST& orig);
    virtual ~BalancedBST();
    
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
    int calculateHeight(const NodeTree<Type>* node) const;
    
    /* Funcions de suport específiques del BalancedBST (AVL) */
    int getBalanceFactor(const NodeTree<Type>* node) const;
    void rightRotation(NodeTree<Type>* node);
    void leftRotation(NodeTree<Type>* node);
    void balanceTree(NodeTree<Type>* unbalanced, int key);
    
    /* Atributs */
    NodeTree<Type>* pRoot;
    
};


// Constructor
template <class Type>
BalancedBST<Type>::BalancedBST() {
    
    pRoot = nullptr;
    cout << "Arbre binari balancejat creat" << endl;
}


// Constructor de còpia (recorrem l'arbre original en preordre)
template <class Type>
BalancedBST<Type>::BalancedBST(const BalancedBST& orig) {
    
    cout << "Constructor de còpia (Arbre binari balancejat)" << endl;
    
    if (orig.isEmpty()) {
        pRoot = nullptr;
    }
    else {
        pRoot = recursiveCopy(orig.pRoot, nullptr);
    }
}


// Destructor (recorrem l'arbre en postordre)
template <class Type>
BalancedBST<Type>::~BalancedBST() {
    
    if (!isEmpty()) {
        postDelete(pRoot);
    }
    cout << "Arbre binari balancejat destruït" << endl;
}



/*
 * Consultors
 */


// Funció que retorna el nombre de nodes que hi ha a l'arbre binari
template <class Type>
int BalancedBST<Type>::size() const {
    
    return size(pRoot);
}


// Funció que retorna l'alçada de l'arbre
template <class Type>
int BalancedBST<Type>::getHeight() const {
    
    return getHeight(pRoot); // Si l'arbre està buit, la seva alçada és 0
}


// Funció que retorna l'adreça del root
template <class Type>
NodeTree<Type>* BalancedBST<Type>::root() const {
    
    return pRoot;
}

template <class Type>
const Type* BalancedBST<Type>::getSearch(int key) const{
    
    if (isEmpty()) {
        return nullptr;
    }
    NodeTree<Type> *match = searchParent(pRoot,key);
    return (match->getKey() == key)? &match->getValue() : nullptr;
    
}


// Funció que retorna cert si l'arbre binari està buit
template <class Type>
bool BalancedBST<Type>::isEmpty() const {
    
    return pRoot == nullptr;
}


// Funció que cerca una clau en l'arbre i retorna cert si la troba
template <class Type>
bool BalancedBST<Type>::search(int key) const {
    
    if (isEmpty()) {
        return false;
    }
    return searchParent(pRoot, key)->getKey() == key;
}


// Funció que mostra el contingut de l’arbre seguint un recorregut en preordre
template <class Type>
void BalancedBST<Type>::printPreorder() const {
    
    if (isEmpty()) {
        cout << "L'arbre està buit. No conté cap pel·lícula" << endl;
    }
    else {
        cout << "Preordre = {";
        printPreorder(pRoot);
        cout << "\b\b" << "}" << endl;
    }
}


// Funció que mostra el contingut de l’arbre seguint un recorregut en postordre
template <class Type>
void BalancedBST<Type>::printPostorder() const {
    
    if (isEmpty()) {
        cout << "L'arbre està buit. No conté cap pel·lícula" << endl;
    }
    else {
        cout << "Postordre = {";
        printPostorder(pRoot);
        cout << "\b\b" << "}" << endl;
    }
}


// Funció que mostra el contingut de l’arbre seguint un recorregut en inordre
template <class Type>
void BalancedBST<Type>::printInorder() const {
    
    if (isEmpty()) {
        cout << "L'arbre està buit. No conté cap pel·lícula" << endl;
    }
    else {
        cout << "Inordre = {";
        printInorder(pRoot);
        cout << "\b\b" << "}" << endl;
    }
 }



/*
 * Modificadors
 */


// Funció que permet afegir un nou node a l'arbre binari
template <class Type>
void BalancedBST<Type>::insert(int key,const Type& value) {
    
    // Si l'arbre està buit, afegim l'arrel inicial
    if (isEmpty()) {
        NodeTree<Type> *arrel = new NodeTree<Type>(key,value);
        pRoot = arrel;
    }
    else {
        NodeTree<Type> *parent = searchParent(pRoot, key);
        
        // Si la pel·lícula ja es troba dins de l'arbre, llançem una excepció
        if (parent->getKey() == key) {
            throw invalid_argument("EXCEPTION: L'arbre ja conté la pel·lícula: " + to_string(key));
        }
        
        // Creem el nou node i li assignem el seu pare
        NodeTree<Type> *nouNode = new NodeTree<Type>(key,value);
        nouNode->setParent(parent);
        
        // Assignem el nou node com a fill del pare
        if (key < parent->getKey()) {
            parent->setLeft(nouNode);
        }
        else {
            parent->setRight(nouNode);
        }
        
        // Només hem de modificar altures i balancejar l'arbre si el node inserit no té germà
        if (!(parent->hasLeft() && parent->hasRight())) {
            balanceTree(parent, key);
        }
    }
}


// Funció que intercanvia els fills (el dret per l'esquerra) de cada node intern de l'arbre
template <class Type>
void BalancedBST<Type>::mirror() {
    
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
int BalancedBST<Type>::size(NodeTree<Type>* p) const {
    
    if (p == nullptr) {
        return 0;
    }
    else {
        return 1 + size(p->getleft()) + size(p->getright());
    }
}


// Funció de suport que retorna l'alçada d'un node a partir del seu atribut alçada
template <class Type>
int BalancedBST<Type>::getHeight(NodeTree<Type>* p) const {
    
    return (p == nullptr)? 0 : p->getHeight();
}


// Funció de suport per a mostrar el contingut de l’arbre seguint un recorregut en preordre
template <class Type>
void BalancedBST<Type>::printPreorder(NodeTree<Type>* p) const {
    
    cout << p->getvalue() << ", ";
    
    if (p->hasLeft()) {
        printPreorder(p->getLeft());
    }
    if (p->hasRight()) {
        printPreorder(p->getRight());
    }
}


// Funció de suport per a mostrar el contingut de l’arbre seguint un recorregut en postordre
template <class Type>
void BalancedBST<Type>::printPostorder(NodeTree<Type>* p) const {
    
    if (p->hasLeft()) {
        printPostorder(p->getLeft());
    }
    if (p->hasRight()) {
        printPostorder(p->getRight());
    }
    
    cout << p->getvalue() << ", ";
}


// Funció de suport per a mostrar el contingut de l’arbre seguint un recorregut en inordre
template <class Type>
void BalancedBST<Type>::printInorder(NodeTree<Type>* p) const {
    
    if (p->hasLeft()) {
        printInorder(p->getLeft());
    }
    
    cout << p->getvalue() << ", ";
    
    if (p->hasRight()) {
        printInorder(p->getRight());
    }
}


// Funció de suport per al destructor de l'arbre
template <class Type>
void BalancedBST<Type>::postDelete(NodeTree<Type>* p) {
    
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
void BalancedBST<Type>::mirror(NodeTree<Type>* p) {
    
    changeChildren(p);
    
    if (p->hasLeft()) {
        mirror(p->getLeft());
    }
    if (p->hasRight()) {
        mirror(p->getRight());
    }
}



/*
 * Private functions (Altres)
 */


// Funció recursiva de suport per al constructor de còpia de l'arbre
template <class Type>
NodeTree<Type>* BalancedBST<Type>::recursiveCopy(const NodeTree<Type>* arrel, NodeTree<Type>* pivot) const {
    
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


// Funció recursiva de suport per a buscar el node pare quan volem inserir un value a l'arbre
// També serà utilitzada per la funció search()
// No permetem duplicats: si l'value ja es troba dins de l'arbre, la funció retorna la direcció del node que el conté
template <class Type>
NodeTree<Type>* BalancedBST<Type>::searchParent(NodeTree<Type>* parent, int key) const {
    
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
void BalancedBST<Type>::changeChildren(NodeTree<Type>* p) {
    
    if (!p->isExternal()) {
        NodeTree<Type> *left = p->getleft();
        p->setLeft(p->getright());
        p->setRight(left);
    }
}


// Funció que calcula l'alçada d'un node a partir de l'alçada dels seus fills
template <class Type>
int BalancedBST<Type>::calculateHeight(const NodeTree<Type>* node) const {
    
    return 1 + max(getHeight(node->getleft()), getHeight(node->getright()));

}



/*
 * Private functions (AVL tree specific)
 */


// Funció que calcula i retorna el factor de balanç d'un node
template <class Type>
int BalancedBST<Type>::getBalanceFactor(const NodeTree<Type>* node) const {
    
    return getHeight(node->getright()) - getHeight(node->getleft());
}


// Funció que realitza una rotació a la dreta sobre el node (que "baixarà")
template <class Type>
void BalancedBST<Type>::rightRotation(NodeTree<Type>* node) {
    
    // Assignem el pare del node com a pare del seu fill esquerre
    // Si aquest pare no és nullptr, li assignem el seu nou fill
    node->getleft()->setParent(node->getparent());
    if (!node->isRoot()) {
        if (node->getparent()->getleft() == node) {
            node->getparent()->setLeft(node->getleft());
        } else {
            node->getparent()->setRight(node->getleft());
        }
    }
    else {
        // Hem d'actualitzar el punter al root
        pRoot = node->getleft();
    }
    
    // Assignem el fill esquerre del node com el seu pare
    node->setParent(node->getleft());
    
    // Assignem el fill dret del nou pare com a fill esquerre del node
    // Si aquest fill no és nullptr, li assignem el seu nou pare
    node->setLeft(node->getparent()->getright());
    if (node->hasLeft()) {
        node->getleft()->setParent(node);
    }
    
    // Finalment, assignem el node com a fill dret del seu nou pare
    node->getparent()->setRight(node);
    
    // Calculem les noves altures dels nodes afectats, o sigui,
    // el que ha "baixat" (node) i el que ha "pujat" (que era el fill esquerre i ara és el seu pare)
    node->setHeight(calculateHeight(node));
    node->getparent()->setHeight(calculateHeight(node->getparent()));
}


// Funció que realitza una rotació a l'esquerra sobre el node (que "baixarà")
template <class Type>
void BalancedBST<Type>::leftRotation(NodeTree<Type>* node) {
    
    // Assignem el pare del node com a pare del seu fill dret
    // Si aquest pare no és nullptr, li assignem el seu nou fill
    node->getright()->setParent(node->getparent());
    if (!node->isRoot()) {
        if (node->getparent()->getleft() == node) {
            node->getparent()->setLeft(node->getright());
        } else {
            node->getparent()->setRight(node->getright());
        }
    }
    else {
        // Hem d'actualitzar el punter al root
        pRoot = node->getright();
    }
    
    // Assignem el fill dret del node com el seu pare
    node->setParent(node->getright());
    
    // Assignem el fill esquerre del nou pare com a fill dret del node
    // Si aquest fill no és nullptr, li assignem el seu nou pare
    node->setRight(node->getparent()->getleft());
    if (node->hasRight()) {
        node->getright()->setParent(node);
    }
    
    // Finalment, assignem el node com a fill esquerre del seu nou pare
    node->getparent()->setLeft(node);
    
    // Calculem les noves altures dels nodes afectats, o sigui,
    // el que ha "baixat" (node) i el que ha "pujat" (que era el fill dret i ara és el seu pare)
    node->setHeight(calculateHeight(node));
    node->getparent()->setHeight(calculateHeight(node->getparent()));
}


// Funció que es crida al final d'una inserció
// Calcula altures, factors de balanç, i balanceja l'arbre aplicant les rotacions necessàries
template <class Type>
void BalancedBST<Type>::balanceTree(NodeTree<Type>* unbalanced, int key) {
    
    int bf, newHeight;
    bool stop = false;
    
    // Anem mirant els pares cap a dalt, comprovant altures i factors de balanç
    while (unbalanced != nullptr && bf != -2 && bf != 2 && !stop) {
        bf = getBalanceFactor(unbalanced);
        if (bf != -2 && bf != 2) {
            newHeight = calculateHeight(unbalanced);
            if (unbalanced->getHeight() != newHeight) {
                unbalanced->setHeight(newHeight);
                unbalanced = unbalanced->getparent();
            } else {
                stop = true;
            }
        }
    }
    
    // Cas Left-Left: Rotació simple
    if (bf == -2 && key < unbalanced->getleft()->getKey()) {
        rightRotation(unbalanced);
    }
    // Cas Right-Right: Rotació simple
    else if (bf == 2 && key > unbalanced->getright()->getKey()) {
        leftRotation(unbalanced);
    }
    // Cas Left-Right: Rotació doble
    else if (bf == -2 && key > unbalanced->getleft()->getKey()) {
        leftRotation(unbalanced->getleft());
        rightRotation(unbalanced);
    }
    // Cas Right-Left: Rotació doble
    else if (bf == 2 && key < unbalanced->getright()->getKey()) {
        rightRotation(unbalanced->getright());
        leftRotation(unbalanced);
    }
}


#endif /* BALANCEDBST_H */
