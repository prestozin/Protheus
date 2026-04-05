struct Color
{
    float r, g, b;

    Color operator*(float value) const
    {
        return { r * value, g * value, b * value };
    }

    Color operator+(const Color& other) const
    {
        return { r + other.r, g + other.g, b + other.b };
    }
};