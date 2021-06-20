#include <math.h>
#include <float.h>
#include <vector>
#include <iostream>

#include "Coordinates.hpp"
#include "primitives.hpp"
#include "geo_calculs.hpp"
#include "maths.hpp"


Vector2f v2::getVectorNull()
{
    return { 0.f, 0.f };
}

Vector2f v2::getVector(const Vector2f& coord_a, const Vector2f& coord_b)
{
    return { coord_b.m_x - coord_a.m_x, coord_b.m_y - coord_a.m_y };
}

float v2::vecMagnitude(const Vector2f& vector)
{
    return sqrtf(dotProduct(vector, vector));
}

float v2::getDistance(const Vector2f& coord_a, const Vector2f& coord_b)
{
    return sqrtf(powf(coord_a.m_x - coord_b.m_x, 2) + powf(coord_a.m_y - coord_b.m_y, 2));
}

float v2::getDistance(float a, float b)
{
    return sqrtf(powf(a, 2) + powf(b, 2));
}

Vector2f&   v2::getDirShortestDistance(std::vector<Coordinates>& positions, const Coordinates& myPos, Coordinates& targetPos)
{
    Coordinates posToFollow = { 0.f, 0.f };
    float distance = -99.99f;
    Vector2f resultantMineDirVec = { 0.f, 0.f };
    for (Coordinates& pos : positions)
    {
        float regularXDistance = pos.getX() - myPos.getX();
        float regularYDistance = pos.getY() - myPos.getY();
        
        float abnormalXDistance = regularXDistance - Coordinates::getGameLength();
        float abnormalYDistance = regularYDistance - Coordinates::getGameHeight();

        float minX = fabsf(regularXDistance) < fabsf(abnormalXDistance) ? regularXDistance : abnormalXDistance;
        float minY = fabsf(regularYDistance) < fabsf(abnormalYDistance) ? regularYDistance : abnormalYDistance;

        float mine_shipDistance = v2::getDistance(minX, minY);

        if (distance == -99.99f || mine_shipDistance < distance)
        {
            distance = mine_shipDistance;
            posToFollow = pos;
            resultantMineDirVec = { minX / Coordinates::getGameLength(), minY / Coordinates::getGameHeight() };
        }
    }
    targetPos = posToFollow;

    return resultantMineDirVec;
}

Vector2f& v2::getDirShortestDistance(std::vector<Coordinates>& positions, const Coordinates& myPos)
{
    float distance = -99.99f;
    Vector2f resultantMineDirVec = { 0.f, 0.f };
    for (Coordinates& pos : positions)
    {
        float regularXDistance = pos.getX() - myPos.getX();
        float regularYDistance = pos.getY() - myPos.getY();

        float abnormalXDistance = (Coordinates::getGameLength() - regularXDistance);
        float abnormalYDistance = (Coordinates::getGameHeight() - regularYDistance );

        float minX = fabsf(regularXDistance) < fabsf(abnormalXDistance) ? regularXDistance : abnormalXDistance;
        float minY = fabsf(regularYDistance) < fabsf(abnormalYDistance) ? regularYDistance : abnormalYDistance;

        float mine_shipDistance = v2::getDistance(minX, minY);

        if (distance == -99.99f || mine_shipDistance < distance)
        {
            distance = mine_shipDistance;
            resultantMineDirVec = { minX / Coordinates::getGameLength(), minY / Coordinates::getGameHeight() };
        }
    }

    return resultantMineDirVec;
}

float   v2::dotProduct(const Vector2f& a, const Vector2f& b)
{
    return { a.m_x * b.m_x + a.m_y * b.m_y };
}

Vector2f v2::getUnitVector(const Vector2f& vector)
{
    float magnitude = vecMagnitude(vector);
    if (magnitude == 0)
    {
        std::cerr << "Division by zero getting unit vector! Exiting...\n" << std::endl;
        exit(1);
    }
    return { vector.m_x / magnitude, vector.m_y / magnitude };
}

Vector2f  v2::normal(const Vector2f& vector)
{
    return { -vector.m_y, vector.m_x };
}

