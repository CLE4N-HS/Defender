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

typedef struct music_SData music_SData;
struct music_SData {
	music_SData* pNext;
	int state;
	char* name;
	sf::Music music;
};

void music_load(int _state);
void music_add(music_SData* _music);
music_SData* music_remove(music_SData* _music);
void music_play(char* _name);
void music_deinit(bool _deinitStateAll);
