/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_moves2_test_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:39:14 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/19 23:00:18 by iamongeo         ###   ########.fr       */
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

	if (!te || !vptr)
		return ;
	dist = distance_from_head_to_vptr(te->ts, vptr);
	if (dist > 0)
		while (dist--)
			te_move(te, M_RA);
	else if (dist < 0)
		while (dist++)
			te_move(te, M_RRA);
}

void	te_find_deltas_to_addj_clusters(t_stk *s, t_stk *sub, int *d1, int *d2)
{
	int	*clst[4];
	int	dt[4];
	int	does_overlap;

	clst[0] = find_fst_chk_member_in_stk_clockwise(s, sub);
	clst[2] = find_fst_chk_member_in_stk_counter_clockwise(s, sub);
	clst[1] = clst[0];
	clst[3] = clst[2];
	while (clst[1] && ((size_t)(clst[1] + 1 - s->arr) < s->len)
		&& find_value_in_stack(sub, *(clst[1] + 1)))
		clst[1]++;
	while (clst[3] && ((clst[3] - 1 - s->arr) > 0)
		&& find_value_in_stack(sub, *(clst[3] - 1))
		&& (*(clst[3] - 1) > *clst[3]))
		clst[3]--;
	dt[0] = clst[0] - s->arr;
	dt[1] = clst[1] - s->arr;
	dt[2] = s->len - (clst[2] - s->arr);
	dt[3] = s->len - (clst[3] - s->arr);
	does_overlap = (dt[0] <= dt[2] && dt[2] <= dt[1])
		|| (dt[2] <= dt[0] && dt[0] <= dt[3])
		|| (ft_abs(dt[0] - dt[2]) <= (s->len * PATH_THREASHOLD));
	*d1 = dt[0] * (does_overlap || (dt[0] < dt[2]));
	*d2 = -dt[3] * (does_overlap || (dt[2] < dt[0]));
}