float v2::getMagnitudeSquared(const Vector2f& vector)
{
    return powf ( vecMagnitude(vector), 2 );
}

Vector2f v2::getNegativeVector(const Vector2f& vector)
{
    return { vector.m_x * -1, vector.m_y * -1};
}

float v2::getAngle(const Vector2f& vectorA, const Vector2f& vectorB)
{
    float magnitudeA = vecMagnitude(vectorA);
    float magnitudeB = vecMagnitude(vectorB);
    if ( magnitudeA == 0 || magnitudeB == 0 ) 
    {
        std::cerr << "Division by zero finding angle! Exiting...\n" << std::endl;
        exit(1);
    }
    float angle = acosf (dotProduct(vectorA, vectorB) / (magnitudeA * magnitudeB));
    if ( angle > 180 )
        return 360 - angle;
    return angle;
}

Vector2f v2::rotateVector(const Vector2f& vector, float angleRotation)
{
    return { cosf(angleRotation) * vector.m_x - sinf(angleRotation) * vector.m_y, sinf(angleRotation) * vector.m_x + cosf(angleRotation) * vector.m_y };
}

Vector2f v2::rotateVector90(const Vector2f& vector)
{
    return { cosf(90) * vector.m_x - sinf(90) * vector.m_y, sinf(90) * vector.m_x + cosf(90) * vector.m_y };
}


Vector2f& rotatePoint(const Vector2f& center, Vector2f& point, float angleRotation)
{
    // angle should be expressed in radians

    angleRotation *= maths::M_PI / 180.f;

    float s = sinf(angleRotation);
    float c = cosf(angleRotation);

    // translate point back to origin:

    point -= center;

    // rotate point
    float xNew = point.m_x * c - point.m_y * s;
    float yNew = point.m_x * s + point.m_y * c;

    // translate point back:

    point.m_x = xNew + center.m_x;
    point.m_y = yNew + center.m_y;

    return point;
}

Vector2f localToGlobalOPWorld(const Vector2f& origin, const Vector2f& originPrime, const Vector2f& vector_i, const Vector2f& vector_j, const Vector2f& pointPp)
{ 
    // on cherche vector OP world

    Vector2f O_P = { 0.f, 0.f };
    Vector2f Op_P = { 0.f, 0.f };

    Vector2f OOp = v2::getVector(origin, originPrime);
    Op_P.m_x = pointPp.m_x * vector_i.m_x + pointPp.m_y * vector_j.m_x;
    Op_P.m_y = pointPp.m_x * vector_i.m_y + pointPp.m_y * vector_j.m_y;

    O_P.m_x = Op_P.m_x + OOp.m_x;
    O_P.m_y = Op_P.m_y + OOp.m_x;

    return O_P;
}

Vector2f localToGlobalVectorWorld(const Vector2f& origin, const Vector2f& originPrime, const Vector2f& vector_i, const Vector2f& vector_j, const Vector2f& vectorPrime)
{
    Vector2f vectorWorld = { 0.f, 0.f };
    vectorWorld.m_x = vectorPrime.m_x * vector_i.m_x + vectorPrime.m_y * vector_j.m_x;
    vectorWorld.m_y = vectorPrime.m_x * vector_i.m_y + vectorPrime.m_y * vector_j.m_y;

    return vectorWorld;
}

Vector2f globalToLocalPPrime(const Vector2f& origin, const Vector2f& originPrime, const Vector2f& vector_i, const Vector2f& vector_j, const Vector2f& pointP)
{
    // on cherche point p prime
    Vector2f pointPp = { 0.f, 0.f };
    const Vector2f Op_P = { pointP.m_x * vector_i.m_x + pointP.m_y * vector_j.m_x, pointP.m_x * vector_i.m_y + pointP.m_y * vector_j.m_y};

    pointPp.m_x = v2::dotProduct(Op_P, vector_i);
    pointPp.m_y = v2::dotProduct(Op_P, vector_j);

    return pointPp;
}

