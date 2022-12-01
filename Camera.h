#pragma once

class Camera
{
public:
	Camera(float x, float y);

	void centerFocus(float x, float y);
	void setFocus(float x, float y);
	void constrain(float x1, float y1, float x2, float y2);

	float getX() const;
	float getY() const;
	float getCenterX() const;
	float getCenterY() const;
	float getViewWidth() const;
	float getViewHeight() const;
private:
	float x_;
	float y_;
	float viewWidth_;
	float viewHeight_;
};