#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.hpp"
#include <algorithm>
using namespace std;   

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & ){}

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && ){}
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( ){}

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & );
        
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && );
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const;
    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const;
    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const;

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const;

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream &out=cout) const

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( );
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & );
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && );
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
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
