/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 10:14:54 by lguiller          #+#    #+#             */
/*   Updated: 2019/10/29 12:05:41 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "npuzzle.h"

int		**make_final_grid(int length, int width)
{
	const int size(length * width);
	int **new_grid = new int*[length];
	int x_minmax[2] = { 0, width - 1 };
	int y_minmax[2] = { 0, length - 1 };
	int i(1);

	for (int y = 0 ; y < length ; ++y)
			new_grid[y] = new int[width];
	while (i <= size)
	{
		for (int x = x_minmax[MIN] ; x <= x_minmax[MAX] && i <= size ; ++x)
			new_grid[y_minmax[MIN]][x] = i++;
		++y_minmax[MIN];
		for (int y = y_minmax[MIN] ; y <= y_minmax[MAX] && i <= size ; ++y)
			new_grid[y][x_minmax[MAX]] = i++;
		--x_minmax[MAX];
		for (int x = x_minmax[MAX] ; x >= x_minmax[MIN] && i <= size ; --x)
			new_grid[y_minmax[MAX]][x] = i++;
		--y_minmax[MAX];
		for (int y = y_minmax[MAX] ; y >= y_minmax[MIN] && i <= size ; --y)
			new_grid[y][x_minmax[MIN]] = i++;
		++x_minmax[MIN];
	}
	return (new_grid);
}

static Coord	find_final_coord(int **grid, int height, int width, int n)
{
	for (int y = 0 ; y < height ; ++y)
		for (int x = 0 ; x < width ; ++x)
			if (grid[y][x] == n)
				return (Coord(x, y));
	return (Coord(-1, -1));
}

void		convert_grid(int **final_grid, State &actual)
{
	int		**wanted_grid = new int*[actual.height];
	Coord	coord;
	int		i(1);

	for (int y = 0 ; y < actual.height ; ++y)
	{
		wanted_grid[y] = new int[actual.width];
		for (int x = 0 ; x < actual.width ; ++x)
			wanted_grid[y][x] = i++;
	}
	for (int y = 0 ; y < actual.height ; ++y)
		for (int x = 0 ; x < actual.width ; ++x)
		{
			coord = find_final_coord(final_grid, actual.height, actual.width, actual.grid[y][x]);
			if (wanted_grid[coord.y][coord.x] == actual.size)
				actual.hole.set(x, y);
			actual.grid[y][x] = wanted_grid[coord.y][coord.x];
		}
	actual.setMixValue();
	for (int y = 0 ; y < actual.height ; ++y)
		delete[] wanted_grid[y];
	delete[] wanted_grid;
}
