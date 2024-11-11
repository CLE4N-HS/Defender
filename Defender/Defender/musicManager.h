/*
 * Copyright (c) 2024, Hugo et No�
 *
 * Ce code a �t� cr�� en langage C pendant l'�t� 2024 par Hugo Miceli et No� Cleenewerck.
 * Il a �t� traduit et adapt� en C++ par les m�mes auteurs.
 * Tous droits r�serv�s.
 *
 * Toute utilisation, distribution, ou modification de ce code est soumise �
 * l'accord des auteurs.
 */

#pragma once
#include "tools.h"

typedef struct music_SData music_SData;
struct music_SData {
	music_SData* pNext;
	int state;
	char* name;
	sf::Music* music;
};

void music_load(int _state);
void music_add(music_SData* _music);
music_SData* music_remove(music_SData* _music);
void music_play(const char* _name);
void music_setLoop(const char* _name, const bool& _loop = true);
void music_stop(const char* _name);
void music_deinit(bool _deinitStateAll);
void music_setVolume(const int& _volume);
