#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "exceptions.hpp"
#include <algorithm>
#include <iostream> 

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree {
  public:
    AvlTree();
    AvlTree(const AvlTree&);
    AvlTree(AvlTree &&);
    ~AvlTree();

    /**
     * Deep copy.
     */
    AvlTree & operator=( const AvlTree &);
    /**
     * Move.
     */
    AvlTree & operator=( AvlTree && );
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
    bool contains( const Comparable &  ) const;
    

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const;


    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const;
    /**
     * Make the tree logically empty.
     */
    void makeEmpty( );
   
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable &  );
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable &&  );
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable &  );

  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode    *left;
        AvlNode    *right;
        int        height;

        AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ ele }, left{ lt }, right{ rt }, height{ h } { }
        
        AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
    };

    AvlNode *root;

    void insert( const Comparable & , AvlNode * &  );

    void insert( Comparable && , AvlNode * &  );
   
    void remove( const Comparable & , AvlNode * &  );
 
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * &  );
    
  
    AvlNode * findMin( AvlNode * ) const;


    AvlNode * findMax( AvlNode * ) const;


    bool contains( const Comparable & , AvlNode * ) const;
   
    void makeEmpty( AvlNode * &  );

    
    void printTree( AvlNode *t ) const;
   
    AvlNode * clone( AvlNode *t ) const;
 
 
    int height( AvlNode * ) const;

    int max( int , int ) const;
	 
    void rotateWithLeftChild( AvlNode * & );
	 
	// right right imbalance
    void rotateWithRightChild( AvlNode * & );

    void doubleWithLeftChild( AvlNode * &  );
  
    void doubleWithRightChild( AvlNode * &  );

};

#endif