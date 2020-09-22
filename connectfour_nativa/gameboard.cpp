#include "gameboard.h"

void gameboard::render()
{
	for (int y = board_height - 1; y >= 0; --y)
	{
		for (int x = 0; x < board_width; ++x)
		{
			switch (board[x][y])
			{
			case chess_type::NOTHING:
				std::cout << ' ';
				break;
			case chess_type::BLACK:
				std::cout << 'x';
				break;
			case chess_type::WHITE:
				std::cout << 'o';
				break;
			}
		}
		std::cout << '\n';
	}
	for (int x = 1; x <= board_width; ++x)
	{
		std::cout << x;
	}
	std::cout << std::endl;
}

gameboard::operation_result gameboard::put(int column, chess_type chess)
{
	auto put_result = put_simple(column, chess);
	if (put_result.has_value())
	{
		if (has_won(*put_result))
		{
			return operation_result::WIN;
		}
		return operation_result::NOTHING;
	}
	return operation_result::UNABLE;
}

std::optional<vec2<int>> gameboard::put_simple(int column, chess_type chess)
{  
	auto &col = board[column];
	auto len = col.size();
	decltype(len) y = 0;
	while (y < board_height and col[y] != chess_type::NOTHING)
	{
		++y;
	}
	if (y != len)
	{
		col[y] = chess;
		return vec2<int>(column, y);
	}
	return std::nullopt;
}

int gameboard::count_chess(vec2<int> source, vec2<int> direction)
{
	int res = 0;
	auto source_chess = board[source.x][source.y];
	source += direction; 
	// 直接复用 source 向量，我们只需要知道 source 本来是什么棋就行了
	while (source.is_inside(0, 0, board_width, board_height)
		and board[source.x][source.y] == source_chess)
	{
		++res;
		source += direction;
	}
	return res;
}

bool gameboard::has_won(vec2<int> source)
{
	return
		count_chess(source, { 0, -1 }) == 3 or
		count_chess(source, { -1, 0 }) + count_chess(source, { 1, 0 }) == 3 or
		count_chess(source, { -1, -1 }) + count_chess(source, { 1, 1 }) == 3 or
		count_chess(source, { -1, 1 }) + count_chess(source, { 1, -1 }) == 3;
}
