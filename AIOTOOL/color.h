#pragma once
#include <imgui/imgui.h>

class C_Color
{
public:
    C_Color();
    C_Color(int _r, int _g, int _b);
    C_Color(int _r, int _g, int _b, int _a);
    C_Color(float _r, float _g, float _b) : C_Color(_r, _g, _b, 1.0f) {}
    C_Color(float _r, float _g, float _b, float _a)
        : C_Color(
            static_cast<int>(_r * 255.0f),
            static_cast<int>(_g * 255.0f),
            static_cast<int>(_b * 255.0f),
            static_cast<int>(_a * 255.0f))
    {
    }
    explicit C_Color(float* rgb) : C_Color(rgb[0], rgb[1], rgb[2], 1.0f) {}
    explicit C_Color(unsigned long argb)
    {
        _CColor[2] = (unsigned char)((argb & 0x000000FF) >> (0 * 8));
        _CColor[1] = (unsigned char)((argb & 0x0000FF00) >> (1 * 8));
        _CColor[0] = (unsigned char)((argb & 0x00FF0000) >> (2 * 8));
        _CColor[3] = (unsigned char)((argb & 0xFF000000) >> (3 * 8));
    }

    unsigned long GetHex(void) const {
        return (unsigned long)((unsigned long)this->_CColor[3] << 24) |
            ((unsigned long)this->_CColor[0] << 16) |
            ((unsigned long)this->_CColor[1] << 8) |
            ((unsigned long)this->_CColor[2]);
    }

    ImU32 GetU32()
    {
        return ((_CColor[3] & 0xff) << 24) + ((_CColor[2] & 0xff) << 16) + ((_CColor[1] & 0xff) << 8)
            + (_CColor[0] & 0xff);
        //return (ImU32)(((_color[3] & 0xff) << 24) + ((_color[0] & 0xff) << 16) + ((_color[1] & 0xff) << 8) + (_color[2] & 0xff));
    }


    static C_Color FromHSB(float hue, float saturation, float brightness);

    void    SetRawColor(int color32);
    int     GetRawColor() const;
    void    SetColor(int _r, int _g, int _b, int _a = 0);
    void    SetColor(float _r, float _g, float _b, float _a = 0);
    void    GetColor(int& _r, int& _g, int& _b, int& _a) const;


    int r() const { return _CColor[0]; }
    int g() const { return _CColor[1]; }
    int b() const { return _CColor[2]; }
    int a() const { return _CColor[3]; }


    void SetAlpha(int alpha) { _CColor[3] = alpha; }

    unsigned char& operator[](int index)
    {
        return _CColor[index];
    }
    const unsigned char& operator[](int index) const
    {
        return _CColor[index];
    }

    bool operator==(const C_Color& rhs) const;
    bool operator!=(const C_Color& rhs) const;
    C_Color& operator=(const C_Color& rhs);

    static C_Color Black;
    static C_Color White;
    static C_Color Red;
    static C_Color Green;
    static C_Color Blue;

private:
    unsigned char _CColor[4]{};
};


namespace utils
{

    long long GetEpochTime();
    C_Color GetRainbowColor(float speed);

    class color_var
    {

    public:
        ImColor col_color = ImColor(0.f, 0.f, 0.f, 1.f);
        bool b_rainbow = false;
        float f_rainbow_speed = 0.f;

        color_var();
        color_var(C_Color color);

        color_var(ImColor col, bool rainbow, float speed);
        ~color_var();
        C_Color color() const;
        C_Color color(int alpha) const;
    };
}
