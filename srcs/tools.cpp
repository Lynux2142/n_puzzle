/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:56:25 by lguiller          #+#    #+#             */
/*   Updated: 2020/01/27 12:08:27 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "npuzzle.h"

int		**ft_makeFinalGrid(int size)
{
	int			**newGrid;
	int			end(pow(size, 2));
	int			xMinMAx[2] = { 0, size - 1 };
	int			yMinMAx[2] = { 0, size - 1 };

	newGrid = new int*[size];
	for (int y(0) ; y < size ; ++y)
			newGrid[y] = new int[size];
	for (int i(1) ; i <= end ; )
	{
		for (int x = xMinMAx[MIN] ; x <= xMinMAx[MAX] && i <= end ; ++x)
			newGrid[yMinMAx[MIN]][x] = i++;
		++yMinMAx[MIN];
		for (int y = yMinMAx[MIN] ; y <= yMinMAx[MAX] && i <= end ; ++y)
			newGrid[y][xMinMAx[MAX]] = i++;
		--xMinMAx[MAX];
		for (int x = xMinMAx[MAX] ; x >= xMinMAx[MIN] && i <= end ; --x)
			newGrid[yMinMAx[MAX]][x] = i++;
		--yMinMAx[MAX];
		for (int y = yMinMAx[MAX] ; y >= yMinMAx[MIN] && i <= end ; --y)
			newGrid[y][xMinMAx[MIN]] = i++;
		++xMinMAx[MIN];
	}
	return (newGrid);
}
