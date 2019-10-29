/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npuzzle.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:49:26 by lguiller          #+#    #+#             */
/*   Updated: 2019/10/29 11:12:37 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_H
# define NPUZZLE_H

# include <string>
# include <algorithm>
# include <list>
# include <unordered_map>
# include "Coord.class.hpp"
# include "State.class.hpp"

enum	e_minamx
{
	MIN = 0,
	MAX
};

int		**make_final_grid(int length, int width);
void	convert_grid(int **final_grid, State &actual);

#endif
