#include "textureManager.h"
#include "ressourcesManager.h"

tex_SData* tex_BeginTex = 0;

void tex_animLoad(tex_SData* _tex, char* _filePath, char* _animPath)
{
	FILE* file;
	char tmpLine[180];
	char tmpWord[100];
	char tmpName[150];
	sf::IntRect tmpAnimRect = sf::IntRect(0, 0, 0, 0);
	float tmpTimerBetweenFrames = 0.f;
	int tmpNbXFrames = 0;

	if (!(file = fopen(_animPath, "r")))
		return;

	fgets(tmpLine, 180, file);
	sscanf(tmpLine, "%s", tmpWord);
	sprintf(tmpName, "%s%s", _filePath, tmpWord);
	_tex->texture = new sf::Texture();
	_tex->texture->loadFromFile(tmpName);

	while (fgets(tmpLine, 180, file) != NULL)
	{
		sscanf(tmpLine, "%s ", tmpWord);

		_tex->anim = (tex_SAnim*)calloc(1, sizeof(tex_SAnim));
		_tex->anim->name = (char*)malloc(sizeof(char) * 30);
		sscanf(tmpLine, "%s %d %d %d %d %f %d", _tex->anim->name, &(_tex->anim->rect.left), &(_tex->anim->rect.top), &(_tex->anim->rect.width), &(_tex->anim->rect.height), &(_tex->anim->timerBetweenFrames), &(_tex->anim->nbXFrames));

		tex_animAdd(_tex);

	}
	fclose(file);
}

void tex_animAdd(tex_SData* _tex)
{
	_tex->anim->pNext = _tex->beginAnim;
	_tex->beginAnim = _tex->anim;
}

void tex_load(int _state)
{
	FILE* file;
	char filePath[150];
	sprintf(filePath, PATH_RESOURCES_TEXTURE "Texture%d.load", _state);
	char tmpLine[180];
	char tmpTexPath[50];
	char tmpTexFullPath[150];
	char tmpTexName[30];
	char tmpWord[100];
	char tmpFilePath[150];

	if (!(file = fopen(filePath, "r")))
		return;

	while (fgets(tmpLine, 180, file) != NULL)
	{
		sscanf(tmpLine, "%s ", tmpWord);

		strcpy(tmpWord, "");
		strcpy(tmpTexName, "");
		sscanf(tmpLine, "%s %s", tmpTexName, tmpTexPath);
		sprintf(tmpTexFullPath, "%s%s", PATH_RESOURCES_TEXTURE, tmpTexPath);

		int tmpTexPathLengthCount = strlen(tmpTexFullPath) - 1;
		strcpy(tmpFilePath, tmpTexFullPath);

		tex_SData* tmpTex = (tex_SData*)calloc(1, sizeof(tex_SData));
		tmpTex->name = new char[30];
		strcpy(tmpTex->name, tmpTexName);
		tmpTex->state = _state;

		// anim
		if (tmpFilePath[tmpTexPathLengthCount--] == 'm' && tmpFilePath[tmpTexPathLengthCount--] == 'i' && tmpFilePath[tmpTexPathLengthCount--] == 'n' && tmpFilePath[tmpTexPathLengthCount--] == 'a' && tmpFilePath[tmpTexPathLengthCount] == '.') {
			while (tmpFilePath[tmpTexPathLengthCount] != '\\' && tmpFilePath[tmpTexPathLengthCount] != '/')
				tmpTexPathLengthCount--;

			tmpFilePath[tmpTexPathLengthCount + 1] = '\0';
			tex_animLoad(tmpTex, tmpFilePath, tmpTexFullPath);
		}
		else {
			tmpTex->texture = new sf::Texture();
			tmpTex->texture->loadFromFile(tmpTexFullPath);
		}

		tex_add(tmpTex);
	}
	fclose(file);
}

void tex_add(tex_SData* _tex)
{
	_tex->pNext = tex_BeginTex;
	tex_BeginTex = _tex;
}

tex_SData* tex_remove(tex_SData* _tex)
{
	if (_tex == tex_BeginTex) {
		tex_SData* tmpTex = _tex->pNext;
		tex_BeginTex = tmpTex;
		free(_tex);
		return tmpTex;
	}
	else {
		tex_SData* tmpTex = tex_BeginTex;
		while (tmpTex->pNext != _tex) tmpTex = tmpTex->pNext;
		tmpTex->pNext = _tex->pNext;
		free(_tex);
		return tmpTex->pNext;
	}
}

void tex_deinit(bool _deinitStateAll)
{
	tex_SData* tmpTex = tex_BeginTex;
	while (tmpTex != NULL)
	{
		if (_deinitStateAll || tmpTex->state != RES_ALL)
			tmpTex = tex_remove(tmpTex);
		else
			tmpTex = tmpTex->pNext;
	}
}

sf::Texture* tex_getTexture(const char* _name)
{
	tex_SData* tmpTexture = tex_BeginTex;
	while (strcmp(tmpTexture->name, _name) != 0)
	{
		tmpTexture = tmpTexture->pNext;
	}

	return tmpTexture->texture;
}

sf::IntRect tex_getAnimRect(const char* _name, const char* _anim)
{
	tex_SData* tmpTexture = tex_BeginTex;
	while (strcmp(tmpTexture->name, _name) != 0)
	{
		tmpTexture = tmpTexture->pNext;
	}

	tex_SAnim* tmpAnim = tmpTexture->beginAnim;
	while (strcmp(tmpAnim->name, _anim) != 0)
	{
		tmpAnim = tmpAnim->pNext;
	}

	return tmpAnim->rect;
}

sf::IntRect texGetRectAnim(Window& _window, const char* _name, const char* _anim, int* frameX, float* timer)
{
	float dt = _window.getDeltaTime();
	tex_SData* tmpTexture = tex_BeginTex;
	while (strcmp(tmpTexture->name, _name) != 0)
	{
		tmpTexture = tmpTexture->pNext;
	}

	tex_SAnim* tmpAnim = tmpTexture->beginAnim;
	while (strcmp(tmpAnim->name, _anim) != 0)
	{
		tmpAnim = tmpAnim->pNext;
	}

	*timer += dt;

	if (*timer > tmpAnim->timerBetweenFrames) {
		*timer = 0.f;
		*frameX += 1;
		if (*frameX > tmpAnim->nbXFrames)
			*frameX = 0;
	}
	sf::IntRect toReturn = tmpAnim->rect;
	toReturn.left += *frameX * tmpAnim->rect.width;
	return toReturn;

}