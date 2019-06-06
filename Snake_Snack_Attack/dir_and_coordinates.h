#pragma once

enum class dir{none, up, right, down, left};

struct y_x {

	unsigned int y, x;

	explicit y_x(const unsigned int y = 0, const unsigned int x = 0) noexcept : y(y), x(x) {}

	~y_x() = default;
};

