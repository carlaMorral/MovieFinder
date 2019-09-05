template <class Type>
class NodeTree {
    
public:
    NodeTree(int key, const Type& value);
    NodeTree(const NodeTree& orig);
    virtual ~NodeTree();
    
    /* Consultors */
    NodeTree<Type>* getright() const;
    NodeTree<Type>* getleft() const;
    NodeTree<Type>* getparent() const;
    bool hasRight() const;
    bool hasLeft() const;
    bool isRoot() const;
    bool isExternal() const;
    const Type& getValue() const;
    int getKey() const;
    int getHeight() const;
    
    /* Modificadors */
    void setHeight(int h);
    void setKey(int newKey);
    void setValue(const Type& newValue);
    void setRight(NodeTree<Type>* newRight);
    void setLeft(NodeTree<Type>* newLeft);
    void setParent(NodeTree<Type>* newParent);
    
private:
    NodeTree<Type>* pParent;
    NodeTree<Type>* pLeft;
    NodeTree<Type>* pRight;
    Type value;
    int key;
    int height;
    
};


// Constructor
template <class Type>
NodeTree<Type>::NodeTree(int key, const Type& value) {
    
    this->pParent = nullptr;
    this->pLeft = nullptr;
    this->pRight = nullptr;
    this->value = value;
    this->key = key;
    this->height = 1;
}

// Constructor de còpia
template <class Type>
NodeTree<Type>::NodeTree(const NodeTree& orig) {
    
    this->pParent = nullptr;
    this->pLeft = nullptr;
    this->pRight = nullptr;
    this->value = std::move(orig.value);
    this->key = orig.getKey();
    this->height = orig.height;

}

// Destructor
template <class Type>
NodeTree<Type>::~NodeTree() {
    
}  


/*
 * Consultors
 */

// Retorna l'adreça del fill dret del node
template <class Type>
NodeTree<Type>* NodeTree<Type>::getright() const {
    
    return pRight;
}

// Retorna l'adreça del fill esquerra del node
template <class Type>
NodeTree<Type>* NodeTree<Type>::getleft() const {
    
    return pLeft;
}

// Retorna l'adreça del pare del node
template <class Type>
NodeTree<Type>* NodeTree<Type>::getparent() const {
    
    return pParent;
}

// Retorna cert si el node té fill dret
template <class Type>
bool NodeTree<Type>::hasRight() const {
    
    return pRight != nullptr;
}

// Retorna cert si el node té fill esquerra
template <class Type>
bool NodeTree<Type>::hasLeft() const {
        
    return pLeft != nullptr;
}

// Retorna cert si és el node arrel del arbre
template <class Type>    
bool NodeTree<Type>::isRoot() const {
    
    return pParent == nullptr;
}

// Retorna cert si és un node extern
template <class Type>
bool NodeTree<Type>::isExternal() const {
    
    return pLeft == nullptr && pRight == nullptr;
}

// Retorna l'element emmagatzemat en el node
template <class Type>
const Type& NodeTree<Type>::getValue() const {
    
    return value;
}

// Retorna la clau (ID) emmagatzemada en el node
template <class Type>
int NodeTree<Type>::getKey() const {
    
    return key;
}

template <class Type>
int NodeTree<Type>::getHeight() const{
    
    return height;
    
}


/*
 * Modificadors
 */


template <class Type>
void NodeTree<Type>::setHeight(int h){
    
    height = h;
    
}

// Permet canviar la clau (ID) emmagatzemada en el node
template <class Type>
void NodeTree<Type>::setKey(int newKey) {
    
    this->key = newKey;
}

// Permet canviar l'element emmagatzemat en el node
template <class Type>
void NodeTree<Type>::setValue(const Type& newValue) {
    
    this->value = newValue;
}

// Modifica l'adreça del fill dret del node
template <class Type>
void NodeTree<Type>::setRight(NodeTree<Type>* newRight) {
    
    pRight = newRight;
}

// Modifica l'adreça del fill esquerra del node
template <class Type>
void NodeTree<Type>::setLeft(NodeTree<Type>* newLeft) {
    
    pLeft = newLeft;
}

// Modifica l'adreça del pare del node
template <class Type>
void NodeTree<Type>::setParent(NodeTree<Type>* newParent) {
    
    pParent = newParent;
}


#endif /* NODETREE_H */
