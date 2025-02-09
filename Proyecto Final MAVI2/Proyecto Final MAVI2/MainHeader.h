#pragma once

// Joints uitilizados en el juego:
// Distance Joint para el ragdoll
// Revolute Joint para los pendulos del level 1
// Pulley Joint para las poleas del level 2
// Motor Joint para las ruedas del level 3

// Inclusion de librerias de SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

// inclusion de liberia Box2D
#include <box2d/box2d.h>

// Inclusion de librerias estandar
#include <iostream>
#include <vector>

// Uso de espacio de nombres SFML y estandar
using namespace sf;
using namespace std;