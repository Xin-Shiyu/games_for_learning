#include <iostream>
#include <limits>
#include "gameboard.h"

bool game();
template <typename T>
bool ask_yn(T words)
{
	std::cout << words;
	std::cout << "(Y/N)?";
	char key;
	do std::cin.get(key);
	while (key != 'Y' and key != 'y' and key != 'N' and key != 'n');
	return key == 'Y' or key == 'y';
}

int main()
{
	std::cout << "Welcome to Connect Four! Written By Xin Shiyu\n\n";
	while (game());
	return 0;
}

bool game()
{
	std::cout << "New Game Starts!\n";
	gameboard board;
	bool is_now_black = true;
	for (;;)
	{
		board.render();
		int place;
		std::cout << "Now " << (is_now_black ? "Black" : "White") << "'s turn.\n";
		std::cout << "Enter the column number where you want to put the chess: ";
		std::cin >> place;
		while (place < 1 or place > 7)
		{
			std::cout << "The given place is invalid. Try enter again: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			std::cin >> place;
		}
		std::cout << '\n';
		auto result =
			board.put(
				place - 1,
				is_now_black ? 
				gameboard::chess_type::BLACK : gameboard::chess_type::WHITE);
		if (result == gameboard::operation_result::UNABLE)
		{
			std::cout << "You cannot put it here.\n";
		}
		else if (result == gameboard::operation_result::WIN)
		{
			board.render();
			std::cout << (is_now_black ? "Black, " : "White, ") << "You win!\n";
			break;
		}
		else
		{
			is_now_black = !is_now_black;
		}
	}
	return ask_yn("Do you want to play again?\n");
}

