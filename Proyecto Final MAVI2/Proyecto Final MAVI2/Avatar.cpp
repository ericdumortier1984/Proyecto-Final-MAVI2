#include"Avatar.h"

Avatar::Avatar(b2Body* mBody, RectangleShape* mRectangleShape) : mBodyAvatar(mBody), mRectangleShapeAvatar(mRectangleShape)
{

	Initialize(mBody);
}

Avatar::Avatar(b2Body* mBody, Sprite* mSprite) : mBodyAvatar(mBody), mSpriteAvatar(mSprite)
{

	Initialize(mBody);
}

void Avatar::Initialize(b2Body* mBody)
{

	b2AABB mDimensions;
	mPositionBodyAvatar = mBodyAvatar->GetPosition();

	if (mRectangleShapeAvatar)
	{
		mRectangleShapeAvatar->setPosition(mPositionBodyAvatar.x, mPositionBodyAvatar.y);
		mRectangleShapeAvatar->setOrigin(mRectangleShapeAvatar->getSize().x / 2, mRectangleShapeAvatar->getSize().y / 2);
		mRectangleShapeAvatar->setRotation(Rad2Deg(mBodyAvatar->GetAngle()));
	}

	if (mSpriteAvatar)
	{
		mSpriteAvatar->setOrigin(mSpriteAvatar->getTexture()->getSize().x / 2.f, mSpriteAvatar->getTexture()->getSize().y / 2.f);
		mSpriteAvatar->setPosition(mPositionBodyAvatar.x, mPositionBodyAvatar.y);
		mSpriteAvatar->setRotation(Rad2Deg(mBodyAvatar->GetAngle()));
	}

	// Inicializamos las dimensiones del AABB (Axis-Aligned Bounding Box)
	mDimensions.lowerBound = (b2Vec2(FLT_MAX, FLT_MAX));
	mDimensions.upperBound = (b2Vec2(-FLT_MAX, -FLT_MAX));

	// Recorremos todas las 'fixtures' del cuerpo de Box2D para calcular el AABB del sprite
	for (b2Fixture* i = mBodyAvatar->GetFixtureList(); i; i = i->GetNext())
	{
		mDimensions = i->GetAABB(0);
	}

	if (mRectangleShapeAvatar)
	{
		mRectangleShapeAvatar->setSize({ mDimensions.GetExtents().x * 2, mDimensions.GetExtents().y * 2 });
	}

	if (mSpriteAvatar)
	{
		mSpriteAvatar->setScale(mDimensions.GetExtents().x * 2.5 / mSpriteAvatar->getTexture()->getSize().x,
			mDimensions.GetExtents().y * 2.5 / mSpriteAvatar->getTexture()->getSize().y);
	}
}

void Avatar::UpdateAvatar()
{

	mPositionBodyAvatar = mBodyAvatar->GetPosition();

	if (mRectangleShapeAvatar)
	{
		mRectangleShapeAvatar->setPosition(mPositionBodyAvatar.x, mPositionBodyAvatar.y);
		mRectangleShapeAvatar->setRotation(Rad2Deg(mBodyAvatar->GetAngle()));
		//cout << "Rectangle Avatar Position: " << mPositionBodyAvatar.x << ", " << mPositionBodyAvatar.y << endl;
	}

	if (mSpriteAvatar)
	{
		mSpriteAvatar->setPosition(mPositionBodyAvatar.x, mPositionBodyAvatar.y);
		mSpriteAvatar->setRotation(Rad2Deg(mBodyAvatar->GetAngle()));
		//cout << "Sprite Avatar Position: " << mPositionBodyAvatar.x << ", " << mPositionBodyAvatar.y << endl;
	}
}

float Avatar::Rad2Deg(float mRadians)
{

	return mRadians * 180 / 3.14;
}

void Avatar::Draw(RenderWindow& mWindow)
{

	UpdateAvatar();

	if (mRectangleShapeAvatar)
	{
		mWindow.draw(*mRectangleShapeAvatar);
	}

	if (mSpriteAvatar)
	{
		mWindow.draw(*mSpriteAvatar);
	}
}

Avatar::~Avatar()
{

	delete mRectangleShapeAvatar;
	delete mSpriteAvatar;
}