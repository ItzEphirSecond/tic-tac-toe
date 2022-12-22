#include "Application.h"

// исполнительный

// конструктор
Application::Application()
{
	
}

// обновление
void Application::Update()
{
	// посмотреть поле screen
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

// спрашивать, кем хочет ходить игрок
void Application::Menu()
{
	// перегенерировать рандом
	srand(time(0));
	turn = 0; // это первый ход
	draw = false; // сейчас точно не ничья
	if (!firstly) // спрашиваем, если первый раз запустили программу
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
	else // если не первый
	{
		std::cout << "Вы начинаете новую игру, продолжить (y - да)?";
		std::string answer;
		std::cin >> answer;
		if (answer == "y")
		{
			// рандом ход
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

// цикл игры
void Application::Game()
{
	// нарисовать поле
	drawField();
	std::cout << "Turn: " << turn << std::endl; // вывести ход
	switch (crest)
	{
	case true: // если игрок ходит крестиками
		if (turn == 5) // если пятый ход (ничейная позиция)
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
	case false // если игрок ходит ноликами
		if (turn == 4) // если 4 ход (ничейная позиция)
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

	// проверяем, выиграл ли кто-нить
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

// игра для крестиков
void Application::gameCrest()
{
	std::cout << "Выберете, куда хотите пойти" << std::endl;
	ask(2); // спрашиваем, куда хотим пойти
	calculate(); // просчитываем ход компьютера
}

// игра для ноликов
void Application::gameNull()
{
	calculate(); // просчитываем ход компьютера
	bool who = false; 
	// проверяем, выиграл ли он
	if (isWinner(who))
	{
		drawField();
		std::string winner = (who ? "Крестики" : "Нолики");
		std::cout << "Выиграли:" << winner << std::endl;
		screen = 0;
		return;
	}
	drawField(); // рисуем поле
	
	std::cout << "Выберете, куда хотите пойти" << std::endl;
	ask(1); // спрашиваем, куда хотим пойти
}

#pragma region Do not use this, omg, this is so bad code that I cant understand why i am doing this

// this is very bad code, dont open it
void Application::calculate()
{
	// смотрим, какой сейчас ход
	switch (turn)
	{
	case 0: // первый ход
		if (crest) // если крестиками ходит игрок
		{
			if (field[4] == 0)
			{
				field[4] = 1; // занимаем центр
			}
			else
			{
				field[0] = 1; // занимаем верхний левый угол
			}
		}
		else // если крестиками ходит компьютер
		{
			field[4] = 2; // занимаем центр
		}
		break;
	case 1:
		if (crest)
		{
			bool who;
			int wheree;
			// проверяем, есть ли кака-то опасность, ставим в свободную клетку
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
				if (field[8] == 2 && field[4] == 2) field[6] = 1; // самая неприятная позиция, если 2 в большой диагонали и мы в верхнем левом углу
				else
				{
					// взависимости от того, какой угол мы заняли, ходим
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
			// я уже не помню, что делает этот код, но по-моему он ставит в противоположный угол от хода игрока
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
			// проверяем опасные позиции
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
				// ходим на рандом
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
			// проверяем опасные ситуации
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
				// взависимости от того, какой угол мы заняли, ходим
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
					elif(field[7] == 1) field[3] = 2;
				}
			}
		}
		break;
	// далее мы просто проверяем, есть ли опасные позиции, иначе ставим на рандом, можно объединить в одну функцию, но мне лень
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
