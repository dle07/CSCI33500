// Code from Mark Allen Weiss textbook
// Modified by: Daniel Le

#ifndef SORT_H
#define SORT_H

/*
    Heap sort ~ If we want a sorted array in ascending order we need a max heap, a min heap for descending order
    Take out the top of the heap, swap it with the last item in the array, and percolate down as needed.
    Repeat the process until there are no more items to work with
*/

/**
 * Several sorting routines.
 * Arrays are rearranged with smallest item first.
 */

#include <vector>
#include <functional>
using namespace std;

/**
 * Internal method for heapsort.
 * i is the index of an item in the heap.
 * Returns the index of the left child.
 */
inline int leftChild( int i )
{
    return 2 * i + 1;
}

/**
 * Internal method for heapsort that is used in
 * deleteMax and buildHeap.
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
 */
/*
    if less<int> we need to build a max heap 
*/
template <typename Comparable, typename Comparator>
void percDown( vector<Comparable> & a, int i, int n, Comparator less_than )
{
    int child;
    Comparable tmp;

    for( tmp = std::move( a[ i ] ); leftChild( i ) < n; i = child )
    {
        child = leftChild( i );
        if( child != n - 1 && less_than(a[ child ] , a[ child + 1 ] ) )
            ++child;
        if( less_than(tmp , a[ child ] ) )
            a[ i ] = std::move( a[ child ] );
        else
            break;
    }
    a[ i ] = std::move( tmp );
}


/**
 * Simple insertion sort.
 */
template <typename Comparable,  typename Comparator>
void insertionSort( vector<Comparable> & a, Comparator less_than )
{
    for( int p = 1; p < a.size( ); ++p )
    {
        Comparable tmp = std::move( a[ p ] );

        int j;
        for( j = p; j > 0 && less_than(tmp , a[ j - 1 ] ); --j )
            a[ j ] = std::move( a[ j - 1 ] );
        a[ j ] = std::move( tmp );
    }
}


/**
 * Internal insertion sort routine for subarrays
 * that is used by quicksort.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void insertionSort( vector<Comparable> & a, int left, int right , Comparator less_than)
{
    for( int p = left + 1; p <= right; ++p )
    {
        Comparable tmp = std::move( a[ p ] );
        int j;

        for( j = p; j > left && less_than(tmp , a[ j - 1 ] ) ; --j )
            a[ j ] = std::move( a[ j - 1 ] );
        a[ j ] = std::move( tmp );
    }
}



/**
 * Shellsort, using Shell's (poor) increments.
 */
template <typename Comparable>
void shellsort( vector<Comparable> & a )
{
    for( int gap = a.size( ) / 2; gap > 0; gap /= 2 )
        for( int i = gap; i < a.size( ); ++i )
        {
            Comparable tmp = std::move( a[ i ] );
            int j = i;

            for( ; j >= gap && tmp < a[ j - gap ]; j -= gap )
                a[ j ] = std::move( a[ j - gap ] );
            a[ j ] = std::move( tmp );
        }
}

/**
 * Standard heapsort.
 */
template <typename Comparable, typename Comparator>
void HeapSort(vector<Comparable> &a, Comparator less_than)
{
    for( int i = a.size( ) / 2 - 1; i >= 0; --i )  /* buildHeap */
        percDown( a, i, a.size(), less_than );

    for( int j = a.size( ) - 1; j > 0; --j )
    {
        std::swap( a[ 0 ], a[ j ] );               /* deleteMax */
        percDown( a, 0, j, less_than );
    }
}


