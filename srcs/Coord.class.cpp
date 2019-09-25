/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Coord.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:47:00 by lguiller          #+#    #+#             */
/*   Updated: 2019/09/23 15:52:28 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Coord.class.hpp>

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

Coord			&Coord::operator=(const Coord &rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	return (*this);
}

bool			Coord::operator==(const Coord &rhs) const
{
	return (this->x == rhs.x && this->y == rhs.y);
}

bool			Coord::operator!=(const Coord &rhs) const
{
	return (this->x != rhs.x || this->y != rhs.y);
}

void			Coord::set(int x, int y)
{
	this->x = x;
	this->y = y;
}

std::ostream	&operator<<(std::ostream &o, const Coord &rhs)
{
	o << '[' << rhs.x << ',' << rhs.y << ']' << std::endl;
	return (o);
}
