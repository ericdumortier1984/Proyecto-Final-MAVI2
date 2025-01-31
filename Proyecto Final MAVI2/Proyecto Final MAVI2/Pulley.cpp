#include "Pulley.h"
#include "Avatar.h"

Pulley::Pulley(b2World& mWorld, b2Vec2 mPosition) : mID(6)
{

	// Texturas
	mPulleyTx = new Texture;
	mCircleTx = new Texture;
	if (!mPulleyTx->loadFromFile("Assets/Objects/brownOff.png")) { cout << "Error al cargar la textura de la polea" << endl; }
	if (!mCircleTx->loadFromFile("Assets/Objects/idle2.png")) { cout << "Error al cargar la textura del circulo" << endl; }

	// Sprites
	mPulleySp = new Sprite;
	mCircleSp = new Sprite;
	mPulleySp->setTexture(*mPulleyTx);
	mCircleSp->setTexture(*mCircleTx);

	// Cuerpos
	// Cuerpo polea horizontal
	mBodyDefPulley.type = b2_staticBody;
	mBodyDefPulley.position = mPosition;
	mBodyPulley = mWorld.CreateBody(&mBodyDefPulley);

	// Cuerpos poleas verticales
	mBodyDefCircleA.type = b2_dynamicBody;
	mBodyDefCircleA.position = b2Vec2(mPosition.x - 15, mPosition.y + 45); // + 25
	mBodyCircleA = mWorld.CreateBody(&mBodyDefCircleA);

	mBodyDefCircleB.type = b2_dynamicBody;
	mBodyDefCircleB.position = b2Vec2(mPosition.x + 15, mPosition.y + 25); // + 45
	mBodyCircleB = mWorld.CreateBody(&mBodyDefCircleB);

	// Formas y fixtures
	b2PolygonShape mPulleyShape;
	mPulleyShape.SetAsBox(15.0f, 1.5f);
	mFixtureDefPulley.shape = &mPulleyShape;
	mFixtureDefPulley.density = 0.005f;
	mFixtureDefPulley.restitution = 0.5f;
	mFixtureDefPulley.friction = 0.3f;
	mFixturePulley = mBodyPulley->CreateFixture(&mFixtureDefPulley);

	//b2CircleShape mCircleAShape;
	b2PolygonShape mPoliB;
	mPoliB.SetAsBox(6.f, 7.f);
	//mCircleAShape.m_radius = 8.f;
	mFixtureDefCircleA.shape = &mPoliB;
	mFixtureDefCircleA.density = 0.8f; // 0.15
	mFixtureDefCircleA.restitution = 0.1f;
	mFixtureDefCircleA.friction = 1.0f; 
	
	//b2CircleShape mCircleBShape;
	b2PolygonShape mPoliA;
	//mCircleBShape.m_radius = 8.f;
	mPoliA.SetAsBox(6.f, 7.f);
	mFixtureDefCircleB.shape = &mPoliA;
	mFixtureDefCircleB.density = 0.9f;
	mFixtureDefCircleB.restitution = 0.1f;
	mFixtureDefCircleA.friction = 1.0f;

	mFixtureCircleA = mBodyCircleA->CreateFixture(&mFixtureDefCircleA);
	mFixtureCircleB = mBodyCircleB->CreateFixture(&mFixtureDefCircleB);

	// Joint
	b2PulleyJointDef mPulleyJointDef;
	b2Vec2 mAnchorA(mPosition.x - 15.f, mPosition.y + 45); // + 25
	b2Vec2 mAnchorB(mPosition.x + 15.f, mPosition.y + 25); // + 40
	b2Vec2 mGroundAnchorA(mPosition.x - 15.f, mPosition.y); // - 20
	b2Vec2 mGroundAnchorB(mPosition.x + 15.f, mPosition.y); // - 20
	float mRatio = 1.0f;

	mPulleyJointDef.Initialize(mBodyCircleA, mBodyCircleB, mGroundAnchorA, mGroundAnchorB, mAnchorA, mAnchorB, mRatio);
	mPulleyJoint = (b2PulleyJoint*)mWorld.CreateJoint(&mPulleyJointDef);

	mBodyPulley->GetUserData().pointer = (uintptr_t)mID; //ID

	// Avatares
	mPulleyAvatar = new Avatar(mBodyPulley, mPulleySp);
	mCircleAvatarA = new Avatar(mBodyCircleA, mCircleSp);
	mCircleAvatarB = new Avatar(mBodyCircleB, mCircleSp);
}

Pulley::~Pulley()
{

	delete mPulleyTx;
	delete mCircleTx;
	delete mPulleySp;
	delete mCircleSp;
	delete mPulleyAvatar;
	delete mCircleAvatarA;
	delete mCircleAvatarB;
}

void Pulley::Draw(RenderWindow& mWindow)
{

	// Dibuja los resortes del PulleyJoint
	b2Vec2 groundAnchorA = mPulleyJoint->GetGroundAnchorA();
	b2Vec2 groundAnchorB = mPulleyJoint->GetGroundAnchorB();
	b2Vec2 anchorA = mPulleyJoint->GetAnchorA();
	b2Vec2 anchorB = mPulleyJoint->GetAnchorB();

	// Convertir las posiciones de Box2D a SFML
	Vector2f sfGroundAnchorA(groundAnchorA.x, groundAnchorA.y);
	Vector2f sfGroundAnchorB(groundAnchorB.x, groundAnchorB.y);
	Vector2f sfAnchorA(anchorA.x, anchorA.y);
	Vector2f sfAnchorB(anchorB.x, anchorB.y);

	// Crear las líneas de los resortes
	VertexArray springA(Lines, 2);
	springA[0].position = sfGroundAnchorA;
	springA[0].color = Color::Black;
	springA[1].position = sfAnchorA;
	springA[1].color = Color::Black;

	VertexArray springB(Lines, 2);
	springB[0].position = sfGroundAnchorB;
	springB[0].color = Color::Black;
	springB[1].position = sfAnchorB;
	springB[1].color = Color::Black;

	// Dibujar las líneas
	mWindow.draw(springA);
	mWindow.draw(springB);

	mPulleyAvatar->Draw(mWindow);
	mCircleAvatarA->Draw(mWindow);
	mCircleAvatarB->Draw(mWindow);
}