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
#include <string.h>

#define PATH_RESOURCES "..\\Resources\\"
#define PATH_RESOURCES_SOUND PATH_RESOURCES "Sounds\\"
#define PATH_RESOURCES_MUSIC PATH_RESOURCES "Musics\\"
#define PATH_RESOURCES_TEXTURE PATH_RESOURCES "Textures\\"

typedef enum {
	RES_ALL,
	RES_SANDLAND,
	RES_FORESTLAND
}res_EState;

void res_load(res_EState _state);
