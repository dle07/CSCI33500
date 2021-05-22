#ifndef AVL_TREE_H
#define AVL_TREE_H
// Modified by Daniel Le

#include "dsexceptions.h"
#include "sequence_map.h"

#include <algorithm>
#include <queue>  //dependency for BFS
#include <cmath>
#include <iostream> 
#include <utility>
#include <fstream>

using namespace std;

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
class AvlTree
{
  public:
    void partOneFind(const Comparable& target){
        partOneFind(target, this->root);
    }
    float getDepthToLogRatio(){
        return (float) getAverageDepth() / (log2(nodeCount));
    }

    float getAverageDepth(){   //Let's first get the internal path length using breadth first search.
                                // Keep track of the current depth, for each node processed in each level, add the depth by one.
                                //We will add nullptrs to represent the end of a level, if it's found, then increment depth by one, if there's two sentinel nodes, then it means we've reach the end, stop and break out of the search
        int currentDepth = 0;  //starts at zero because root's path to root is zero.
        int internalPathLength = 0;
        float result;
        queue<AvlNode*> myQueue;
        myQueue.push(this->root);
        myQueue.push(nullptr);  //push nullptr to start marking end

        while( !myQueue.empty() ){           //Modified BFS 
            AvlNode* curr = myQueue.front();
            myQueue.pop();
            if( curr == nullptr ){  //sentinel node was found
                currentDepth++;
                myQueue.push(nullptr);
                if(myQueue.front() == nullptr) break; //duplicate, found 2 in a row, stop
            }else{
                if(curr -> left) myQueue.push( curr->left );
                if(curr -> right) myQueue.push( curr->right ); 
                internalPathLength += currentDepth;
            }
        }
        result = (float) internalPathLength / this->getNodeCount();


        return result;
    }

    //Gets the data all in one shot for efficency || 1st = successful matches, 2nd recursion calls / numbers of queries
    //Queries from each string in sequences.txt
    pair<int,float> getStepFourData(const string& file_name){

        pair<int,float> result;
        int successful_queries = 0;
        int total_queries = 0;
        int recursive_calls = 0;

        string currSequence;
        fstream file_stream(file_name, ios :: in);
        if( file_stream.is_open() ){
            while( getline(file_stream, currSequence ) ){  //For each recognition sequence, execute a search!
                if(currSequence.empty()) continue;
                ++total_queries;
                modifiedContains( recursive_calls, successful_queries, currSequence, this->root);
            }
        }
        file_stream.close();
        result.first = successful_queries;
        result.second = (float) recursive_calls / total_queries;
        return result;
    }
    
    pair<int,float> getStepFiveData(const string &file_name){

        pair<int,float> result;
        int successful_removes = 0;
        int remove_calls = 0;
        int recursive_calls = 0;
        int i = 0;
        int j = 0;
        string currSequence;
        fstream file_stream(file_name, ios :: in);
        if( file_stream.is_open() ){
            while( getline(file_stream, currSequence)){

                    if( i % 2 == 0 && !currSequence.empty() ){
                    ++remove_calls;
                    SequenceMap target(currSequence,"");  //create a compare to test against nodes in the tree
                    modifiedRemove( recursive_calls, successful_removes, target, root);
                    
                }
                ++i;
            }
        }
        result.first = successful_removes;
        result.second = (float) recursive_calls / remove_calls;
        return result;
    }
    int getNodeCount(){
        return this -> nodeCount;
    }




    /** End of Added functions    **/
    AvlTree( ) : root{ nullptr }
      { }
    
    AvlTree( const AvlTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    AvlTree( AvlTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    ~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Deep copy.
     */
    AvlTree & operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    AvlTree & operator=( AvlTree && rhs )
    {
        std::swap( root, rhs.root );
        
        return *this;
    }
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }
//PRIVATE*********************PRIVATE
  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;

        AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ ele }, left{ lt }, right{ rt }, height{ h } { }
        
        AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
    };

    AvlNode *root;
    int nodeCount = 0;

    /***================Modified added functions to complete the assignment==================***/

    void modifiedContains(int &recursive_calls, int &successful_queries, string &target, AvlNode *t){
        ++recursive_calls;
        if( t == nullptr) return; //stop non found;
        else if( target < t->element.getRecognitionSequence() )  // less than, go left!
            modifiedContains(recursive_calls, successful_queries, target, t->left);
        else if( t -> element.getRecognitionSequence() < target ) // greater than go right!
            modifiedContains( recursive_calls, successful_queries, target, t->right);
        else{           //A match was found!
            ++successful_queries;
        }
    }
    //int &recursive_calls , int &successful_removes

    void modifiedRemove( int &recursive_calls , int &successful_removes, const Comparable & target, AvlNode * & t )  //Pass by reference to update the counters
    {
        recursive_calls++;         //increment recursive calls
        if( t == nullptr )
            return;   
        
        else if( target < t->element )
            modifiedRemove(recursive_calls, successful_removes, target, t->left ); 
        else if( t->element < target )
            modifiedRemove(recursive_calls, successful_removes, target, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            modifiedRemove(recursive_calls, successful_removes, t->element, t->right );
        }
        else
        {
            ++successful_removes;        //if there was a match, we increment the sucessful remove counter and remove the function
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
            this->nodeCount--;
            balance(t);
        }
        
        
    }



    
    void partOneFind(const Comparable& target,AvlNode* root ){
        if( root == nullptr ){
            cout<<"Not Found"<<endl;
            return;
        }
        else if( target < root->element ){
            partOneFind(target, root->left);
        }
        else if( root->element < target ){
            partOneFind(target,root->right);
        }
        else{
            cout<<root->element;
            return;
        }
    }
    /* End of modified functions   */

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr ){
            t = new AvlNode{ x, nullptr, nullptr };
            this -> nodeCount++;
        }
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else{
            t->element.Merge(x);
        }
        balance( t );
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, AvlNode * & t )
    {
        if( t == nullptr ){
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
            this -> nodeCount++;
        }
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x ) //basically means if the current element is less than the element to be inserted, the inserted elem is "bigger"
            insert( std::move( x ), t->right );
        else{
            t->element.Merge(x);
        }
        balance( t );
    }
     
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, AvlNode * & t )
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
            this->nodeCount--;
        }
        
        balance( t );
    }
    
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ) {
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        } else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ) {
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
	}
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
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
    AvlNode * findMax( AvlNode *t ) const
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
    bool contains( const Comparable & x, AvlNode *t ) const
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
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
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
    void printTree( AvlNode *t ) const
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
    AvlNode * clone( AvlNode *t ) const
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
    int height( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
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
    void rotateWithRightChild( AvlNode * & k1 )
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
    void doubleWithLeftChild( AvlNode * & k3 )
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
    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
};

#endif
