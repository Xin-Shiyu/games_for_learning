#include <iostream>
#include <random>
#include <vector>
#include <string>

struct match_result
{
	unsigned hits = 0;
	unsigned blows = 0;

	bool missed()
	{
		return hits == 0 and blows == 0;
	}

	bool win()
	{
		return hits == 4;
	}
};

std::vector<int> gen_ans();
void run_game();
std::vector<int> read_guess();
match_result match(
	std::vector<int> & real_ans,
	std::vector<int> && player_ans);

int main()
{
	std::cout << "Hits & Blows\n\n";
	for (;;) run_game();
}

void run_game()
{
	int current_player = 0;
	auto ans = gen_ans();

	std::cout << "New Game Starts.\n";

	for (;;)
	{
		std::cout << "It's player " << (current_player + 1) << "\'s turn.\n"
			<< "Enter your guess: ";
		auto res = match(ans, read_guess());
		if (res.missed())
		{
			std::cout << "Sorry you've missed!\n\n";
		}
		else if (res.win())
		{
			std::cout << "Player " << (current_player + 1) << ", you win!\n\n";
			return;
		}
		else
		{
			std::cout << "You've got " << res.hits << " hits and " << res.blows << " blows.\n\n";
		}
		if (current_player == 1) current_player = 0;
		else current_player = 1;
	}
}

std::vector<int> gen_ans()
{
	std::random_device seed;
	std::default_random_engine random;
	random.seed(seed());
	std::uniform_int_distribution<> range(1, 6);
	std::vector<int> res;
	for (size_t i = 0; i < 4; ++i)
	{
		res.push_back(range(random));
	}
	return res;
}

std::vector<int> read_guess()
{
	bool failed = true;
	std::vector<int> res;
	do
	{
		std::string input;
		std::getline(std::cin >> std::ws, input);
		if (input.size() == 4)
		{
			for (char & c : input)
			{
				if ('1' <= c and c <= '6')
				{
					res.push_back(static_cast<int>(c - '0'));
					failed = false;
				}
				else
				{
					std::cout << "Your input is invalid! Try again: ";
					break;
				}
			}
		}
		else
		{
			std::cout << "Your input is invalid! Try again: ";
		}
	} while (failed);
	return res;
}

match_result match(
	std::vector<int> & real_ans,
	std::vector<int> && player_ans)
{
	bool matched[4] = {0};
	bool matched_player[4] = {0};
	match_result res;
	for (int i = 0; i < 4; ++i)
	{
		if (real_ans[i] == player_ans[i])
		{
			++res.hits;
			matched[i] = true;
			matched_player[i] = true;
		}
	}
	if (res.hits == 4) return res;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (real_ans[j] == player_ans[i] and
				!(matched[j] or matched_player[i]))
			{
				++res.blows;
				matched[j] = true;
				break;
			}
		}
}
	return res;
}