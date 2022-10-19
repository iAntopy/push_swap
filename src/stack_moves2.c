/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_moves2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:23:27 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/17 21:35:08 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	psw_move_delta(t_ps *ps, t_stk *s, int delta)
{
	int	is_b;

	if (!ps || !s || !delta)
		return ;
	is_b = (s == ps->B);
	if (delta > 0)
		while (delta--)
			psw_move(ps, M_RA + is_b);
	else if (delta < 0)
		while (delta++)
			psw_move(ps, M_RRA + is_b);
}

void	psw_move_delta_push(t_ps *ps, t_stk *s, int delta)
{
	int	is_b;

	if (!ps || !s)
		return ;
	is_b = (s == ps->B);
	psw_move_delta(ps, s, delta);
	psw_move(ps, M_PB - is_b);
}

void	psw_move_to(t_ps *ps, t_stk *s, int value)
{
	int	delta;

	if (!ps || !s)
		return ;
	delta = distance_from_head(s, value);
	psw_move_delta(ps, s, delta);
}

void	psw_move_to_vptr(t_ps *ps, t_stk *s, int *vptr)
{
	int	delta;

	if (!ps || !s || !vptr)
		return ;
	delta = distance_from_head_to_vptr(s, vptr);
	psw_move_delta(ps, s, delta);
}
