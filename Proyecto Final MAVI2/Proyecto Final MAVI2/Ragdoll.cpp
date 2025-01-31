#include"Ragdoll.h"
#include"Avatar.h"

Ragdoll::Ragdoll(Vector2f mPositionRagdoll, b2World& mWorld)
{

	mID = 0;

	//Fisicas del ragdoll
	for (int i = 0; i < 6; i++)
	{
		mBodyDefRagdoll[i].type = b2_dynamicBody;
	}

	mBodyDefRagdoll[0].position = b2Vec2(mPositionRagdoll.x, mPositionRagdoll.y - 2.8f);          //Cabeza
	mBodyDefRagdoll[1].position = b2Vec2(mPositionRagdoll.x - 0.6f, mPositionRagdoll.y + 2.7f);   //Torso
	mBodyDefRagdoll[2].position = b2Vec2(mPositionRagdoll.x + 2.79f, mPositionRagdoll.y + 4.2f);  //Brazo izquierdo
	mBodyDefRagdoll[3].position = b2Vec2(mPositionRagdoll.x - 2.41f, mPositionRagdoll.y + 4.2f);  //Brazo derecho
	mBodyDefRagdoll[4].position = b2Vec2(mPositionRagdoll.x + 1.29f, mPositionRagdoll.y + 8.7f);  //Pierna izquierda 
	mBodyDefRagdoll[5].position = b2Vec2(mPositionRagdoll.x - 0.21f, mPositionRagdoll.y + 8.7f);  //Pierna derecha
	
	for (int i = 0; i < 6; i++)
	{
		mBodyRagdoll[i] = mWorld.CreateBody(&mBodyDefRagdoll[i]);
		mBodyRagdoll[i]->GetUserData().pointer = (uintptr_t)0; // ID
	}
	
	b2PolygonShape mShapeRagdoll[6];
	mShapeRagdoll[0].SetAsBox(2.0f, 2.0f);  //Cabeza
	mShapeRagdoll[1].SetAsBox(1.5f, 3.5f);  //Torso
	mShapeRagdoll[2].SetAsBox(0.5f, 2.2f);  //Brazo izquierdo
	mShapeRagdoll[3].SetAsBox(0.5f, 2.2f);  //Brazo derecho
	mShapeRagdoll[4].SetAsBox(0.5f, 3.2f);  //Pierna izquierda
	mShapeRagdoll[5].SetAsBox(0.5f, 3.2f);  //Pierna derecha

	for (int i = 0; i < 6; i++)
	{
		mFixtureDefRagdoll[i].shape = &mShapeRagdoll[i];
		mFixtureDefRagdoll[i].density = 0.01f;
		mFixtureDefRagdoll[i].restitution = 0.9f;
		mFixtureDefRagdoll[i].friction = 0.3f;

		mFixtureRagdoll[i] = mBodyRagdoll[i]->CreateFixture(&mFixtureDefRagdoll[i]);
		mBodyRagdoll[i]->GetUserData().pointer = (uintptr_t)mID;
	}

	//resortes
	//cabeza-pecho
	mJointDefRagdoll[0].Initialize(mBodyRagdoll[0], mBodyRagdoll[1],                                    //primero y segundo
		b2Vec2(mBodyRagdoll[0]->GetPosition().x, mBodyRagdoll[0]->GetPosition().y),       //ancho primer cuerpo + 1.0 + 0.3
		b2Vec2(mBodyRagdoll[1]->GetPosition().x, mBodyRagdoll[1]->GetPosition().y));      //ancho segundo cuerpo + 0.9 - 0.4

	//pecho-brazo izquierdo
	mJointDefRagdoll[1].Initialize(mBodyRagdoll[1], mBodyRagdoll[2],                                    //primero y segundo 
		b2Vec2(mBodyRagdoll[1]->GetPosition().x + 3.5f, mBodyRagdoll[1]->GetPosition().y + 1.0f),       //ancho primer cuerpo 
		b2Vec2(mBodyRagdoll[2]->GetPosition().x - 0.3f, mBodyRagdoll[2]->GetPosition().y - 0.75f));     //ancho segundo cuerpo 

	//pecho-brazo derecho
	mJointDefRagdoll[2].Initialize(mBodyRagdoll[1], mBodyRagdoll[3],                                    //primero y segundo 
		b2Vec2(mBodyRagdoll[1]->GetPosition().x - 1.0f, mBodyRagdoll[1]->GetPosition().y + 0.8f),       //ancho primer cuerpo 
		b2Vec2(mBodyRagdoll[3]->GetPosition().x + 2.0f, mBodyRagdoll[3]->GetPosition().y - 0.75f));     //ancho segundo cuerpo 

	//pecho-pierna izquierda
	mJointDefRagdoll[3].Initialize(mBodyRagdoll[1], mBodyRagdoll[4],                                    //primero y segundo 
		b2Vec2(mBodyRagdoll[1]->GetPosition().x + 2.0f, mBodyRagdoll[1]->GetPosition().y + 6.5f),       //ancho primer cuerpo 
		b2Vec2(mBodyRagdoll[4]->GetPosition().x + 0.2f, mBodyRagdoll[4]->GetPosition().y));             //ancho segundo cuerpo 

	//pecho-pierna derecha
	mJointDefRagdoll[4].Initialize(mBodyRagdoll[1], mBodyRagdoll[5],                                    //primero y segundo 
		b2Vec2(mBodyRagdoll[1]->GetPosition().x + 1.0f, mBodyRagdoll[1]->GetPosition().y + 6.5f),       //ancho primer cuerpo 
		b2Vec2(mBodyRagdoll[5]->GetPosition().x + 0.7f, mBodyRagdoll[5]->GetPosition().y));             //ancho segundo cuerpo 

	for (int i = 0; i < 5; i++)
	{
		mJointDefRagdoll[i].damping = 0.3f;
		mJointDefRagdoll[i].length = 0.25f;
		mJointDefRagdoll[i].collideConnected = true;
		mJointRagdoll[i] = (b2DistanceJoint*)mWorld.CreateJoint(&mJointDefRagdoll[i]);
	}

	
	mTextureHead = new Texture;
	mTextureTorso = new Texture;
	mTextureArmLeft = new Texture;
	mTextureArmRight = new Texture;
	mTextureLegLeft = new Texture;
	mTextureLegRight = new Texture;

	if (!mTextureHead->loadFromFile("Assets/Ragdoll/headClown.png") ||
		!mTextureTorso->loadFromFile("Assets/Ragdoll/bodyClown.png") ||
		!mTextureArmLeft->loadFromFile("Assets/Ragdoll/lHandClown.png") ||
		!mTextureArmRight->loadFromFile("Assets/Ragdoll/rHandClown.png") ||
		!mTextureLegLeft->loadFromFile("Assets/Ragdoll/lLegClown.png") ||
		!mTextureLegRight->loadFromFile("Assets/Ragdoll/rLegClown.png"))
	{

		cout << "Error cargando las texturas" << endl;
	}
	
	// Inicializar las formas de SFML con texturas
	for (int i = 0; i < 6; i++)
	{
		mSfmlRagdoll[i] = new Sprite;
		switch (i)
		{
		case 0:
			mSfmlRagdoll[i]->setTexture(*mTextureHead);
			break;
		case 1:
			mSfmlRagdoll[i]->setTexture(*mTextureTorso);
			break;
		case 2:
			mSfmlRagdoll[i]->setTexture(*mTextureArmLeft);
			break;
		case 3:
			mSfmlRagdoll[i]->setTexture(*mTextureArmRight);
			break;
		case 4:
			mSfmlRagdoll[i]->setTexture(*mTextureLegLeft);
			break;
		case 5:
			mSfmlRagdoll[i]->setTexture(*mTextureLegRight);
			break;
		}
		mAvatarRagdoll[i] = new Avatar(mBodyRagdoll[i], mSfmlRagdoll[i]);
	}
}

int Ragdoll::GetUserData()
{

	return 0;
}

void Ragdoll::ApplyForce(Vector2f mPositionMouse)
{

	for (int i = 0; i < 6; i++)
	{
		mBodyRagdoll[i]->ApplyForceToCenter(b2Vec2(mPositionMouse.x * 16, mPositionMouse.y * 16), true);
	}
}

float Ragdoll::Rad2Deg(float mRadians)
{

	return mRadians * 180 / 3.14;
}

void Ragdoll::Draw(RenderWindow& mWindow)
{

	for (int i = 0; i < 6; i++)
	{
		mAvatarRagdoll[i]->Draw(mWindow);
	}
}

Ragdoll::~Ragdoll()
{

	for (int i = 0; i < 6; i++ )
	{
		delete mSfmlRagdoll[i];
		delete mAvatarRagdoll[i];
	}

	delete mTextureHead;
	delete mTextureTorso;
	delete mTextureArmLeft;
	delete mTextureArmRight;
	delete mTextureLegLeft;
	delete mTextureLegRight;
}