/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 10:21:40 by lguiller          #+#    #+#             */
/*   Updated: 2020/01/28 15:17:24 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "npuzzle.h"

static std::string	ft_generateKey(State actual)
{
	std::string key;

	for (int y(0) ; y < actual.size ; ++y)
		for (int x(0) ; x < actual.size ; ++x)
			key += std::to_string(actual.grid[y][x]) + ',';
	return (key);
}

static bool			ft_alreadyExplored(std::unordered_map<std::string, State> &close, State actual)
{
	std::unordered_map<std::string, State>::iterator state(close.find(ft_generateKey(actual)));

	if (state != close.end())
	{
		if (state->second.mixValue <= actual.mixValue)
			return (true);
		else
			close.erase(state);
	}
	return (false);
}

static void			ft_insertElem(std::list<State> &open, State state)
{
	std::list<State>::iterator i(open.begin());

	for ( ; i != open.end() ; ++i)
		if ((*i).mixValue > state.mixValue)
			break ;
	open.insert(i, state);
}

static void			ft_expand(std::unordered_map<std::string, State> &close, std::list<State> &open, State current, State tmp)
{
	if (current.hole.y > 0)
	{
		tmp = current.swap('N');
		if (!ft_alreadyExplored(close, tmp))
			ft_insertElem(open, tmp);
	}
	if (current.hole.y < current.size - 1)
	{
		tmp = current.swap('S');
		if (!ft_alreadyExplored(close, tmp))
			ft_insertElem(open, tmp);
	}
	if (current.hole.x < current.size - 1)
	{
		tmp = current.swap('E');
		if (!ft_alreadyExplored(close, tmp))
			ft_insertElem(open, tmp);
	}
	if (current.hole.x > 0)
	{
		tmp = current.swap('W');
		if (!ft_alreadyExplored(close, tmp))
			ft_insertElem(open, tmp);
	}
}

static void			ft_resolve(State firstState)
{
	std::list<State>						open(1, firstState);
	std::unordered_map<std::string, State>	close;
	std::list<State>::iterator				current;
	State									tmp(firstState);

	while (open.front().heuristic > 0)
	{
		current = open.begin();
		close.insert(std::pair<std::string, State>(ft_generateKey(*current), *current));
		ft_expand(close, open, *current, tmp);
		open.erase(current);
	}
	std::cout << std::endl << open.front();
	std::cout << open.front().shortestPath << std::endl;
	std::cout << open.front().shortestPath.size() << " moves" << std::endl;
	open.clear();
	close.clear();
}

static bool			ft_isItDoable(State firstState)
{
	int n;
	int j;
	int size = pow(firstState.size, 2);
	int np;
	int copie[size];

	for (int i(0) ; i < size ; ++i)
		if ((copie[i] = firstState.grid[i / firstState.size][i % firstState.size]) == 0) j = i;

	n = firstState.getFinalCoord(0);
	np = abs(n % firstState.size - j % firstState.size) + abs(n / firstState.size - j / firstState.size);
	for (int n(size - 1) ; n > 0 ; --n)
	{
		int test(firstState.getFinalCoord(copie[j]));
		if (test != j)
		{
			int tmp(copie[j]);

			copie[j] = copie[firstState.getFinalCoord(tmp)];
			copie[firstState.getFinalCoord(tmp)] = tmp;
			++np;
		}
		for (j = 0 ; copie[j] != n ; ++j);
	}
	return (1 & np);
}

void				ft_createFirstState(State &firstState, std::ifstream &file)
{
	std::string		line;
	int				**grid;
	int				size;
	int				begin;
	int				end;

	std::getline(file, line);
	while (line[0] == '#')
		std::getline(file, line);
	size = std::stoi(line);
	grid = new int*[size];
	for (int i(0) ; i < size ; ++i)
		grid[i] = new int[size];

	for (int y(0) ; y < size ; ++y)
	{
		std::getline(file, line);
		for (begin = 0 ; line[begin] == ' ' ; ++begin);
		for (int x(0) ; x < size ; ++x)
		{
			for (end = begin ; line[end] != ' ' ; ++ end);
			grid[y][x] = std::stoi(line.substr(begin, end));
			for (begin = end ; line[begin] == ' ' ; ++begin);
		}
	}
	firstState.init(size, grid);
}

int					main(int ac, char **av)
{
	State			firstState;
	std::ifstream	file;

	if (ac != 2)
		std::cout << "usage: ./npuzzle file" << std::endl;
	else
	{
		file.open(av[1]);
		ft_createFirstState(firstState, file);
		file.close();
		std::cout << "Begin State:" << std::endl;
		std::cout << firstState;
		if (!ft_isItDoable(firstState))
			ft_resolve(firstState);
		else
			std::cout << "Not Solvable" << std::endl;
	}
	return (0);
}
