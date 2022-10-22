/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:34:35 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/21 21:56:56 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

/*
void	te_find_deltas_to_surrounding_clusters(t_stk *s, t_stk *sub, int *delta1, int *delta2)
{
	int	*clst[4];
	int	dt[4];
	int	does_overlap;

//	ft_printf("find clusters deltas : Entered\n");
	clst[0] = find_fst_chk_member_in_stk_clockwise(s, sub);
	clst[2] = find_fst_chk_member_in_stk_counter_clockwise(s, sub);
	clst[1] = clst[0];
	clst[3] = clst[2];
	while (clst[1] && ((size_t)(clst[1] + 1 - s->arr) < s->len)
		&& find_value_in_stack(sub, *(clst[1] + 1)))
		clst[1]++;
	while (clst[3] && ((clst[3] - 1 - s->arr) > 0)
		&& find_value_in_stack(sub, *(clst[3] - 1)) && (*(clst[3] - 1) > *clst[3]))
		clst[3]--;
	dt[0] = clst[0] - s->arr;
	dt[1] = clst[1] - s->arr;
	dt[2] = s->len - (clst[2] - s->arr);
	dt[3] = s->len - (clst[3] - s->arr);
	does_overlap = (dt[0] <= dt[2] && dt[2] <= dt[1])
		|| (dt[2] <= dt[0] && dt[0] <= dt[3])
		|| (ft_abs(dt[0] - dt[2]) <= (s->len * PATH_THREASHOLD));
	*delta1 = dt[0] * (does_overlap || (dt[0] < dt[2]));
	*delta2 = -dt[3] * (does_overlap || (dt[2] < dt[0]));
}

void	tec_find_deltas_to_surrounding_clusters(t_stk *s, t_chks *ch, int *delta1, int *delta2)
{
	int	*clst[4];
	int	dt[4];
	int	does_overlap;

//	ft_printf("find clusters deltas : Entered\n");
	clst[0] = find_fst_chks_member_in_stk_clockwise(s, ch);
	clst[2] = find_fst_chks_member_in_stk_counter_clockwise(s, ch);
	clst[1] = clst[0];
	clst[3] = clst[2];
	while (clst[1] && ((size_t)(clst[1] + 1 - s->arr) < s->len)
		&& chks_is_in_cur_chks(ch, *(clst[1] + 1), NULL))
		clst[1]++;
	while (clst[3] && ((clst[3] - 1 - s->arr) > 0)
		&& chks_is_in_cur_chks(ch, *(clst[3] - 1), NULL) && (*(clst[3] - 1) > *clst[3]))
		clst[3]--;
	dt[0] = clst[0] - s->arr;
	dt[1] = clst[1] - s->arr;
	dt[2] = s->len - (clst[2] - s->arr);
	dt[3] = s->len - (clst[3] - s->arr);
	does_overlap = (dt[0] <= dt[2] && dt[2] <= dt[1])
		|| (dt[2] <= dt[0] && dt[0] <= dt[3])
		|| (ft_abs(dt[0] - dt[2]) <= (s->len * PATH_THREASHOLD));
	*delta1 = dt[0] * (does_overlap || (dt[0] < dt[2]));
	*delta2 = -dt[3] * (does_overlap || (dt[2] < dt[0]));
}
*/

t_te	*te_seek_nearest_neighbors(t_te *te, t_te tes[2], t_stk *sub, int ori_len, int depth)
{
	int	delta1;
	int	delta2;
	
	while (te->members->len < sub->len)
	{
		te_find_deltas_to_addj_clusters(te->ts, sub, &delta1, &delta2);
		if ((te->members->len < (sub->len - 1)) && delta1 && delta2)
		{
			ft_printf("REC : SPLIT !\n");
			if (!te_copy(tes, te) || te_clear(te) || !te_copy(tes + 1, tes))
				return (te_clear_all(te, tes, tes + 1));
			te_move_delta_and_push_all_members(tes, sub, delta1);
			if (tes->members->len == sub->len)
				return (tes);
			te_move_delta_and_push_all_members(tes + 1, sub, delta2);
			if (!te_recursive_pathfinder(tes, sub, ori_len, depth + 1)
				|| !te_recursive_pathfinder(tes + 1, sub, ori_len, depth + 1))
				return (te_clear_all(te, tes, tes + 1));
			return (tes + ((tes + 1)->nb_moves < tes->nb_moves));
		}
		else
			te_move_delta_and_push_all_members(te, sub, delta1 + delta2 * !(delta1 && delta2));
	}
	return (te);
}

