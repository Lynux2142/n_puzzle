/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:51:32 by lguiller          #+#    #+#             */
/*   Updated: 2020/01/28 11:26:20 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_CLASS_HPP
# define STATE_CLASS_HPP

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
	State			swap(char action) const ;
	void			setMixValue();
	int				getFinalCoord(int value);
	void			init(int size, int **values);

	int				size;
	Coord			hole;
	int				**grid;
	int				**finalGrid;
	int				heuristic;
	int				mixValue;
	std::string		shortestPath;
};

std::ostream		&operator<<(std::ostream &o, const State &rhs);

#endif
