#include"AvlTree.hpp"
#include "dsexceptions.hpp"
#include <algorithm>
#include <iostream> 
using namespace std;




template <typename Comparable>
 AvlTree<Comparable>::AvlTree( ) : root{ nullptr }
    { 
	}
    
    template <typename Comparable>
     AvlTree<Comparable>::AvlTree( const AvlTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }
    template <typename Comparable>
     AvlTree<Comparable>::AvlTree( AvlTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    template <typename Comparable>
     AvlTree<Comparable>::~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Deep copy.
     */
    template <typename Comparable>
    AvlTree<Comparable> &  AvlTree<Comparable>::operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    template <typename Comparable>
    AvlTree<Comparable> &  AvlTree<Comparable>::operator=( AvlTree && rhs )
    {
        std::swap( root, rhs.root );
        return *this;
    }
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    template <typename Comparable>
    const Comparable & AvlTree<Comparable>:: findMin( ) const
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
    const Comparable &  AvlTree<Comparable>::findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    template <typename Comparable>
    bool  AvlTree<Comparable>::contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    template <typename Comparable>
    bool  AvlTree<Comparable>::isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    template <typename Comparable>
    void  AvlTree<Comparable>::printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }

    /**
     * Make the tree logically empty.
     */
    template <typename Comparable>
    void  AvlTree<Comparable>::makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    template <typename Comparable>
    void  AvlTree<Comparable>::insert( const Comparable & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    template <typename Comparable>
    void  AvlTree<Comparable>::insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    template <typename Comparable>
    void  AvlTree<Comparable>::remove( const Comparable & x )
    {
        remove( x, root );
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    template <typename Comparable>
    void AvlTree<Comparable>::insert( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ x, nullptr, nullptr };
		
        else if( x < t->element )
            insert( x, t->left );
		
        else if( t->element < x )
            insert( x, t->right );
		
        balance( t );
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    template <typename Comparable>
    void AvlTree<Comparable>::insert( Comparable && x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
		
        else if( x < t->element )
            insert( std::move( x ), t->left );
		
        else if( t->element < x )
            insert( std::move( x ), t->right );
		
        balance( t );
    }
     
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    template <typename Comparable>
    void AvlTree<Comparable>::remove( const Comparable & x, AvlNode * & t )
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
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
        
        balance( t );
    }
    
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    template <typename Comparable>
    void AvlTree<Comparable>::balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
			// Left left imbalance
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
			// Left right imbalance
            else
                doubleWithLeftChild( t );
        else
        if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
			// Right right imbalance
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
			// Right left imbalance
            else
                doubleWithRightChild( t );
        
		// Update the height
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    template <typename Comparable>
    AvlTree<Comparable>::AvlNode * AvlTree<Comparable>::findMin( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
		
        if( t->left == nullptr )
            return t;
		
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    template <typename Comparable>
    AvlTree<Comparable>::AvlNode * AvlTree<Comparable>::findMax( AvlNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    template <typename Comparable>
    bool AvlTree<Comparable>::contains( const Comparable & x, AvlNode *t ) const
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

    /**
     * Internal method to make subtree empty.
     */
    template <typename Comparable>
    void AvlTree<Comparable>::makeEmpty( AvlNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    template <typename Comparable>
    void AvlTree<Comparable>::printTree( AvlNode *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    template <typename Comparable>
    AvlTree<Comparable>::AvlNode * AvlTree<Comparable>::clone( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }
	
    // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    template <typename Comparable>
    int AvlTree<Comparable>::height( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }
    template <typename Comparable>
    int AvlTree<Comparable>::max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
	 
	// left left imbalance
    template <typename Comparable>
    void AvlTree<Comparable>::rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
	 
	// right right imbalance
    template <typename Comparable>
    void AvlTree<Comparable>::rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
	 
	// Left right imbalance
    template <typename Comparable>
    void AvlTree<Comparable>::doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
	 
	// right left imbalance
    template <typename Comparable>
    void AvlTree<Comparable>::doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }