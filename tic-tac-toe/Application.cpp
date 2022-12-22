#include "Application.h"

Application::Application()
{
	
}

void Application::Update()
{
	switch (screen)
	{
	case 0:
		Menu();
		break;
	case 1:
		Game();
		break;
	default:
		stopped = true;
		break;
	}
}

void Application::Menu()
{
	srand(time(0));
	turn = 0;
	draw = false;
	if (!firstly)
	{
		std::cout << "Выберете, за кого будете играть (1 - крестики, 0 - нолиики):" << std::endl;
		std::cin >> crest;
		if (!(crest == 0 || crest == 1))
		{
			std::cout << "Exiting...";
			stopped = true;
			return;
		}
		firstly = true;
	}
	else
	{
		std::cout << "Вы начинаете новую игру, продолжить (y - да)?";
		std::string answer;
		std::cin >> answer;
		if (answer == "y")
		{
			crest = rand() % 2;
			for (int i = 0; i < 9; i++)
			{
				field[i] = 0;
			}
		}
		else
		{
			stopped = true;
			return;
		}
	}
	screen = 1;
}

void Application::Game()
{
	drawField();
	std::cout << "Turn: " << turn << std::endl;
	switch (crest)
	{
	case true:
		if (turn == 5)
		{
			drawField();
			bool who = false;
			if (isWinner(who))
			{
				std::string winner = (who ? "Крестики" : "Нолики");
				std::cout << "Выиграли:" << winner << std::endl;
				screen = 0;
				return;
			}
			else
			{
				draw = true;
				screen = 0;
				std::cout << "Ничья" << std::endl;
				return;
			}
		}
		gameCrest();
		break;
	case false:
		if (turn == 4)
		{
			calculate();
			drawField();
			bool who = false;
			if (isWinner(who))
			{
				std::string winner = (who ? "Крестики" : "Нолики");
				std::cout << "Выиграли:" << winner << std::endl;
				screen = 0;
				return;
			}
			else
			{
				draw = true;
				screen = 0;
				std::cout << "Ничья" << std::endl;
				return;
			}
		}
		gameNull();
		break;
	default:
		std::cout << "Error";
		stopped = true;
		return;
	}

	bool who = false;

	if (isWinner(who))
	{
		drawField();
		std::string winner = (who ? "Крестики" : "Нолики");
		std::cout << "Выиграли:" << winner << std::endl;
		screen = 0;
		return;
	}
	turn++;
}

void Application::gameCrest()
{
	std::cout << "Выберете, куда хотите пойти" << std::endl;
	int answer;
	std::cin >> answer;
	switch (answer)
	{
	case 1:
		if (field[6] == 0) field[6] = 2;
		else std::cout << "Поле занято, выберете другое: " << std::endl;
		break;
	case 2:
		if(field[7] == 0) field[7] = 2;
		else std::cout << "Поле занято, выберете другое: " << std::endl;
		break;
	case 3:
		if (field[8] == 0)field[8] = 2;
		else std::cout << "Поле занято, выберете другое: " << std::endl;
		break;
	case 4:
		if (field[3] == 0) field[3] = 2;
		else std::cout << "Поле занято, выберете другое: " << std::endl;
		break;
	case 5:
		if (field[4] == 0) field[4] = 2;
		else std::cout << "Поле занято, выберете другое: " << std::endl;
		break;
	case 6:
		if (field[5] == 0) field[5] = 2;
		else std::cout << "Поле занято, выберете другое: " << std::endl;
		break;
	case 7:
		if (field[0] == 0) field[0] = 2;
		else std::cout << "Поле занято, выберете другое: " << std::endl;
		break;
	case 8:
		if (field[1] == 0) field[1] = 2;
		else std::cout << "Поле занято, выберете другое: " << std::endl;
		break;
	case 9:
		if (field[2] == 0) field[2] = 2;
		else std::cout << "Поле занято, выберете другое: " << std::endl;
		break;
	default:
		std::cout << "Exiting...";
		stopped = true;
		return;
	}
	calculate();
}

