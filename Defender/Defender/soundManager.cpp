#include "soundManager.h"
#include "ressourcesManager.h"

sound_SData* sound_BeginSound = 0;

void sound_load(int _state)
{
	FILE* file;
	char filePath[150];
	sprintf(filePath, PATH_RESOURCES_SOUND "Sound%d.load", _state);
	char tmpLine[180];
	char tmpSoundPath[50];
	char tmpSoundFullPath[150];
	char tmpSoundName[30];
	char tmpWord[100];

	if (!(file = fopen(filePath, "r")))
		return;
	
	while (fgets(tmpLine, 180, file) != NULL)
	{
		sscanf(tmpLine, "%s ", tmpWord);

		strcpy(tmpWord, "");
		strcpy(tmpSoundName, "");
		strcpy(filePath, "");
		sscanf(tmpLine, "%s %s", tmpSoundName, tmpSoundPath);
		sprintf(tmpSoundFullPath, "%s%s", PATH_RESOURCES_SOUND, tmpSoundPath);
		sound_SData* tmpSound = (sound_SData*)calloc(1, sizeof(sound_SData));
		tmpSound->name = (char*)malloc(sizeof(char) * 30);
		strcpy(tmpSound->name, tmpSoundName);
		tmpSound->sound;
		tmpSound->soundBuffer.loadFromFile(tmpSoundFullPath);
		tmpSound->state = _state;
		
		sound_add(tmpSound);

	}
	fclose(file);
}

void sound_add(sound_SData* _sound)
{
	_sound->pNext = sound_BeginSound;
	sound_BeginSound = _sound;
}

sound_SData* sound_remove(sound_SData* _sound)
{
	if (_sound == sound_BeginSound) {
		sound_SData* tmpSound = _sound->pNext;
		sound_BeginSound = tmpSound;
		free(_sound);
		return tmpSound;
	}
	else {
		sound_SData* tmpSound = sound_BeginSound;
		while (tmpSound->pNext != _sound) tmpSound = tmpSound->pNext;
		tmpSound->pNext = _sound->pNext;
		free(_sound);
		return tmpSound->pNext;
	}
}

void sound_play(char* _name)
{
	sound_SData* tmpSound = sound_BeginSound;
	while (strcmp(_name, tmpSound->name) != 0)
	{
		tmpSound = tmpSound->pNext;
	}
	tmpSound->sound.setBuffer(tmpSound->soundBuffer);
	tmpSound->sound.play();
}

void sound_deinit(bool _deinitStateAll)
{
	sound_SData* tmpSound = sound_BeginSound;
	while (tmpSound != NULL)
	{
		if (_deinitStateAll || tmpSound->state != RES_ALL)
			tmpSound = sound_remove(tmpSound);
		else
			tmpSound = tmpSound->pNext;
	}
}
