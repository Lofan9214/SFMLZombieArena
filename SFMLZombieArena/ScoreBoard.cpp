#include "stdafx.h"
#include <fstream>
#include "ScoreBoard.h"
#include "UiUpgrade.h"

const std::string ScoreBoard::path = "save.dat";
int ScoreBoard::highscore;
int ScoreBoard::wave;
float ScoreBoard::upgrade[6];
float ScoreBoard::itemtime[2];
int ScoreBoard::allammo;
int ScoreBoard::score;

void ScoreBoard::Write()
{
	std::ofstream outFile(path);
	if (!outFile)
	{
		std::cerr << "Write():Error" << std::endl;
		return;
	}
	outFile << highscore << std::endl;
	outFile << wave << std::endl;
	for (int i = 0;i < sizeof(upgrade) / sizeof(upgrade[0]);++i)
	{
		outFile << upgrade[i] << std::endl;
	}
	for (int i = 0;i < sizeof(itemtime) / sizeof(itemtime[0]);++i)
	{
		outFile << itemtime[i] << std::endl;
	}
	outFile << score << std::endl;
	outFile << allammo << std::endl;

	outFile.close();
}

void ScoreBoard::Read()
{
	Clear();

	std::ifstream inFile(path);
	if (!inFile)
	{
		std::cerr << "Read():Error" << std::endl;
		return;
	}
	inFile >> highscore;
	inFile >> wave;
	for (int i = 0;i < sizeof(upgrade) / sizeof(upgrade[0]);++i)
	{
		inFile >> upgrade[i];
	}
	for (int i = 0;i < sizeof(itemtime) / sizeof(itemtime[0]);++i)
	{
		inFile >> itemtime[i];
	}

	inFile >> score;
	inFile >> allammo;

	inFile.close();
}

void ScoreBoard::Clear()
{
	highscore = 0;
	wave = 0;
	allammo = 0;
	for (int i = 0;i < sizeof(upgrade) / sizeof(upgrade[0]);++i)
	{
		upgrade[i] = 0;
	}
}
