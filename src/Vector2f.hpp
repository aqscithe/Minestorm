#pragma once

class Vector2f
{
    private:
        

    public:
        float                   m_x = 0.f;
        float                   m_y = 0.f;


        Vector2f();
        Vector2f(float x, float y);

        ~Vector2f() = default;

        void                    set(float x, float y);
        static Vector2f         fromAngle(float speed, float rotation);

        Vector2f                operator*(const Vector2f& other);
        Vector2f                operator+(const Vector2f& other);
        Vector2f                operator-(const Vector2f& other);
        Vector2f                operator*(float scalaire);
        Vector2f&               operator+=(const Vector2f& other);
        Vector2f&               operator-=(const Vector2f& other);
        Vector2f&               operator*=(float scalaire);
        bool                    operator==(const Vector2f& other);
        bool                    operator!=(const Vector2f& other);
};