/*
 * Copyright (c) 2024, Hugo et Noé
 *
 * Ce code a été créé en langage C pendant l'été 2024 par Hugo Miceli et Noé Cleenewerck.
 * Il a été traduit et adapté en C++ par les mêmes auteurs.
 * Tous droits réservés.
 *
 * Toute utilisation, distribution, ou modification de ce code est soumise à
 * l'accord des auteurs.
 */

#pragma once
#include "Window.h"

typedef struct tex_SAnim tex_SAnim;
struct tex_SAnim {
	tex_SAnim* pNext;
	char* name;
	sf::IntRect rect;
	float timerBetweenFrames;
	int nbXFrames;
};

typedef struct tex_SData tex_SData;
struct tex_SData {
	tex_SData* pNext;
	int state;
	char* name;
	sf::Texture* texture;
	tex_SAnim* anim;
	tex_SAnim* beginAnim;
};

void tex_animLoad(tex_SData* _tex, char* _filePath, char* _animPath);
void tex_animAdd(tex_SData* _tex);

void tex_load(int _state);
void tex_add(tex_SData* _tex);
tex_SData* tex_remove(tex_SData* _tex);
void tex_deinit(bool _deinitStateAll);

sf::Texture* tex_getTexture(const char* _name);
sf::IntRect tex_getAnimRect(const char* _name, const char* _anim);

sf::IntRect texGetRectAnim(Window& _window, const char* _name, const char* _anim, int* frameX, float* timer);
