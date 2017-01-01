#ifndef __ICOMPONENT_H__
#define __ICOMPONENT_H__
#include "..\FrameWork\define.h"
#include "..\FrameWork\Sprite.h"
#include <numeric>
#include <map>
using namespace std;

class IComponent
{
public:
	virtual void update(float deltatime) = 0;
	virtual string GetName();
};

class Movement : public IComponent
{
public:
	Movement(GVector2 accel, GVector2 veloc, Sprite* refSprite);
	void update(float deltatime);

	void setAccelerate(GVector2 accel);
	void setVelocity(GVector2 veloc);
	GVector2 getAccelerate();
	GVector2 getVelocity();

private:
	GVector2 _accelerate;
	GVector2 _velocity;
	Sprite* _refSprite;
};

enum eGravityStatus
{
	FALLING__DOWN,
	SHALLOWED
};

class Gravity : public IComponent
{
public:
	Gravity(GVector2 gravity, Movement* movement);
	void setStatus(eGravityStatus status);
	eGravityStatus getStatus();
	void update(float deltatime);
	void setGravity(GVector2 gravity);

private:
	GVector2 _gravity;
	GVector2 _additionalVeloc;
	Movement* _refmovement;
	eGravityStatus _status;
	Sprite* _refSprite;
};

// chuyển động hình sin
class SinMovement : public IComponent
{
public:
	/*
	chuyển động hình sin
	@amplitude :  biên độ
	@frequency : tần số chuyển động
	@Axis : hướng chuyển động ( = X hoặc Y)
	throw exception nếu Axis khác x hoặc y
	*/
	SinMovement(GVector2 amplitude, float frequency, Sprite* refSprite);

	void update(float deltatime);
	void setAmplitude(GVector2 amplitude);
	void setFrequency(float freq);

	string GetName() override;

private:
	Sprite* _refSprite;

	float _radianVeloc; // vận tốc góc (= ω)
	float _radian; // góc xoay (= φ) biến thiên theo thời gian

	GVector2 _amplitude; // biên độ		(= A)
	GVector2 _linearVeloc; // vận tốc tuyến tính (= ωA)
};

class RoundMovement : public IComponent
{
public:

	RoundMovement(float radius, float frequency, float radian, Sprite* refSprite);

	void update(float deltatime);
	void setRadius(float r);
	void setAngularVeloc(float frequency);
	float getRadius();
	float getAngularVeloc();
	~RoundMovement();

private:
	Sprite* _refSprite;
	float _radius; // Bán Kính.
	GVector2 _roundposition;
	float _radianVeloc; // vận tốc góc (= ω)
	float _radian; // góc xoay (= φ) biến thiên theo thời gian
};


#endif // !__ICOMPONENT_H__
