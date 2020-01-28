/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Coord.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:39:37 by lguiller          #+#    #+#             */
/*   Updated: 2020/01/23 14:05:29 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COORD_CLASS_HPP
# define COORD_CLASS_HPP

# include <iostream>

class				Coord
{
public:
	Coord(void);
	Coord(int x, int y);
	Coord(const Coord &rhs);
	~Coord(void);

	Coord			&operator=(const Coord &rhs);
	void			set(int x, int y);

	int				x;
	int				y;
};

#endif
