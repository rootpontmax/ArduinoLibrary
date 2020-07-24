
#include "Display.h"

//#define SMALL_FONT

////////////////////////////////////////////////////////////////////////////////////////////////////
// Text size == 1, display: 32x15 symbols
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef SMALL_FONT
static const uint8_t    TEXT_SIZE = 0;
static const uint8_t    LETTER_SIZE_X = 5;
static const uint8_t    LETTER_SIZE_Y = 7;
static const uint8_t    LETTER_COUNT_X = 65;
static const uint8_t    LETTER_COUNT_Y = 30;
#else
static const uint8_t    TEXT_SIZE = 1;
static const uint8_t    LETTER_SIZE_X = 11;
static const uint8_t    LETTER_SIZE_Y = 15;
static const uint8_t    LETTER_COUNT_X = 32;
static const uint8_t    LETTER_COUNT_Y = 15;
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////
CDisplay::CDisplay() :
    m_backColor( COLOR_BLACK ),
    m_textColor( COLOR_GREEN ),
    m_critColor( COLOR_RED ),
    m_rotation( 0 )
{}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CDisplay::Init()
{
    const int screenW = m_device.width();
    const int screenH = m_device.height();
    uint16_t id = m_device.readID();

    Serial.print("Dysplay " + String( screenW ) + "x" + String( screenH ) + " ID = 0x");
    Serial.println( id, HEX );

    if( 0x00D3 == id  || 0xD3D3 == id ) 
        id = 0x9481; // write-only shield
    if( 0xFFFF == id )
        id = 0x9341; // serial

    m_device.begin( id );
    m_device.fillScreen( m_backColor );

    m_device.setRotation( m_rotation );
    m_device.setTextColor( m_textColor );
    m_device.setTextSize( TEXT_SIZE );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CDisplay::SetRotation( const int rotation )
{
    m_rotation = rotation;
    m_device.setRotation( m_rotation );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CDisplay::SetTextColor( const uint16_t color )
{
    m_textColor = color;
    m_device.setTextColor( m_textColor );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CDisplay::SetTextMode()
{
    m_device.setRotation( m_rotation );
    m_device.setTextColor( m_textColor );
    m_device.setTextSize( TEXT_SIZE );

#ifdef SMALL_FONT
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000000000000000000000000000000000000" );
    m_device.println( "+--------|+--------|+--------|+--------|+--------|+--------|+---|" );
#else
    m_device.println( "00000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000" );
    //m_device.println( "Yaw angle:     13.0" );
    //m_device.println( "Pitch angle:  317.0" );
    //m_device.println( "Roll angle:    45.1" );
    m_device.println( "00000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000" );
    m_device.println( "00000000000000000000000000000000" );
    //m_device.println( "--------------------------------" );
    m_device.println( "00000000000000000000000000000000" );
#endif
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CDisplay::ClearScreen( const uint16_t color )
{
    m_device.fillScreen( color );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CDisplay::DrawText( const uint16_t x, const uint16_t y, const char *pString )
{
    m_device.setCursor( x, y );
    m_device.print( pString );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CDisplay::DrawInt( const uint16_t x, const uint16_t y, const int32_t value )
{
    m_device.setCursor( x, y );
    m_device.print( value );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CDisplay::DrawLong( const uint16_t x, const uint16_t y, const int64_t value )
{
    m_device.setCursor( x, y );
    m_device.print( (int32_t)value );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CDisplay::DrawFlt( const uint16_t x, const uint16_t y, const float value )
{
    m_device.setCursor( x, y );
    m_device.print( value );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CDisplay::FillRect( const int16_t x, const int16_t y, const int16_t w, const int16_t h, const uint16_t color )
{
    m_device.fillRect( x, y, w, h, color );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
uint16_t CDisplay::GetPixelPosX( const uint8_t symbolPosX ) const
{
    return symbolPosX * LETTER_SIZE_X;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
uint16_t CDisplay::GetPixelPosY( const uint8_t symbolPosY ) const
{
    return symbolPosY * LETTER_SIZE_Y;
}
////////////////////////////////////////////////////////////////////////////////////////////////////