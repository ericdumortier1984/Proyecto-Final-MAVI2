#include"Ragdoll.h"
#include"Avatar.h"

Ragdoll::Ragdoll(Vector2f mPositionRagdoll, b2World& mWorld)
{
	/*
	// Inicializa las texturas 
	mRagdolTx[0] = new Texture;
	mRagdolTx[1] = new Texture; 
	mRagdolTx[2] = new Texture; 
	mRagdolTx[3] = new Texture; 
	mRagdolTx[4] = new Texture; 
    mRagdolTx[5] = new Texture;

	if (!mRagdolTx[0]->loadFromFile("Assets/headClown.png")) std::cout << "Error al cargar la textura de la cabeza" << std::endl;
	if (!mRagdolTx[1]->loadFromFile("Assets/bodyClown.png")) std::cout << "Error al cargar la textura del torso" << std::endl; 
	if (!mRagdolTx[2]->loadFromFile("Assets/lHandClown.png")) std::cout << "Error al cargar la textura del brazo izquierdo" << std::endl;
	if (!mRagdolTx[3]->loadFromFile("Assets/rHandClown.png")) std::cout << "Error al cargar la textura del brazo derecho" << std::endl; 
	if (!mRagdolTx[4]->loadFromFile("Assets/lLegClown.png")) std::cout << "Error al cargar la textura de la pierna izquierda" << std::endl; 
	if (!mRagdolTx[5]->loadFromFile("Assets/rLegClown.png")) std::cout << "Error al cargar la textura de la pierna derecha" << std::endl;*/

	//Fisicas del ragdoll
	for (int i = 0; i < 6; i++)
	{
		mBodyDefRagdoll[i].type = b2_dynamicBody;
	}

	mBodyDefRagdoll[0].position = b2Vec2(mPositionRagdoll.x, mPositionRagdoll.y);                 //Cabeza
	mBodyDefRagdoll[1].position = b2Vec2(mPositionRagdoll.x - 0.6f, mPositionRagdoll.y + 2.7f);   //Torso
	mBodyDefRagdoll[2].position = b2Vec2(mPositionRagdoll.x + 2.79f, mPositionRagdoll.y + 4.2f);  //Brazo izquierdo
	mBodyDefRagdoll[3].position = b2Vec2(mPositionRagdoll.x - 2.41f, mPositionRagdoll.y + 4.2f);  //Brazo derecho
	mBodyDefRagdoll[4].position = b2Vec2(mPositionRagdoll.x + 1.29f, mPositionRagdoll.y + 8.7f);  //Pierna izquierda 
	mBodyDefRagdoll[5].position = b2Vec2(mPositionRagdoll.x - 0.21f, mPositionRagdoll.y + 8.7f);  //Pierna derecha*/
	/*
	for (int i = 0; i < 6; i++)
	{
		mBodyDefRagdoll[i].type = b2_dynamicBody;
	}

	mBodyDefRagdoll[0].position = b2Vec2(mPositionRagdoll.x, mPositionRagdoll.y);   //Cabeza
	mBodyDefRagdoll[1].position = b2Vec2(mPositionRagdoll.x, mPositionRagdoll.y + 0.25f);  //Torso
	mBodyDefRagdoll[2].position = b2Vec2(mPositionRagdoll.x + 1.25f, mPositionRagdoll.y + 1.25f);  //Brazo izquierdo
	mBodyDefRagdoll[3].position = b2Vec2(mPositionRagdoll.x - 1.25f, mPositionRagdoll.y + 1.25f);  //Brazo derecho
	mBodyDefRagdoll[4].position = b2Vec2(mPositionRagdoll.x + 1.15f, mPositionRagdoll.y + 1.25f);  //Pierna izquierda 
	mBodyDefRagdoll[5].position = b2Vec2(mPositionRagdoll.x - 1.15f, mPositionRagdoll.y + 1.25f);  //Pierna derecha*/

	for (int i = 0; i < 6; i++)
	{
		mBodyRagdoll[i] = mWorld.CreateBody(&mBodyDefRagdoll[i]);
	}
	
	b2PolygonShape mShapeRagdoll[6];
	mShapeRagdoll[0].SetAsBox(0.7f, 0.7f);  //Cabeza
	mShapeRagdoll[1].SetAsBox(1.5f, 3.5f);  //Torso
	mShapeRagdoll[2].SetAsBox(0.5f, 2.2f);  //Brazo izquierdo
	mShapeRagdoll[3].SetAsBox(0.5f, 2.2f);  //Brazo derecho
	mShapeRagdoll[4].SetAsBox(0.5f, 3.2f);  //Pierna izquierda
	mShapeRagdoll[5].SetAsBox(0.5f, 3.2f);  //Pierna derecha
	/*
	b2PolygonShape mShapeRagdoll[6];
	mShapeRagdoll[0].SetAsBox(8.0f, 8.0f);  //Cabeza
	mShapeRagdoll[1].SetAsBox(12.0f, 15.0f);  //Torso
	mShapeRagdoll[2].SetAsBox(10.5f, 12.2f);  //Brazo izquierdo
	mShapeRagdoll[3].SetAsBox(10.5f, 12.2f);  //Brazo derecho
	mShapeRagdoll[4].SetAsBox(10.5f, 13.2f);  //Pierna izquierda
	mShapeRagdoll[5].SetAsBox(10.5f, 13.2f);  //Pierna derecha*/

	for (int i = 0; i < 6; i++)
	{
		mFixtureDefRagdoll[i].shape = &mShapeRagdoll[i];
		mFixtureDefRagdoll[i].density = 0.01f;
		mFixtureDefRagdoll[i].restitution = 0.9f;
		mFixtureDefRagdoll[i].friction = 0.3f;

		mFixtureRagdoll[i] = mBodyRagdoll[i]->CreateFixture(&mFixtureDefRagdoll[i]);
	}
	
	//resortes
	//cabeza-pecho
	mJointDefRagdoll[0].Initialize(mBodyRagdoll[0], mBodyRagdoll[1],                                    // primero y segundo
		b2Vec2(mBodyRagdoll[0]->GetPosition().x + 1.0f, mBodyRagdoll[0]->GetPosition().y + 0.3f),       //ancho primer cuerpo 
		b2Vec2(mBodyRagdoll[1]->GetPosition().x + 0.9f, mBodyRagdoll[1]->GetPosition().y - 0.4f));      // ancho segundo cuerpo 

	//pecho-brazo izquierdo
	mJointDefRagdoll[1].Initialize(mBodyRagdoll[1], mBodyRagdoll[2],                                    // primero y segundo 
		b2Vec2(mBodyRagdoll[1]->GetPosition().x + 3.5f, mBodyRagdoll[1]->GetPosition().y + 1.0f),       // ancho primer cuerpo 
		b2Vec2(mBodyRagdoll[2]->GetPosition().x - 0.3f, mBodyRagdoll[2]->GetPosition().y - 0.75f));     //ancho segundo cuerpo 

	//pecho-brazo derecho
	mJointDefRagdoll[2].Initialize(mBodyRagdoll[1], mBodyRagdoll[3],                                    // primero y segundo 
		b2Vec2(mBodyRagdoll[1]->GetPosition().x - 1.0f, mBodyRagdoll[1]->GetPosition().y + 0.8f),       // ancho primer cuerpo 
		b2Vec2(mBodyRagdoll[3]->GetPosition().x + 2.0f, mBodyRagdoll[3]->GetPosition().y - 0.75f));     //ancho segundo cuerpo 

	//pecho-pierna izquierda
	mJointDefRagdoll[3].Initialize(mBodyRagdoll[1], mBodyRagdoll[4],                                    // primero y segundo 
		b2Vec2(mBodyRagdoll[1]->GetPosition().x + 2.0f, mBodyRagdoll[1]->GetPosition().y + 6.5f),       // ancho primer cuerpo 
		b2Vec2(mBodyRagdoll[4]->GetPosition().x + 0.2f, mBodyRagdoll[4]->GetPosition().y));             // ancho segundo cuerpo 

	//pecho-pierna derecha
	mJointDefRagdoll[4].Initialize(mBodyRagdoll[1], mBodyRagdoll[5],                                    // primero y segundo 
		b2Vec2(mBodyRagdoll[1]->GetPosition().x + 1.0f, mBodyRagdoll[1]->GetPosition().y + 6.5f),       // ancho primer cuerpo 
		b2Vec2(mBodyRagdoll[5]->GetPosition().x + 0.7f, mBodyRagdoll[5]->GetPosition().y));             // ancho segundo cuerpo 

	/*
	//resortes
	//cabeza-pecho
	mJointDefRagdoll[0].Initialize(mBodyRagdoll[0], mBodyRagdoll[1],                                    // primero y segundo
		b2Vec2(mBodyRagdoll[0]->GetPosition().x, mBodyRagdoll[0]->GetPosition().y),       //ancho primer cuerpo 
		b2Vec2(mBodyRagdoll[1]->GetPosition().x, mBodyRagdoll[1]->GetPosition().y - 0.5f));      // ancho segundo cuerpo 

	//pecho-brazo izquierdo
	mJointDefRagdoll[1].Initialize(mBodyRagdoll[1], mBodyRagdoll[2],                                    // primero y segundo 
		b2Vec2(mBodyRagdoll[1]->GetPosition().x + 0.2f, mBodyRagdoll[1]->GetPosition().y + 0.5f ),       // ancho primer cuerpo 
		b2Vec2(mBodyRagdoll[2]->GetPosition().x - 0.2f , mBodyRagdoll[2]->GetPosition().y - 0.5f ));     //ancho segundo cuerpo 

	//pecho-brazo derecho
	mJointDefRagdoll[2].Initialize(mBodyRagdoll[1], mBodyRagdoll[3],                                    // primero y segundo 
		b2Vec2(mBodyRagdoll[1]->GetPosition().x - 0.5f, mBodyRagdoll[1]->GetPosition().y + 0.5f),       // ancho primer cuerpo 
		b2Vec2(mBodyRagdoll[3]->GetPosition().x + 0.5f, mBodyRagdoll[3]->GetPosition().y - 0.5f));     //ancho segundo cuerpo 

	//pecho-pierna izquierda
	mJointDefRagdoll[3].Initialize(mBodyRagdoll[1], mBodyRagdoll[4],                                    // primero y segundo 
		b2Vec2(mBodyRagdoll[1]->GetPosition().x + 0.5f , mBodyRagdoll[1]->GetPosition().y + 0.5f),       // ancho primer cuerpo 
		b2Vec2(mBodyRagdoll[4]->GetPosition().x + 0.5f, mBodyRagdoll[4]->GetPosition().y));             // ancho segundo cuerpo 

	//pecho-pierna derecha
	mJointDefRagdoll[4].Initialize(mBodyRagdoll[1], mBodyRagdoll[5],                                    // primero y segundo 
		b2Vec2(mBodyRagdoll[1]->GetPosition().x + 0.5f, mBodyRagdoll[1]->GetPosition().y + 0.5f),       // ancho primer cuerpo 
		b2Vec2(mBodyRagdoll[5]->GetPosition().x + 0.5f, mBodyRagdoll[5]->GetPosition().y));             // ancho segundo cuerpo */

	for (int i = 0; i < 5; i++)
	{
		mJointDefRagdoll[i].damping = 0.3f;
		mJointDefRagdoll[i].length = 0.25f;
		mJointDefRagdoll[i].collideConnected = true;
		mJointRagdoll[i] = (b2DistanceJoint*)mWorld.CreateJoint(&mJointDefRagdoll[i]);
	}
	/*
	//Inicializa Ragdoll
	for (int i = 0; i < 6; i++)
	{
		mSfmlRagdoll[i] = new Sprite;
		mSfmlRagdoll[i]->setTexture(*mRagdolTx[i]);
		mSfmlRagdoll[i]->setScale(50.0f, 50.0f);
		mAvatarRagdoll[i] = new Avatar(mBodyRagdoll[i], mSfmlRagdoll[i]);
	}*/

	//Inicializa Ragdoll
	for (int i = 0; i < 6; i++)
	{
		mSfmlRagdoll[i] = new RectangleShape;
		switch (i) 
		{ 
		case 0: 
			mSfmlRagdoll[i]->setFillColor(Color::Yellow); 
		break;
		case 1: 
			mSfmlRagdoll[i]->setFillColor(Color::Red);
		break; 
		case 2: 
			mSfmlRagdoll[i]->setFillColor(Color::Blue);
		break; 
		case 3: 
			mSfmlRagdoll[i]->setFillColor(Color::Blue); 
		break; 
		case 4: 
			mSfmlRagdoll[i]->setFillColor(Color::White); 
		break; 
		case 5: mSfmlRagdoll[i]->setFillColor(Color::White);
        break; 
		}
		mAvatarRagdoll[i] = new Avatar(mBodyRagdoll[i], mSfmlRagdoll[i]);
	}
}

void Ragdoll::ApplyForce(Vector2f mPositionMouse)
{

	for (int i = 0; i < 6; i++)
	{
		mBodyRagdoll[i]->ApplyForceToCenter(b2Vec2(mPositionMouse.x * 8, mPositionMouse.y * 8), false);
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