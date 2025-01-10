#include"Avatar.h"

Avatar::Avatar(b2Body* mBody, RectangleShape* mRectangleShape) : mBodyAvatar(mBody), mRectangleShapeAvatar(mRectangleShape)
{

	b2AABB mDimensions;
	mPositionBodyAvatar = mBodyAvatar->GetPosition();

	mRectangleShapeAvatar->setPosition(mPositionBodyAvatar.x, mPositionBodyAvatar.y);
	mRectangleShapeAvatar->setOrigin(mRectangleShapeAvatar->getSize().x / 2, mRectangleShapeAvatar->getSize().y / 2);
	mRectangleShapeAvatar->setRotation(Rad2Deg(mBodyAvatar->GetAngle()));

	// Inicializamos las dimensiones del AABB (Axis-Aligned Bounding Box)
	mDimensions.lowerBound = (b2Vec2(FLT_MAX, FLT_MAX));
	mDimensions.upperBound = (b2Vec2(-FLT_MAX, -FLT_MAX));

	// Recorremos todas las 'fixtures' del cuerpo de Box2D para calcular el AABB del sprite
	for (b2Fixture* i = mBodyAvatar->GetFixtureList(); i; i = i->GetNext())
	{
		mDimensions = i->GetAABB(0);
	}

	mRectangleShapeAvatar->setSize({ mDimensions.GetExtents().x * 2, mDimensions.GetExtents().y * 2 });

}

Avatar::Avatar(b2Body* mBody, Sprite* mSprite) : mBodyAvatar(mBody), mSpriteAvatar(mSprite)
{

	b2AABB mDimensions;
	mPositionBodyAvatar = mBodyAvatar->GetPosition();

	mSpriteAvatar->setOrigin(mSpriteAvatar->getTexture()->getSize().x / 2.f, mSpriteAvatar->getTexture()->getSize().y / 2.f);
	mSpriteAvatar->setPosition(mPositionBodyAvatar.x, mPositionBodyAvatar.y);
	mSpriteAvatar->setRotation(Rad2Deg(mBodyAvatar->GetAngle()));

	// Inicializamos las dimensiones del AABB (Axis-Aligned Bounding Box)
	mDimensions.lowerBound = (b2Vec2(FLT_MAX, FLT_MAX));
	mDimensions.upperBound = (b2Vec2(-FLT_MAX, -FLT_MAX));

	// Recorremos todas las 'fixtures' del cuerpo de Box2D para calcular el AABB del sprite
	for (b2Fixture* i = mBodyAvatar->GetFixtureList(); i; i = i->GetNext())
	{
		mDimensions = i->GetAABB(0);
	}

	mSpriteAvatar->setScale(mDimensions.GetExtents().x * 2.5 / mSpriteAvatar->getTexture()->getSize().x,
		mDimensions.GetExtents().y * 2.5 / mSpriteAvatar->getTexture()->getSize().y);
}

void Avatar::UpdateAvatar()
{

	mPositionBodyAvatar = mBodyAvatar->GetPosition();
	mRectangleShapeAvatar->setPosition(mPositionBodyAvatar.x, mPositionBodyAvatar.y);
	mRectangleShapeAvatar->setRotation(Rad2Deg(mBodyAvatar->GetAngle()));

	mSpriteAvatar->setPosition(mPositionBodyAvatar.x, mPositionBodyAvatar.y);
	mSpriteAvatar->setRotation(Rad2Deg(mBodyAvatar->GetAngle()));
}

float Avatar::Rad2Deg(float mRadians)
{

	return mRadians * 180 / 3.14;
}

void Avatar::Draw(RenderWindow& mWindow)
{

	UpdateAvatar();
	mWindow.draw(*mRectangleShapeAvatar);
	mWindow.draw(*mSpriteAvatar);
}

Avatar::~Avatar()
{

	delete mRectangleShapeAvatar;
	delete mSpriteAvatar;
}