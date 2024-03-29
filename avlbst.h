#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};


/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{
    //std::cout << "constructor balance: " << static_cast<int16_t>(balance_) << std::endl;
}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
    //std::cout << "new balance: " << static_cast<int16_t>(balance_) << std::endl;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    //AVLTree();
    //~AVLTree();
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
    //typename BinarySearchTree<Key, Value>::iterator find(const Key & k) const;

    //typename BinarySearchTree<Key, Value>::iterator begin() const;

protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    //AVLNode<Key, Value> *getSmallestNode() const;

    //void clear();

    // Add helper functions here
    //AVLNode<Key, Value>* internalFind(const Key& k) const;
    void leftRotation(AVLNode<Key, Value>* no);
    void rightRotation(AVLNode<Key, Value>* no);
    void insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);
    void removeFix(AVLNode<Key, Value>* n, int diff);
    //static AVLNode<Key, Value>* predecessor(AVLNode<Key, Value>* current);
    //AVLNode<Key, Value>* root_; //COME BACK TO THIS


};

/*template<class Key, class Value>
AVLTree<Key, Value>::AVLTree()
{
    // TODO
    this->root_ = NULL;
}

template<class Key, class Value>
AVLTree<Key, Value>::~AVLTree()
{
    // TODO
    clear();
}*/

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    Key k = new_item.first;
    Value v = new_item.second;

    //std::cout << "NEW ITEM: " << k << std::endl;
    bool equal = false;

    //bool bruh = false;
    AVLNode<Key, Value>* in = new AVLNode<Key, Value>(k, v, NULL);
    //std::cout << "balance: " << static_cast<int16_t>(in->getBalance()) << std::endl;
    //std::cout << in->getValue() << std::endl;
    if (this->root_ == NULL) {
        //std::cout << "adding root: " << in->getKey() << std::endl;
        this->root_ = in;
        //BinarySearchTree<Key, Value>::root_ = in;
        //std::cout << in->getValue() << " is the root." << std::endl;

        in->setBalance(0);
        //std::cout << "balance of new root: " << static_cast<int16_t>(in->getBalance()) << std::endl;
        //std:: cout << root_->getKey() << std::endl;
        return;
    }
    AVLNode<Key, Value>* cur = static_cast<AVLNode<Key, Value>*>(this->root_);
    while (in->getParent() == NULL) {
        //std::cout << "Cur: " << cur->getKey() << std::endl;
        //std::cout << "In: " << in->getKey() << std::endl;
        if (cur != NULL && in->getKey() < cur->getKey()) { //smaller
            //std::cout << "left child of " << cur->getKey() << " is " << cur->getLeft() << std::endl;
            if (cur->getLeft() == NULL) {
                //std::cout << in->getKey() << " becomes left child of " << cur->getKey() << std::endl;
                in->setParent(cur);
                cur->setLeft(in);
                //bruh = true;
            }
            else {
                //std::cout << cur->getLeft() << std::endl;
                //std::cout << in->getKey() << " is smaller than " << cur->getKey() << std::endl;
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
        else if (cur != NULL && cur->getKey() == in->getKey()) { //equal
            //if (cur == NULL) throw std::overflow_error("cur is bad");
            //if (in == NULL) throw std::overflow_error("in is bad");
            //std::cout << cur->getValue() << std::endl; //<< " edited to " << keyValuePair.second <<  ". Parent is " << cur->getParent()->getValue() << std::endl;
            //std::cout << "added duplicate key. editing value" << std::endl;
            cur->setValue(in->getValue());
            AVLNode<Key, Value>* trash = in;
            in = cur;
            delete trash;
            equal = true;
            break;

            //bruh = true;
        }

    }

    if (!equal) {
        in->setBalance(0);
        if (in->getParent() == NULL);
        else if (in->getParent()->getBalance() == -1 || in->getParent()->getBalance() == 1) in->getParent()->setBalance(0);
        else {
            if (in->getParent()->getLeft() == in) in->getParent()->setBalance(-1);
            else in->getParent()->setBalance(1);
            //std::cout << in->getKey() << "'s parent's balance: " << static_cast<int16_t>(in->getParent()->getBalance()) << std::endl;
            insertFix(in->getParent(), in);
            //if (in->getParent() != NULL) std::cout << in->getParent()->getKey() << "'s balance:" << static_cast<int16_t>(in->getParent()->getBalance()) <<std::endl;
        }
    }
    //std::cout << "added new node " << in->getKey() << ". parent is " << in->getParent() << std::endl;
    //std::cout << "balance of new node: " << static_cast<int16_t>(in->getBalance()) << std::endl;
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    //std::cout << "Tree before removing " << key << std::endl;
    //BinarySearchTree<Key, Value>:: print();
    AVLNode<Key, Value>* rem = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    AVLNode<Key, Value>* remParent = NULL;
    Node<Key, Value>* s = BinarySearchTree<Key, Value>::predecessor(rem);
    int diff = 0;

    if (rem == NULL) return;

    if (rem->getLeft() != NULL && rem->getRight() != NULL) {
        this->nodeSwap(rem, (AVLNode<Key, Value>*) s);
    }

    remParent = rem->getParent();

    //if (rem == NULL);
    if (rem->getParent() == NULL && rem->getLeft() == NULL && rem->getRight() == NULL) { //root
        delete rem;
        this->root_ = NULL;
        //BinarySearchTree<Key, Value>::root_ = NULL;
    }
    else if (rem->getLeft() == NULL && rem->getRight() == NULL) { //leaf node
        //std::cout << "blah" << std::endl;
        if (rem->getParent()->getLeft() == rem) {
            //std::cout << "left leaf node deleted" << std::endl;
            rem->getParent()->setLeft(NULL);
            diff = 1;
        }
        else {
            //std::cout << "right leaf node deleted" << std::endl;
            rem->getParent()->setRight(NULL);
            diff = -1;
        }
        delete rem;
    }
    else if (rem->getLeft() == NULL && rem->getRight() != NULL) { //one child (right)
        if (rem->getParent() == NULL) {
            rem->getRight()->setParent(NULL);
            this->root_ = rem->getRight();
            //BinarySearchTree<Key, Value>::root_ = rem->getRight();
        }
        else if (rem->getParent()->getLeft() == rem) {
            //std::cout << "one right child promoted" << std::endl;
            rem->getParent()->setLeft(rem->getRight());
            rem->getRight()->setParent(rem->getParent());
            diff = 1;
        }
        else {
            //std::cout << "one right child promoted" << std::endl;
            rem->getParent()->setRight(rem->getRight());
            rem->getRight()->setParent(rem->getParent());
            diff = -1;
        }
        delete rem;
    }
    else if (rem->getLeft() != NULL && rem->getRight() == NULL) { //one child (left)
        if (rem->getParent() == NULL) {
            rem->getLeft()->setParent(NULL);
            this->root_ = rem->getLeft();
            //BinarySearchTree<Key, Value>::root_ = rem->getLeft();
        }
        else if (rem->getParent()->getLeft() == rem) {
            rem->getParent()->setLeft(rem->getLeft());
            rem->getLeft()->setParent(rem->getParent());
            diff = 1;
        }
        else {
            rem->getParent()->setRight(rem->getLeft());
            rem->getLeft()->setParent(rem->getParent());
            diff = -1;
        }
        delete rem;
    }
    /*else { //two children
        //std::cout << rem->getKey() << " has two children" << std::endl;
        //std::cout << "Predecessor: " << predecessor(rem)->getKey() << std::endl;
        AVLNode<Key, Value>* s = predecessor(rem);
        std::cout << "before switching, " << rem->getKey() << "'s parent is " << remParent   << std::endl;
        std::cout << "pred parent: " << s->getParent()->getKey() << std::endl;

        nodeSwap(rem, s);
        remParent = rem->getParent();

        std::cout << "after switching, " << rem->getKey() << "'s parent is " << remParent->getKey() << std::endl;
        std::cout << "pred parent: " << s->getParent() << std::endl;
        //std::cout << rem->getKey() << " initiating second remove instance" << std::endl;
        //guarantees that rem has one or no children

        if (rem->getLeft() == NULL && rem->getRight() == NULL) { //leaf node
            std::cout << "after switching with its predecessor, " << rem->getKey() << " is a leaf node" << std::endl;
            if (remParent != NULL) { //setting difference
                if (remParent->getLeft() == rem) {
                    diff = 1;
                    remParent->setLeft(NULL);
                }
                else {
                    diff = -1;
                    remParent->setRight(NULL);
                }
            }
            delete rem;
        }

        else if (rem->getLeft() == NULL && rem->getRight() != NULL) { //one child (right)
            if (rem->getParent() == NULL) {
                rem->getRight()->setParent(NULL);
                root_ = rem->getRight();
                BinarySearchTree<Key, Value>::root_ =  rem->getRight();
            }
            else if (rem->getParent()->getLeft() == rem) {
                if (remParent != NULL) { //setting difference
                    if (remParent->getLeft() == rem) diff = 1;
                    else diff = -1;
                }

                rem->getParent()->setLeft(rem->getRight());
                rem->getRight()->setParent(rem->getParent());
            }
            else {
                if (remParent != NULL) { //setting difference
                    if (remParent->getLeft() == rem) diff = 1;
                    else diff = -1;
                }

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
                if (remParent != NULL) { //setting difference
                    if (remParent->getLeft() == rem) diff = 1;
                    else diff = -1;
                }

                rem->getParent()->setLeft(rem->getLeft());
                rem->getLeft()->setParent(rem->getParent());
            }
            else {
                if (remParent != NULL) { //setting difference
                    if (remParent->getLeft() == rem) diff = 1;
                    else diff = -1;
                }

                rem->getParent()->setRight(rem->getLeft());
                rem->getLeft()->setParent(rem->getParent());
            }
            delete rem;
        }
        //std::cout << s->getKey() << " second remove instance done" << std::endl;
        if (remParent != NULL) std::cout << "remparent: " << remParent->getKey() << std::endl;
    }
    */

    //if (remParent != NULL) std::cout << "remparent: " << remParent->getKey() << std::endl;
    //else std::cout << "remparent is NULL. \n\n";

    //std::cout << "Tree after removing " << key << std::endl;
    //BinarySearchTree<Key, Value>::print();
    //if (remParent != NULL) std::cout << remParent->getKey() << std::endl;
    //std::cout << diff << std::endl;
    removeFix(remParent, diff);
    //std::cout << "remove fix done!" << std::endl;

}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

/*
 * Precondition: p and n are balanced
 * Postcondition: p, n, and g are balanced
 *
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value> *p, AVLNode<Key, Value> *n) {
    //std::cout << "initiate insertFix" << std::endl;
    if (p == NULL || p->getParent() == NULL) return;
    AVLNode<Key, Value>* g = p->getParent();
    if (g->getLeft() == p) { //left child of grandparent
        g->updateBalance(-1);
        //std::cout << "Balance of " << g->getKey() << static_cast<int16_t>(g->getBalance()) << std::endl;
        if (g->getBalance() == 0) {
            //std::cout << "(insertFix) " << g->getKey() << "'s balance is 0." << std::endl;
            return;
        }
        else if (g->getBalance() == -1) {
            //std::cout << "(insertFix) " << g->getKey() << "'s balance is -1." << std::endl;
            insertFix(g, p);
        }
        else if (g->getBalance() == -2) {
            if (p->getLeft() == n) { //zig-zig
                //std::cout << "(insertFix) "<< "zig-ZIG left parent child" << std::endl;
                rightRotation(g);
                g->setBalance(0);
                p->setBalance(0);
            }
            else { //zig-zag
                //std::cout << "(insertFix)"<< "zig-zag left parent child" << std::endl;
                leftRotation(p);
                rightRotation(g);
                //std::cout << p->getKey() << "'s parent: " /*<< p->getParent()->getKey()*/ << std::endl;
                if (n->getBalance() == -1) {
                    p->setBalance(0);
                    g->setBalance(1);
                    n->setBalance(0);
                }
                else if (n->getBalance() == 0) {
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                }
                else if (n->getBalance() == 1) {
                    p->setBalance(-1);
                    g->setBalance(0);
                    n->setBalance(0);
                }
            }
        }
    }

    else if (g->getRight() == p) {
        g->updateBalance(1);
        if (g->getBalance() == 0) {
            //std::cout << "(insertFix) " << g->getKey() << "'s balance is 0." << std::endl;
            return;
        }
        else if (g->getBalance() == 1) insertFix(g, p);
        else if (g->getBalance() == 2) {
            if (p->getRight() == n) { //zig-zig
                //std::cout << "(insertFix) "<< "zig-ZIG right parent child" << std::endl;
                leftRotation(g);
                g->setBalance(0);
                p->setBalance(0);
            }
            else { //zig-zag
                rightRotation(p);
                leftRotation(g);
                //std::cout << "(insertFix) "<< "zig-zag right parent child"<< std::endl;
                //std::cout << p->getKey() << "'s parent: " /*<< p->getParent()->getKey()*/ << std::endl;
                if (n->getBalance() == 1) {
                    p->setBalance(0);
                    g->setBalance(-1);
                    n->setBalance(0);
                }
                else if (n->getBalance() == 0) {
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                }
                else if (n->getBalance() == -1) {
                    p->setBalance(1);
                    g->setBalance(0);
                    n->setBalance(0);
                }
            }
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value> *n, int diff) {
    //if (n != NULL) std::cout << "(removeFix) nparent: " << n->getParent() << std::endl;
    //else std::cout << "n is NULL." << std::endl;

    //std::cout << "init removeFix" << std::endl;
    //if (n != NULL) std::cout << n->getKey() << std::endl;
    if (n == NULL) return;
    int ndiff = 0;
    if (n->getParent() == NULL);
    else if (n->getParent()->getLeft() == n) ndiff = 1;
    else ndiff = -1;
    AVLNode<Key, Value>* p = n->getParent();

    //std::cout << "value of n: " << n->getKey() << std::endl;
    //std::cout << "difference: " << diff << std::endl;

    if (diff == -1) {
        if (n->getBalance() + diff == -2) {
            AVLNode<Key, Value>* c = n->getLeft();
            if (c->getBalance() == -1) { //zig-zig #1
                rightRotation(n);
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p, ndiff);
            }
            else if (c->getBalance() == 0) { //zig-zig #2
                rightRotation(n);
                n->setBalance(-1);
                c->setBalance(1);
            }
            else if (c->getBalance() == 1) { //zig-zag
                AVLNode<Key, Value>* g = c->getRight();
                //std::cerr << c->getRight() << std::endl;
                leftRotation(c);
                rightRotation(n);
                if (g->getBalance() == 1) {
                    n->setBalance(0);
                    c->setBalance(-1);
                    g->setBalance(0);
                }
                else if (g->getBalance() == 0) {
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                else if (g->getBalance() == -1) {
                    n->setBalance(1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                removeFix(p, ndiff);
            }
        }
        else if (n->getBalance() + diff == -1) n->setBalance(-1);
        else if (n->getBalance() + diff == 0) {
            n->setBalance(0);
            removeFix(p, ndiff);
        }
    }
    else if (diff == 1) {
        if (n->getBalance() + diff == 2) {
            AVLNode<Key, Value>* c = n->getRight();
            if (c->getBalance() == 1) { //zig-zig #1
                leftRotation(n);
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p, ndiff);
            }
            else if (c->getBalance() == 0) { //zig-zig #2
                leftRotation(n);
                n->setBalance(1);
                c->setBalance(-1);
            }
            else if (c->getBalance() == -1) { //zig-zag
                AVLNode<Key, Value>* g = c->getLeft();
                rightRotation(c);
                leftRotation(n);
                if (g->getBalance() == -1) {
                    n->setBalance(0);
                    c->setBalance(1);
                    g->setBalance(0);
                }
                else if (g->getBalance() == 0) {
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                else if (g->getBalance() == 1) {
                    n->setBalance(-1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                removeFix(p, ndiff);
            }
        }
        else if (n->getBalance() + diff == 1) {
            //std::cout << "blah" << std::endl;
            n->setBalance(1);
        }
        else if (n->getBalance() + diff == 0) {
            n->setBalance(0);
            removeFix(p, ndiff);
        }
    }
}


/*template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::internalFind(const Key &key) const {
    std::cout << "internal finding" << std::endl;

    if (this->root_ == NULL) return NULL;
    AVLNode<Key, Value>* ret = static_cast<AVLNode<Key, Value>*>(this->root_);
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
}*/

template<class Key, class Value>
void AVLTree<Key, Value>::leftRotation(AVLNode<Key, Value> *no) {
    //BinarySearchTree<Key, Value>::print();
    //std::cout << "initiate leftRotation of " << no->getKey() << std::endl;
    AVLNode<Key, Value>* no_l = no->getRight()->getLeft();
    AVLNode<Key, Value>* no_r = no->getRight();

    //std::cout << "node being rotated: " << no->getKey() << std::endl;
    //std::cout << "node taking its place: " << no_r->getKey() << std::endl;

    if (no->getParent() != NULL) {
        if (no->getParent()->getLeft() == no) no->getParent()->setLeft(no_r);
        else no->getParent()->setRight(no_r);
    }
    no_r->setParent(no->getParent());
    no_r->setLeft(no);
    no->setParent(no_r);
    no->setRight(no_l);
    if (no_l != NULL) no_l->setParent(no);

    /*std::cout << "new g: " << no_r->getParent() << std::endl;
    std::cout << "new p: " << no_r->getKey() << std::endl;
    std::cout << "new c: " << no->getKey() << std::endl;*/

    if (this->root_ == no) {
        //BinarySearchTree<Key, Value>::root_ = no_r;
        this->root_ = no_r;
        //std::cout << "root is now: " << this->root_->getKey() << std::endl;
    }

    //BinarySearchTree<Key, Value>::print();
}

template<class Key, class Value>
void AVLTree<Key, Value>::rightRotation(AVLNode<Key, Value> *no) {
    //BinarySearchTree<Key, Value>::print();
    //std::cout << "initiate rightRotation of " << no->getKey() << std::endl;
    AVLNode<Key, Value>* no_r = no->getLeft()->getRight();
    AVLNode<Key, Value>* no_l = no->getLeft();

    //std::cout << "node being rotated: " << no->getKey() << std::endl;
    //std::cout << "node taking its place: " << no_l->getKey() << std::endl;

    if (no->getParent() != NULL) {
        if (no->getParent()->getLeft() == no) no->getParent()->setLeft(no_l);
        else no->getParent()->setRight(no_l);
    }
    no_l->setParent(no->getParent());
    no_l->setRight(no);
    no->setParent(no_l);
    no->setLeft(no_r);
    if (no_r != NULL) no_r->setParent(no);

    /*if (no_r != NULL) {
        std::cout << "new g: " << no_r->getParent() << std::endl;
        std::cout << "new p: " << no_r->getKey() << std::endl;
    }
    std::cout << "new c: " << no->getKey() << std::endl;*/

    if (this->root_ == no) {
        //BinarySearchTree<Key, Value>::root_ = no_l;
        this->root_ = no_l;
        //std::cout << "root is now: " << this->root_->getKey() << std::endl;
    }

    //BinarySearchTree<Key, Value>::print();
}

/*template<class Key, class Value>
AVLNode<Key, Value>*
AVLTree<Key, Value>::predecessor(AVLNode<Key, Value>* current)
{
    // TODO
    AVLNode<Key, Value>* ret = NULL;
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
}*/

/*template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
AVLTree<Key, Value>::find(const Key & k) const
{
    std::cout << "init find" << std::endl;
    AVLNode<Key, Value> *curr = internalFind(k);
    typename BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}*/

/*template<typename Key, typename Value>
AVLNode<Key, Value>*
AVLTree<Key, Value>::getSmallestNode() const
{
    // TODO
    AVLNode<Key, Value>* bro = root_;
    if (bro == NULL) return NULL;
    while (bro->getLeft() != NULL) {
        bro = bro->getLeft();
    }
    return bro;
}*/

/*template<typename Key, typename Value>
void AVLTree<Key, Value>::clear()
{
    // TODO
    BinarySearchTree<Key, Value>::del(this->root_);
    this->root_ = NULL;
    //BinarySearchTree<Key, Value>::root_ = NULL;
}*/

/*template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
AVLTree<Key, Value>::begin() const
{
    typename BinarySearchTree<Key, Value>::iterator begin(this->getSmallestNode());
    return begin;
}*/

#endif
