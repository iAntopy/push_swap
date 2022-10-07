/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_moves2_tec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:10:23 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/06 18:13:21 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	tec_move_to(t_tec *tec, int value)
{
	int	dist;

	if (!tec)
		return ;
	dist = distance_from_head(tec->ts, value);
	if (dist > 0)
		while (dist--)
			tec_move(tec, M_RA);
	else if (dist < 0)
		while (dist++)
			tec_move(tec, M_RRA);
}

void	tec_move_to_vptr(t_tec *tec, int *vptr)
{
	int	dist;

//	ft_printf("tec_move_to_vptr : Entered\n");
//	tec_print(te);
//	ft_printf("tec_move_to_vptr : tec %p, vptr : %p\n", tec, vptr);
//	ft_printf("tec_move_to_vptr : tec->ts %p, tec->near_c %p, tec->near_cc %p\n", tec->ts, tec->near_c, tec->near_cc);
	if (!tec || !vptr)
		return ;
	dist = distance_from_head_to_vptr(tec->ts, vptr);
//	ft_printf("tec_move_to_vptr : dist from %p to %p : %d\n", tec->ts->arr, vptr, dist);
	if (dist > 0)
		while (dist--)
			tec_move(tec, M_RA);
	else if (dist < 0)
		while (dist++)
			tec_move(tec, M_RRA);
}
