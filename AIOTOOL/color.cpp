#include "color.h"
#include <chrono>


C_Color C_Color::Black(0, 0, 0, 255);
C_Color C_Color::White(255, 255, 255, 255);
C_Color C_Color::Red(255, 0, 0, 255);
C_Color C_Color::Green(0, 255, 0, 255);
C_Color C_Color::Blue(0, 0, 255, 255);

C_Color::C_Color()
{
    *((int*)this) = 0;
}
C_Color::C_Color(int _r, int _g, int _b)
{
    SetColor(_r, _g, _b, 255);
}
C_Color::C_Color(int _r, int _g, int _b, int _a)
{
    SetColor(_r, _g, _b, _a);
}

C_Color C_Color::FromHSB(float hue, float saturation, float brightness)
{
    float h = hue == 1.0f ? 0 : hue * 6.0f;
    float f = h - (int)h;
    float p = brightness * (1.0f - saturation);
    float q = brightness * (1.0f - saturation * f);
    float t = brightness * (1.0f - (saturation * (1.0f - f)));

    if (h < 1)
    {
        return C_Color(
            (unsigned char)(brightness * 255),
            (unsigned char)(t * 255),
            (unsigned char)(p * 255)
        );
    }
    else if (h < 2)
    {
        return C_Color(
            (unsigned char)(q * 255),
            (unsigned char)(brightness * 255),
            (unsigned char)(p * 255)
        );
    }
    else if (h < 3)
    {
        return C_Color(
            (unsigned char)(p * 255),
            (unsigned char)(brightness * 255),
            (unsigned char)(t * 255)
        );
    }
    else if (h < 4)
    {
        return C_Color(
            (unsigned char)(p * 255),
            (unsigned char)(q * 255),
            (unsigned char)(brightness * 255)
        );
    }
    else if (h < 5)
    {
        return C_Color(
            (unsigned char)(t * 255),
            (unsigned char)(p * 255),
            (unsigned char)(brightness * 255)
        );
    }
    else
    {
        return C_Color(
            (unsigned char)(brightness * 255),
            (unsigned char)(p * 255),
            (unsigned char)(q * 255)
        );
    }
}



void C_Color::SetRawColor(int color32)
{
    *((int*)this) = color32;
}
int C_Color::GetRawColor() const
{
    return *((int*)this);
}

void C_Color::SetColor(int _r, int _g, int _b, int _a)
{
    _CColor[0] = (unsigned char)_r;
    _CColor[1] = (unsigned char)_g;
    _CColor[2] = (unsigned char)_b;
    _CColor[3] = (unsigned char)_a;
}
void C_Color::SetColor(float _r, float _g, float _b, float _a)
{
    _CColor[0] = static_cast<unsigned char>(_r * 255.0f);
    _CColor[1] = static_cast<unsigned char>(_g * 255.0f);
    _CColor[2] = static_cast<unsigned char>(_b * 255.0f);
    _CColor[3] = static_cast<unsigned char>(_a * 255.0f);
}
void C_Color::GetColor(int& _r, int& _g, int& _b, int& _a) const
{
    _r = _CColor[0];
    _g = _CColor[1];
    _b = _CColor[2];
    _a = _CColor[3];
}


bool C_Color::operator== (const C_Color& rhs) const
{
    return (*((int*)this) == *((int*)&rhs));
}
bool C_Color::operator!= (const C_Color& rhs) const
{
    return !(operator==(rhs));
}
C_Color& C_Color::operator=(const C_Color& rhs)
{
    SetRawColor(rhs.GetRawColor());
    return *this;
}


namespace utils
{

    long long GetEpochTime()
    {
        const auto duration = std::chrono::system_clock::now().time_since_epoch();

        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }


    color_var::color_var()
    {
        col_color = ImColor(0.f, 0.f, 0.f, 1.f);
        b_rainbow = false;
        f_rainbow_speed = 0.f;
    }

    color_var::color_var(C_Color color)
    {
        col_color = ImColor(color.r() / 255.f, color.g() / 255.f, color.b() / 255.f, 1.f);
        b_rainbow = false;
        f_rainbow_speed = 0.f;
    }

    color_var::color_var(ImColor col, bool rainbow, float speed)
    {
        col_color = col;
        b_rainbow = rainbow;
        f_rainbow_speed = speed;
    }
    color_var::~color_var()
    {

    }

    C_Color color_var::color() const
    {
        C_Color col_result = { static_cast<int>(col_color.Value.x * 255), static_cast<int>(col_color.Value.y * 255), static_cast<int>(col_color.Value.z * 255), static_cast<int>(col_color.Value.w * 255) };
        if (b_rainbow)
        {
            col_result = GetRainbowColor(f_rainbow_speed);
            col_result.SetAlpha(static_cast<int>(col_color.Value.w * 255));
        }

        return col_result;
    }

    C_Color color_var::color(int alpha) const
    {


        C_Color col_result = { static_cast<int>(col_color.Value.x * 255), static_cast<int>(col_color.Value.y * 255), static_cast<int>(col_color.Value.z * 255), alpha };
        if (b_rainbow)
        {
            col_result = GetRainbowColor(f_rainbow_speed);
            col_result.SetAlpha(alpha);
        }

        return col_result;
    }


    C_Color GetRainbowColor(float speed)
    {
        speed = 0.002f * speed;
        const auto now = GetEpochTime();
        const auto hue = now % static_cast<int>(1.0f / speed) * speed;

        return C_Color::FromHSB(hue, 1.0f, 1.0f);
    }

}