Vector2f convertPointGameScreen(const Vector2f& point)
{
    return { point.m_x, (float)Coordinates::getSpaceHeight() - point.m_y };
}



Vector2f globalToLocalVectorPrime(const Vector2f& origin, const Vector2f& originPrime, const Vector2f& vector_i, const Vector2f& vector_j, Vector2f& vectorWorld)
{
    Vector2f vectorLocal = { 0.f, 0.f};

    vectorLocal.m_x = v2::dotProduct(vectorWorld, vector_i);
    vectorLocal.m_y = v2::dotProduct(vectorWorld, vector_j);
    return vectorLocal;
}


float minf(float valA, float valB)
{
    if (valA < valB)
        return valA;
    return valB;
}

float maxf(float valA, float valB)
{
    if (valA > valB)
        return valA;
    return valB;
}

range getEncompassingRange(const range rangeA, const range rangeB)
{
    range result = { 0.f, 0.f };

    if (rangeA.min < rangeB.min)
        result.min = rangeA.min;
    else
        result.min = rangeB.min;
    
    if (rangeA.max > rangeB.max)
        result.max = rangeA.max;
    else
        result.max = rangeB.max;

    return result;
}

range getProjectedRange(range currRange, float projection)
{
    currRange.min += projection;
    currRange.max += projection;

    return currRange;
}

bool rangesIntersect(const range rangeA, const range rangeB)
{
    return (rangeB.max < rangeA.max && rangeB.max > rangeA.min) || (rangeB.min > rangeA.min && rangeB.min < rangeA.max) || (rangeA.min > rangeB.min && rangeA.min < rangeB.max) || (rangeA.max < rangeB.max && rangeA.max > rangeB.min);
}

range getRangeOfPoint(const Vector2f& point)
{
    return  {point.m_x, point.m_x};
}

Vector2f getMaxPoint(const Vector2f& pointA, const Vector2f& pointB)
{
    if (pointA.m_x > pointB.m_x)
        return pointA;
    return pointB;
}

Vector2f getMinPoint(const Vector2f& pointA, const Vector2f& pointB)
{
    if (pointA.m_x < pointB.m_x)
        return pointA;
    return pointB;
}

range getRangeOfSegment(const segment seg)
{
    return { getMinPoint(seg.pointA, seg.pointB).m_x, getMaxPoint(seg.pointA, seg.pointB).m_x };
}

range getRangeOfBox(const rectangle rect)
{
    // obtenir coordonnées des quatres coins
    Vector2f bottomLeft = { rect.center.m_x - (0.5f * rect.width), rect.center.m_y - (0.5f * rect.height) };
    Vector2f topLeft = { rect.center.m_x - (0.5f * rect.width), rect.center.m_y + (0.5f * rect.height) };
    Vector2f topRight = { rect.center.m_x + (0.5f * rect.width), rect.center.m_y + (0.5f * rect.height) };
    Vector2f bottomRight = { rect.center.m_x + (0.5f * rect.width), rect.center.m_y - (0.5f * rect.height) };

    // initialiser box range
    range boxRange = { 0.f, 0.f };

    // trouver le minimum
    if (topLeft.m_x < boxRange.min)
    {
        boxRange.min = topLeft.m_x;
    }
    if (topRight.m_x < boxRange.min)
    {
        boxRange.min = topRight.m_x; 
    }
    if (bottomRight.m_x < boxRange.min)
    {
        boxRange.min = bottomRight.m_x; 
    }

    // trouver le max
    if (topLeft.m_x > boxRange.max)
    {
        boxRange.max = topLeft.m_x;
    }
    if (topRight.m_x > boxRange.max)
    {
        boxRange.max = topRight.m_x;
    }
    if (bottomRight.m_x > boxRange.max)
    {
        boxRange.max = bottomRight.m_x;
    }

    return boxRange;
}


range getRangeOfCircle(const circle cir)
{
    // obtenir 2 points diamétricalment opposés
    Vector2f pointA = { cir.center.m_x + cir.radius, cir.center.m_y };
    Vector2f pointB = { cir.center.m_x - cir.radius, cir.center.m_y };

    return { getMinPoint(pointA, pointB).m_x, getMaxPoint(pointA, pointB).m_x };
}