/**
 * Internal method that merges two sorted halves of a subarray.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * leftPos is the left-most index of the subarray.
 * rightPos is the index of the start of the second half.
 * rightEnd is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void merge( vector<Comparable> & a, vector<Comparable> & tmpArray,
            int leftPos, int rightPos, int rightEnd , Comparator & less_than)
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    // Main loop
    while( leftPos <= leftEnd && rightPos <= rightEnd )
        if(less_than( a[ leftPos ] , a[ rightPos ] ) )
            tmpArray[ tmpPos++ ] = std::move( a[ leftPos++ ] );
        else
            tmpArray[ tmpPos++ ] = std::move( a[ rightPos++ ] );

    while( leftPos <= leftEnd )    // Copy rest of first half
        tmpArray[ tmpPos++ ] = std::move( a[ leftPos++ ] );

    while( rightPos <= rightEnd )  // Copy rest of right half
        tmpArray[ tmpPos++ ] = std::move( a[ rightPos++ ] );

    // Copy tmpArray back
    for( int i = 0; i < numElements; ++i, --rightEnd )
        a[ rightEnd ] = std::move( tmpArray[ rightEnd ] );
}

/**
 * Internal method that makes recursive calls.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void mergeSort( vector<Comparable> & a,
                vector<Comparable> & tmpArray, int left, int right , Comparator &less_than)
{
    if( left < right )
    {
        int center = ( left + right ) / 2;
        mergeSort( a, tmpArray, left, center , less_than);
        mergeSort( a, tmpArray, center + 1, right, less_than );
        merge( a, tmpArray, left, center + 1, right , less_than);
    }
}

/**
 * Mergesort algorithm (driver).
 */
template <typename Comparable, typename Comparator>
void MergeSort(vector<Comparable> &a, Comparator  less_than)
{
    vector<Comparable> tmpArray( a.size( ) );

    mergeSort( a, tmpArray, 0, a.size( ) - 1 , less_than);
}




/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
template <typename Comparable, typename Comparator>
Comparable  median3( vector<Comparable> & a, int left, int right, Comparator less_than )
{
    int center = ( left + right ) / 2;
    
    if( less_than(a[ center ] , a[ left ] ) )
        std::swap( a[ left ], a[ center ] );
    if( less_than(a[ right ] , a[ left ] ))
        std::swap( a[ left ], a[ right ] );
    if( less_than(a[ right ] , a[ center ] ))
        std::swap( a[ center ], a[ right ] );

        // Place pivot at position right - 1
    std::swap( a[ center ], a[ right - 1 ] );
    return a[ right - 1 ];
}

template <typename Comparable>
Comparable  middlePivot( vector<Comparable> & a, int left, int right){
    int center = (left + right ) /2;

    std :: swap( a[center], a[right]);
    return a[right ];
}

template <typename Comparable>
Comparable  firstPivot( vector<Comparable> & a, int left, int right){
    std :: swap (a[left], a[right]);
    return a[ right ];
}


