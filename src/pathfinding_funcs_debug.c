/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:34:35 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/04 18:43:51 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	te_print(t_te *te)
{
	ft_printf("\no-----------< test stack env >------------o\n");
	ft_printf("o-\tstack arr\t: %p\no-\tstack len\t: %d\no-\tts\t\t: %p\n", te->stk_ts.arr, te->stk_ts.len, te->ts);
	ft_printf("o-\tnear_c\t\t: %p (%d)\no-\tnear_cc\t\t: %p (%d)\n", te->near_c, (te->near_c) ? *te->near_c : -1, te->near_cc, (te->near_cc) ? *te->near_cc : -1);
	ft_printf("o-\tcur run\t\t: %d\no-\tnb moves\t: %d\n", te->cur_run, te->nb_moves);
	ft_printf("o-----------------------------------------o\n\n");
}

void	*te_clear(t_te *te, char clear_moves)
{
	if (!te)
		return (NULL);
	ft_printf("te_clear : entered, attempting to stk_clear. clear_moves : %d\n", clear_moves);
	te_print(te);
	stk_clear(te->ts);
//	ft_printf("te_clear : stk_clear SUCCESS\n");
	if (clear_moves)
	{
//		ft_printf("te_clear : attempting to varr_clear.\n");
		varr_clear(&te->moves);
//		ft_printf("te_clear : varr_clear SUCCESS\n");
	}
//	ft_printf("te_clear : attempting to memclear te\n");
	ft_memclear(te, sizeof(*te));
//	ft_printf("te_clear : memclear SUCCESS\n");
	return (NULL);
}

