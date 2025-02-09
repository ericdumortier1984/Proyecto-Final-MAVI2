#include"Avatar.h"

// Constructor Box2D y RectangleShape
Avatar::Avatar(b2Body* mBody, RectangleShape* mRectangleShape) : mBodyAvatar(mBody), mRectangleShapeAvatar(mRectangleShape)
{

	Initialize(mBody);
}

// Constructor Box2D y Sprite
Avatar::Avatar(b2Body* mBody, Sprite* mSprite) : mBodyAvatar(mBody), mSpriteAvatar(mSprite)
{

	Initialize(mBody);
}

//  Inicializacion del avatar
void Avatar::Initialize(b2Body* mBody)
{

	b2AABB mDimensions;
	mPositionBodyAvatar = mBodyAvatar->GetPosition();

	// Configuracion incial del RectangleShape si existe
	if (mRectangleShapeAvatar)
	{
		mRectangleShapeAvatar->setPosition(mPositionBodyAvatar.x, mPositionBodyAvatar.y);
		mRectangleShapeAvatar->setOrigin(mRectangleShapeAvatar->getSize().x / 2, mRectangleShapeAvatar->getSize().y / 2);
		mRectangleShapeAvatar->setRotation(Rad2Deg(mBodyAvatar->GetAngle()));
	}

	// Configuracion inicial del Sprite si existe 
	if (mSpriteAvatar)
	{
		mSpriteAvatar->setOrigin(mSpriteAvatar->getTexture()->getSize().x / 2.f, mSpriteAvatar->getTexture()->getSize().y / 2.f);
		mSpriteAvatar->setPosition(mPositionBodyAvatar.x, mPositionBodyAvatar.y);
		mSpriteAvatar->setRotation(Rad2Deg(mBodyAvatar->GetAngle()));
	}

	// Inicializacion de las dimensiones del AABB
	mDimensions.lowerBound = (b2Vec2(FLT_MAX, FLT_MAX));
	mDimensions.upperBound = (b2Vec2(-FLT_MAX, -FLT_MAX));

	// Recorrido de todos los fixtures del cuerpo de Box2D para calcular el AABB del sprite
	for (b2Fixture* i = mBodyAvatar->GetFixtureList(); i; i = i->GetNext())
	{
		mDimensions = i->GetAABB(0);
	}

	// Ajuste del tamaño de la RectangleShape segun dimensiones del AABB
	if (mRectangleShapeAvatar)
	{
		mRectangleShapeAvatar->setSize({ mDimensions.GetExtents().x * 2, mDimensions.GetExtents().y * 2 });
	}

	// Ajuste del tamaño del Sprite segun dimensiones del AABB
	if (mSpriteAvatar)
	{
		mSpriteAvatar->setScale(mDimensions.GetExtents().x * 2.5 / mSpriteAvatar->getTexture()->getSize().x,
			mDimensions.GetExtents().y * 2.5 / mSpriteAvatar->getTexture()->getSize().y);
	}
}

// Metodo para actualizar la posicion y rotacion del avatar
void Avatar::UpdateAvatar()
{

	mPositionBodyAvatar = mBodyAvatar->GetPosition();

	// Actualizacion de la posicion y rotacion del RectangleShape si existe
	if (mRectangleShapeAvatar)
	{
		mRectangleShapeAvatar->setPosition(mPositionBodyAvatar.x, mPositionBodyAvatar.y);
		mRectangleShapeAvatar->setRotation(Rad2Deg(mBodyAvatar->GetAngle()));
		//cout << "Rectangle Avatar Position: " << mPositionBodyAvatar.x << ", " << mPositionBodyAvatar.y << endl; // Debug
	}

	// Actualizacion de la posicion y rotacion del Sprite si existe
	if (mSpriteAvatar)
	{
		mSpriteAvatar->setPosition(mPositionBodyAvatar.x, mPositionBodyAvatar.y);
		mSpriteAvatar->setRotation(Rad2Deg(mBodyAvatar->GetAngle()));
		//cout << "Sprite Avatar Position: " << mPositionBodyAvatar.x << ", " << mPositionBodyAvatar.y << endl; // Debug
	}
}

// Metodo para convertir de radianes a grados
float Avatar::Rad2Deg(float mRadians)
{

	return mRadians * 180 / 3.14;
}

// Metodo para dibujar el avartar en la ventana
void Avatar::Draw(RenderWindow& mWindow)
{

	// Actualizar avatar
	UpdateAvatar();

	// Dibujar el RectanShape si existe
	if (mRectangleShapeAvatar)
	{
		mWindow.draw(*mRectangleShapeAvatar);
	}

	// Dibujar el Sprite si existe
	if (mSpriteAvatar)
	{
		mWindow.draw(*mSpriteAvatar);
	}
}

// Destructor
Avatar::~Avatar()
{
}
