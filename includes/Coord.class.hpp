/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Coord.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:47:51 by lguiller          #+#    #+#             */
/*   Updated: 2019/10/29 10:54:06 by lguiller         ###   ########.fr       */
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
	bool			operator==(const Coord &rhs) const ;
	bool			operator!=(const Coord &rhs) const ;

	void			set(int x, int y);

	int				x;
	int				y;
};

std::ostream		&operator<<(std::ostream &o, const Coord &rhs);

#endif