// Creates copy of some reference stack to test hypothetical moves and
// find optimal paths.
t_te	*te_init_test_stack_env(t_te *te, t_stk *s, t_varr *moves)
{
	if (!te || !s)
		return (NULL);
//	ft_printf("te init : sizeof(t_te) : %d, te ptr : %p, te->near_c ptr : %p, near_c offset : %d\n", sizeof(t_te), te, te->near_c, (size_t)((void *)&te->near_c - (void *)te));
//	ft_printf("te init : te->nb_moves 1 : %d, te->stk_te->arr ptr : %p, te->near_c : %p, te->near_cc : %p\n", te->nb_moves, te->stk_ts.arr, te->near_c, te->near_cc);
	ft_memclear(te, sizeof(*te));
	te->ts = &te->stk_ts;
//	ft_printf("te init : te->nb_moves 2 : %d, te->stk_te->arr ptr : %p, te->near_c : %p, te->near_cc : %p\n", te->nb_moves, te->stk_ts.arr, te->near_c, te->near_cc);
//	ft_printf("te init : stack to copy : arr %p, len : %d\n", s->arr, s->len);
	if (!stk_copy(te->ts, s))
		return (te_clear(te, 1));
//	ft_printf("te init : te->nb_moves 3 : %d, te->stk_te->arr ptr : %p, te->near_c : %p, te->near_cc : %p\n", te->nb_moves, te->stk_ts.arr, te->near_c, te->near_cc);
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
	ft_printf("\n\nte_copy : Entered\n");
	if (!dst || !src)
		return (NULL);
//	ft_printf("te_copy : Pre copy, src->ts->arr : %p\n", src->ts->arr);
//	ft_printf("te_copy : Pre copy, src->ts->len : %d, src->nb_moves : %d\n", src->ts->len, src->nb_moves);
//	ft_printf("te_copy : Pre copy, src->moves : %p\n", src->moves);
//	ft_printf("te_copy : Pre copy, dst->ts : %p, dst->stk_ts->arr : %p\n", dst->ts, dst->stk_ts.arr);
//	ft_printf("te_copy : Pre copy, dst->ts->len : %d, dst->nb_moves : %d\n", dst->stk_ts.len, dst->nb_moves);
//	ft_printf("te_copy : Pre copy, dst->moves : %p\n", dst->moves);
//	ft_memcpy(dst, src, sizeof(*src));
	
	ft_memclear(dst, sizeof(*dst));
	dst->ts = &dst->stk_ts;
	if (!stk_copy(dst->ts, src->ts))
		return (NULL);
	dst->moves = varr_copy(src->moves);
	if (!dst->moves)
		return (stk_clear(dst->ts));
	dst->near_c = src->near_c;
	dst->near_cc = src->near_cc;
	if (dst->near_c)
		dst->near_c = dst->stk_ts.arr + (src->near_c - src->stk_ts.arr);
	if (dst->near_cc)
		dst->near_cc = dst->stk_ts.arr + (src->near_cc - src->stk_ts.arr);
	dst->cur_run = src->cur_run;
	dst->nb_moves = src->nb_moves;
	
//	ft_printf("\nte_copy : Post copy, src->ts->arr : %p\n", src->ts->arr);
//	ft_printf("te_copy : Post copy, src->ts->len : %d, src->nb_moves : %d\n", src->ts->len, src->nb_moves);
//	ft_printf("te_copy : Post copy, src->moves : %p\n", src->moves);
//	ft_printf("te_copy : Post copy, dst->ts : %p, dst->stk_ts->arr : %p\n", dst->ts, dst->stk_ts.arr);
//	ft_printf("te_copy : Post copy, dst->ts->len : %d, dst->nb_moves : %d\n", dst->stk_ts.len, dst->nb_moves);
//	ft_printf("te_copy : Post copy, dst->moves : %p\n\n", dst->moves);
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
	ft_printf("\n\n\n\n\n----------------REC : ENTERING RECURSIVE PATHFINDING--------------\n\n");
	ft_printf("REC : te->nb_moves : %d\n", te->nb_moves);
	ft_memclear(&te1, sizeof(te1));
	ft_memclear(&te2, sizeof(te2));
	while (te->ts->len > (ori_len - lowest->len))
	{
		ft_printf("\n\n\nREC : BIG WHILE STARTS !\n");
		ft_printf("REC : test stack :\n");
		print_single_stack(te->ts);
		te->near_c = find_fst_chk_member_in_stk_clockwise(te->ts, lowest);
		te->near_cc = find_fst_chk_member_in_stk_counter_clockwise(te->ts, lowest);
		ft_printf("REC : te after find first in chunk :\n");
		te_print(te);
		if (!te->near_c)
			break ;
		delta1 = te->near_c - te->ts->arr;
		delta2 = te->ts->len - (te->near_cc - te->ts->arr);

//		while (find_value_in_stack(lowest, te->ts->arr[((te->near_cc - 1) - te->ts->arr) % te->ts->len]))
//			te->near_cc = te->ts->arr + ((te->near_cc - 1) - te->ts->arr) % te->ts->len;

		ft_printf("REC : delta1, delta2 : %d, %d\n", delta1, delta2);
		ft_printf("REC : is (ori_len - te->ts->len) (%d) < (lowest->len - 1) (%d) : %d\n", (ori_len - te->ts->len), (lowest->len - 1), (ori_len - te->ts->len) < (lowest->len - 1));
		if (((ori_len - te->ts->len) < (lowest->len - 1)) && (ft_abs(delta2 - delta1)) <= (int)(ori_len * (2 / 100)))//-delta1 == delta2)
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
//			ft_printf("REC : new test stack copies initialized\n");
			ft_printf("\nREC : Moving te1 head to value %d by %d moves clockwise,\n", *te1.near_c, delta1);
			te_move_to_vptr(&te1, te1.near_c);
			while (find_value_in_stack(lowest, te1.ts->arr[0]))
				te_push(&te1);
			if (te1.ts->len == (ori_len - lowest->len))
				break ;
			ft_printf("\nREC : Moving te2 head to value %d by %d moves counter clockwise,\n", *te2.near_c, delta2);
			te_move_to_vptr(&te2, te2.near_cc);
			te_push(&te2);

//			ft_printf("REC : test stacks moved to respective closest chunk member\n");
//			ft_printf("REC : New test stacks sent back to recursive func\n");
			if (!recursive_pathfinder(&te1, lowest, ori_len) || !recursive_pathfinder(&te2, lowest, ori_len))
				return ((t_varr *)((size_t)te_clear(&te1, 1) & (size_t)te_clear(&te2, 1)));
			ft_printf("REC : Return from recursive func\n");
			ft_printf("REC : te1.moves : %p, len : %d, te2.moves : %p, len : %d\n", te1.moves, te1.nb_moves, te2.moves, te2.nb_moves);
			te->moves = te1.moves + (te2.moves - te1.moves) * (te2.nb_moves < te1.nb_moves);
			ft_printf("REC : te1 after recursive return : \n");
			print_single_stack(te1.ts);
			ft_printf("REC : te1 moves after recursive return : \n");
			varr_print(te1.moves);
			ft_printf("REC : te2 after recursive return : \n");
			print_single_stack(te2.ts);
			ft_printf("REC : te2 moves after recursive return : \n");
			varr_print(te2.moves);
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
	ft_printf("REC : EXITED BIG WHILE !!\n");
	ft_printf("REC : path found at end of branch : \n");
	
	varr_print(te->moves);
	te_clear(&te1, te1.moves != te->moves);
	te_clear(&te2, te2.moves != te->moves);
	return (te->moves);
}

t_varr	*path_to_n_lowest(t_ps *ps, t_stk *s, int n)
{
	t_stk	*lowest;
	t_te	te;
	t_varr	*shortest_path;

	ft_printf("path to n lowest : entered\n");
	if (!ps || !s || n < 1)
		return (NULL);
	n = n + (s->len - n) * (n > s->len);
	ft_printf("path to n lowest : passed checks\n");
	lowest = get_n_lowest_members(ps, s, n);
	ft_printf("path to n lowest : lowest ptr : %p\n", lowest);
	if (!lowest || !te_init_test_stack_env(&te, s, NULL))
		return (NULL);
	ft_printf("path to n lowest : te after first init :\n");
	te_print(&te);
	ft_printf("path to n lowest : push from stack :\n");
	print_single_stack(te.ts);
	ft_printf("path to n lowest : members of chunk :\n");
	print_single_stack(lowest);
	ft_printf("path to n lowest : test env stack initialized. Entering recursive func.\n");
	shortest_path = recursive_pathfinder(&te, lowest, s->len);
	ft_printf("path to n lowest : returned from recursive pathfinder\n");
	if (!shortest_path)
		return (te_clear(&te, 1));
	ft_printf("path to n lowest : smallest path not null\n");
	varr_print(shortest_path);
	te_clear(&te, 0);
	return (shortest_path);
}