// point to point collision detection
bool collision::pointToPoint(const Vector2f& pointA, const Vector2f& pointB)
{
    return powf((pointB.m_x - pointA.m_x), 2) + powf((pointB.m_y - pointA.m_y), 2) < FLT_EPSILON;
}

bool collision::pointToLine(const Vector2f& point, const line _line)
{
    const Vector2f AP = v2::getVector(_line.point, point);
    const Vector2f m = v2::normal(_line.vector);

    return (abs(v2::dotProduct(AP, m)) < FLT_EPSILON);
}

bool collision::lineToLine(const line lineA, const line lineB)
{
    Vector2f AB = v2::getVector(lineA.point, lineB.point);

    if (v2::dotProduct(v2::normal(lineA.vector), lineB.vector) != 0)
        return true;
    
    if (v2::dotProduct(v2::normal(lineA.vector), lineB.vector) == 0)
        return false;

    if (v2::dotProduct(AB, v2::normal(lineB.vector)) < FLT_EPSILON)
        return true;
    return false;
}

bool collision::lineToSegment(const line _line, const segment seg)
{
    Vector2f AP = v2::getVector(_line.point, seg.pointA);
    Vector2f BP = v2::getVector(_line.point, seg.pointB);

    if (v2::dotProduct(AP, _line.vector ) * v2::dotProduct(BP, _line.vector) > 0)
        return false;

    line fromSegment = { seg.pointA, v2::getVector(seg.pointA, seg.pointB) };

    return collision::lineToLine(_line, fromSegment);
}

float min(float num1, float num2)
{
    if (num1 < num2)
        return num1;
    return num2;
}

float max(float num1, float num2)
{
    if (num1 > num2)
        return num1;
    return num2;
}

bool collision::segmentToSegment(const segment segA, const segment segB)
{
    range _range;

    // 
    Vector2f midSegA = { (segA.pointA.m_x + segA.pointB.m_x) / 2, (segA.pointA.m_y + segA.pointB.m_y) / 2 };
    Vector2f midSegB = { (segB.pointA.m_x + segB.pointB.m_x) / 2, (segB.pointA.m_y + segB.pointB.m_y) / 2 };

    //_range.min.m_x = min(getDotProduct())
    return true;
}

bool collision::circleToPoint(const circle cir, const Vector2f& point)
{
    if (pow(cir.center.m_x, 2) + pow(cir.center.m_y, 2) <= pow(cir.radius, 2))
        return true;
    return false;
}

bool collision::circleToLine(const circle cir, const line _line)
{
    return (abs(v2::dotProduct(v2::getVector(_line.point, cir.center), v2::normal(_line.vector)) <= cir.radius));
}

bool collision::circleToSegment(const circle cir, const segment seg)
{
    line fromSegment = { seg.pointA, v2::getVector(seg.pointA, seg.pointB) };
    if (!collision::circleToLine(cir, fromSegment))
        return true;
    
    Vector2f AC = v2::getVector(seg.pointA, cir.center);
    Vector2f segmentVector = v2::getVector(seg.pointA, seg.pointB);

    float dotProductACSeg = v2::dotProduct(AC, segmentVector);

    Vector2f projected = { segmentVector.m_x * dotProductACSeg, segmentVector.m_y * dotProductACSeg };

    return (v2::dotProduct(projected, segmentVector) >= 0 || v2::dotProduct(projected, segmentVector) <= v2::getMagnitudeSquared(segmentVector));
}

float clamp(float value, float min, float max)
{
    if (value > max)
        return max;
    if (value < min)
        return min;
    return value;
}

float angleClamp(float value)
{
    if (value < 0.f)
        return 360.f + value;
    if (value > 360.f)
        return value - 360;
    return value;
}

