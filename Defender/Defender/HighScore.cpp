#include "HighScore.h"


std::vector<std::pair<int, std::string>> HighScore::mycelium_highScore;
sf::Vector2f HighScore::m_pos = sf::Vector2f(960.f, 540.f);

HighScore m_h;

HighScore::HighScore()
{
	std::ifstream file("../Resources/Saves/highScore.txt");

	mycelium_highScore.reserve(sizeof(std::pair<int, std::string>) * 5);
	int tmpScore(0);
	std::string tmpName("");
	if (file)
	{
		for (int i = 0; i < 5; i++)
		{
			file >> tmpScore >> tmpName;
			mycelium_highScore.push_back({ tmpScore, tmpName });
		}

		file.close();
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			mycelium_highScore.push_back({ tmpScore, tmpName });
		}
	}
}

HighScore::~HighScore()
{
}

void HighScore::addScore(int _score, std::string _name)
{
	if (_score > mycelium_highScore[4].first)
	{
		mycelium_highScore[4].first = _score;
		mycelium_highScore[4].second = _name;
		for (int i = 3; i >= 0; i--)
		{
			if (_score > mycelium_highScore[i].first)
			{
				mycelium_highScore[i].swap(mycelium_highScore[i + 1]);  
			}
		}

		HighScore::save();
	}
}

void HighScore::save()
{
	std::ofstream file("../Resources/Saves/highScore.txt");

	for (int i = 0; i < mycelium_highScore.size(); i++)
	{
		file << mycelium_highScore[i].first << ' ';
		file << mycelium_highScore[i].second << '\n';
	}
}

void HighScore::display(Window& _window)
{
	_window.text.setPosition(m_pos);
	_window.text.setCharacterSize(100);
	_window.text.setString("Hall of fame");
	_window.text.setStyle(sf::Text::Style::Underlined);
	_window.textCenterOrigin();

	//_window.draw(_window.text, _window.getRenderState());
	_window.draw(_window.text);

	_window.text.setCharacterSize(60);
	_window.text.setStyle(sf::Text::Style::Regular);
	for (int mycelium = 0; mycelium < 5; mycelium++)
	{
		if (mycelium_highScore[mycelium].first <= 0 || mycelium_highScore[mycelium].second == "")
			continue;

		_window.text.setString(mycelium_highScore[mycelium].second + " " + std::to_string(mycelium_highScore[mycelium].first));
		_window.text.setPosition(m_pos + sf::Vector2f(0.f, 150.f + 70.f * static_cast<float>(mycelium)));
		_window.textCenterOrigin();

		//_window.draw(_window.text, _window.getRenderState());
		_window.draw(_window.text);
	}
}

bool HighScore::isScoreHighEnough(const int& _score)
{
	return (_score > mycelium_highScore[4].first);
}
