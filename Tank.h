#pragma once
class Tank
{
public:
	void Setter(int Hp, int Speed, int Lvl) { hp = Hp; speed = Speed; lvl = Lvl; }
private:
	int hp;
	int speed;
	int lvl;
};