/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void quicksort( vector<Comparable> & a, int left, int right, Comparator less_than )
{   
    if( left + 10 <= right )
    {   
        Comparable pivot;
        pivot = median3( a, left, right , less_than);
        

            // Begin partitioning
        int i = left, j = right - 1;
        
        for( ; ; )
        {      
            while( less_than (a[ ++i ] , pivot ) ) { }// 
            while( less_than (pivot , a[ --j ] ) ) { }
            if( i < j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }

        std::swap( a[ i ], a[ right - 1 ] );  // Restore pivot

        quicksort( a, left, i - 1 , less_than);     // Sort small elements
        quicksort( a, i + 1, right , less_than);    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right, less_than );
}

//Middle Pivot Quicksort
template <typename Comparable, typename Comparator>
void quicksort2( vector<Comparable> & a, int left, int right, Comparator less_than )
{   
    if( left + 10 <= right )
    {   
        Comparable pivot;
        pivot = middlePivot(a, left, right);
        

            // Begin partitioning
        int i = left-1, j = right;   
        
        for( ; ; )
        {       
            while( less_than (a[ ++i ] , pivot ) ) { }
            while( less_than (pivot , a[ --j ] ) ) { }
            if( i < j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }

        std::swap( a[ i ], a[ right ] );  // Restore pivot

        quicksort2( a, left, i - 1 , less_than);     // Sort small elements
        quicksort2( a, i + 1, right , less_than);    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right, less_than );
}

//first pivot  quicksort
template <typename Comparable, typename Comparator>
void quicksort3( vector<Comparable> & a, int left, int right, Comparator less_than )
{   
    if( left + 10 <= right )
    {   
        Comparable pivot;
        pivot = firstPivot(a, left, right);
        

            // Begin partitioning
        int i = left-1, j = right;  
        
        for( ; ; )
        {       
            while( less_than (a[ ++i ] , pivot ) ) { }// 
            while( less_than (pivot , a[ --j ] ) ) { }
            if( i < j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }

        std::swap( a[ i ], a[ right ] );  // Restore pivot

        quicksort3( a, left, i - 1 , less_than);     // Sort small elements
        quicksort3( a, i + 1, right , less_than);    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right, less_than );
}



/**
 * Quicksort algorithm (driver).
 */
template <typename Comparable, typename Comparator>
void QuickSort(vector<Comparable> &a, Comparator less_than)
{
    quicksort( a, 0, a.size( ) - 1, less_than);
}


//Middle Pivot Wrapper
template <typename Comparable, typename Comparator>
void QuickSort2(vector<Comparable> &a, Comparator less_than){
     quicksort2( a, 0, a.size( ) - 1, less_than );

}

//First Pivot Wrapper
template <typename Comparable, typename Comparator>
void QuickSort3(vector<Comparable> &a, Comparator less_than){
     quicksort3( a, 0, a.size( ) - 1, less_than );
}


/**
 * Internal selection method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * k is the desired rank (1 is minimum) in the entire array.
 */
template <typename Comparable>
void quickSelect( vector<Comparable> & a, int left, int right, int k )
{
    if( left + 10 <= right )
    {
        const Comparable & pivot = median3( a, left, right );

            // Begin partitioning
        int i = left, j = right - 1;
        for( ; ; )
        {
            while( a[ ++i ] < pivot ) { }
            while( pivot < a[ --j ] ) { }
            if( i < j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }

        std::swap( a[ i ], a[ right - 1 ] );  // Restore pivot

            // Recurse; only this part changes
        if( k <= i )
            quickSelect( a, left, i - 1, k );
        else if( k > i + 1 )
            quickSelect( a, i + 1, right, k );
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right );
}

/**
 * Quick selection algorithm.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * k is the desired rank (1 is minimum) in the entire array.
 */
template <typename Comparable>
void quickSelect( vector<Comparable> & a, int k )
{
    quickSelect( a, 0, a.size( ) - 1, k );
}


template <typename Comparable>
void SORT( vector<Comparable> & items )
{
    if( items.size( ) > 1 )
    {
        vector<Comparable> smaller;
        vector<Comparable> same;
        vector<Comparable> larger;
        
        auto chosenItem = items[ items.size( ) / 2 ];
        
        for( auto & i : items )
        {
            if( i < chosenItem )
                smaller.push_back( std::move( i ) );
            else if( chosenItem < i )
                larger.push_back( std::move( i ) );
            else
                same.push_back( std::move( i ) );
        }
        
        SORT( smaller );     // Recursive call!
        SORT( larger );      // Recursive call!
        
        std::move( begin( smaller ), end( smaller ), begin( items ) );
        std::move( begin( same ), end( same ), begin( items ) + smaller.size( ) );
        std::move( begin( larger ), end( larger ), end( items ) - larger.size( ) );

/*
        items.clear( );
        items.insert( end( items ), begin( smaller ), end( smaller ) );
        items.insert( end( items ), begin( same ), end( same ) );
        items.insert( end( items ), begin( larger ), end( larger ) );
*/
    }
}

/*
 * This is the more public version of insertion sort.
 * It requires a pair of iterators and a comparison
 * function object.
 */
template <typename RandomIterator, typename Comparator>
void insertionSort( const RandomIterator & begin,
                    const RandomIterator & end,
                    Comparator lessThan )
{
    if( begin == end )
        return;
        
    RandomIterator j;

    for( RandomIterator p = begin+1; p != end; ++p )
    {
        auto tmp = std::move( *p );
        for( j = p; j != begin && lessThan( tmp, *( j-1 ) ); --j )
            *j = std::move( *(j-1) );
        *j = std::move( tmp );
    }
}

/*
 * The two-parameter version calls the three parameter version, using C++11 decltype
 */
template <typename RandomIterator>
void insertionSort( const RandomIterator & begin,
                    const RandomIterator & end )
{
    insertionSort( begin, end, less<decltype(*begin )>{ } );
}



#endif
