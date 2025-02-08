#include "Pulley.h"
#include "Avatar.h"

// Constructor
Pulley::Pulley(b2World& mWorld, b2Vec2 mPosition) : mID(6)
{

	// Texturas
	mPulleyTx = new Texture;
	mLoadTx = new Texture;
	if (!mPulleyTx->loadFromFile("Assets/Objects/staticPlatform.png")) { cout << "Error al cargar la textura de la plataforma" << endl; }
	if (!mLoadTx->loadFromFile("Assets/Objects/staticBox.png")) { cout << "Error al cargar la textura de la carga" << endl; }

	// Sprites
	mPulleySp = new Sprite;
	mLoadSp = new Sprite;
	mPulleySp->setTexture(*mPulleyTx);
	mLoadSp->setTexture(*mLoadTx);

	/////////////////     Cuerpos      ///////////////////
	
	// Cuerpo plataforma horizontal de las poleas
	mBodyDefPulley.type = b2_staticBody;
	mBodyDefPulley.position = mPosition;
	mBodyPulley = mWorld.CreateBody(&mBodyDefPulley);

	// Cuerpos de las cargas o pesos de las poleas
	mBodyDefLoadA.type = b2_dynamicBody;
	mBodyDefLoadA.position = b2Vec2(mPosition.x - 15, mPosition.y + 45);
	mBodyDefLoadA.fixedRotation = true; // Evitar rotación
	mBodyLoadA = mWorld.CreateBody(&mBodyDefLoadA);

	mBodyDefLoadB.type = b2_dynamicBody;
	mBodyDefLoadB.position = b2Vec2(mPosition.x + 15, mPosition.y + 25); 
	mBodyDefLoadB.fixedRotation = true; // Evitar rotación
	mBodyLoadB = mWorld.CreateBody(&mBodyDefLoadB);

	/////////// Formas y fixtures /////////////

	//  Shape de la plataforma que sostiene las cargas
	b2PolygonShape mPulleyShape;
	mPulleyShape.SetAsBox(15.0f, 1.5f);
	mFixtureDefPulley.shape = &mPulleyShape;
	mFixtureDefPulley.density = 0.005f;
	mFixtureDefPulley.restitution = 0.3f;
	mFixtureDefPulley.friction = 0.3f;
	mFixturePulley = mBodyPulley->CreateFixture(&mFixtureDefPulley);

	// Shape de cargas lado izquierdo
	b2PolygonShape mLoadShapeA;
	mLoadShapeA.SetAsBox(4.5f, 4.5f);
	mFixtureDefLoadA.shape = &mLoadShapeA;
	mFixtureDefLoadA.density = 0.1f;
	
	// Shape de cargas lado derecho
	b2PolygonShape mLoadShapeB;
	mLoadShapeB.SetAsBox(4.5f, 4.5f);
	mFixtureDefLoadB.shape = &mLoadShapeB;
	mFixtureDefLoadB.density = 0.2f;

	mFixtureLoadA = mBodyLoadA->CreateFixture(&mFixtureDefLoadA);
	mFixtureLoadB = mBodyLoadB->CreateFixture(&mFixtureDefLoadB);

	// Pulley Joint
	b2PulleyJointDef mPulleyJointDef;
	b2Vec2 mAnchorA(mPosition.x - 15.f, mPosition.y + 45);
	b2Vec2 mAnchorB(mPosition.x + 15.f, mPosition.y + 25);
	b2Vec2 mGroundAnchorA(mPosition.x - 15.5f, mPosition.y); 
	b2Vec2 mGroundAnchorB(mPosition.x + 15.5f, mPosition.y); 
	float mRatio = 1.0f;

	mPulleyJointDef.Initialize(mBodyLoadA, mBodyLoadB, mGroundAnchorA, mGroundAnchorB, mAnchorA, mAnchorB, mRatio);
	mPulleyJoint = (b2PulleyJoint*)mWorld.CreateJoint(&mPulleyJointDef);

	mBodyPulley->GetUserData().pointer = (uintptr_t)mID; //ID

	// Avatares
	mPulleyAvatar = new Avatar(mBodyPulley, mPulleySp);
	mLoadAvatarA = new Avatar(mBodyLoadA, mLoadSp);
	mLoadAvatarB = new Avatar(mBodyLoadB, mLoadSp);
}

// Liberamos memoria
Pulley::~Pulley()
{

	delete mPulleyTx;
	delete mLoadTx;
	delete mPulleySp;
	delete mLoadSp;
	delete mPulleyAvatar;
	delete mLoadAvatarA;
	delete mLoadAvatarB;
}

void Pulley::Draw(RenderWindow& mWindow)
{

	// Anclas del Pulley Joint en render SFML
	b2Vec2 groundAnchorA = mPulleyJoint->GetGroundAnchorA();
	b2Vec2 groundAnchorB = mPulleyJoint->GetGroundAnchorB();
	b2Vec2 anchorA = mPulleyJoint->GetAnchorA();
	b2Vec2 anchorB = mPulleyJoint->GetAnchorB();

	// Convercion de posiciones de Box2D a SFML
	Vector2f sfGroundAnchorA(groundAnchorA.x, groundAnchorA.y);
	Vector2f sfGroundAnchorB(groundAnchorB.x, groundAnchorB.y);
	Vector2f sfAnchorA(anchorA.x, anchorA.y);
	Vector2f sfAnchorB(anchorB.x, anchorB.y);

	// Recorrido de los resortes izquierdos
	VertexArray springA(Lines, 2);
	springA[0].position = sfGroundAnchorA;
	springA[0].color = Color::Black;
	springA[1].position = sfAnchorA;
	springA[1].color = Color::Black;

	// Recorrido de los resortes derechos
	VertexArray springB(Lines, 2);
	springB[0].position = sfGroundAnchorB;
	springB[0].color = Color::Black;
	springB[1].position = sfAnchorB;
	springB[1].color = Color::Black;

	// Dibuja
	mWindow.draw(springA);
	mWindow.draw(springB);

	mPulleyAvatar->Draw(mWindow);
	mLoadAvatarA->Draw(mWindow);
	mLoadAvatarB->Draw(mWindow);
}