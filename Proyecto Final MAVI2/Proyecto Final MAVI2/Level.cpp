#include "Level.h"

Level::Level(int mWidth, int mHeight) : mFps(60.f), mFrameTime(1.f / mFps), mActualTime(0.f), mLevelFinish(false), mRagdollCount(0)
{
    mWindow = new RenderWindow(VideoMode(1280, 720), "LEVEL");
    mWindow->setFramerateLimit(mFps);

    mEvent = new Event;
    mCamara = new View;
    mClock = new Clock;
    mInitTime = new Time;

    mCrosshairTx = new Texture;
    if (!mCrosshairTx->loadFromFile("Assets/Objects/crosshair.png")) { cout << "Error al cargar la textura de crosshair" << endl; }
    mCrosshairSp = new Sprite;

    // Crosshair
    mCrosshairSp->setTexture(*mCrosshairTx);
    mCrosshairSp->setScale(0.10f, 0.10f);
    mCrosshairSp->setOrigin(mCrosshairTx->getSize().x / 2, mCrosshairTx->getSize().y / 2);
    mCrosshairSp->setPosition(mWindow->mapPixelToCoords(Mouse::getPosition(*mWindow)));

    mFont = new Font;
    if (!mFont->loadFromFile("Fonts/ARLRDBD.ttf")) { cout << "Error al cargar la fuente" << endl; }

    mCountdownTimer = new Text;
    mCountdownTimer->setFont(*mFont);
    mCountdownTimer->setCharacterSize(12);
    mCountdownTimer->setPosition(-5.f, 28.f);
    mCountdownTimer->setFillColor(Color::White);
    mCountdownTimer->setOutlineThickness(1);
    mCountdownTimer->setOutlineColor(Color::Black);

    mRagdollCounter = new Text;
    mRagdollCounter->setFont(*mFont);
    mRagdollCounter->setCharacterSize(12);
    mRagdollCounter->setPosition(-80.f, 28.f);
    mRagdollCounter->setFillColor(Color::White);
    mRagdollCounter->setOutlineThickness(1);
    mRagdollCounter->setOutlineColor(Color::Black);

    InitPhysics();

    // Inicializacion de objetos
    mCanon = new Canon(*mWorld);
    mFloor = new Floor(*mWorld);
}

Level::~Level()
{
    delete mWindow;
    delete mFont;
    delete mClock;
    delete mInitTime;
    delete mCamara;
    delete mEvent;
    delete mCountdownTimer;
    delete mRagdollCounter;
    delete mCrosshairSp;
    delete mCrosshairTx;
}

void Level::SetCamara(float mZoom)
{
    mCamara->setSize(mWindow->getSize().x * mZoom, mWindow->getSize().y * mZoom);
    mCamara->setCenter(20, 100);
    mWindow->setView(*mCamara);
}

void Level::InitPhysics()
{
    mWorld = new b2World({ 0.f, 9.8f });
}

void Level::UpdatePhysics()
{
    mWorld->Step(mFrameTime, 8, 8);
    mWorld->ClearForces();
}

void Level::Run()
{
    while (mWindow->isOpen())
    {
        *mInitTime = mClock->getElapsedTime();

        if (mActualTime + mFrameTime < mInitTime->asSeconds())
        {
            ProcessEvents();
            Update();
            UpdatePhysics();
            Draw();
        }
    }
}

void Level::ProcessEvents()
{
    while (mWindow->pollEvent(*mEvent))
    {
        // Cerrar ventana
        if (mEvent->type == Event::Closed)
        {
            mWindow->close();
        }

        // Eventos del teclado
        if (mEvent->type == Event::KeyPressed)
        {
            if (mEvent->key.code == Keyboard::Escape)
            {
                mWindow->close();
            }
        }

        // Eventos del mouse
        if (mEvent->type == Event::MouseButtonPressed)
        {
            Vector2f mPositionMouse;
            mPositionMouse = mWindow->mapPixelToCoords(Mouse::getPosition(*mWindow));
            mCanon->Shoot(mWorld, mPositionMouse, *mWindow);
            mRagdoll = mCanon->GetRagdoll();
            mRagdollCount++;
            mRagdollCounter->setString("Ragdolls: " + to_string(mRagdollCount));
        }

        if (mEvent->type == Event::MouseMoved)
        {
            Vector2f mPositionMouse;
            mPositionMouse = mWindow->mapPixelToCoords(Mouse::getPosition(*mWindow));
            mCanon->Update(mPositionMouse);

            mCrosshairSp->setPosition(mPositionMouse);
        }
    }
}

void Level::Update()
{
    float mTimeRemaining = 0.f;
    float elapsedTime = mClock->getElapsedTime().asSeconds();
    mTimeRemaining = 60.f - elapsedTime;

    if (mTimeRemaining <= 0)
    {
        cout << "[TIME UP LEVEL]" << endl; // Debug
    }

    int seconds = static_cast<int>(mTimeRemaining) % 60;
    mCountdownTimer->setString("TIME: " + to_string(seconds));
}

void Level::Draw()
{
   
    RunLevel();
}