bool collision::boxToCircle(const rectangle rect, const circle cir)
{
    // trouver le point sur le box le plus proche (H) au centre du cercle

    Vector2f coord_H = { 0.f, 0.f };

    coord_H.m_x = clamp(cir.center.m_x, rect.center.m_x - 0.5f * rect.width, rect.center.m_x + 0.5f * rect.width);
    coord_H.m_y = clamp(cir.center.m_y, rect.center.m_y - 0.5f * rect.height, rect.center.m_y + 0.5f * rect.height);

    if (cir.center.m_x >= rect.center.m_x - 0.5f * rect.width && cir.center.m_x <= rect.center.m_x + 0.5f * rect.width
         && cir.center.m_y >= rect.center.m_y - 0.5 * rect.height && cir.center.m_y <= rect.center.m_y + 0.5f * rect.height)
        return true;
    
    return v2::getDistance(coord_H, cir.center) <= cir.radius;

}

void getPolyNormals(std::vector<Vector2f>& normals, const std::vector<Vector2f>& vertices)
{
    for (int i = 0; i < vertices.size(); ++i)
    {
        if ((i + 1) == vertices.size())
            normals.push_back(v2::getUnitVector(v2::normal(v2::getVector(convertPointGameScreen(vertices.at(i)), convertPointGameScreen(vertices.at(0))))));
        else
            normals.push_back(v2::getUnitVector(v2::normal(v2::getVector(convertPointGameScreen(vertices.at(i)), convertPointGameScreen(vertices.at(i + 1))))));
    }
}

void getPolyRanges(const std::vector<Vector2f>& normals, const convexPolygon cp, std::vector<range>& axisRanges)
{
    float max = 0.f;
    float min = 0.f;

    for (int i = 0; i < normals.size(); ++i)
    {
        for (int j = 0; j < cp.vertices.size(); ++j)
        {
            // should be between normal and vector OP
            float dotProd = v2::dotProduct(normals.at(i), convertPointGameScreen(cp.vertices.at(j)));
            if (j == 0)
            {
                min = dotProd;
                max = dotProd;
            }
            else if (dotProd < min)
                min = dotProd;
            else if (dotProd > max)
                max = dotProd;
        }
        axisRanges.push_back({ min, max });
    }
}

void getPointRanges(std::vector<range>& pointRanges, const std::vector<Vector2f>& normals, const Vector2f& origin, const Vector2f& point)
{
    for (int i = 0; i < normals.size(); ++i)
    {
        float dotProd = v2::dotProduct(normals.at(i), convertPointGameScreen(point));
        pointRanges.push_back({ dotProd, dotProd });
    }
}

bool collision::convexPolyToConvexPoly(convexPolygon cp1, convexPolygon cp2)
{
    if (cp1.vertices.size() < 3 || cp2.vertices.size() < 3)
    {
        return false;
    }

    std::vector<Vector2f> normalsCP1;
    std::vector<Vector2f> normalsCP2;
    std::vector<range>    axisRangesCP1;
    std::vector<range>    axisRangesCP2;

    getPolyNormals(normalsCP1, cp1.vertices);
    getPolyNormals(normalsCP2, cp2.vertices);

    getPolyRanges(normalsCP1, cp1, axisRangesCP1);
    getPolyRanges(normalsCP2, cp2, axisRangesCP2);

    for (int i = 0; i < axisRangesCP1.size(); ++i)
    {
        if (!rangesIntersect(axisRangesCP1.at(i), axisRangesCP2.at((i + 0) % axisRangesCP2.size())))
            return false;
    }

    return true;
}

bool collision::convexPolyToPoint(const convexPolygon cp, const Vector2f& point)
{
    std::vector<Vector2f> normals;
    std::vector<range>    axisRanges;
    std::vector<range>    pointRanges;

    getPolyNormals(normals, cp.vertices);
    getPolyRanges(normals, cp, axisRanges);
    getPointRanges(pointRanges, normals, cp.local.origin, point);

    for (int i = 0; i < pointRanges.size(); ++i)
    {
        if (!rangesIntersect(axisRanges.at(i), pointRanges.at(i)))
        {
            return false;
        }
    }
    return true;
}

