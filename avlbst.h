#ifndef RBBST_H
#define RBBST_H

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
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

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
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);


    // Add helper functions here
    void insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    void rotateRight(AVLNode<Key,Value>* curr);
    void rotateLeft(AVLNode<Key,Value>* curr);
    void removeFix(AVLNode<Key,Value>* n, int8_t diff);


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    //checking if the key is already in the tree to overwrite its value
    AVLNode<Key, Value> *findNode = static_cast<AVLNode<Key,Value>*> (this->internalFind(new_item.first));
    if(findNode!=nullptr)
    {
        findNode->setValue(new_item.second);
        return;
    }
    else
    {
      delete findNode;
    }


    //making node using key,value pair
    AVLNode<Key,Value>* curr = new AVLNode<Key,Value>(new_item.first, new_item.second,nullptr);
    //if empty tree, set n as root, balance = 0
    if(this->root_==nullptr)
    {
      this->root_ = curr;
      static_cast<AVLNode<Key,Value>*>(this->root_)->setBalance(0);
      return;
    }
    //else insert n by walking the tree to a leaf, p, and inserting
    //the new node as its child, set balance to 0, and look at its parent
    //p
    else
    {
      AVLNode<Key,Value>* loc=static_cast<AVLNode<Key,Value>*> (this->root_);
      //walking the tree to leaf
      while(loc!=nullptr)
      {
        //walking left
        if(curr->getKey() < loc->getKey())
        {
          //setting curr to be the left child of the leaf
          if(loc->getLeft()==nullptr)
          {
            //changing the pointers
            curr->setParent(loc);
            loc->setLeft(curr);
            curr->setBalance(0);
            //balance checks
            if(loc->getBalance()==-1)
            {
              loc->setBalance(0);
              return;
            }
            else if(loc->getBalance()==1)
            {
              loc->setBalance(0);
              return;
            }
            else if(loc->getBalance()==0)
            {
              loc->setBalance(-1);
              //AVLNode<Key,Value>* parent = loc;
              //call insert-fix
              insertFix(loc, curr);
            }
            break;
            return;
          }
          //not at a leaf, keep walking
          else
          {
            loc = loc->getLeft();
          }
        }
        //walking right
        else if(curr->getKey() > loc->getKey())
        {
          //setting curr to be the right child of the leaf
          if(loc->getRight()==nullptr)
          {
            //changing the pointers
            curr->setParent(loc);
            loc->setRight(curr);
            curr->setBalance(0);
            //balance checks
            if(loc->getBalance()==-1)
            {
              loc->setBalance(0);
              return;
            }
            else if(loc->getBalance()==1)
            {
              loc->setBalance(0);
              return;
            }
            else if(loc->getBalance()==0)
            {
              loc->setBalance(1);
              //AVLNode<Key,Value>* parent = loc;
              //call insert-fix
              insertFix(loc, curr);
            }
            break;
            return;
          }
          //not at a leaf, keep walking
          else
          {
            loc = loc->getRight();
          }
        }
      }

    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n)
{
  //if p is null or parent(p) is null, return
  if(p==nullptr || p->getParent()==nullptr)
  {
    return;
  }

  AVLNode<Key,Value>* g = p->getParent();

  //p is the left child of g
  if(p==g->getLeft())
  {
    g->updateBalance(-1);
    //case 1: b(g)==0
    if(g->getBalance()==0)
    {
      return;
    }
    //case 2: b(g)==-1
    else if(g->getBalance()==-1)
    {
      insertFix(g,p);
    }
    //case 3:b(g)==-2
    else if(g->getBalance()==-2)
    {
      //if zig-zig, rotateRight(g) and b(p) = b(g) = 0

      //zig-zig if parent is left child of grandparent & grandchild is left child of parent
      //already checked for parent being left child of grandparent earlier

      //if getLeft is not null then left child exists
      if(p->getLeft()==n)
      {
        rotateRight(g);
        p->setBalance(0);
        g->setBalance(0);

        return;
      }
      //if zig-zag, rotateLeft(p) and rotate(g), and then set balances accordingly
      else if(p->getLeft()!=n)
      {
        rotateLeft(p);
        rotateRight(g);
        //case 3a: b(n)==-1, b(p)=0; b(g) = +1; b(n) = 0;
        if(n->getBalance()==-1)
        {
          p->setBalance(0);
          g->setBalance(1);
          n->setBalance(0);
        }
        //case 3b: b(n)==0, b(p)=0; b(g)=0; b(n)=0;
        else if(n->getBalance()==0)
        {
          p->setBalance(0);
          g->setBalance(0);
          n->setBalance(0);
        }
        //case 3b: b(n)==1, b(p)=-1; b(g)=0; b(n)=0;
        else if(n->getBalance()==1)
        {
          p->setBalance(-1);
          g->setBalance(0);
          n->setBalance(0);
        }

        return;
      }
    }
  }
  else if(p==g->getRight())
  {
    g->updateBalance(1);
    //case 1: b(g)==0
    if(g->getBalance()==0)
    {
      return;
    }
    //case 2: b(g)==1
    else if(g->getBalance()==1)
    {
      insertFix(g,p);
    }
    //case 3:b(g)==2
    else if(g->getBalance()==2)
    {
      //if zig-zig, rotateLeft(g) and b(p) = b(g) = 0

      //zig-zig if parent is right child of grandparent & grandchild is right child of parent
      //already checked for parent being right child of grandparent earlier

      //if getRight is not null then right child exists
      if(p->getRight()==n)
      {
        rotateLeft(g);
        p->setBalance(0);
        g->setBalance(0);

        return;
      }
      //if zig-zag, rotateRight(p) and rotateLeft(g), and then set balances accordingly
      else if(p->getRight()!=n)
      {
        rotateRight(p);
        rotateLeft(g);
        //case 3a: b(n)==1, b(p)=0; b(g) = -1; b(n) = 0;
        if(n->getBalance()==1)
        {
          p->setBalance(0);
          g->setBalance(-1);
          n->setBalance(0);
        }
        //case 3b: b(n)==0, b(p)=0; b(g)=0; b(n)=0;
        else if(n->getBalance()==0)
        {
          p->setBalance(0);
          g->setBalance(0);
          n->setBalance(0);
        }
        //case 3b: b(n)==-1, b(p)=1; b(g)=0; b(n)=0;
        else if(n->getBalance()==-1)
        {
          p->setBalance(1);
          g->setBalance(0);
          n->setBalance(0);
        }

        return;
      }
    }
  }
  
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* curr)
{

  //taking left child, making it the parent, and making original parent the 
  //new right child


  //make curr the right child of its current child node
  AVLNode<Key,Value>* child = curr->getLeft();
  
  //parent exists and we have to change parent pointers as well
  if(curr->getParent()!=nullptr)
  {
    AVLNode<Key,Value>* parent = curr->getParent();
    if(curr==parent->getRight())
    {
      parent->setRight(child);
      child->setParent(parent);
    }
    else if(curr==parent->getLeft())
    {
      parent->setLeft(child);
      child->setParent(parent);
    }
  }
  else if(curr->getParent()==nullptr)
  {
    child->setParent(nullptr);
    this->root_=child;
  }


  //grabbing new root's right child (if it has one) and making it curr's left child
  if(child->getRight()!=nullptr)
  {
    AVLNode<Key,Value>* newLeftChild = child->getRight();
    curr->setLeft(newLeftChild);
    newLeftChild->setParent(curr);
  }
  else 
  {
    curr->setLeft(nullptr);
  }

  child->setRight(curr);
  curr->setParent(child);


  

}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* curr)
{
  //make curr the right child of its current child node
  AVLNode<Key,Value>* child = curr->getRight();
  
  //parent exists and we have to change parent pointers as well
  if(curr->getParent()!=nullptr)
  {
    AVLNode<Key,Value>* parent = curr->getParent();
    if(curr==parent->getLeft())
    {
      parent->setLeft(child);
      child->setParent(parent);
    }
    else if(curr==parent->getRight())
    {
      parent->setRight(child);
      child->setParent(parent);
    }
  }
  else if(curr->getParent()==nullptr)
  {
    child->setParent(nullptr);
    this->root_=child;
  }


  //grabbing new root's left child (if it has one) and making it curr's right child
  if(child->getLeft()!=nullptr)
  {
    AVLNode<Key,Value>* newRightChild = child->getLeft();
    curr->setRight(newRightChild);
    newRightChild->setParent(curr);
  }
  else
  {
    curr->setRight(nullptr);
  }

  child->setLeft(curr);
  curr->setParent(child);

}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    //find node,n, to remove by walking the tree
    AVLNode<Key,Value>* n = static_cast<AVLNode<Key,Value>*> (this->internalFind(key));
    
    //if node is not found, return
    if(n==nullptr)
    {
      return;
    }

    //if n has 2 children, swap positions with in-order predecessor
    if(n->getLeft()!=nullptr && n->getRight()!=nullptr)
    {
      AVLNode<Key,Value>* swapNode=static_cast<AVLNode<Key,Value>*> (this->predecessor(n));
      nodeSwap(n,swapNode);
    } 

    //Let p = parent(n)
    AVLNode<Key,Value>* p= n->getParent();
    int8_t diff;
    //if p is not null
    if(p!=nullptr)
    {
      //if n is a left child, let diff = +1
      if(n==p->getLeft())
      {
        diff=1;
      }
      //if n is a right child, let diff = -1
      else if(n==p->getRight())
      {
        diff=-1;
      }
    }

  //delete n and update pointers

  //0 children: if the value is in a leaf node, simply remove that leaf node
  if(n->getLeft()==nullptr && n->getRight()==nullptr)
  {
    if(n==this->root_)
    {
      this->root_=nullptr;
      delete n;
      return;
    }
    else if(n!=this->root_)
    {
      if(p->getLeft()==n)
      {
        p->setLeft(nullptr);
      }
      else if(p->getRight()==n)
      {
        p->setRight(nullptr);
      }
      delete n;
      //patching tree
      removeFix(p,diff);
      return;
    }
    //return;
  }
  //1 child: Promote the child into the node's location
  //if the child is a left child 
  else if(n->getLeft()!=nullptr && n->getRight()==nullptr)
  {
    AVLNode<Key,Value>* left = n->getLeft();
    if(n==this->root_)
    {
      this->root_=left;
      left->setParent(nullptr);
      delete n;
      removeFix(p,diff);
      return;
    }
    else if(n!=this->root_)
    {
      if(p->getLeft()==n)
      {
        p->setLeft(left);
        left->setParent(p);
        //delete n;
      }
      else
      {
        p->setRight(left);
        left->setParent(p);
        //delete n;
      }
      delete n;
      //patching tree
      removeFix(p,diff);
      return;
    }
    //return;
  }
  //if the child is a right child 
  else if(n->getLeft()==nullptr && n->getRight()!=nullptr)
  {
    AVLNode<Key,Value>* right=n->getRight();
    if(n==this->root_)
    {
      this->root_=right;
      this->root_->setParent(nullptr);
      delete n;
      //return;
    }
    else if(n!=this->root_)
    {
      if(p->getLeft()==n)
      {
        p->setLeft(right);
        right->setParent(p);
        //delete n;
      }
      else
      {
        p->setRight(right);
        right->setParent(p);
        //delete n;
      }
      //patching tree
      delete n;
      removeFix(p,diff);
      return;
    }
    //return;
  } 
  return;
  //removeFix(p,diff);     
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* n, int8_t diff)
{
  //if n is null, return
  if(n==nullptr)
  {
    return;
  }
  //compute next recursive call's arguments now before altering the tree
  //let p = parent(n) and if p is not NULL let ndiff(nextdiff)=+1
  //if n is a left child and -1 otherwise
  AVLNode<Key,Value>* p = n->getParent();
  int8_t ndiff;
  if(p!=nullptr)
  {
    if(p->getLeft()==n)
    {
      ndiff = 1;
    }
    else if(p->getRight()==n)
    {
      ndiff = -1;
    }
  }



  //assuming diff=-1
  if(diff==-1)
  {
    //Case 1: b(n) + diff == -2
    if(n->getBalance() + diff == -2)
    {
      //let c=left(n), the taller of the children
      AVLNode<Key,Value>* c = n->getLeft();
      //Case 1a: b(c)==-1 zig-zig case
      if(c->getBalance()==-1)
      {
        rotateRight(n);
        n->setBalance(0);
        c->setBalance(0);
        //calling recursive case
        removeFix(p, ndiff);
        return;
      }
      //Case 1b: b(c)==0 zig-zig case
      else if(c->getBalance()==0)
      {
        rotateRight(n);
        n->setBalance(-1);
        c->setBalance(1);
        return;
      }
      //Case 1c: b(c)==1 zig-zag case
      else if(c->getBalance()==1)
      {
        //let g=right(c)
        AVLNode<Key,Value>* g = c->getRight();
        rotateLeft(c);
        rotateRight(n);
        //if b(g) was +1 
        if(g->getBalance()==1)
        {
          n->setBalance(0);
          c->setBalance(-1);
          g->setBalance(0);
        }
        //if b(g) was 0
        else if(g->getBalance()==0)
        {
          n->setBalance(0);
          c->setBalance(0);
          g->setBalance(0);
        }
        //if b(g) was -1
        else if(g->getBalance()==-1)
        {
          n->setBalance(1);
          c->setBalance(0);
          g->setBalance(0);
        }
        //calling recursive case
        removeFix(p,ndiff);
        return;
      }
    }
    //Case 2: b(n) + diff == -1, then b(n) = -1
    else if(n->getBalance() + diff == -1)
    {
      n->setBalance(-1);
      return;
    }
    //Case 3: b(n) + diff == 0, then b(n) = 0
    else if(n->getBalance() + diff == 0)
    {
      n->setBalance(0);
      removeFix(p, ndiff);
      return;
    }

  }
  //assuming diff==1
  else if(diff==1)
  {
    //Case 1: b(n) + diff == 2
    if(n->getBalance() + diff == 2)
    {
      //let c=right(n), the taller of the children
      AVLNode<Key,Value>* c= n->getRight();
      //Case 1a: b(c) == 1 zig-zig
      if(c->getBalance() == 1)
      {
        rotateLeft(n);
        n->setBalance(0);
        c->setBalance(0);
        removeFix(p, ndiff);
        return;
      }
      //Case 1b: b(c) == 0 zig-zig
      else if(c->getBalance() == 0)
      {
        rotateLeft(n);
        n->setBalance(1);
        c->setBalance(-1);
        return;
      }
      //Case 1c: b(c) == -1 zig-zag
      else if(c->getBalance() == -1)
      {
        AVLNode<Key,Value>* g= c->getLeft();
        rotateRight(c);
        rotateLeft(n);
        //if b(g) was -1
        if(g->getBalance()==-1)
        {
          n->setBalance(0);
          c->setBalance(1);
          g->setBalance(0);
        }
        //if b(g) was 0
        else if(g->getBalance()==0)
        {
          n->setBalance(0);
          c->setBalance(0);
          g->setBalance(0);
        }
        //if b(g) was 1
        else if(g->getBalance()==1)
        {
          n->setBalance(-1);
          c->setBalance(0);
          g->setBalance(0);
        }

        //calling recursive case
        removeFix(p, ndiff);
        return;

      }
    }
    else if(n->getBalance() + diff == 1)
    {
      n->setBalance(1);
      return;
    }
    else if(n->getBalance() + diff == 0)
    {
      n->setBalance(0);
      removeFix(p, ndiff);
      return;
    }
  }

  return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
