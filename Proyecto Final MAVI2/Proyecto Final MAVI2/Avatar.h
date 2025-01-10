#pragma once
#include<box2d/box2d.h>
#include<SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

class Avatar
{
public:

	Avatar(b2Body* mBody, RectangleShape* mRectangleShape);
	Avatar(b2Body* mBody, Sprite* mSprite );
	~Avatar();

	void UpdateAvatar();
	void Draw(RenderWindow& mWindow);

	float Rad2Deg(float mRadians);

private:

	b2Body* mBodyAvatar;
	RectangleShape* mRectangleShapeAvatar;
	Sprite* mSpriteAvatar;

	b2Vec2 mPositionBodyAvatar;
};