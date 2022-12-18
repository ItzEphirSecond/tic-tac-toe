#pragma once
#include <iostream>

#define elif else if

class Application
{
public:
	Application();

	void Update();

	bool isStopped()
	{
		return stopped;
	}

protected:
	void Menu();

	void Game();

	void gameCrest();

	void gameNull();

	void calculate();

	bool isWinner(bool& res)
	{
		if (field[0] == field[1] && field[0] == field[2] && field[0] != 0)
		{
			res = field[0] == 2;
			return true;
		}
		elif(field[0] == field[4] && field[0] == field[8] && field[0] != 0)
		{
			res = field[0] == 2;
			return true;
		}
		elif(field[0] == field[3] && field[0] == field[6] && field[0] != 0)
		{
			res = field[0] == 2;
			return true;
		}
		elif(field[1] == field[4] && field[1] == field[7] && field[1] != 0)
		{
			res = field[1] == 2;
			return true;
		}
		elif(field[2] == field[5] && field[2] == field[8] && field[2] != 0)
		{
			res = field[2] == 2;
			return true;
		}
		elif(field[2] == field[4] && field[2] == field[6] && field[2] != 0)
		{
			res = field[2] == 2;
			return true;
		}
		elif(field[3] == field[4] && field[3] == field[5] && field[3] != 0)
		{
			res = field[3] == 2;
			return true;
		}
		elif(field[6] == field[7] && field[6] == field[8] && field[6] != 0)
		{
			res = field[6] == 2;
			return true;
		}
		else
		{
			res = false;
			return false;
		}
	}

	void drawField()
	{
		std::string s = "";
		for (int i = 0; i < 9; i++)
		{
			switch (field[i])
			{
			case 0:
				s += " ";
				s += "|";
				break;
			case 1:
				s += "0";
				s += "|";
				break;
			case 2:
				s += "X";
				s += "|";
				break;
			default:
				std::cout << "Error" << field[i];
				stopped = true;
				return;
			}
			
			if ((i + 1) % 3 == 0)
			{
				s += "\n";
				s += "_______";
				s += "\n";
			}
		}
		std::cout << s << std::endl;
	}

	bool isDanger(bool& crest, int& wheree)
	{
		crest = false;
		wheree = 0;

		if (field[0] == field[1] && field[0] != 0 && field[2] == 0 || field[1] == field[2] && field[1] != 0 && field[0] == 0 || field[0] == field[2] && field[0] != 0 && field[1] == 0)
		{
			if (field[0] == field[1] && field[0] != 0 && field[2] == 0 || field[0] == field[2] && field[0] != 0 && field[1] == 0)
			{
				crest = field[0] == 2;
			}
			else
			{
				crest = field[1] == 2;
			}
			wheree = 0;
			return true;
		}
		else if (field[0] == field[3] && field[0] != 0 && field[6] == 0 || field[3] == field[6] && field[3] != 0 && field[0] == 0 || field[0] == field[6] && field[0] != 0 && field[3] == 0)
		{
			if (field[0] == field[3] && field[0] != 0 && field[6] == 0 || field[0] == field[6] && field[0] != 0 && field[3] == 0)
			{
				crest = field[0] == 2;
			}
			else
			{
				crest = field[3] == 2;
			}
			wheree = 4;
			return true;
		}
		else if (field[0] == field[4] && field[0] != 0 && field[8] == 0 || field[4] == field[8] && field[4] != 0 && field[0] == 0 || field[0] == field[8] && field[0] != 0 && field[4] == 0)
		{
			if (field[0] == field[4] && field[0] != 0 && field[8] == 0 || field[0] == field[8] && field[0] != 0 && field[4] == 0)
			{
				crest = field[0] == 2;
			}
			else
			{
				crest = field[4] == 2;
			}
			wheree = 3;
			return true;
		}
		else if (field[3] == field[4] && field[3] != 0 && field[5] == 0 || field[3] == field[5] && field[3] != 0 && field[4] == 0 || field[4] == field[5] && field[4] != 0 && field[3] == 0)
		{
			if (field[3] == field[4] && field[3] != 0 && field[5] == 0 || field[3] == field[5] && field[3] != 0 && field[4] == 0)
			{
				crest = field[3] == 2;
			}
			else
			{
				crest = field[4] == 2;
			}
			wheree = 1;
			return true;
		}
		else if (field[1] == field[4] && field[1] != 0 && field[7] == 0 || field[4] == field[7] && field[4] != 0 && field[1] == 0 || field[1] == field[7] && field[1] != 0 && field[4] == 0)
		{
			if (field[1] == field[4] && field[1] != 0 && field[7] == 0 || field[1] == field[7] && field[1] != 0 && field[4] == 0)
			{
				crest = field[1] == 2;
			}
			else
			{
				crest = field[4] == 2;
			}
			wheree = 5;
			return true;
		}
		else if (field[6] == field[7] && field[6] != 0 && field[8] == 0 || field[7] == field[8] && field[7] != 0 && field[6] == 0 || field[6] == field[8] && field[6] != 0 && field[7] == 0)
		{
			if (field[6] == field[7] && field[6] != 0 && field[8] == 0 || field[6] == field[8] && field[6] != 0 && field[7] == 0)
			{
				crest = field[6] == 2;
			}
			else
			{
				crest = field[7] == 2;
			}
			wheree = 2;
			return true;
		}
		else if (field[6] == field[4] && field[6] != 0 && field[2] == 0 || field[4] == field[2] && field[4] != 0 && field[6] == 0 || field[6] == field[2] && field[6] != 0 && field[4] == 0)
		{
			if (field[6] == field[4] && field[6] != 0 && field[2] == 0 || field[6] == field[2] && field[6] != 0 && field[4] == 0)
			{
				crest = field[6] == 2;
			}
			else
			{
				crest = field[4] == 2;
			}
			wheree = 7;
			return true;
		}
		else if (field[2] == field[5] && field[2] != 0 && field[8] == 0 || field[5] == field[8] && field[5] != 0 && field[2] == 0 || field[2] == field[8] && field[2] != 0 && field[5] == 0)
		{
			if (field[2] == field[5] && field[2] != 0 && field[8] == 0 || field[2] == field[8] && field[2] != 0 && field[5] == 0)
			{
				crest = field[2] == 2;
			}
			else
			{
				crest = field[5] == 2;
			}
			wheree = 6;
			return true;
		}
		return false;
	}

	int field[9]{};
	int screen = 0;
	bool stopped = false;
	bool crest = false;
	int turn = 0;
	bool draw = false;
	bool firstly = false;
};

