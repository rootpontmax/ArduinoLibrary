#include "Timer.h"
#include "Arduino.h"
#include <assert.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
CTimer::CTimer( const bool bIsMilliseconds ) :
	m_delayTime( 0 ),
	m_startTime( 0 ),
	m_bIsWorking( false ),
	m_bIsAutoRestarted( false ),
	m_bIsMilliseconds( bIsMilliseconds )
{}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CTimer::Start( const unsigned long delayTime, const bool isRepeatedly )
{
	m_delayTime = delayTime;
	if( m_bIsMilliseconds )
		m_startTime = millis();
	else
		m_startTime = micros();
	m_bIsAutoRestarted = isRepeatedly;
	m_bIsWorking = true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CTimer::Stop()
{
	m_bIsWorking = false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool CTimer::IsReady()
{
	if( !m_bIsWorking )
		return false;

	const unsigned long thisTime = m_bIsMilliseconds ? millis() : micros();
	const unsigned long deltaTime = thisTime - m_startTime;
	if( deltaTime > m_delayTime )
	{
		if( m_bIsAutoRestarted )
			m_startTime = thisTime;
		else
			m_bIsWorking = false;

		return true;
	}

	return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