t_te	*te_recursive_pathfinder(t_te *te, t_stk *sub, int ori_len, int depth)
{
	t_te	tes[2];
	t_te	*winner;

	if (!te || !sub || !sub->len || !te->ts->len)
		return (NULL);
//	ft_printf("\n\n\n\n\n----------------REC : RECURSIVE PATHFINDING (depth %d) --------------\n\n", depth);
	ft_memclear(tes, sizeof(tes));
	winner = NULL;
	te_move_delta_and_push_all_members(te, sub, 0);
	winner = te_seek_nearest_neighbors(te, tes, sub, ori_len, depth);
	if (!winner)
		return (NULL);
	if ((winner != te) && (!varr_copy(winner->moves, &te->moves)
				|| !varr_copy(winner->members, &te->members)))
		return (te_clear_all(te, tes, tes + 1));
	te->nb_moves = winner->nb_moves;
	te_clear_all(NULL, tes, tes + 1);
	return (te);
}

t_tec	*tec_seek_nearest_neighbors(t_tec *tec, t_tec tecs[2], int depth)
{
	int	delta1;
	int	delta2;

	while (tec->ts->len > 5)
	{
		tec_find_deltas_to_addj_clusters(tec->ts, tec->ch, &delta1, &delta2);
		if (tec->ts->len > 6 && delta1 && delta2)
		{
			ft_printf("RECC : SPLIT !\n");
			if (!tec_copy(tecs, tec) || tec_clear(tec) || !tec_copy(tecs + 1, tecs))
			{
				ft_printf("RECC : icopy failed !\n");
				return (tec_clear_all(tec, tecs, tecs + 1));
			}
			ft_printf("RECC : moving all members at delta : %d\n", delta1);
			ft_printf("RECC : tec->ch : %p\n", tecs->ch);
			tec_move_delta_and_push_all_members(tecs, tecs->ch, delta1);
			if (tecs->ts->len <= 5)
				return (tecs);
			tec_move_delta_and_push_all_members(tecs + 1, (tecs + 1)->ch, delta2);
//			ft_printf("RECC : going recursive with te1, te2 : \n");
//			tec_print(tecs);
//			tec_print(tecs + 1);
			if (!tec_recursive_pathfinder(tecs, depth + 1)
				|| !tec_recursive_pathfinder(tecs + 1, depth + 1))
				return (tec_clear_all(tec, tecs, tecs + 1));
			return (tecs + ((tecs + 1)->nb_moves < tecs->nb_moves));
		}
		else
			tec_move_delta_and_push_all_members(tec, tec->ch, delta1 + delta2 * !(delta1 && delta2));
	}
	return (tec);
}

t_tec	*tec_recursive_pathfinder(t_tec *tec, int depth)
{
	t_tec	tecs[2];
	t_tec	*winner;

	if(!tec || !tec->ch)
		return (NULL);
//	ft_printf("\n\n\n\n\n----------------RECC : RECURSIVE PATHFINDER CHKS (depth %d) --------------\n\n", depth);
	ft_memclear(tecs, sizeof(tecs));
	winner = NULL;
	tec_move_delta_and_push_all_members(tec, tec->ch, 0);
	winner = tec_seek_nearest_neighbors(tec, tecs, depth);
	if (!winner)
		return (NULL);
	if (!(winner != tec) && (varr_copy(winner->moves, &tec->moves)))
		return (tec_clear_all(tec, tecs, tecs + 1));
	tec->nb_moves = winner->nb_moves;
	tec_clear_all(NULL, tecs, tecs + 1);
	return (tec);
}

t_varr	*optimal_push_a_to_b(t_ps *ps)
{
	t_tec	tec;

	if (!ps || ps->stack_max <= 5 || !tec_init(ps, &tec, ps->A))
		return (NULL);
///	ft_printf("\n\noptimal push a to b : Entered\n");
	varr_clear(&ps->shortest_mvs);
	varr_clear(&ps->shortest_mbrs);
	if (!tec_recursive_pathfinder(&tec, 0))//, "root"))
		return (tec_clear(&tec));
	ps->shortest_mvs = tec.moves;
	chks_clear(&tec.ch);
	stk_clear(&tec.ts);
//	ft_memclear(&tec, sizeof(tec));
	return (ps->shortest_mvs);
}

t_varr	*path_to_n_extreme(t_ps *ps, t_stk *s, size_t n, int find_lowest)
{
	t_stk	*ext;
	t_te	te;

//	ft_printf("path to n highest : Entered\n");
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
	if (!te_recursive_pathfinder(&te, ext, s->len, 0))//, "root"))
		return (te_clear(&te));
	ps->shortest_mvs = te.moves;
	ps->shortest_mbrs = te.members;
	stk_clear(&te.ts);
//	ft_memclear(&te, sizeof(te));
	return (ps->shortest_mvs);
}
