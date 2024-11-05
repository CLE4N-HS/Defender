#include "HighScore.h"

HighScore::HighScore() : m_highScore()
{
	std::ifstream file("../Resources/Saves/highScore.txt");

	m_highScore.reserve(sizeof(std::pair<int, std::string>) * 5);
	int tmpScore(0);
	std::string tmpName("");
	if (file)
	{
		for (int i = 0; i < 5; i++)
		{
			file >> tmpScore >> tmpName;
			m_highScore.push_back({ tmpScore, tmpName });
		}

		file.close();
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			m_highScore.push_back({ tmpScore, tmpName });
		}
	}
}

HighScore::~HighScore()
{
}

void HighScore::addScore(int _score, std::string _name)
{
	if (_score > m_highScore[4].first)
	{
		m_highScore[4].first = _score;
		m_highScore[4].second = _name;
		for (int i = 3; i >= 0; i--)
		{
			if (_score > m_highScore[i].first)
			{
				m_highScore[i].swap(m_highScore[i + 1]);
			}
		}
	}
}

void HighScore::display()
{
	for (int i = 0; i < 5; i++)
	{
		std::cout << m_highScore[i].first << ", " << m_highScore[i].second << std::endl;
	}
}
