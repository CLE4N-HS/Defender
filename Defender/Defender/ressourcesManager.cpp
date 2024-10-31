#include "ressourcesManager.h"
#include "soundManager.h"
#include "musicManager.h"
#include "textureManager.h"

void res_load(res_EState _state)
{
	sound_load(_state);
	music_load(_state);
	tex_load(_state);
}
