#include "dsexceptions.hpp"
#include <algorithm>
#include"BinarySearchTree.hpp"
#include <iostream>
using std::ostream;
using namespace std;   


    template <typename Comparable>
    BinarySearchTree<Comparable>::BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    template <typename Comparable>
  BinarySearchTree<Comparable>::BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
  
    template <typename Comparable>
      BinarySearchTree<Comparable>::~BinarySearchTree( )
    {
        makeEmpty( );
    }

    template <typename Comparable>
      BinarySearchTree<Comparable>& BinarySearchTree<Comparable>:: operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    template <typename Comparable>
      BinarySearchTree<Comparable>&   BinarySearchTree<Comparable>::operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );       
        return *this;
    }
    
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    template <typename Comparable>
    const Comparable &   BinarySearchTree<Comparable>:: findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    template <typename Comparable>
    const Comparable &   BinarySearchTree<Comparable>::findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    template <typename Comparable>
    bool  BinarySearchTree<Comparable>::contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    template <typename Comparable>
    bool   BinarySearchTree<Comparable>::isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::printTree(std::ostream &out= cout)const
    {
        if (isEmpty())
            out << "Empty tree" << std::endl;
        else
            printTree(root, out);
    }

    /**
     * Make the tree logically empty.
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    template <typename Comparable>
    void   BinarySearchTree<Comparable>::insert( const Comparable & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    template <typename Comparable>
    void   BinarySearchTree<Comparable>::insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    template <typename Comparable>
    void   BinarySearchTree<Comparable>::remove( const Comparable & x )
    {
        remove( x, root );
    }

    template <typename Comparable>
    void   BinarySearchTree<Comparable>::insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            ;  // Duplicate; do nothing
    }
    
    template <typename Comparable>
    void   BinarySearchTree<Comparable>::insert( Comparable && x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            ;  // Duplicate; do nothing
    }

    template <typename Comparable>
    void   BinarySearchTree<Comparable>::remove( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
    }

    template <typename Comparable>
    typename BinarySearchTree<Comparable>::BinaryNode* BinarySearchTree<Comparable>::findMin(BinaryNode* t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }

    template <typename Comparable>
      BinarySearchTree<Comparable>::BinaryNode *   BinarySearchTree<Comparable>::findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    template <typename Comparable>
    bool   BinarySearchTree<Comparable>::contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
     template <typename Comparable>
    void   BinarySearchTree<Comparable>::makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    template <typename Comparable>
    void   BinarySearchTree<Comparable>::printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }

    template <typename Comparable>
      BinarySearchTree<Comparable>::BinaryNode *   BinarySearchTree<Comparable>::clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }