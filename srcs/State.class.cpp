/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:42:02 by lguiller          #+#    #+#             */
/*   Updated: 2020/01/28 11:43:18 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "npuzzle.h"

State::State(void) : grid(NULL)
{
	return ;
}

static int			**ft_makeFinalGrid(int size)
{
	int			**newGrid;
	int			end(pow(size, 2));
	int			xMinMAx[2] = { 0, size - 1 };
	int			yMinMAx[2] = { 0, size - 1 };

	newGrid = new int*[size];
	for (int y(0) ; y < size ; ++y)
			newGrid[y] = new int[size];
	for (int i(0) ; i < end ; )
	{
		for (int x = xMinMAx[MIN] ; x <= xMinMAx[MAX] && i < end ; ++x)
			newGrid[yMinMAx[MIN]][x] = (++i < end) ? i : 0;
		++yMinMAx[MIN];
		for (int y = yMinMAx[MIN] ; y <= yMinMAx[MAX] && i < end ; ++y)
			newGrid[y][xMinMAx[MAX]] = (++i < end) ? i : 0;
		--xMinMAx[MAX];
		for (int x = xMinMAx[MAX] ; x >= xMinMAx[MIN] && i < end ; --x)
			newGrid[yMinMAx[MAX]][x] = (++i < end) ? i : 0;
		--yMinMAx[MAX];
		for (int y = yMinMAx[MAX] ; y >= yMinMAx[MIN] && i < end ; --y)
			newGrid[y][xMinMAx[MIN]] = (++i < end) ? i : 0;
		++xMinMAx[MIN];
	}
	return (newGrid);
}

void				State::init(int size, int **values)
{
	this->size = size;
	this->grid = new int*[size];
	for (int y(0) ; y < size ; ++y)
	{
		this->grid[y] = new int[size];
		for (int x(0) ; x < size ; ++x)
		{
			if (values[y][x] == 0)
				this->hole.set(x, y);
			this->grid[y][x] = values[y][x];
		}
	}
	this->finalGrid = ft_makeFinalGrid(size);
	this->heuristic = 0;
	this->setMixValue();
	this->shortestPath = "";
}

State::State(int size) : size(size), grid(NULL), heuristic(0), mixValue(0), shortestPath("")
{
	this->grid = new int*[size];
	for (int y(0) ; y < size ; ++y)
	{
		this->grid[y] = new int[size];
		for (int x(0) ; x < size ; ++x)
			this->grid[y][x] = 0;
	}
}

State::State(const State &rhs)
{
	this->size = rhs.size;
	this->hole = rhs.hole;
	this->grid = new int*[size];
	this->finalGrid = new int*[size];
	for (int y(0) ; y < size ; ++y)
	{
		this->grid[y] = new int[size];
		this->finalGrid[y] = new int[size];
		for (int x(0) ; x < size ; ++x)
		{
			this->grid[y][x] = rhs.grid[y][x];
			this->finalGrid[y][x] = rhs.finalGrid[y][x];
		}
	}
	this->heuristic = rhs.heuristic;
	this->mixValue = rhs.mixValue;
	this->shortestPath = rhs.shortestPath;
}

State::~State(void)
{
	if (this->grid)
	{
		for (int y(0) ; y < this->size ; ++y)
		{
			delete[] this->grid[y];
			delete[] this->finalGrid[y];
		}
		delete[] this->grid;
		delete[] this->finalGrid;
	}
}

State				&State::operator=(State const &rhs)
{
	this->size = rhs.size;
	this->hole = rhs.hole;
	for (int y(0) ; y < size ; ++y)
		for (int x(0) ; x < size ; ++x)
		{
			this->grid[y][x] = rhs.grid[y][x];
			this->finalGrid[y][x] = rhs.finalGrid[y][x];
		}
	this->heuristic = rhs.heuristic;
	this->mixValue = rhs.mixValue;
	this->shortestPath = rhs.shortestPath;
	return (*this);
}

static Coord		ft_findFinalCoord(int size, int **finalGrid, int value)
{
	for (int y(0) ; y < size ; ++y)
		for (int x(0) ; x < size ; ++x)
			if (finalGrid[y][x] == value)
				return (Coord(x, y));
	return (Coord(-1, -1));
}

State				State::swap(char action) const
{
	State	newState(*this);
	int		x(0);
	int		y(0);

	if ((action == 'E' && this->hole.x < this->size - 1) || (action == 'W' && this->hole.x > 0))
		x = (action == 'E') ? 1 : -1;
	if ((action == 'S' && this->hole.y < this->size - 1) || (action == 'N' && this->hole.y > 0))
		y = (action == 'S') ? 1 : -1;
	newState.grid[this->hole.y][this->hole.x] = newState.grid[this->hole.y + y][this->hole.x + x];
	newState.grid[this->hole.y + y][this->hole.x + x] = 0;
	newState.hole.x += x;
	newState.hole.y += y;
	newState.shortestPath += action;
	newState.setMixValue();
	return (newState);
}

void				State::setMixValue()
{
	unsigned int	value(0);
	Coord			b;

	for (Coord a(0, 0) ; a.y < this->size ; ++a.y)
		for (a.x = 0 ; a.x < this->size ; ++a.x)
			if (this->grid[a.y][a.x] != this->finalGrid[a.y][a.x])
			{
				b = ft_findFinalCoord(this->size, this->finalGrid, this->grid[a.y][a.x]);
				value += abs(b.x - a.x) + abs(b.y - a.y);
			}
	this->heuristic = value;
	this->mixValue = this->shortestPath.size() + value;
}

int					State::getFinalCoord(int value)
{
	Coord finalCoord(ft_findFinalCoord(this->size, this->finalGrid, value));
	return (finalCoord.y * this->size + finalCoord.x);
}

std::ostream		&operator<<(std::ostream &o, const State &rhs)
{
	int valueSize(0);
	int holeSize(0);

	if (!rhs.grid)
		o << '/' << std::endl;
	else
	{
		for (int tmp = pow(rhs.size, 2) ; tmp >= 10 ; tmp /= 10)
			++holeSize;
		for (int y = 0 ; y < rhs.size ; ++y)
		{
			for (int x = 0 ; x < rhs.size ; ++x)
			{
				valueSize = 0;
				if (rhs.grid[y][x] != 0)
					for (int tmp = rhs.grid[y][x] ; tmp >= 10 ; tmp /= 10)
						++valueSize;
				for (int i = valueSize ; i < holeSize ; ++i)
					o << ' ';
				o << rhs.grid[y][x] << ' ';
			}
			o << std::endl;
		}
	}
	return (o);
}
