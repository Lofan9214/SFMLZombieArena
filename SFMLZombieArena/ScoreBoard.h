#pragma once

enum class Upgrade;

class ScoreBoard
{
protected:
	const static std::string path;

	static int highscore;
	static int wave;
	static float upgrade[6];
	static float itemtime[2];
	static int score;
	static int allammo;

public:
	static void Write();
	static void Read();
	static void Clear();

	static void SetHighScore(int hs) { highscore = hs; }
	static int GetHighScore() { return highscore; }

	static void SetWave(int wv) { wave = wv<0?0:wv; }
	static int GetWave() { return wave; }

	static void SetUpgrade(Upgrade idx, float v) { upgrade[(int)idx] = v; }
	static float GetUpgrade(Upgrade idx) { return upgrade[(int)idx]; }

	static void SetUpgradeQt(Upgrade idx, float v)
	{
		if ((int)idx >= 4)
		{
			itemtime[(int)idx - 4] = v;
		}
	}
	static float GetUpgradeQt(Upgrade idx) 
	{ 
		if ((int)idx >= 4)
		{
			return itemtime[(int)idx - 4];
		}
		else
		{
			return 0.f;
		}
	}
	static void SetScore(int sc) { score = sc; }
	static int GetScore() { return score; }
	static void SetAllAmmo(int ammo) { allammo = ammo; }
	static int GetAllAmmo() { return allammo; }

	
};

