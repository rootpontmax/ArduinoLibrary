////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple media filter.                                                                           //
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#include <assert.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, int N>
class CMedianFilter
{
public:
	CMedianFilter();

    void    Add( T value );
    void    Sort();
    T       Get() const { return m_sortBuffer[N/2]; }
private:

    int     Compare( T lhs, T rhs ) const;
    void    Swap( T *pLhs, T *pRhs );

    T       m_ringBuffer[N];
    T       m_sortBuffer[N];
    int     m_ringPos;
};
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T, int N >
CMedianFilter< T, N >::CMedianFilter() :
    m_ringPos( 0 )
{}
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T, int N >
void CMedianFilter< T, N >::Add( T value )
{
    m_ringBuffer[m_ringPos] = value;
    ++m_ringPos;
    m_ringPos %= N;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T, int N >
void CMedianFilter< T, N >::Sort()
{
    // Копируем массив
    memcpy( m_sortBuffer, m_ringBuffer, sizeof( T ) * N );

    // Сортируем
    const int64_t MAX_LEVELS = 128;
    int64_t lo[MAX_LEVELS], hi[MAX_LEVELS];

    // 'lo' is the lower index, 'hi' is the upper index
    // of the region of the array that is being sorted.
    lo[0] = 0;
    hi[0] = N - 1;

    for( int64_t level = 0; level >= 0; )
    {
        int64_t i = lo[level];
        int64_t j = hi[level];

        // Only use quick-sort when there are 4 or more elements in this region and we are below MAX_LEVELS.
        // Otherwise fall back to an insertion-sort.
        if ( ( ( j - i ) >= 4 ) && ( level < ( MAX_LEVELS - 1 ) ) )
        {
            // Use the center element as the pivot.
            // The median of a multi point sample could be used
            // but simply taking the center works quite well.
            int64_t pi = ( i + j ) / 2;

            // Move the pivot element to the end of the region.
            Swap( &m_sortBuffer[j], &m_sortBuffer[pi] );

            // Get a reference to the pivot element.
            T & pivot = m_sortBuffer[j--];

            // Partition the region.
            do
            {
                while( Compare( m_sortBuffer[i], pivot ) < 0 )
                {
                    if( ++i >= j )
                        break;
                }
                while( Compare( m_sortBuffer[j], pivot ) > 0 )
                {
                    if( --j <= i )
                        break;
                }
                if( i >= j )
                    break;
                    
                Swap( &m_sortBuffer[i], &m_sortBuffer[j] );
            }
            while( ++i < --j );

            // Without these iterations sorting of arrays with many duplicates may
            // become really slow because the partitioning can be very unbalanced.
            // However, these iterations are unnecessary if all elements are unique.
            while( Compare( m_sortBuffer[i], pivot ) <= 0 && i < hi[level] )
            {
                i++;
            }
            while( Compare( m_sortBuffer[j], pivot ) >= 0 && lo[level] < j )
            {
                j--;
            }

            // Move the pivot element in place.
            Swap( &pivot, &m_sortBuffer[i] );

            assert( level < MAX_LEVELS - 1 );
            lo[level+1] = i;
            hi[level+1] = hi[level];
            hi[level] = j;
            level++;
        }
        else
        {

            // Insertion-sort of the remaining elements.
            for( ; i < j; j-- )
            {
                int64_t m = i;
                for( int64_t k = i + 1; k <= j; k++ )
                {
                    if( Compare( m_sortBuffer[k], m_sortBuffer[m] ) > 0 )
                    {
                        m = k;
                    }
                }
                Swap( &m_sortBuffer[m], &m_sortBuffer[j] );
            }
            --level;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T, int N >
int CMedianFilter< T, N >::Compare( T lhs, T rhs ) const
{
    return ( lhs - rhs );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T, int N >
void CMedianFilter< T, N >::Swap( T *pLhs, T *pRhs )
{
    const T tmp = *pRhs;
    *pRhs = *pLhs;
    *pLhs = tmp;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

