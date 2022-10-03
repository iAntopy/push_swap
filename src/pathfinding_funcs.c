/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:34:35 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/02 23:59:53 by iamongeo         ###   ########.fr       */
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
//	printf("te init : te->nb_moves 1 : %d, sizeof(t_te) : %zu\n", te->nb_moves, sizeof(t_te));
	ft_printf("te_init : sizeof(t_te) : %d, sizeof(te) : %d, sizeof(*te) : %d\n", sizeof(t_te), sizeof(te), sizeof(*te));
	ft_printf("te init : sizeof(t_te) : %d, te ptr : %p, te->near_c ptr : %p, near_c offset : %d\n", sizeof(t_te), te, te->near_c, (size_t)((void *)&te->near_c - (void *)te));
	ft_printf("te init : te->nb_moves 1 : %d, te->stk_te->arr ptr : %p, te->near_c : %p, te->near_cc : %p\n", te->nb_moves, te->stk_ts.arr, te->near_c, te->near_cc);
	ft_memclear(te, sizeof(te));
	ft_printf("te init : te->nb_moves 2 : %d, te->stk_te->arr ptr : %p, te->near_c : %p, te->near_cc : %p\n", te->nb_moves, te->stk_ts.arr, te->near_c, te->near_cc);
	if (!stk_copy(te->ts, s))
		return (te_clear(te, 1));
	ft_printf("te init : te->nb_moves 3 : %d, te->stk_te->arr ptr : %p, te->near_c : %p, te->near_cc : %p\n", te->nb_moves, te->stk_ts.arr, te->near_c, te->near_cc);
//	ft_printf("te init : te->nb_moves 3 : %d\n", te->nb_moves);
	if (moves)
		te->moves = moves;
	else
		te->moves = varr_create(1);
	if (!te->moves)
		return (te_clear(te, 1));
	return (te);
}

t_te	*te_copy(t_te *dst, t_te *src)
{
	if (!dst || !src)
		return (NULL);
	ft_printf("te_copy : src->ts->len : %d, src->nb_moves : %d\n", src->ts->len, src->nb_moves);
	ft_memcpy(dst, src, sizeof(t_te));
	if (!stk_copy(dst->ts, src->ts))
		return (NULL);
	dst->moves = varr_copy(src->moves);
	if (!dst->moves)
		return (stk_clear(dst->ts));
	return (dst);
}

t_varr	*recursive_pathfinder(t_te *te, t_stk *lowest, int ori_len)
{
	t_te	te1;
	t_te	te2;
	int		delta1;
	int		delta2;

	if(!te || !lowest)
		return (NULL);
	ft_printf("REC : te->nb_moves : %d\n", te->nb_moves);
	while (te->ts->len > (ori_len - lowest->len))
	{
		ft_printf("REC : test stack :\n");
		print_single_stack(te->ts);
		te->near_c = find_fst_chk_member_in_stk_clockwise(te->ts, lowest);
		te->near_cc = find_fst_chk_member_in_stk_counter_clockwise(te->ts, lowest);
		ft_printf("REC : arr, near_c, near_cc : %p, %p, %p\n", te->ts->arr, te->near_c, te->near_cc);
		ft_printf("REC : *near_c, *near_cc : %d, %d\n", *te->near_c, *te->near_cc);
		if (!te->near_c)
			break ;
		delta1 = te->near_c - te->ts->arr;
		delta2 = te->ts->len - (te->near_cc - te->ts->arr);
		ft_printf("REC : delta1, delta2 : %d, %d\n", delta1, delta2);
		if ((ft_abs(delta2 - delta1)) <= (int)(ori_len * (2 / 100)))//-delta1 == delta2)
		{
			ft_printf("\nREC : Split\n");
//			te1.moves = varr_copy(te->moves);
//			te2.moves = varr_copy(te->moves);
//			varr_clear(&te->moves);
//			ft_printf("REC : old te moves cleared\n");
//			if (!te_init_test_stack_env(&te1, te->ts, te1.moves)
//				|| !te_init_test_stack_env(&te2, te->ts, te2.moves))
			if (!te_copy(&te1, te) || !te_copy(&te2, te))
				return (te_clear(&te1, 1));
			te_clear(te, 1);
			ft_printf("REC : new test stack copies initialized\n");
			ft_printf("\nREC : Moving te1 head to value %d by %d moves clockwise,\n", *te1.near_c, delta1);
			te_move_to_vptr(&te1, te->near_c);
			ft_printf("\nREC : Moving te2 head to value %d by %d moves clockwise,\n", *te2.near_c, delta2);
			te_move_to_vptr(&te2, te->near_cc);
			ft_printf("REC : test stacks moved to respective closest chunk member\n");
			ft_printf("REC : New test stacks sent back to recursive func\n");
			if (!recursive_pathfinder(&te1, lowest, ori_len) || !recursive_pathfinder(&te2, lowest, ori_len))
				return ((t_varr *)((size_t)te_clear(&te1, 1) & (size_t)te_clear(&te2, 1)));
			ft_printf("REC : Return from recursive func\n");
			ft_printf("REC : te1.moves : %p, len : %d, te2.moves : %p, len : %d\n", te1.moves, te1.nb_moves, te2.moves, te2.nb_moves);
			te->moves = te1.moves + (te2.moves - te1.moves) * (te2.nb_moves < te1.nb_moves);
			ft_printf("REC : new shortest node : %p\n", te->moves);
			break ;
		}
		else
		{
			ft_printf("\nREC : No Split\n");
			ft_printf("REC : near_c : %p, near_cc : %p\n", te->near_c, te->near_cc);
			ft_printf("REC : stack before move.\n");
			print_single_stack(te->ts);
			te_move_to_vptr(te, te->near_c + (te->near_cc - te->near_c) * (delta1 > delta2));
			ft_printf("REC : stack after move.\n");
			print_single_stack(te->ts);
			while (find_value_in_stack(lowest, te->ts->arr[0]))
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

	ft_printf("push n lowest : entered\n");
	if (!ps || !s || n < 1)
		return (NULL);
	ft_printf("push n lowest : passed checks\n");
	lowest = get_n_lowest_members(ps, s, n);
	ft_printf("push n lowest : lowest ptr : %p\n", lowest);
	if (!lowest || !te_init_test_stack_env(&te, s, NULL))
		return (NULL);
	ft_printf("push n lowest : push from stack :\n");
	print_single_stack(s);
	ft_printf("push n lowest : members of chunk :\n");
	print_single_stack(lowest);
	ft_printf("push n lowest : test env stack initialized. Entering recursive func.\n");
	shortest_path = recursive_pathfinder(&te, lowest, s->len);
	ft_printf("push n lowest : returned from recursive pathfinder\n");
	if (!shortest_path)
		return (te_clear(&te, 1));
	ft_printf("push n lowest : smallest path not null\n");
	varr_print(shortest_path);
	te_clear(&te, 0);
	return (te.moves);
}
