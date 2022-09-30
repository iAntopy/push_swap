/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:34:35 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/29 20:23:19 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	*te_clear(t_te *te, char clear_moves)
{
	stk_clear(te->ts);
	if (clear_moves)
		varr_clear(te->moves_list);
	return (NULL);
}

// Creates copy of some reference stack to test hypothetical moves and
// find optimal paths.
t_te	*te_init_test_stack_env(t_te *te, t_stk *s, t_varr *moves_list)
{
	int	*arr;

	if (!te || !s)
		return (NULL);
	te->ts = &te->stk_ts;
	ft_memclear(te, sizeof(te));
	if (!stk_copy(te->ts, s))
		return (te_clear(te, 1));
	if (moves_list)
		te->moves_list = moves_list;
	else
		te->moves_list = varr_create(&te->moves_list);

	if (!te->moves_list)
		return (te_clear(te, 1));
	return (te);
}

t_te	*te_copy(t_te *dst, t_te *src, char cpy_va);
{
	t_varr	*moves_cpy;
	
	ft_memclear(dst, sizeof(t_te));
	moves_cpy = varr_copy(src->moves_list);
	if (!moves_cpy)
		return (NULL);
	te_init_test_stack_env(dst, src->ts, moves_cpy);

}

t_varr	*recursive_pathfinder(t_stk *s, t_stk *chk)
{
	t_te	te;
	int		delta1;
	int		delta2;
	int		nearest_delta;

	if(!te_init_test_stack_env(&te, s))
		return (NULL);
	ft_memclear(te, sizeof(te));
	while (te->ts->len > (s->len - n))
	{
		te->near_c = find_fst_chk_member_in_stk_clockwise(te->ts, lowest);
		te->near_cc = find_fst_chk_member_in_stk_counter_clockwise(te->ts, lowest);
		if (!te->near_c)
			break ;
		delta1 = te->near_c - te->ts->arr;
		delta2 = te->ts->len - (te->near_cc - te->ts->arr);
		if (-delta1 == delta2)
		{
			
		}
		else
		{
			nearest_delta = delta1 + (delta2 - delta1) * (-delta2 < delta1);
			if (nearest_delta == delta1)
				te_move_to_vptr(&te, te->near_c);
			else
				te_move_to_vptr(&te, te->near_cc);
			te_push(te);
		}
	}
	te_clear(&te, 0);
	return (te->moves_list);

}

t_varr	*push_n_lowest(t_ps *ps, t_stk *s, int n)
{
	t_stk	*lowest;

	lowest = get_n_lowest_members(ps, s, n);
	if (!lowest)
		return (NULL);
	return (recursive_pathfinder(s, lowest));
/*
	while (te->ts->len > (s->len - n))
	{
		te->near_c = find_fst_chk_member_in_stk_clockwise(te->ts, lowest);
		te->near_cc = find_fst_chk_member_in_stk_counter_clockwise(te->ts, lowest);
		if (!te->near_c)
			break ;
		delta1 = distance_from_head_vptr(te->ts, te->near_c);
		delta2 = distance_from_head_vptr(te->ts, te->near_cc);
		if (-delta1 == delta2)
			//split();
		else
			varr_append(te->moves_list, delta1 + (delta2 - delta1) * (-delta2 < delta1));
	}
	te_clear(&te, 0);
	return (te->moves_list);
*/
}
