#include "Camera.h"
#include "Config.h"

Camera::Camera(float x, float y) :
	x_(x),
	y_(y),
	viewWidth_(Config::windowWidth / Config::globalScale),
	viewHeight_(Config::windowHeight / Config::globalScale)
{}

void Camera::centerFocus(float x, float y)
{
	x_ = x - viewWidth_ * 0.5f;
	y_ = y - viewHeight_ * 0.5f;
}

void Camera::setFocus(float x, float y)
{
	x_ = x;
	y_ = y;
}

void Camera::constrain(float x1, float y1, float x2, float y2)
{
	float currX2 = x_ + viewWidth_;
	float currY2 = y_ + viewHeight_;

	if (x_ < x1)
	{
		x_ = x1;
	}
	if (y_ < y1)
	{
		y_ = y1;
	}
	if (currX2 > x2)
	{
		x_ = x2 - viewWidth_;
	}
	if (currY2 > y2)
	{
		y_ = y2 - viewHeight_;
	}
}

float Camera::getX() const
{
	return x_;
}

float Camera::getY() const
{
	return y_;
}

float Camera::getCenterX() const
{
	return x_ + viewWidth_ * 0.5f;
}

float Camera::getCenterY() const
{
	return y_ + viewHeight_ * 0.5f;
}

float Camera::getViewWidth() const
{
	return viewWidth_;
}

float Camera::getViewHeight() const
{
	return viewHeight_;
}