/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:34:35 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/26 21:55:11 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

/*
t_te	*te_seek_nearest_neighbors(t_te *te, t_te tes[2], t_stk *sub)
{
	int	delta1;
	int	delta2;

	while (te->members->len < sub->len)
	{
		te_find_deltas_to_addj_clusters(te->ts, sub, &delta1, &delta2);
		if ((te->members->len < (sub->len - 1)) && delta1 && delta2)
		{
			if (!te_copy(tes, te) || te_clear(te) || !te_copy(tes + 1, tes))
				return (te_clear_all(te, tes, tes + 1));
			te_move_delta_and_push_all_members(tes, sub, delta1);
			if (tes->members->len == sub->len)
				return (tes);
			te_move_delta_and_push_all_members(tes + 1, sub, delta2);
			if (!te_recursive_pathfinder(tes, sub)
				|| !te_recursive_pathfinder(tes + 1, sub))
				return (te_clear_all(te, tes, tes + 1));
			return (tes + ((tes + 1)->nb_moves < tes->nb_moves));
		}
		else
			te_move_delta_and_push_all_members(te, sub,
				delta1 + delta2 * !(delta1 && delta2));
	}
	return (te);
}

t_te	*te_recursive_pathfinder(t_te *te, t_stk *sub)
{
	t_te	tes[2];
	t_te	*winner;

	if (!te || !sub || !sub->len || !te->ts->len)
		return (NULL);
	ft_memclear(tes, sizeof(tes));
	winner = NULL;
	te_move_delta_and_push_all_members(te, sub, 0);
	winner = te_seek_nearest_neighbors(te, tes, sub);
	if (!winner)
		return (NULL);
	if ((winner != te) && (!varr_copy(winner->moves, &te->moves)
			|| !varr_copy(winner->members, &te->members)))
		return (te_clear_all(te, tes, tes + 1));
	te->nb_moves = winner->nb_moves;
	te_clear_all(NULL, tes, tes + 1);
	return (te);
}

t_tec	*tec_seek_nearest_neighbors(t_tec *tec, t_tec tecs[2])
{
	int	delta1;
	int	delta2;

	while (tec->ts->len > 5)
	{
		tec_find_deltas_to_addj_clusters(tec->ts, tec->ch, &delta1, &delta2);
		if (tec->ts->len > 6 && delta1 && delta2)
		{
			if (!tec_copy(tecs, tec)
				|| tec_clear(tec) || !tec_copy(tecs + 1, tecs))
				return (tec_clear_all(tec, tecs, tecs + 1));
			tec_move_delta_and_push_all_members(tecs, tecs->ch, delta1);
			if (tecs->ts->len <= 5)
				return (tecs);
			tec_move_delta_and_push_all_members(tecs + 1, tecs[1].ch, delta2);
			if (!tec_recursive_pathfinder(tecs)
				|| !tec_recursive_pathfinder(tecs + 1))
				return (tec_clear_all(tec, tecs, tecs + 1));
			return (tecs + ((tecs + 1)->nb_moves < tecs->nb_moves));
		}
		else
			tec_move_delta_and_push_all_members(tec, tec->ch,
				delta1 + delta2 * !(delta1 && delta2));
	}
	return (tec);
}

t_tec	*tec_recursive_pathfinder(t_tec *tec)
{
	t_tec	tecs[2];
	t_tec	*winner;

	if (!tec || !tec->ch)
		return (NULL);
	ft_memclear(tecs, sizeof(tecs));
	winner = NULL;
	tec_move_delta_and_push_all_members(tec, tec->ch, 0);
	winner = tec_seek_nearest_neighbors(tec, tecs);
	if (!winner)
		return (NULL);
	if ((winner != tec) && !varr_copy(winner->moves, &tec->moves))
		return (tec_clear_all(tec, tecs, tecs + 1));
	tec->nb_moves = winner->nb_moves;
	tec_clear_all(NULL, tecs, tecs + 1);
	return (tec);
}
*/
t_varr	*optimal_push_a_to_b(t_ps *ps)
{
	t_tec	tec;

	if (!ps || ps->stack_max <= 5 || !tec_init(ps, &tec, ps->A))
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
