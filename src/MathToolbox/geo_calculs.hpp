#pragma once

#include "primitives.hpp"

namespace v2
{

	Vector2f getVectorNull();

	Vector2f getVector(const Vector2f& coord_a, const Vector2f& coord_b);

	float vecMagnitude(const Vector2f& vector);

	float getDistance(const Vector2f& coord_a, const Vector2f& coord_b);

	float getDistance(float a, float b);

	Vector2f& getDirShortestDistance(std::vector<Coordinates>& positions, const Coordinates& myPos, Coordinates& targetPos);

	Vector2f& getDirShortestDistance(std::vector<Coordinates>& positions, const Coordinates& myPos);

	float   dotProduct(const Vector2f& a, const Vector2f& b);

	Vector2f getUnitVector(const Vector2f& vector);

	Vector2f  normal(const Vector2f& vector);

	float getMagnitudeSquared(const Vector2f& vector);

	Vector2f getNegativeVector(const Vector2f& vector);

	float getAngle(const Vector2f& vectorA, const Vector2f& vectorB);

	Vector2f rotateVector(const Vector2f& vector, float angleRotation);

	Vector2f rotateVector90(const Vector2f& vector);

}

Vector2f& rotatePoint(const Vector2f& center, Vector2f& point, float angleRotation);

Vector2f localToGlobalOPWorld(const Vector2f& origin, const Vector2f& originPrime, const Vector2f& vector_i, const Vector2f& vector_j, const Vector2f& pointP);

Vector2f localToGlobalVectorWorld(const Vector2f& origin, const Vector2f& originPrime, const Vector2f& vector_i, const Vector2f& vector_j, const Vector2f& vectorPrime);

Vector2f globalToLocalPPrime(const Vector2f& origin, const Vector2f& originPrime, const Vector2f& vector_i, const Vector2f& vector_j, const Vector2f& pointP);

Vector2f getMaxPoint(const Vector2f& pointA, const Vector2f& pointB);

Vector2f getMinPoint(const Vector2f& pointA, const Vector2f& pointB);

range getEncompassingRange(const range rangeA, const range rangeB);

range getProjectedRange(range currRange, float projection);

bool rangesIntersect(const range rangeA, const range rangeB);

range getRangeOfPoint(const Vector2f& point);

range getRangeOfSegment(const segment seg);

range getRangeOfBox(const rectangle rect);

range getRangeOfCircle(const circle cir);

float min(float num1, float num2);

float max(float num1, float num2);

float clamp(float value, float min, float max);

float angleClamp(float value);

void getPolyNormals(std::vector<Vector2f>& normals, const std::vector<Vector2f>& vertices);

void getPolyRanges(const std::vector<Vector2f>& normals, const convexPolygon cp, std::vector<range>& axisRanges);

void getPointRanges(std::vector<range>& pointRange, const std::vector<Vector2f>& normals, const Vector2f& origin, const Vector2f& point);

Vector2f convertPointGameScreen(const Vector2f& point);

float minf(float valA, float valB);

float maxf(float valA, float valB);

namespace collision
{
	bool pointToPoint(const Vector2f& pointA, const Vector2f& pointB);

	bool pointToLine(const Vector2f& point, const line _line);

	bool lineToLine(const line lineA, const line lineB);

	bool lineToSegment(const line _line, const segment seg);

	bool segmentToSegment(const segment segA, const segment segB);

	bool circleToPoint(const circle cir, const Vector2f& point);

	bool circleToLine(const circle cir, const line _line);

	bool circleToSegment(const circle cir, const segment seg);

	bool boxToCircle(const rectangle rect, const circle cir);

	bool convexPolyToPoint(const convexPolygon cp, const Vector2f& point);

	bool convexPolyToConvexPoly( convexPolygon cp1, convexPolygon cp2);
}