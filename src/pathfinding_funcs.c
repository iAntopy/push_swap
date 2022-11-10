/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:34:35 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/10 17:07:37 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

t_varr	*optimal_push_a_to_b(t_ps *ps)
{
	t_tec	tec;

	if (!ps || ps->stack_max <= 5 || !tec_init(ps, &tec, ps->a))
		return (NULL);
	varr_clear(&ps->shortest_mvs);
	varr_clear(&ps->shortest_mbrs);
	if (!tec_recursive_pathfinder(&tec))
		return (tec_clear(&tec));
	ps->shortest_mvs = tec.moves;
	chks_clear(&tec.ch);
	stk_clear(&tec.ts);
	return (ps->shortest_mvs);
}

t_varr	*path_to_n_extreme(t_ps *ps, t_stk *s, size_t n, int find_lowest)
{
	t_stk	*ext;
	t_te	te;

	if (!ps || !s || n > s->len)
		return (NULL);
	varr_clear(&ps->shortest_mvs);
	varr_clear(&ps->shortest_mbrs);
	n = n + (s->len - n) * (n > s->len);
	if (find_lowest)
		ext = get_n_lowest_members(ps, s, n);
	else
		ext = get_n_highest_members(ps, s, n);
	if (!ext || !te_init(&te, s))
		return (NULL);
	if (!te_recursive_pathfinder(&te, ext))
		return (te_clear(&te));
	ps->shortest_mvs = te.moves;
	ps->shortest_mbrs = te.members;
	stk_clear(&te.ts);
	return (ps->shortest_mvs);
}
