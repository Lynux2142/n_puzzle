/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:58:32 by lguiller          #+#    #+#             */
/*   Updated: 2019/10/29 10:54:39 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_CLASS_HPP
# define TOOLS_CLASS_HPP

# include <iostream>
# include "Coord.class.hpp"

class				State
{
public:
	State(void);
	State(int size);
	State(const State &rhs);
	~State(void);

	State			&operator=(const State &rhs);
	bool			operator==(const State &rhs) const ;

	void			printState(void) const ;
	State			swap(char action) const ;
	void			setMixValue(void);

	int				width;
	int				height;
	int				size;
	Coord			hole;
	int				**grid;
	int				heuristic;
	int				mixValue;
	std::string		shortestPath;
	Coord			findFinalCoord(int value) const ;

private:
	int				coord2Dto1D(int x, int y) const ;
};

std::ostream		&operator<<(std::ostream &o, const State &rhs);

#endif
