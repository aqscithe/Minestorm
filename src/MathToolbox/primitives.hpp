#pragma once

#include <vector>

#include "Vector2f.hpp"


typedef struct line
{
    Vector2f point;
    Vector2f vector;
} line;

typedef struct segment
{
    Vector2f pointA;
    Vector2f pointB;
} segment;

typedef struct circle
{
    Vector2f center;
    float radius;
} circle;

typedef struct rectangle
{
    Vector2f center;
    float width;
    float height;
} rectangle;

typedef struct orientedRect
{
    rectangle rect;
    float angle;
} orientedRect;

typedef struct referential2
{
    Vector2f origin;     // l'origine locale
    Vector2f vector_i;  // x unit vector
    Vector2f vector_j;  // y unit vector
    float    angle;     // l'angle de rotation du référentiel par rapport au référentiel parent (le World)
} referential2;

typedef struct convexPolygon
{
    referential2            local;
    std::vector<Vector2f>   vertices;
} convexPolygon;

typedef struct range  // contient l'intervalle des quantités de projection d'une figure géométrique sur un axe
{
    float min;
    float max;
} range;

// le référentiel 2D d'un gameobject , défini par la position d'origine et deux vecteurs unitaires orthonormés . 
//La structure peut également contenir l'angle de rotation du référentiel par rapport au référentiel parent (le World)
