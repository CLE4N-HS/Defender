#include "musicManager.h"
#include "ressourcesManager.h"

music_SData* music_BeginMusic = 0;

void music_load(int _state)
{
	FILE* file;
	char filePath[150];
	sprintf(filePath, PATH_RESOURCES_MUSIC "Music%d.load", _state);
	char tmpLine[180];
	char tmpMusicPath[50];
	char tmpMusicFullPath[150];
	char tmpMusicName[30];
	char tmpWord[100];

	if (!(file = fopen(filePath, "r")))
		return;

	while (fgets(tmpLine, 180, file) != NULL)
	{
		sscanf(tmpLine, "%s ", tmpWord);

		strcpy(tmpWord, "");
		strcpy(tmpMusicName, "");
		strcpy(filePath, "");
		sscanf(tmpLine, "%s %s", tmpMusicName, tmpMusicPath);
		sprintf(tmpMusicFullPath, "%s%s", PATH_RESOURCES_MUSIC, tmpMusicPath);
		music_SData* tmpMusic = (music_SData*)calloc(1, sizeof(music_SData));
		tmpMusic->name = (char*)malloc(sizeof(char) * 30);
		strcpy(tmpMusic->name, tmpMusicName);
		tmpMusic->music.openFromFile(tmpMusicFullPath);
		tmpMusic->state = _state;

		music_add(tmpMusic);

	}
	fclose(file);
}

void music_add(music_SData* _music)
{
	_music->pNext = music_BeginMusic;
	music_BeginMusic = _music;
}

music_SData* music_remove(music_SData* _music)
{
	if (_music == music_BeginMusic) {
		music_SData* tmpMusic = _music->pNext;
		music_BeginMusic = tmpMusic;
		free(_music);
		return tmpMusic;
	}
	else {
		music_SData* tmpMusic = music_BeginMusic;
		while (tmpMusic->pNext != _music) tmpMusic = tmpMusic->pNext;
		tmpMusic->pNext = _music->pNext;
		free(_music);
		return tmpMusic->pNext;
	}
}

void music_play(char* _name)
{
	music_SData* tmpMusic = music_BeginMusic;
	while (strcmp(_name, tmpMusic->name) != 0)
	{
		tmpMusic = tmpMusic->pNext;
	}
	tmpMusic->music.play();
}

void music_deinit(bool _deinitStateAll)
{
	music_SData* tmpMusic = music_BeginMusic;
	while (tmpMusic != NULL)
	{
		if (_deinitStateAll || tmpMusic->state != RES_ALL)
			tmpMusic = music_remove(tmpMusic);
		else
			tmpMusic = tmpMusic->pNext;
	}
}
