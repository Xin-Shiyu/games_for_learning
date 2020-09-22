#pragma once
#include <array>
#include "vec2.h"
#include <optional>
#include <memory>
#include <iostream>

constexpr int board_width = 7;
constexpr int board_height = 6;

class gameboard
{
public:
	enum class chess_type : short
	{
		NOTHING,
		BLACK,
		WHITE
	};
	enum class operation_result
	{
		NOTHING,
		UNABLE,
		WIN
	};
	using board_type = std::array<std::array<chess_type, board_height>, board_width>;
	void render();
	operation_result put(int column, chess_type chess);
private:
	board_type board = {};
	std::optional<vec2<int>> put_simple(int column, chess_type chess);
	int count_chess(vec2<int> source, vec2<int> direction);
	bool has_won(vec2<int> source);
	// 外层代表列数，内层代表行数，最下为 0
};