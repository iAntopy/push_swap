/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_moves2_test_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:39:14 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/04 13:55:32 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	te_move_to(t_te *te, int value)
{
	int	dist;

	if (!te)
		return ;
	dist = distance_from_head(te->ts, value);
	if (dist > 0)
		while (dist--)
			te_move(te, M_RA);
	else if (dist < 0)
		while (dist++)
			te_move(te, M_RRA);
}

void	te_move_to_vptr(t_te *te, int *vptr)
{
	int	dist;

//	ft_printf("te_move_to_vptr : Entered\n");
//	ft_printf("te_move_to_vptr : te recieved\n");
//	te_print(te);
//	ft_printf("te_move_to_vptr : te %p, vptr : %p\n", te, vptr);
//	ft_printf("te_move_to_vptr : te->ts %p, te->near_c %p, te->near_cc %p\n", te->ts, te->near_c, te->near_cc);
	if (!te || !vptr)
		return ;
	dist = distance_from_head_to_vptr(te->ts, vptr);
//	ft_printf("te_move_to_vptr : dist from %p to %p : %d\n", te->ts->arr, vptr, dist);
	if (dist > 0)
		while (dist--)
			te_move(te, M_RA);
	else if (dist < 0)
		while (dist++)
			te_move(te, M_RRA);
}
