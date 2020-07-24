#ifndef DISPLAY_H
#define DISPLAY_H

#include <MCUFRIEND_kbv.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// Screen rotation (White labels on the right side of the display set the orientation):
// 0 - top on the left side
// 1 - top on the top side
// 2 - top on the right side
// 3 - top on the bottom side
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
class CDisplay
{
public:
    static const uint16_t   COLOR_WHITE = 0xFFFF;
    static const uint16_t   COLOR_GREY = 0x7FFF;
    static const uint16_t   COLOR_BLACK = 0x0000;
    static const uint16_t   COLOR_BLUE = 0x001F;
    static const uint16_t   COLOR_RED = 0xF800;
    static const uint16_t   COLOR_GREEN = 0x07E0;
    static const uint16_t   COLOR_CYAN = 0x07FF;
    static const uint16_t   COLOR_MAGENTA = 0xF81F;
    static const uint16_t   COLOR_YELLOW = 0xFFE0;
    


    CDisplay();
    void        Init();

    void        SetRotation( const int rotation );
    void        SetTextColor( const uint16_t color );
    void        SetTextMode();

    // Drawing
    void        ClearScreen( const uint16_t color );
    void        DrawText( const uint16_t x, const uint16_t y, const char *pString );
    void        DrawInt( const uint16_t x, const uint16_t y, const int32_t value );
    void        DrawLong( const uint16_t x, const uint16_t y, const int64_t value );
    void        DrawFlt( const uint16_t x, const uint16_t y, const float value );
    void        FillRect( const int16_t x, const int16_t y, const int16_t w, const int16_t h, const uint16_t color );

    // Get position in pixels by pos in symbols
    uint16_t    GetPixelPosX( const uint8_t symbolPosX ) const;
    uint16_t    GetPixelPosY( const uint8_t symbolPosY ) const;

private:
    MCUFRIEND_kbv   m_device;
    uint16_t        m_backColor;
    uint16_t        m_textColor;
    uint16_t        m_critColor;
    uint8_t         m_rotation;
};
////////////////////////////////////////////////////////////////////////////////////////////////////

#endif