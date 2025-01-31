#pragma once
#include "mainHeader.h"

class Avatar
{
public:

	Avatar(b2Body* mBody, RectangleShape* mRectangleShape);
	Avatar(b2Body* mBody, Sprite* mSprite);
	~Avatar();

	float Rad2Deg(float mRadians);

	void UpdateAvatar();
	void Draw(RenderWindow& mWindow);

private:

	b2Body* mBodyAvatar;
	RectangleShape* mRectangleShapeAvatar = nullptr;
	Sprite* mSpriteAvatar = nullptr;
	b2Vec2 mPositionBodyAvatar;

	void Initialize(b2Body* mBody);
};