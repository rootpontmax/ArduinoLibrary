////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple average filter.                                                                         //
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MS_TECH_AVERAGE_FILTER_H
#define MS_TECH_AVERAGE_FILTER_H

////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T, int N>
class CAverageFilter
{
public:
	CAverageFilter();
	void    Add( T value );
    T    	Calc( const T zero );

private:
	T       m_ringBuffer[N];
    int     m_ringPos;
    int		m_count;
};
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, int N>
CAverageFilter< T, N>::CAverageFilter() :
    m_ringPos( 0 ),
    m_count( 0 )
{}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, int N>
void CAverageFilter< T, N>::Add( T value )
{
    m_ringBuffer[m_ringPos] = value;
    ++m_ringPos;
    m_ringPos %= N;
    if( m_count < N )
    	++m_count;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, int N>
T CAverageFilter< T, N>::Calc(const T zero)
{
	if( 0 == m_count )
		return zero;

	T sum = zero;
	for( int i = 0; i < m_count; ++i )
	{
		sum += m_ringBuffer[i];
	}

	sum /= m_count;
	return sum;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif