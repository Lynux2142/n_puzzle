/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Coord.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:45:01 by lguiller          #+#    #+#             */
/*   Updated: 2020/01/23 14:06:23 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Coord.class.hpp"

Coord::Coord(void)
{
	return ;
}

Coord::Coord(int x, int y) : x(x), y(y)
{
	return ;
}

Coord::Coord(const Coord &rhs)
{
	*this = rhs;
}

Coord::~Coord(void)
{
	return ;
}

Coord	&Coord::operator=(const Coord &rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	return (*this);
}

void	Coord::set(int x, int y)
{
	this->x = x;
	this->y = y;
}
