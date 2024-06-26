#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();
        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        iterator(Node<Key,Value>* ptr);
        friend class BinarySearchTree<Key, Value>;
        //iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    void del(Node<Key, Value>* root);
    int treeHeight(Node<Key, Value>* root) const;
    bool balHelp(Node<Key, Value>* root) const;

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = NULL;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    if (rhs.current_ == current_) return true;
    else if (rhs.current_ == NULL || current_ == NULL) return false;
    return current_->getKey() == rhs.current_->getKey(); //??
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    if (rhs.current_ == current_) return false;
    else if (rhs.current_ == NULL || current_ == NULL) return true;
    return current_->getKey() != rhs.current_->getKey(); //??

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    //??
    //Node<Key, Value>* ret = current_;
    if (current_ == NULL);
    else if (current_->getRight() != NULL) {
        current_ = current_->getRight();
        if (current_->getLeft() != NULL) {
            current_ = current_->getLeft();
            while (current_->getLeft() != NULL) current_ = current_->getLeft();
        }
    }
    else {
        while (current_->getParent() != NULL
        && current_->getParent()->getLeft() != current_) {
            current_ = current_->getParent();
        }
        if (current_->getParent() == NULL) current_ = NULL;
        else current_ = current_->getParent();
    }
    return *this;
    //right subtree, go right until there's a left subtree
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    //std::cout << "init find" << std::endl;
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    Key k = keyValuePair.first;
    Value v = keyValuePair.second;
    //bool bruh = false;
    Node<Key, Value>* in = new Node<Key, Value>(k, v, NULL);
    //std::cout << in->getValue() << std::endl;
    if (root_ == NULL) {
        root_ = in;
        //std::cout << in->getValue() << " is the root." << std::endl;
        return;
    }
    Node<Key, Value>* cur = root_;
    while (in->getParent() == NULL) {
        //std::cout << "Cur: " << cur->getKey() << std::endl;
        //std::cout << "In: " << in->getKey() << std::endl;

        if (cur != NULL && in->getKey() < cur->getKey()) { //smaller
            if (cur->getLeft() == NULL) {
                //std::cout << in->getKey() << " becomes left child of " << cur->getKey() << std::endl;
                in->setParent(cur);
                cur->setLeft(in);
                //bruh = true;
            }
            else {
                //std::cout << cur->getLeft() << std::endl;
                cur = cur->getLeft();
            }
        }
        else if (cur != NULL && in->getKey() > cur->getKey()) { //larger
            if (cur->getRight() == NULL) {
                //std::cout << in->getKey() << " becomes right child of " << cur->getKey() << std::endl;
                in->setParent(cur);
                cur->setRight(in);
                //bruh = true;
            }
            else cur = cur->getRight();
        }
        else { //equal
            //if (cur == NULL) throw std::overflow_error("cur is bad");
            //if (in == NULL) throw std::overflow_error("in is bad");
            //std::cout << cur->getValue() << std::endl; //<< " edited to " << keyValuePair.second <<  ". Parent is " << cur->getParent()->getValue() << std::endl;
            cur->setValue(in->getValue());
            delete in;
            return;
            //bruh = true;
        }
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    Node<Key, Value>* rem = internalFind(key);
    //std::cout << rem << std::endl;

    if (rem == NULL);
    else if (rem->getParent() == NULL && rem->getLeft() == NULL && rem->getRight() == NULL) { //root case
        delete rem;
        root_ = NULL;
        BinarySearchTree<Key, Value>::root_ = NULL;
    }
    else if (rem->getLeft() == NULL && rem->getRight() == NULL) {
        if (rem->getParent()->getLeft() == rem) {
            //std::cout << "left leaf node deleted" << std::endl;
            rem->getParent()->setLeft(NULL);
        }
        else rem->getParent()->setRight(NULL);
        delete rem;
    }
    else if (rem->getLeft() == NULL && rem->getRight() != NULL) { //one child (right)
        if (rem->getParent() == NULL) {
            rem->getRight()->setParent(NULL);
            root_ = rem->getRight();
            BinarySearchTree<Key, Value>::root_ = rem->getRight();
        }
        else if (rem->getParent()->getLeft() == rem) {
            rem->getParent()->setLeft(rem->getRight());
            rem->getRight()->setParent(rem->getParent());
        }
        else {
            rem->getParent()->setRight(rem->getRight());
            rem->getRight()->setParent(rem->getParent());
        }
        delete rem;
    }
    else if (rem->getLeft() != NULL && rem->getRight() == NULL) { //one child (left)
        if (rem->getParent() == NULL) {
            rem->getLeft()->setParent(NULL);
            root_ = rem->getLeft();
            BinarySearchTree<Key, Value>::root_ = rem->getLeft();
        }
        else if (rem->getParent()->getLeft() == rem) {
            rem->getParent()->setLeft(rem->getLeft());
            rem->getLeft()->setParent(rem->getParent());
        }
        else {
            rem->getParent()->setRight(rem->getLeft());
            rem->getLeft()->setParent(rem->getParent());
        }
        delete rem;
    }
    else { //two children
        //std::cout << "Predecessor: " << predecessor(rem)->getKey() << std::endl;
        Node<Key, Value>* s = predecessor(rem);
        nodeSwap(rem, s);
        //std::cout << rem->getKey() << " initiating second remove instance" << std::endl;
        //guarantees that rem has one or no children

        if (rem->getLeft() == NULL && rem->getRight() == NULL) {
            if (rem->getParent()->getLeft() == rem) {
                //std::cout << "left leaf node deleted" << std::endl;
                rem->getParent()->setLeft(NULL);
            }
            else rem->getParent()->setRight(NULL);
            delete rem;
        }

        else if (rem->getLeft() == NULL && rem->getRight() != NULL) { //one child (right)
            if (rem->getParent() == NULL) {
                rem->getRight()->setParent(NULL);
                root_ = rem->getRight();
                BinarySearchTree<Key, Value>::root_ = rem->getRight();
            }
            else if (rem->getParent()->getLeft() == rem) {
                rem->getParent()->setLeft(rem->getRight());
                rem->getRight()->setParent(rem->getParent());
            }
            else {
                rem->getParent()->setRight(rem->getRight());
                rem->getRight()->setParent(rem->getParent());
            }
            delete rem;
        }

        else if (rem->getLeft() != NULL && rem->getRight() == NULL) { //one child (left)
            if (rem->getParent() == NULL) {
                rem->getLeft()->setParent(NULL);
                root_ = rem->getLeft();
                BinarySearchTree<Key, Value>::root_ = rem->getLeft();
            }
            else if (rem->getParent()->getLeft() == rem) {
                rem->getParent()->setLeft(rem->getLeft());
                rem->getLeft()->setParent(rem->getParent());
            }
            else {
                rem->getParent()->setRight(rem->getLeft());
                rem->getLeft()->setParent(rem->getParent());
            }
            delete rem;
        }

        //std::cout << s->getKey() << " second remove instance done" << std::endl;
    }

}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    Node<Key, Value>* ret = NULL;
    if (current == NULL) return NULL;
    ret = current;
    if (current->getLeft() != NULL) {
        ret = current->getLeft();
        while (ret->getRight() != NULL) ret = ret->getRight();
    }
    else {
        while (ret->getParent() != NULL && ret->getParent()->getRight() != ret) {
            ret = ret->getParent();
        }
        ret = ret->getParent();
    }
    return ret;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    del(root_);
    root_ = NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::del(Node<Key, Value>* root) {
    if (root == NULL) return;
    del(root->getLeft());
    del(root->getRight());
    delete root;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    Node<Key, Value>* bro = root_;
    if (bro == NULL) return NULL;
    while (bro->getLeft() != NULL) {
        bro = bro->getLeft();
    }
    return bro;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    if (root_ == NULL) return NULL;
    Node<Key, Value>* ret = root_;
    while (ret != NULL && key != ret->getKey()) {
        if (key < ret->getKey()) {
            ret = ret->getLeft();
            //std::cout << "going left..." << std::endl;
        }
        else if (key > ret->getKey()) {
            ret = ret->getRight();
            //std::cout << ret << std::endl;
        }
    }
    return ret;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    //std::cout << root_ << std::endl;
    return balHelp(root_);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::balHelp(Node<Key, Value>* root) const {
    if (root == NULL) return true;
    //cout << treeHeight(root->left) << " " << treeHeight(root->right) << endl;
    int diff = treeHeight(root->getLeft()) - treeHeight(root->getRight());
    if (diff >= -1 && diff <= 1) {
        //bool get = root->getLeft() == NULL;
        return balHelp(root->getLeft()) && balHelp(root->getRight());
    }
    return false;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::treeHeight(Node<Key, Value>* root) const {
    if (root == NULL) return 0;
    return std::max(1 + treeHeight(root->getLeft()), 1 + treeHeight(root->getRight()));
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
