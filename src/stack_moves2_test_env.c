/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_moves2_test_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:39:14 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/28 21:38:42 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	te_move_to(t_te *te, int value)
{
	int	dist;

	if (!ps || !s)
		return ;
	dist = distance_from_head(te->ts, value);
	if (dist > 0)
		while (dist--)
			te_move(te, M_RA);
	else if (dist < 0)
		while (dist++)
			te_move(te, M_RRA);
}

void	te_move_to_vptr(t_te *te, t_stk *s, int *vptr)
{
	int	dist;

	if (!ps || !s || !vptr)
		return ;
	dist = distance_from_head_to_vptr(s, vptr);
	if (dist > 0)
		while (dist--)
			te_move(ps, M_RA);
	else if (dist < 0)
		while (dist++)
			te_move(ps, M_RRA);
}
