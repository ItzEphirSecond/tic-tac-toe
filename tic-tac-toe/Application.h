#pragma once
#include <iostream>

// хэдер

#define elif else if

class Application
{
public:
	// конструктор
	Application();


	// обновление экрана
	void Update();

	// вернуть, остановилась ли игра
	bool isStopped()
	{
		return stopped;
	}

protected:
	// меню (выбор ходить крестиками или ноликами)
	void Menu();

	// основной цикл игры
	void Game();


	// подразделение цикла игры - дл€ крестиков
	void gameCrest();

	// дл€ ноликов
	void gameNull();


	// просчитать ход компьютера
	void calculate();

	// вернуть, выиграл ли кто-нибудь?
	bool isWinner(bool& res)
	{
		
		if (field[0] == field[1] && field[0] == field[2] && field[0] != 0) // провер€ем первую строку
		{
			res = field[0] == 2;
			return true;
		}
		elif(field[0] == field[4] && field[0] == field[8] && field[0] != 0) // больша€ диагональ
		{
			res = field[0] == 2;
			return true;
		}
		elif(field[0] == field[3] && field[0] == field[6] && field[0] != 0) // первый столбец
		{
			res = field[0] == 2;
			return true;
		}
		elif(field[1] == field[4] && field[1] == field[7] && field[1] != 0) // второй столбец
		{
			res = field[1] == 2;
			return true;
		}
		elif(field[2] == field[5] && field[2] == field[8] && field[2] != 0) // третий столбец
		{
			res = field[2] == 2;
			return true;
		}
		elif(field[2] == field[4] && field[2] == field[6] && field[2] != 0) // мала€ диагональ
		{
			res = field[2] == 2;
			return true;
		}
		elif(field[3] == field[4] && field[3] == field[5] && field[3] != 0) // втора€ строка
		{
			res = field[3] == 2;
			return true;
		}
		elif(field[6] == field[7] && field[6] == field[8] && field[6] != 0) // треть€ стока
		{
			res = field[6] == 2;
			return true;
		}
		else // если никто не выиграл
		{
			res = false;
			return false;
		}
	}

	// нарисовать поле
	void drawField()
	{

		std::string s = "_______";
		s += "\n";
		s += "|";
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
				if (i != 8)
				{
					s += "|";
				}
			}
		}

		std::cout << s << std::endl;
	}

	// вернуть, есть ли опасна€ позици€? (передаютс€ ин-параметры, первый = кто выиграл, второй = где выиграл)
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

	// спросить у игрока, куда он хочет ходить, параметр = знак, которым ходит игрок
	void ask(int sign)
	{
		int answer;
		std::cin >> answer;
		switch (answer)
		{
		case 1:
			if (field[6] == 0) { field[6] = sign; return; }
			else { std::cout << "ѕоле зан€то, выберете другое: " << std::endl; ask(sign); }
			break;
		case 2:
			if (field[7] == 0) { field[7] = sign; return; }
			else { std::cout << "ѕоле зан€то, выберете другое: " << std::endl; ask(sign); }
			break;
		case 3:
			if (field[8] == 0) { field[8] = sign; return; }
			else { std::cout << "ѕоле зан€то, выберете другое: " << std::endl; ask(sign); }
			break;
		case 4:
			if (field[3] == 0) { field[3] = sign; return; }
			else { std::cout << "ѕоле зан€то, выберете другое: " << std::endl; ask(sign); }
			break;
		case 5:
			if (field[4] == 0) { field[4] = sign; return; }
			else { std::cout << "ѕоле зан€то, выберете другое: " << std::endl; ask(sign); }
			break;
		case 6:
			if (field[5] == 0) { field[5] = sign; return; }
			else { std::cout << "ѕоле зан€то, выберете другое: " << std::endl; ask(sign); }
			break;
		case 7:
			if (field[0] == 0) { field[0] = sign; return; }
			else { std::cout << "ѕоле зан€то, выберете другое: " << std::endl; ask(sign); }
			break;
		case 8:
			if (field[1] == 0) { field[1] = sign; return; }
			else { std::cout << "ѕоле зан€то, выберете другое: " << std::endl; ask(sign); }
			break;
		case 9:
			if (field[2] == 0) { field[2] = sign; return; }
			else { std::cout << "ѕоле зан€то, выберете другое: " << std::endl; ask(sign); }
			break;
		default:
			std::cout << "Exiting...";
			stopped = true;
			return;
		}
	}

	int field[9]{}; // поле
	int screen = 0; // экран, который сейчас проицируетс€
	bool stopped = false; // остановилась ли игра
	bool crest = false; // ходит ли игрок крестиками
	int turn = 0; // какой по счету ход игрока
	bool draw = false; // ничь€ ли сейчас
	bool firstly = false; // первый раз запустили программу
};

