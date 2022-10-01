/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:34:35 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/30 23:52:10 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	*te_clear(t_te *te, char clear_moves)
{
	stk_clear(te->ts);
	if (clear_moves)
		varr_clear(&te->moves);
	return (NULL);
}

// Creates copy of some reference stack to test hypothetical moves and
// find optimal paths.
t_te	*te_init_test_stack_env(t_te *te, t_stk *s, t_varr *moves)
{
	if (!te || !s)
		return (NULL);
	te->ts = &te->stk_ts;
	ft_memclear(te, sizeof(te));
	if (!stk_copy(te->ts, s))
		return (te_clear(te, 1));
	if (moves)
		te->moves = moves;
	else
		te->moves = varr_create(1);
	if (!te->moves)
		return (te_clear(te, 1));
	return (te);
}
/*
t_te	*te_copy(t_te *dst, t_te *src, char cpy_va);
{
	t_varr	*moves_cpy;
	
	ft_memclear(dst, sizeof(t_te));
	if (!moves_cpy)
		return (NULL);
	if (!te_init_test_stack_env(dst, src->ts, moves_cpy))
		return (NULL);
	return (dst);
}
*/

t_varr	*recursive_pathfinder(t_te *te, t_stk *lowest, int ori_len)
{
	t_te	te1;
	t_te	te2;
	int		delta1;
	int		delta2;

	if(!te || !lowest)
		return (NULL);
	while (te->ts->len > (ori_len - lowest->len))
	{
		te->near_c = find_fst_chk_member_in_stk_clockwise(te->ts, lowest);
		te->near_cc = find_fst_chk_member_in_stk_counter_clockwise(te->ts, lowest);
		if (!te->near_c)
			break ;
		delta1 = te->near_c - te->ts->arr;
		delta2 = te->ts->len - (te->near_cc - te->ts->arr);
		if (-delta1 == delta2)
		{
			te1.moves = varr_copy(te->moves);
			te2.moves = varr_copy(te->moves);
			varr_clear(&te->moves);
			if (!te1.moves || !te2.moves)
				return ((t_varr *)((size_t)varr_clear(&te1.moves) & (size_t)varr_clear(&te2.moves)));
			if (!te_init_test_stack_env(&te1, te->ts, te1.moves)
				|| !te_init_test_stack_env(&te2, te->ts, te2.moves))
				return ((t_varr *)((size_t)te_clear(&te1, 1) & (size_t)te_clear(&te2, 1)));
			te_move_to_vptr(&te1, te->near_c);
			te_move_to_vptr(&te2, te->near_cc);
			if (!recursive_pathfinder(&te1, lowest, ori_len) || !recursive_pathfinder(&te2, lowest, ori_len))
				return ((t_varr *)((size_t)te_clear(te, 1) & (size_t)te_clear(&te1, 1) & (size_t)te_clear(&te2, 1)));
			te->moves = te1.moves + (te2.moves - te1.moves) * (te2.moves->len < te1.moves->len);
			break ;
		}
		else
		{
			te_move_to_vptr(te, te->near_c + (te->near_cc - te->near_c) * (delta1 > delta2));
			te_push(te);
		}
	}
	te_clear(&te1, te1.moves != te->moves);
	te_clear(&te2, te2.moves != te->moves);
	return (te->moves);
}

t_varr	*push_n_lowest(t_ps *ps, t_stk *s, int n)
{
	t_stk	*lowest;
	t_te	te;
	t_varr	*shortest_path;

	if (!ps || !s || n < 1)
		return (NULL);
	lowest = get_n_lowest_members(ps, s, n);
	if (!lowest || !te_init_test_stack_env(&te, s, NULL))
		return (NULL);
	shortest_path = recursive_pathfinder(&te, lowest, s->len);
	if (!shortest_path)
		return 
	te_clear(&te, 0);
	return (te.moves);
}
