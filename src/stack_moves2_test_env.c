/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_moves2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:23:27 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/24 23:20:35 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	psw_move_to(t_ps *ps, t_stk *s, int value)
{
	int	dist;
	int	is_b;

	if (!ps || !s)
		return ;
	is_b = (s == ps->B);
	dist = distance_from_head(s, value);
	if (dist > 0)
		while (dist--)
			psw_move(ps, M_RA + is_b);
	else if (dist < 0)
		while (dist++)
			psw_move(ps, M_RRA + is_b);
}

void	psw_move_to_vptr(t_ps *ps, t_stk *s, int *vptr)
{
	int	dist;
	int	is_b;

	if (!ps || !s || !vptr)
		return ;
	is_b = (s == ps->B);
	dist = distance_from_head_to_vptr(s, vptr);
	if (dist > 0)
		while (dist--)
			psw_move(ps, M_RA + is_b);
	else if (dist < 0)
		while (dist++)
			psw_move(ps, M_RRA + is_b);
}