void Application::gameNull()
{
	calculate();
	bool who = false;
	if (isWinner(who))
	{
		drawField();
		std::string winner = (who ? "Крестики" : "Нолики");
		std::cout << "Выиграли:" << winner << std::endl;
		screen = 0;
		return;
	}
	drawField();
	std::cout << "Выберете, куда хотите пойти" << std::endl;
	int answer;
	std::cin >> answer;
	
	switch (answer)
	{
	case 1:
		field[6] = 1;
		break;
	case 2: 
		field[7] = 1;
		break;
	case 3:
		field[8] = 1;
		break;
	case 4:
		field[3] = 1;
		break;
	case 5:
		field[4] = 1;
		break;
	case 6:
		field[5] = 1;
		break;
	case 7:
		field[0] = 1;
		break;
	case 8:
		field[1] = 1;
		break;
	case 9:
		field[2] = 1;
		break;
	default:
		std::cout << "Exiting...";
		stopped = true;
		return;
	}
}

#pragma region Do not use this, omg, this is so bad code that I cant understand why i am doing this

// this is very bad code, dont open it
void Application::calculate()
{
	switch (turn)
	{
	case 0:
		if (crest)
		{
			if (field[4] == 0)
			{
				field[4] = 1;
			}
			else
			{
				field[0] = 1;
			}
		}
		else
		{
			field[4] = 2;
		}
		break;
	case 1:
		if (crest)
		{
			bool who;
			int wheree;
			if (isDanger(who, wheree))
			{
				switch (wheree)
				{
				case 0:
					if (field[0] == 0) field[0] = 1;
					elif(field[1] == 0) field[1] = 1;
					elif(field[2] == 0) field[2] = 1;
					break;
				case 1:
					if (field[3] == 0) field[3] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[5] == 0) field[5] = 1;
					break;
				case 2:
					if (field[6] == 0) field[6] = 1;
					elif(field[7] == 0) field[7] = 1;
					elif(field[8] == 0) field[8] = 1;
					break;
				case 3:
					if (field[0] == 0) field[0] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[8] == 0) field[8] = 1;
					break;
				case 4:
					if (field[0] == 0) field[0] = 1;
					elif(field[3] == 0) field[3] = 1;
					elif(field[6] == 0) field[6] = 1;
					break;
				case 5:
					if (field[1] == 0) field[1] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[7] == 0) field[7] = 1;
					break;
				case 6:
					if (field[2] == 0) field[2] = 1;
					elif(field[5] == 0) field[5] = 1;
					elif(field[8] == 0) field[8] = 1;
					break;
				case 7:
					if (field[6] == 0) field[6] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[2] == 0) field[2] = 1;
					break;
				}
			}
			else
			{
				if (field[8] == 2 && field[4] == 2) field[6] = 1;
				else
				{
					if (field[0] == 2)
					{
						if (field[8] == 2 || field[5] == 2) field[7] = 1;
						elif(field[7] == 2) field[5] = 1;
					}
					elif(field[2] == 2)
					{
						if (field[6] == 2 || field[3] == 2) field[7] = 1;
						elif(field[7] == 2) field[3] = 1;
					}
					elif(field[6] == 2)
					{
						if (field[2] == 2 || field[5] == 2) field[1] = 1;
						elif(field[1] == 2) field[5] = 1;
					}
					elif(field[8] == 2)
					{
						if (field[0] == 2 || field[3] == 2) field[1] = 1;
						elif(field[1] == 2) field[3] = 1;
					}
					elif(field[1] == 2)
					{
						if (field[3] == 2) field[0] = 1;
						elif(field[7] == 2) field[2] = 1;
						elif(field[5] == 2) field[2] = 1;
					}
					elif(field[3] == 2)
					{
						if (field[7] == 2) field[6] = 1;
						elif(field[5] == 2) field[6] = 1;
						elif(field[1] == 2) field[0] = 1;
					}
					elif(field[7] == 2)
					{
						if (field[5] == 2) field[8] = 1;
					}
				}
			}
		}
		else
		{
			if (field[0] == 1 || field[1] == 1 || field[3] == 1) field[8] = 2;
			else if (field[6] == 1 || field[7] == 1) field[2] = 2;
			else if (field[8] == 1 || field[5] == 1) field[0] = 2;
			else field[6] = 2;
		}
		break;
	case 2:
		if (crest)
		{
			bool who;
			int wheree;
			if (isDanger(who, wheree))
			{
				switch (wheree)
				{
				case 0:
					if (field[0] == 0) field[0] = 1;
					elif(field[1] == 0) field[1] = 1;
					elif(field[2] == 0) field[2] = 1;
					break;
				case 1:
					if (field[3] == 0) field[3] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[5] == 0) field[5] = 1;
					break;
				case 2:
					if (field[6] == 0) field[6] = 1;
					elif(field[7] == 0) field[7] = 1;
					elif(field[8] == 0) field[8] = 1;
					break;
				case 3:
					if (field[0] == 0) field[0] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[8] == 0) field[8] = 1;
					break;
				case 4:
					if (field[0] == 0) field[0] = 1;
					elif(field[3] == 0) field[3] = 1;
					elif(field[6] == 0) field[6] = 1;
					break;
				case 5:
					if (field[1] == 0) field[1] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[7] == 0) field[7] = 1;
					break;
				case 6:
					if (field[2] == 0) field[2] = 1;
					elif(field[5] == 0) field[5] = 1;
					elif(field[8] == 0) field[8] = 1;
					break;
				case 7:
					if (field[6] == 0) field[6] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[2] == 0) field[2] = 1;
					break;
				}
			}
			else
			{
				if (field[0] == 0) field[0] = 1;
				elif(field[1] == 0) field[1] = 1;
				elif(field[2] == 0) field[2] = 1;
				elif(field[3] == 0) field[3] = 1;
				elif(field[4] == 0) field[4] = 1;
				elif(field[5] == 0) field[5] = 1;
				elif(field[6] == 0) field[6] = 1;
				elif(field[7] == 0) field[7] = 1;
				elif(field[8] == 0) field[8] = 1;
			}
		}
		else
		{
			bool who;
			int wheree;
			if (isDanger(who, wheree))
			{
				switch (wheree)
				{
				case 0:
					if (field[0] == 0) field[0] = 2;
					elif(field[1] == 0) field[1] = 2;
					elif(field[2] == 0) field[2] = 2;
					break;
				case 1:
					if (field[3] == 0) field[3] = 2;
					elif(field[4] == 0) field[4] = 2;
					elif(field[5] == 0) field[5] = 2;
					break;
				case 2:
					if (field[6] == 0) field[6] = 2;
					elif(field[7] == 0) field[7] = 2;
					elif(field[8] == 0) field[8] = 2;
					break;
				case 3:
					if (field[0] == 0) field[0] = 2;
					elif(field[4] == 0) field[4] = 2;
					elif(field[8] == 0) field[8] = 2;
					break;
				case 4:
					if (field[0] == 0) field[0] = 2;
					elif(field[3] == 0) field[3] = 2;
					elif(field[6] == 0) field[6] = 2;
					break;
				case 5:
					if (field[1] == 0) field[1] = 2;
					elif(field[4] == 0) field[4] = 2;
					elif(field[7] == 0) field[7] = 2;
					break;
				case 6:
					if (field[2] == 0) field[2] = 2;
					elif(field[5] == 0) field[5] = 2;
					elif(field[8] == 0) field[8] = 2;
					break;
				case 7:
					if (field[6] == 0) field[6] = 2;
					elif(field[4] == 0) field[4] = 2;
					elif(field[2] == 0) field[2] = 2;
					break;
				}
			}
			else
			{
				if (field[8] == 2)
				{
					if (field[7] == 1) field[5] = 2;
					elif(field[5] == 1) field[7] = 2;
				}
				elif(field[2] == 2)
				{
					if (field[1] == 1) field[5] = 2;
					elif(field[5] == 1) field[1] = 2;
				}
				elif(field[0] == 2)
				{
					if (field[1] == 1) field[3] = 2;
					elif(field[3] == 1) field[1] = 2;
				}
				elif(field[6] == 2)
				{
					if (field[3] == 1) field[7] = 2;
					elif(field[7] == 2) field[3] = 2;
				}
			}
		}
		break;
	case 3:
		if (crest)
		{
			bool who;
			int wheree;
			if (isDanger(who, wheree))
			{
				switch (wheree)
				{
				case 0:
					if (field[0] == 0) field[0] = 1;
					elif(field[1] == 0) field[1] = 1;
					elif(field[2] == 0) field[2] = 1;
					break;
				case 1:
					if (field[3] == 0) field[3] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[5] == 0) field[5] = 1;
					break;
				case 2:
					if (field[6] == 0) field[6] = 1;
					elif(field[7] == 0) field[7] = 1;
					elif(field[8] == 0) field[8] = 1;
					break;
				case 3:
					if (field[0] == 0) field[0] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[8] == 0) field[8] = 1;
					break;
				case 4:
					if (field[0] == 0) field[0] = 1;
					elif(field[3] == 0) field[3] = 1;
					elif(field[6] == 0) field[6] = 1;
					break;
				case 5:
					if (field[1] == 0) field[1] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[7] == 0) field[7] = 1;
					break;
				case 6:
					if (field[2] == 0) field[2] = 1;
					elif(field[5] == 0) field[5] = 1;
					elif(field[8] == 0) field[8] = 1;
					break;
				case 7:
					if (field[6] == 0) field[6] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[2] == 0) field[2] = 1;
					break;
				}
			}
			else
			{
				if (field[0] == 0) field[0] = 1;
				elif(field[1] == 0) field[1] = 1;
				elif(field[2] == 0) field[2] = 1;
				elif(field[3] == 0) field[3] = 1;
				elif(field[4] == 0) field[4] = 1;
				elif(field[5] == 0) field[5] = 1;
				elif(field[6] == 0) field[6] = 1;
				elif(field[7] == 0) field[7] = 1;
				elif(field[8] == 0) field[8] = 1;
			}
		}
		else
		{
			bool who;
			int wheree;
			if (isDanger(who, wheree))
			{
				switch (wheree)
				{
				case 0:
					if (field[0] == 0) field[0] = 2;
					elif(field[1] == 0) field[1] = 2;
					elif(field[2] == 0) field[2] = 2;
					break;
				case 1:
					if (field[3] == 0) field[3] = 2;
					elif(field[4] == 0) field[4] = 2;
					elif(field[5] == 0) field[5] = 2;
					break;
				case 2:
					if (field[6] == 0) field[6] = 2;
					elif(field[7] == 0) field[7] = 2;
					elif(field[8] == 0) field[8] = 2;
					break;
				case 3:
					if (field[0] == 0) field[0] = 2;
					elif(field[4] == 0) field[4] = 2;
					elif(field[8] == 0) field[8] = 2;
					break;
				case 4:
					if (field[0] == 0) field[0] = 2;
					elif(field[3] == 0) field[3] = 2;
					elif(field[6] == 0) field[6] = 2;
					break;
				case 5:
					if (field[1] == 0) field[1] = 2;
					elif(field[4] == 0) field[4] = 2;
					elif(field[7] == 0) field[7] = 2;
					break;
				case 6:
					if (field[2] == 0) field[2] = 2;
					elif(field[5] == 0) field[5] = 2;
					elif(field[8] == 0) field[8] = 2;
					break;
				case 7:
					if (field[6] == 0) field[6] = 2;
					elif(field[4] == 0) field[4] = 2;
					elif(field[2] == 0) field[2] = 2;
					break;
				}
			}
			else
			{
				if (field[0] == 0) field[0] = 2;
				elif(field[1] == 0) field[1] = 2;
				elif(field[2] == 0) field[2] = 2;
				elif(field[3] == 0) field[3] = 2;
				elif(field[4] == 0) field[4] = 2;
				elif(field[5] == 0) field[5] = 2;
				elif(field[6] == 0) field[6] = 2;
				elif(field[7] == 0) field[7] = 2;
				elif(field[8] == 0) field[8] = 2;
 			}
		}
		break;
	case 4:
		if (crest)
		{
			bool who;
			int wheree;
			if (isDanger(who, wheree))
			{
				switch (wheree)
				{
				case 0:
					if (field[0] == 0) field[0] = 1;
					elif(field[1] == 0) field[1] = 1;
					elif(field[2] == 0) field[2] = 1;
					break;
				case 1:
					if (field[3] == 0) field[3] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[5] == 0) field[5] = 1;
					break;
				case 2:
					if (field[6] == 0) field[6] = 1;
					elif(field[7] == 0) field[7] = 1;
					elif(field[8] == 0) field[8] = 1;
					break;
				case 3:
					if (field[0] == 0) field[0] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[8] == 0) field[8] = 1;
					break;
				case 4:
					if (field[0] == 0) field[0] = 1;
					elif(field[3] == 0) field[3] = 1;
					elif(field[6] == 0) field[6] = 1;
					break;
				case 5:
					if (field[1] == 0) field[1] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[7] == 0) field[7] = 1;
					break;
				case 6:
					if (field[2] == 0) field[2] = 1;
					elif(field[5] == 0) field[5] = 1;
					elif(field[8] == 0) field[8] = 1;
					break;
				case 7:
					if (field[6] == 0) field[6] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[2] == 0) field[2] = 1;
					break;
				}
			}
			else
			{
				if (field[0] == 0) field[0] = 1;
				elif(field[1] == 0) field[1] = 1;
				elif(field[2] == 0) field[2] = 1;
				elif(field[3] == 0) field[3] = 1;
				elif(field[4] == 0) field[4] = 1;
				elif(field[5] == 0) field[5] = 1;
				elif(field[6] == 0) field[6] = 1;
				elif(field[7] == 0) field[7] = 1;
				elif(field[8] == 0) field[8] = 1;
			}
		}
		else
		{
			bool who;
			int wheree;
			if (isDanger(who, wheree))
			{
				switch (wheree)
				{
				case 0:
					if (field[0] == 0) field[0] = 2;
					elif(field[1] == 0) field[1] = 2;
					elif(field[2] == 0) field[2] = 2;
					break;
				case 1:
					if (field[3] == 0) field[3] = 2;
					elif(field[4] == 0) field[4] = 2;
					elif(field[5] == 0) field[5] = 2;
					break;
				case 2:
					if (field[6] == 0) field[6] = 2;
					elif(field[7] == 0) field[7] = 2;
					elif(field[8] == 0) field[8] = 2;
					break;
				case 3:
					if (field[0] == 0) field[0] = 2;
					elif(field[4] == 0) field[4] = 2;
					elif(field[8] == 0) field[8] = 2;
					break;
				case 4:
					if (field[0] == 0) field[0] = 2;
					elif(field[3] == 0) field[3] = 2;
					elif(field[6] == 0) field[6] = 2;
					break;
				case 5:
					if (field[1] == 0) field[1] = 2;
					elif(field[4] == 0) field[4] = 2;
					elif(field[7] == 0) field[7] = 2;
					break;
				case 6:
					if (field[2] == 0) field[2] = 2;
					elif(field[5] == 0) field[5] = 2;
					elif(field[8] == 0) field[8] = 2;
					break;
				case 7:
					if (field[6] == 0) field[6] = 2;
					elif(field[4] == 0) field[4] = 2;
					elif(field[2] == 0) field[2] = 2;
					break;
				}
			}
			else
			{
				if (field[0] == 0) field[0] = 2;
				elif(field[1] == 0) field[1] = 2;
				elif(field[2] == 0) field[2] = 2;
				elif(field[3] == 0) field[3] = 2;
				elif(field[4] == 0) field[4] = 2;
				elif(field[5] == 0) field[5] = 2;
				elif(field[6] == 0) field[6] = 2;
				elif(field[7] == 0) field[7] = 2;
				elif(field[8] == 0) field[8] = 2;
			}
		}
		break;
	case 5:
		if (crest)
		{
			bool who;
			int wheree;
			if (isDanger(who, wheree))
			{
				switch (wheree)
				{
				case 0:
					if (field[0] == 0) field[0] = 1;
					elif(field[1] == 0) field[1] = 1;
					elif(field[2] == 0) field[2] = 1;
					break;
				case 1:
					if (field[3] == 0) field[3] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[5] == 0) field[5] = 1;
					break;
				case 2:
					if (field[6] == 0) field[6] = 1;
					elif(field[7] == 0) field[7] = 1;
					elif(field[8] == 0) field[8] = 1;
					break;
				case 3:
					if (field[0] == 0) field[0] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[8] == 0) field[8] = 1;
					break;
				case 4:
					if (field[0] == 0) field[0] = 1;
					elif(field[3] == 0) field[3] = 1;
					elif(field[6] == 0) field[6] = 1;
					break;
				case 5:
					if (field[1] == 0) field[1] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[7] == 0) field[7] = 1;
					break;
				case 6:
					if (field[2] == 0) field[2] = 1;
					elif(field[5] == 0) field[5] = 1;
					elif(field[8] == 0) field[8] = 1;
					break;
				case 7:
					if (field[6] == 0) field[6] = 1;
					elif(field[4] == 0) field[4] = 1;
					elif(field[2] == 0) field[2] = 1;
					break;
				}
			}
			else
			{
				if (field[0] == 0) field[0] = 1;
				elif(field[1] == 0) field[1] = 1;
				elif(field[2] == 0) field[2] = 1;
				elif(field[3] == 0) field[3] = 1;
				elif(field[4] == 0) field[4] = 1;
				elif(field[5] == 0) field[5] = 1;
				elif(field[6] == 0) field[6] = 1;
				elif(field[7] == 0) field[7] = 1;
				elif(field[8] == 0) field[8] = 1;
			}
		}
		else
		{
			bool who;
			int wheree;
			if (isDanger(who, wheree))
			{
				switch (wheree)
				{
				case 0:
					if (field[0] == 0) field[0] = 2;
					elif(field[1] == 0) field[1] = 2;
					elif(field[2] == 0) field[2] = 2;
					break;
				case 1:
					if (field[3] == 0) field[3] = 2;
					elif(field[4] == 0) field[4] = 2;
					elif(field[5] == 0) field[5] = 2;
					break;
				case 2:
					if (field[6] == 0) field[6] = 2;
					elif(field[7] == 0) field[7] = 2;
					elif(field[8] == 0) field[8] = 2;
					break;
				case 3:
					if (field[0] == 0) field[0] = 2;
					elif(field[4] == 0) field[4] = 2;
					elif(field[8] == 0) field[8] = 2;
					break;
				case 4:
					if (field[0] == 0) field[0] = 2;
					elif(field[3] == 0) field[3] = 2;
					elif(field[6] == 0) field[6] = 2;
					break;
				case 5:
					if (field[1] == 0) field[1] = 2;
					elif(field[4] == 0) field[4] = 2;
					elif(field[7] == 0) field[7] = 2;
					break;
				case 6:
					if (field[2] == 0) field[2] = 2;
					elif(field[5] == 0) field[5] = 2;
					elif(field[8] == 0) field[8] = 2;
					break;
				case 7:
					if (field[6] == 0) field[6] = 2;
					elif(field[4] == 0) field[4] = 2;
					elif(field[2] == 0) field[2] = 2;
					break;
				}
			}
			else
			{
				if (field[0] == 0) field[0] = 2;
				elif(field[1] == 0) field[1] = 2;
				elif(field[2] == 0) field[2] = 2;
				elif(field[3] == 0) field[3] = 2;
				elif(field[4] == 0) field[4] = 2;
				elif(field[5] == 0) field[5] = 2;
				elif(field[6] == 0) field[6] = 2;
				elif(field[7] == 0) field[7] = 2;
				elif(field[8] == 0) field[8] = 2;
			}
		}
		break;
	}
}

#pragma endregion
