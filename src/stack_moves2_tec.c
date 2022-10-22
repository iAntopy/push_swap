/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_moves2_tec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:10:23 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/21 17:47:20 by iamongeo         ###   ########.fr       */
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

	if (!tec || !vptr)
		return ;
	dist = distance_from_head_to_vptr(tec->ts, vptr);
	if (dist > 0)
		while (dist--)
			tec_move(tec, M_RA);
	else if (dist < 0)
		while (dist++)
			tec_move(tec, M_RRA);
}

void	tec_find_deltas_to_addj_clusters(t_stk *s, t_chks *ch, int *d1, int *d2)
{
	int	*clst[4];
	int	dt[4];
	int	does_overlap;

	clst[0] = find_fst_chks_member_in_stk_clockwise(s, ch);
	clst[2] = find_fst_chks_member_in_stk_counter_clockwise(s, ch);
	clst[1] = clst[0];
	clst[3] = clst[2];
	while (clst[1] && ((size_t)(clst[1] + 1 - s->arr) < s->len)
		&& chks_is_in_cur_chks(ch, *(clst[1] + 1), NULL))
		clst[1]++;
	while (clst[3] && ((clst[3] - 1 - s->arr) > 0)
		&& chks_is_in_cur_chks(ch, *(clst[3] - 1), NULL)
		&& (*(clst[3] - 1) > *clst[3]))
		clst[3]--;
	dt[0] = clst[0] - s->arr;
	dt[1] = clst[1] - s->arr;
	dt[2] = s->len - (clst[2] - s->arr);
	dt[3] = s->len - (clst[3] - s->arr);
	does_overlap = (dt[0] <= dt[2] && dt[2] <= dt[1]);
	does_overlap |= (dt[2] <= dt[0] && dt[0] <= dt[3]);
	does_overlap |= (ft_abs(dt[2] - dt[0]) <= s->len * PATH_THREASHOLD);
	*d1 = dt[0] * (does_overlap || (dt[0] < dt[2]));
	*d2 = -dt[3] * (does_overlap || (dt[2] < dt[0]));
}
