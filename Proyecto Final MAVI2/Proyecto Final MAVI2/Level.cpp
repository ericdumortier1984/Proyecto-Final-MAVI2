#include "Level.h"

Level::Level(int mWidth, int mHeight, bool mUnlocked) : mFps(60.f), mFrameTime(1.f / mFps), mActualTime(0.f), mLevelFinish(false), mLevelUnlocked(false), mRagdollCount(10)
{

    mWindow = new RenderWindow(VideoMode(1280, 720), "LEVEL");
    mWindow->setFramerateLimit(mFps);

    mEvent = new Event;
    mCamara = new View;
    mClock = new Clock;
    mInitTime = new Time;

    // Audio
    mLevelMusic = new Music;
    mShootSound = new Sound;
    mLoseSound = new Sound;
    mVictorySound = new Sound;
    mShootBuffer = new SoundBuffer;
    mLoseBuffer = new SoundBuffer;
    mVictoryBuffer = new SoundBuffer;

    if (!mLevelMusic->openFromFile("Sounds/musicCircusLevel.ogg")) { cout << "Error al cargar la musica del nivel" << endl; }
    if (!mShootBuffer->loadFromFile("Sounds/canonShoot.ogg")) { cout << "Error al cargar el sonido del disparo" << endl; }
    if (!mLoseBuffer->loadFromFile("Sounds/boohCircusSound.ogg")) { cout << "Error al cargar el sonido de derrota" << endl; }
    if (!mVictoryBuffer->loadFromFile("Sounds/victoryCircusSound.ogg")) { cout << "Error al cargar sonido de victoria" << endl; }
    mLevelMusic->setLoop(true);
    mLevelMusic->play();
    mShootSound->setBuffer(*mShootBuffer);
    mShootSound->setVolume(25.0f);
    mLoseSound->setBuffer(*mLoseBuffer);
    mVictorySound->setBuffer(*mVictoryBuffer);

    //Crosshair
    mCrosshairTx = new Texture;
    if (!mCrosshairTx->loadFromFile("Assets/Objects/crosshair.png")) { cout << "Error al cargar la textura de crosshair" << endl; }
    mCrosshairSp = new Sprite;
    mCrosshairSp->setTexture(*mCrosshairTx);
    mCrosshairSp->setScale(0.10f, 0.10f);
    mCrosshairSp->setOrigin(mCrosshairTx->getSize().x / 2, mCrosshairTx->getSize().y / 2);
    mCrosshairSp->setPosition(mWindow->mapPixelToCoords(Mouse::getPosition(*mWindow)));

    //UI
    for (int i = 0; i < 3; i ++) 
    {
        mUItx[i] = new Texture;
        if (!mUItx[i]->loadFromFile("Assets/Objects/UI.png")) { cout << "Error al cargar textura de UI" << endl; }
        mUItx[i]->setSmooth(true);
        mUIsp[i] = new Sprite;
        mUIsp[i]->setTexture(*mUItx[i]);
        mUIsp[i]->setScale(0.4f, 0.4f);
    }
    mUIsp[0]->setPosition(-104.f, 30.f);
    mUIsp[1]->setPosition(-3.f, 30.f);
    mUIsp[2]->setPosition(88.f, 30.f);

    mFont = new Font;
    if (!mFont->loadFromFile("Fonts/COOPBL.ttf")) { cout << "Error al cargar la fuente" << endl; }

    mCountdownTimer = new Text;
    mCountdownTimer->setFont(*mFont);
    mCountdownTimer->setCharacterSize(20);
    mCountdownTimer->setScale(0.5f, 0.5f);
    mCountdownTimer->setPosition(5.f, 38.f);
    mCountdownTimer->setFillColor(Color::Black);
    mCountdownTimer->setOutlineThickness(2);
    mCountdownTimer->setOutlineColor(Color::White);

    mRagdollCounter = new Text;
    mRagdollCounter->setFont(*mFont);
    mRagdollCounter->setScale(0.5f, 0.5f);
    mRagdollCounter->setCharacterSize(14);
    mRagdollCounter->setPosition(-98.f, 40.f);
    mRagdollCounter->setFillColor(Color::Black);
    mRagdollCounter->setOutlineThickness(2);
    mRagdollCounter->setOutlineColor(Color::White);
    mRagdollCounter->setString("RAGDOLL: 10");

    mCanonPower = new Text;
    mCanonPower->setFont(*mFont);
    mCanonPower->setScale(0.5f, 0.5f);
    mCanonPower->setCharacterSize(14);
    mCanonPower->setPosition(95.f, 40.f);
    mCanonPower->setFillColor(Color::Black);
    mCanonPower->setOutlineThickness(2);
    mCanonPower->setOutlineColor(Color::White);
    mCanonPower->setString("POWER: 0");

    mStateMsg = new Text;
    mStateMsg->setFont(*mFont);
    mStateMsg->setScale(0.5f, 0.5f);
    mStateMsg->setCharacterSize(32);
    mStateMsg->setPosition(-10.f, 55.f);
    mStateMsg->setFillColor(Color::Red);
    mStateMsg->setOutlineThickness(2);
    mStateMsg->setOutlineColor(Color::White);

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
    delete mLevelMusic;
    delete mShootSound;
    delete mVictorySound;
    delete mLoseSound;
    delete mShootBuffer;
    delete mLoseBuffer;
    delete mVictoryBuffer;
    delete mCountdownTimer;
    delete mRagdollCounter;
    delete mStateMsg;
    delete mCrosshairSp;
    delete mCrosshairTx;
    for (int i = 0; i < 3; i++) {delete mUItx[i]; delete mUIsp[i];}
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

    if (!UnlockedLevel()) 
    {
        cout << "LEVEL BLOQUED" << endl;
        return;
    }

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
                mLevelMusic->stop();
                mMainmenu = new MainMenu(1280.f, 720.f);
                mMainmenu->PlayMusic();
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
            mRagdollCount--;
            mRagdollCounter->setString("RAGDOLL: " + to_string(mRagdollCount));

            // Sonido de disparo
            mShootSound->play();

            if (mRagdollCount < 0)
            {
                mStateMsg->setPosition(-60.f, 55.f);

                // Sonido de derrota
                mLevelMusic->stop();
                mLoseSound->play();

                ShowMsg("NO MORE RAGDOLLS");

                mMainmenu = new MainMenu(1280.f, 720.f);
                mMainmenu->PlayMusic();
            }
        }

        if (mEvent->type == Event::MouseMoved)
        {
            Vector2f mPositionMouse;
            mPositionMouse = mWindow->mapPixelToCoords(Mouse::getPosition(*mWindow));
            mCanon->Update(mPositionMouse);
           
            // Calcular la potencia del disparo
            Vector2f canonPosition = mCanon->GetPosition();
            float power = sqrt(pow(mPositionMouse.x - canonPosition.x, 2) + pow(mPositionMouse.y - canonPosition.y, 2));
            mCanonPower->setString("POWER: " + to_string(static_cast<int>(power)));

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
        mLevelMusic->stop();
        mLoseSound->play();
        ShowMsg("TIME UP");

        mMainmenu = new MainMenu(1280.f, 720.f);
        mMainmenu->PlayMusic();
    }

    int seconds = static_cast<int>(mTimeRemaining) % 60;
    mCountdownTimer->setString("TIME: " + to_string(seconds));
}

void Level::ShowMsg(const string& mMessage)
{

    mStateMsg->setString(mMessage);
    mWindow->draw(*mStateMsg);
    mWindow->display();
    sleep(seconds(3));
    mWindow->close();
}

void Level::Draw()
{
   
    RunLevel();
}
