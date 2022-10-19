/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:34:35 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/18 23:53:37 by iamongeo         ###   ########.fr       */
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

t_varr	*recursive_pathfinder(t_te *te, t_stk *sub, int ori_len, int depth)//, char *side)
{
	t_te	te1;
	t_te	te2;
	int		delta1;
	int		delta2;
	t_te	*winner;

	if (!te || !sub || !sub->len || !te->ts->len)
		return (NULL);
//	ft_printf("\n\n\n\n\n----------------REC : RECURSIVE PATHFINDING (depth %d, side %s) --------------\n\n", depth, side);
	ft_memclear(&te1, sizeof(te1));
	ft_memclear(&te2, sizeof(te2));
	winner = NULL;
	te_move_delta_and_push_all_members(te, sub, 0);
	while (te->members->len < sub->len)
	{
		te_find_deltas_to_addj_clusters(te->ts, sub, &delta1, &delta2);
		if ((te->members->len < (sub->len - 1)) && delta1 && delta2)
		{
			if (!te_copy(&te1, te) || te_clear(te) || !te_copy(&te2, &te1))
				return (te_clear_all(te, &te1, &te2));
			te_move_delta_and_push_all_members(&te1, sub, delta1);
			if (te1.members->len == sub->len)
			{
				winner = &te1;
				break ;
			}
			te_move_delta_and_push_all_members(&te2, sub, delta2);
			if (!recursive_pathfinder(&te1, sub, ori_len, depth + 1)
				|| !recursive_pathfinder(&te2, sub, ori_len, depth + 1))
				return (te_clear_all(te, &te1, &te2));
			winner = &te1 + (&te2 - &te1) * (te2.nb_moves < te1.nb_moves);
			break ;
		}
		else
			te_move_delta_and_push_all_members(te, sub, delta1 + delta2 * !(delta1 && delta2));
	}

	if (!winner)
		return (te->moves);
	if (!varr_copy(winner->moves, &te->moves) || !varr_copy(winner->members, &te->members))
		return (te_clear_all(te, &te1, &te2));
	te->nb_moves = winner->nb_moves;
	te_clear_all(NULL, &te1, &te2);
	return (te->moves);
}

t_varr	*recursive_pathfinder_chks(t_tec *tec, int depth)//, char *side)
{
	t_tec	tec1;
	t_tec	tec2;
	int		delta1;
	int		delta2;
	t_tec	*winner;

	if(!tec || !tec->ch)
		return (NULL);
//	ft_printf("\n\n\n\n\n----------------RECC : RECURSIVE PATHFINDER CHKS (depth %d, side %s) --------------\n\n", depth, side);
	ft_memclear(&tec1, sizeof(tec1));
	ft_memclear(&tec2, sizeof(tec2));
	winner = NULL;
	tec_move_delta_and_push_all_members(tec, tec->ch, 0);
	while (tec->ts->len > 5)
	{
		tec_find_deltas_to_addj_clusters(tec->ts, tec->ch, &delta1, &delta2);
		if (tec->ts->len > 6 && delta1 && delta2)
		{
			if (!tec_copy(&tec1, tec) || tec_clear(tec) || !tec_copy(&tec2, &tec1))
				return (tec_clear_all(tec, &tec1, &tec2));
			tec_move_delta_and_push_all_members(&tec1, tec1.ch, delta1);
			if (tec1.ts->len <= 5)
			{
				winner = &tec1;
				break ;
			}
			tec_move_delta_and_push_all_members(&tec2, tec2.ch, delta2);
			if (!recursive_pathfinder_chks(&tec1, depth + 1)
				|| !recursive_pathfinder_chks(&tec2, depth + 1))
				return (tec_clear_all(tec, &tec1, &tec2));
			winner = &tec1 + (&tec2 - &tec1) * (tec2.nb_moves < tec1.nb_moves);
			break ;
		}
		else
			tec_move_delta_and_push_all_members(tec, tec->ch, delta1 + delta2 * !(delta1 && delta2));
	}
	if (!winner)
		return (tec->moves);
	if (!varr_copy(winner->moves, &tec->moves))
		return (tec_clear_all(tec, &tec1, &tec2));
	tec->nb_moves = winner->nb_moves;
	tec_clear_all(NULL, &tec1, &tec2);
	return (tec->moves);
}

t_varr	*optimal_push_a_to_b(t_ps *ps)
{
	t_tec	tec;

	if (!ps || ps->stack_max <= 5 || !tec_init(ps, &tec, ps->A))
		return (NULL);
///	ft_printf("\n\noptimal push a to b : Entered\n");
	varr_clear(&ps->shortest_mvs);
	varr_clear(&ps->shortest_mbrs);
	if (!recursive_pathfinder_chks(&tec, 0))//, "root"))
		return (tec_clear(&tec));
	ps->shortest_mvs = tec.moves;
	chks_clear(&tec.ch);
	stk_clear(&tec.ts);
	ft_memclear(&tec, sizeof(tec));
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
	if (!recursive_pathfinder(&te, ext, s->len, 0))//, "root"))
		return (te_clear(&te));
	ps->shortest_mvs = te.moves;
	ps->shortest_mbrs = te.members;
	stk_clear(&te.ts);
	ft_memclear(&te, sizeof(te));
	return (ps->shortest_mvs);
}
