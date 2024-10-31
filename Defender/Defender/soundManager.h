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
#include "tools.h"

typedef struct sound_SData sound_SData;
struct sound_SData {
	sound_SData* pNext;
	int state;
	char* name;
	sf::Sound sound;
	sf::SoundBuffer soundBuffer;
};

void sound_load(int _state);
void sound_add(sound_SData* _sound);
sound_SData* sound_remove(sound_SData* _sound);
void sound_play(char* _name);
void sound_deinit(bool _deinitStateAll);
