/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 10:21:40 by lguiller          #+#    #+#             */
/*   Updated: 2019/10/29 12:22:51 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "npuzzle.h"
#include "State.class.hpp"

static std::string	grid2String(State actual)
{
	std::string key;

	for (int y(0) ; y < actual.height ; ++y)
		for (int x(0) ; x < actual.width ; ++x)
			key += std::to_string(actual.grid[y][x]) + ',';
	return (key);
}

static void		insertElem(std::list<State> &open, State elem)
{
	std::list<State>::iterator i(open.begin());

	for ( ; i != open.end() ; ++i)
		if ((*i).mixValue > elem.mixValue)
		{
			open.insert(i, elem);
			return ;
		}
	open.insert(i, elem);
}

static bool		alreadyExplored(std::unordered_map<std::string, State> &close, State actual)
{
	std::unordered_map<std::string, State>::iterator ret(close.find(grid2String(actual)));

	if (ret != close.end())
	{
		if (ret->second.mixValue <= actual.mixValue)
			return (true);
		else
		{
			close.erase(ret);
			return (false);
		}
	}
	return (false);
}

static void		expand(std::unordered_map<std::string, State> &close, std::list<State> &open, State current, State tmp)
{
	if (current.hole.y > 0)
	{
		tmp = current.swap('N');
		if (!alreadyExplored(close, tmp))
			insertElem(open, tmp);
	}
	if (current.hole.y < current.height - 1)
	{
		tmp = current.swap('S');
		if (!alreadyExplored(close, tmp))
			insertElem(open, tmp);
	}
	if (current.hole.x < current.width - 1)
	{
		tmp = current.swap('E');
		if (!alreadyExplored(close, tmp))
			insertElem(open, tmp);
	}
	if (current.hole.x > 0)
	{
		tmp = current.swap('W');
		if (!alreadyExplored(close, tmp))
			insertElem(open, tmp);
	}
}

static void		printEnd(std::list<State> open, unsigned long maxNumberState)
{
	std::cout << "Final State:" << std::endl;
	std::cout << open.front();
	std::cout << "Complexity in time:" << std::endl;
	std::cout << open.size() << std::endl;
	std::cout << "Complexity in size:" << std::endl;
	std::cout << maxNumberState << std::endl;
	std::cout << "Number of moves:" << std::endl;
	std::cout << open.front().shortestPath.size() << std::endl;
	std::cout << "Path:" << std::endl;
	std::cout << open.front().shortestPath << std::endl;
}

static void		resolve(State firstState)
{
	std::list<State>						open(1, firstState);
	std::unordered_map<std::string, State>	close;
	std::list<State>::iterator				current;
	State									tmp(firstState.width);
	unsigned long							maxNumberState(0);

	while (open.front().heuristic > 0)
	{
		current = open.begin();
		close.insert(std::pair<std::string, State>(grid2String(*current), *current));
		expand(close, open, *current, tmp);
		open.erase(current);
		if (open.size() > maxNumberState)
			maxNumberState = open.size();
	}
	printEnd(open, maxNumberState);
	open.clear();
	close.clear();
	return ;
}

static void		initState(State &actual)
{
//	const char value[] = { 8, 9, 7, 1, 4, 2, 5, 3, 6 };
//	const char value[] = { 10, 9, 6, 7, 15, 1, 11, 2, 4, 12, 16, 3, 14, 5, 8, 13 };
//	const char value[] =  { 16, 11, 13, 14, 8, 1, 15, 2, 4, 6, 7, 3, 9, 12, 5, 10 };
//	const char value[] = { 10, 11, 16, 13, 12, 1, 3, 5, 8, 15, 6, 14, 7, 9, 4, 2 };
	const char value[] = {
		 7,  6, 13,  5,
11, 15, 14,  3,
10, 16,  1, 12,
 8,  9,  4,  2
	};
	for (int y(0) ; y < actual.height ; ++y)
		for (int x(0) ; x < actual.width ; ++x)
		{
			if (value[y * actual.height + x] == actual.size)
				actual.hole.set(x, y);
			actual.grid[y][x] = value[y * actual.height + x];
		}
	actual.setMixValue();
}

int				main(void)
{
	int			size(4);
	State		actual(size);
	int			**final_grid = make_final_grid(size, size);

	initState(actual);
	convert_grid(final_grid, actual);
	std::cout << "Begin state:" << std::endl;
	std::cout << actual << std::endl;
	resolve(actual);
	std::cout << std::endl;
	return (0);
}
