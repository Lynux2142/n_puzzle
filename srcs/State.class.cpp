/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:55:42 by lguiller          #+#    #+#             */
/*   Updated: 2019/09/25 16:30:54 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "State.class.hpp"

State::State(void) : grid(NULL)
{
	return ;
}

State::State(int size) : width(size), height(size), size(size * size), grid(NULL)
{
	this->grid = new int*[this->height];
	for (int y = 0 ; y < size ; ++y)
	{
		this->grid[y] = new int[this->width];
		for (int x = 0 ; x < size ; ++x)
			this->grid[y][x] = 0;
	}
}

State::State(const State &rhs)
{
	this->width = rhs.width;
	this->height = rhs.height;
	this->size = rhs.size;
	this->hole = rhs.hole;
	this->grid = new int*[this->height];
	for (int y = 0 ; y < this->height ; ++y)
	{
		this->grid[y] = new int[this->width];
		for (int x = 0 ; x < this->width ; ++x)
			this->grid[y][x] = rhs.grid[y][x];
	}
	this->heuristic = rhs.heuristic;
	this->mixValue = rhs.mixValue;
	this->shortestPath = rhs.shortestPath;
}

State::~State(void)
{
	if (this->grid)
	{
		for (int y = 0 ; y < this->height ; ++y)
			delete[] this->grid[y];
		delete[] this->grid;
	}
}

State			&State::operator=(State const &rhs)
{
	this->width = rhs.width;
	this->height = rhs.height;
	this->size = rhs.size;
	this->hole = rhs.hole;
	for (int y = 0 ; y < this->height ; ++y)
		for (int x = 0 ; x < this->width ; ++x)
			this->grid[y][x] = rhs.grid[y][x];
	this->heuristic = rhs.heuristic;
	this->mixValue = rhs.mixValue;
	this->shortestPath = rhs.shortestPath;
	return (*this);
}

bool			State::operator==(const State &rhs) const
{
	for (int y = 0 ; y < this->height ; ++y)
		for (int x = 0 ; x < this-> width ; ++x)
			if (this->grid[y][x] != rhs.grid[y][x])
				return (false);
	return (true);
}

int				State::coord2Dto1D(int x, int y) const
{
	return (y * this->width + x);
}

Coord			State::findFinalCoord(int value) const
{
	return (Coord((value - 1) % this->width, (value - 1) / this->height));
}

void			State::setMixValue(void)
{
	unsigned int value(0);

	for (Coord a(0, 0) ; a.y < this->height ; ++a.y)
		for (a.x = 0 ; a.x < this->width ; ++a.x)
			if (this->grid[a.y][a.x] != this->coord2Dto1D(a.x, a.y) + 1)
			{
				++value;
				Coord b(this->findFinalCoord(this->grid[a.y][a.x]));
				value += (std::abs(a.x - b.x) + std::abs(a.y - b.y));
			}
	this->heuristic = value;
	this->mixValue = this->heuristic + this->shortestPath.size();
}

void			State::printState(void) const
{
	std::ostream &o(std::cout);

	o << "Actual State:" << std::endl;
	o << *this;
	o << std::endl << "ShortestPath:" << std::endl;
	o << (this->shortestPath.empty() ? "/" : this->shortestPath) << std::endl;
	o << std::endl << this->shortestPath.size() << " moves" << std::endl;
}

State			State::swap(char action) const
{
	State	newState(*this);
	int		x(0);
	int		y(0);

	if ((action == 'E' && this->hole.x < this->width - 1) || (action == 'W' && this->hole.x > 0))
		x = (action == 'E') ? 1 : -1;
	if ((action == 'S' && this->hole.y < this->height - 1) || (action == 'N' && this->hole.y > 0))
		y = (action == 'S') ? 1 : -1;
	newState.grid[this->hole.y][this->hole.x] = newState.grid[this->hole.y + y][this->hole.x + x];
	newState.grid[this->hole.y + y][this->hole.x + x] = this->size;
	newState.hole.x += x;
	newState.hole.y += y;
	newState.shortestPath += action;
	newState.setMixValue();
	return (newState);
}

std::ostream	&operator<<(std::ostream &o, const State &rhs)
{
	int valueSize(0);
	int holeSize(0);

	if (!rhs.grid)
		o << '/' << std::endl;
	else
	{
		for (int tmp = rhs.size ; tmp >= 10 ; tmp /= 10)
			++holeSize;
		for (int y = 0 ; y < rhs.height ; ++y)
		{
			for (int x = 0 ; x < rhs.width ; ++x)
			{
				valueSize = 0;
				if (rhs.grid[y][x] != rhs.size)
					for (int tmp = rhs.grid[y][x] ; tmp >= 10 ; tmp /= 10)
						++valueSize;
				for (int i = valueSize ; i < holeSize ; ++i)
					o << ' ';
				o << ((rhs.grid[y][x] == rhs.size) ? 0 : rhs.grid[y][x]) << ' ';
			}
			o << std::endl;
		}
	}
	return (o);
}
