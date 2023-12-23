#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "exceptions.hpp"
#include <algorithm>
#include <ostream>
#include <iostream>
using namespace std;   

template <typename Comparable>
class BSTree {
  public:
    BSTree();
    BSTree(const BSTree &){}
    BSTree(BSTree &&){}
    ~BSTree(){}

    BSTree & operator=( const BSTree & );
    BSTree & operator=( BSTree && );

    const Comparable & findMin() const;
    const Comparable & findMax() const;
    bool contains(const Comparable& x) const;
    bool isEmpty() const;
    void printTree(ostream &out = cout) const;
    void makeEmpty();

    void insert( const Comparable & );
    void insert( Comparable && );
    void remove( const Comparable &);

  private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };
    BinaryNode *root;
  
    void insert( const Comparable & , BinaryNode * & );
    void insert( Comparable && , BinaryNode * &  );

    void remove( const Comparable & , BinaryNode * &  );

    BinaryNode * findMin( BinaryNode * ) const;
    BinaryNode * findMax( BinaryNode *) const;

    bool contains( const Comparable & , BinaryNode * ) const;
    void makeEmpty( BinaryNode * & );
    void printTree( BinaryNode *, ostream & ) const;
    BinaryNode * clone( BinaryNode * ) const;

};

#endif
