#include "Object.h"

Object::Object(float x, float y, int width, int height) {
	X = x;
	Y = y;
	m_width = width;
	m_height = height;
	m_left = -m_width / 2;
	m_right = m_width / 2;
	m_top = -m_height / 2;
	m_bottom = m_height / 2;
	Scale = 1.0f;
	Angle = 0.0f;
	RMask = BMask = GMask = AMask = 1.0f;
	HitR = 1.0f;
	Acceleration = 0.1f;
	Speed = 0.0f;
}

float Object::fixAngle(float angle) {
	if (angle < 0)
		angle += 360;
	if (angle > 360)
		angle -= 360;

	return angle;
}

void Object::turn(float targetAngle, float angleSpeed, int deltaTime) {
	float arch1 = 0.0;
	float arch2 = 0.0;

	if (Angle > targetAngle) {
		arch1 = Angle - targetAngle;
		arch2 = 360 + targetAngle - Angle;
	}

	if (Angle < targetAngle) {
		arch1 = 360 + Angle - targetAngle;
		arch2 = targetAngle - Angle;
	}

	if (arch1 < arch2)
		Angle -= deltaTime * angleSpeed;

	if (arch1 >= arch2)
		Angle += deltaTime * angleSpeed;

	Angle = Object::fixAngle(Angle);
}

float Object::calculateAngle(float x1, float y1, float x2, float y2) {
	float a = x2 - x1;
	float b = -y2 + y1;

	float angle = 0;

	if (a != 0 && b != 0)
		angle = acos(b / sqrt(pow(a, 2) + pow(b, 2)));

	if (b == 0 && a != 0) {
		angle = 90;
	} else if (a == 0 && b < 0)
		angle = 180;
	else if (angle != 0)
		angle = 180.0f / M_PI * angle;

	if (a < 0)
		angle = 360 - angle;

	return angle;
}

const float Object::getWidth()
{
	return m_width;
}

const float Object::getHeight()
{
	return m_width;
}

float Object::calculateDistance(float x1, float y1, float x2, float y2) {
	float a = x2 - x1;
	float b = -y2 + y1;

	return sqrt(pow(a, 2) + pow(b, 2));
}

void Object::move(int deltaTime) {
	X -= cos((Angle + 90) * M_PI / 180) * deltaTime * Speed;
	Y -= sin((Angle + 90) * M_PI / 180) * deltaTime * Speed;
}

const float Object::getLeft() {
	return X + m_left * Scale;
}

const float Object::getRight() {
	return X + m_right * Scale;
}

const float Object::getTop() {
	return Y + m_top * Scale;
}

const float Object::getBottom() {
	return Y + m_bottom * Scale;
}

const bool Object::detectCollide(Object *refObj) {
	return calculateDistance(X, Y, refObj->X, refObj->Y) < HitR * Scale * m_width + refObj->HitR * refObj->Scale * refObj->getWidth();
}
