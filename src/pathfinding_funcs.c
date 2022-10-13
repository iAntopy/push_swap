/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:34:35 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/13 04:06:49 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"


void	*te_clear_all(t_te *te, t_te *te1, t_te *te2)
{
	if (te)
		te_clear(te);
	if (te1)
		te_clear(te1);
	if (te2)
		te_clear(te2);
	return (NULL);
}

void	*tec_clear_all(t_tec *tec, t_tec *tec1, t_tec *tec2)
{
	if (tec)
		tec_clear(tec);
	if (tec1)
		tec_clear(tec1);
	if (tec2)
		tec_clear(tec2);
	return (NULL);
}

t_varr	*recursive_pathfinder(t_te *te, t_stk *sub, int ori_len, t_varr *ret[2], int depth, char *side)
{
	t_te	te1;
	t_te	te2;
	int		delta1;
	int		delta2;
	t_te	*winner;

	if(!te || !sub || !sub->len)
		return (NULL);
	winner = NULL;
	ft_printf("\n\n\n\n\n----------------REC : RECURSIVE PATHFINDING (depth %d, side %s) --------------\n\n", depth, side);
//	ft_printf("REC : te->nb_moves : %d\n", te->nb_moves);
	ft_memclear(&te1, sizeof(te1));
	ft_memclear(&te2, sizeof(te2));
	while (te->members->len < sub->len)
	{
		ft_printf("\nREC : Big loopadoop !\n");
		te->near_c = find_fst_chk_member_in_stk_clockwise(te->ts, sub);
		te->near_cc = find_fst_chk_member_in_stk_counter_clockwise(te->ts, sub);
		if (!te->near_c)
			break ;
		delta1 = te->near_c - te->ts->arr;
		delta2 = te->ts->len - (te->near_cc - te->ts->arr);

		ft_printf("REC : delta1, delta2 : %d, %d\n", delta1, delta2);
		if ((te->members->len < (sub->len - 1)) && (ft_abs(delta2 - delta1)) <= (te->ts->len * PATH_THREASHOLD))//te->threashold)
		{
			ft_printf("\nREC : Split\n");
			if (!te_copy(&te1, te) || te_clear(te) || !te_copy(&te2, &te1))
				return (te_clear_all(te, &te1, &te2));
//				return (te_clear(&te1, 1));
			ft_printf("REC : copy DONE\n");
			te_move_to_vptr(&te1, te1.near_c);
			while (find_value_in_stack(sub, stk_head(te1.ts)))
				te_push(&te1);
			ft_printf("REC : return if te1 stack len == sub len : %d =? %d, quit ? %d\n", te1.members->len, sub->len, te1.members->len == sub->len);
			if (te1.members->len == sub->len)
				winner = &te1;
			if (winner)
				break ;
			ft_printf("REC : move te1 len != sub len. Continue moving te2 to near_cc.\n");
			te_move_to_vptr(&te2, te2.near_cc);
			te_push(&te2);
			ft_printf("REC : te2 move and push DONE\n");
			if (!recursive_pathfinder(&te1, sub, ori_len, ret, depth + 1, "left") || !recursive_pathfinder(&te2, sub, ori_len, ret, depth + 1, "right"))
				return (te_clear_all(te, &te1, &te2));
			ft_printf("REC : Returned from recursions at depth %d\n", depth);
//			winner = &te1 + (&te2 - &te1) * (te2.nb_moves < te1.nb_moves);
			if (te2.nb_moves < te1.nb_moves)
				winner = &te2;
			else
				winner = &te1;
			break ;
		}
/*
//			if (!varr_copy(winner->moves, ret) || !varr_copy(winner->members, ret + 1))
//				return ((t_varr *)((size_t)te_clear(&te1) | (size_t)te_clear(&te2)));
//			te_clear(&te1)
//			te_clear(&te2)
//			return (ret[0]);
//			return ((t_varr *)((size_t)te_clear(&te1, 1) | (size_t)te_clear(&te2, 0)));

//			te_clear(&te1, te1.moves != te->moves);
//			te_clear(&te2, te2.moves != te->moves);
//			te->moves = te1.moves + (te2.moves - te1.moves) * (te2.nb_moves < te1.nb_moves);
//			break ;
*/
		else
		{
			ft_printf("\nREC : No Split\n");
			te_move_to_vptr(te, te->near_c + (te->near_cc - te->near_c) * (delta1 > delta2));
//			ft_printf("REC : can we find value %d in sub:\n", stk_head(te->ts));
//			print_single_stack(sub);
//			ft_printf("REC : current stack : %p\n", te->ts);
//			print_single_stack(te->ts);	

			while (te->ts->len && find_value_in_stack(sub, stk_head(te->ts)))
			{
				ft_printf("REC : push ts head : %d, sub->len : %d, ts->len : %d\n", stk_head(te->ts), sub->len, te->ts->len);
				te_push(te);
			}
		}
	}
	if (!winner)
		winner = te;
//		return ((t_varr *)((size_t)te_clear(&te1) | (size_t)te_clear(&te2)));
	if (!varr_copy(winner->moves, ret) || !varr_copy(winner->members, ret + 1))
		return (te_clear_all(te, &te1, &te2));
	te_clear_all(te, &te1, &te2);
	return (ret[0]);

//	ft_printf("REC : EXITED BIG WHILE !!\n");
//	ft_printf("REC : path found at end of branch : \n");
//	varr_print(ret[0]);

//	te_clear(&te1, te1.moves != te->moves);
//	te_clear(&te2, te2.moves != te->moves);
//	return (ret[0]);
}

t_varr	*recursive_pathfinder_chks(t_tec *tec, t_varr *ret[2], int depth, char *side)
{
	t_tec	tec1;
	t_tec	tec2;
	int		delta1;
	int		delta2;
	t_tec	*winner;

	if(!tec || !tec->ch)
		return (NULL);
	ft_printf("\n\n\n\n\n----------------REC : RECURSIVE PATHFINDER CHKS (depth %d, side %s) --------------\n\n", depth, side);
//	ft_printf("RECC : tec->nb_moves : %d\n", tec->nb_moves);
	ft_memclear(&tec1, sizeof(tec1));
	ft_memclear(&tec2, sizeof(tec2));
	while (tec->ts->len > 5)
	{
//		ft_printf("current tec stack : \n");
//		print_single_stack(tec->ts);
		tec->near_c = find_fst_chks_member_in_stk_clockwise(tec->ts, tec->ch);
		tec->near_cc = find_fst_chks_member_in_stk_counter_clockwise(tec->ts, tec->ch);
		if (!tec->near_c)
			break ;
//		ft_printf("RECC : near_c and near_cc found : %d, %d\n", *tec->near_c, *tec->near_cc);
//		delta1 = distance_from_head_to_vptr(tec->ts, tec->near_c);
//		delta2 = distance_from_head_to_vptr(tec->ts, tec->near_cc);
		delta1 = tec->near_c - tec->ts->arr;
		delta2 = tec->ts->len - (tec->near_cc - tec->ts->arr);

		while ((tec->near_cc > tec->ts->arr) && chks_is_in_cur_chks(tec->ch, *(tec->near_cc - 1), NULL))
			tec->near_cc--;

		ft_printf("RECC : delta1, delta2 : %d, %d\n", delta1, delta2);
		if (tec->ts->len > 6 && (ft_abs(delta2 - delta1)) <= (tec->ts->len * PATH_THREASHOLD))//tec->threashold))
		{
			ft_printf("\nRECC : Split\n");
			if (!tec_copy(&tec1, tec) || tec_clear(tec) || !tec_copy(&tec2, &tec1))
//			{
//				ft_printf("\nRECC : TEC COPY FAILED\n");
				return (tec_clear_all(tec, &tec1, &tec2));
//			}
//			ft_printf("RECC : post split clearing original tec\n");

//			ft_printf("RECC : post split moving tec1 to near_c\n");
			tec_move_to_vptr(&tec1, tec1.near_c);
			while (chks_is_in_cur_chks(tec->ch, stk_head(tec1.ts), NULL))
				tec_push(&tec1);
			if (tec1.ts->len <= 5)
				return (tec_clear_all(tec, &tec1, &tec2));//(t_varr *)((size_t)tec_clear(&tec1, 0) | (size_t)tec_clear(&tec2, 1)));
//				break ;
//			ft_printf("RECC : post split moving tec2 to near_cc\n");
			tec_move_to_vptr(&tec2, tec2.near_cc);
			tec_push(&tec2);
//			ft_printf("RECC : post split going recursive baby !\n");
			if (!recursive_pathfinder_chks(&tec1, ret, depth + 1, "left")
				|| !recursive_pathfinder_chks(&tec2, ret, depth + 1, "right"))
				return (tec_clear_all(tec, &tec1, &tec2));//(t_varr *)((size_t)tec_clear(&tec1, 1) & (size_t)tec_clear(&tec2, 1)));
			ft_printf("RECC : Returned from recursions at depth %d\n", depth);
			varr_clear(&tec->moves);
			if (tec2.nb_moves < tec1.nb_moves)
				winner = &tec2;
			else
				winner = &tec1;
			break ;
/*
			if (tec2.nb_moves < tec1.nb_moves)
			{
				tec->moves = tec2.moves;
				return ((t_varr *)((size_t)tec_clear(&tec1, 1) | (size_t)tec_clear(&tec2, 0)));
//				tec_clear(&tec1, 1);
//				tec_clear(&tec2, 0);
			}
			else
			{
				tec->moves = tec1.moves;
				return ((t_varr *)((size_t)tec_clear(&tec1, 0) | (size_t)tec_clear(&tec2, 1)));
//				tec_clear(&tec1, 0);
//				tec_clear(&tec2, 1);
			}
*/
//			return (tec->moves);

//			tec->moves = tec1.moves + (tec2.moves - tec1.moves) * (tec2.nb_moves < tec1.nb_moves);
//			break ;
		}
		else
		{
			ft_printf("\nRECC : No Split\n");
			tec_move_to_vptr(tec, tec->near_c + (tec->near_cc - tec->near_c) * (delta1 > delta2));
			while (chks_is_in_cur_chks(tec->ch, stk_head(tec->ts), NULL))
//			while (find_value_in_stack(sub, tec->ts->arr[0]))
				tec_push(tec);
		}
	}
	if (!winner)
		winner = tec;
//		return ((t_varr *)((size_t)te_clear(&te1) | (size_t)te_clear(&te2)));
	if (!varr_copy(winner->moves, ret))
		return (tec_clear_all(tec, &tec1, &tec2));
	tec_clear_all(tec, &tec1, &tec2);

	return (ret[0]);
/*
	ft_printf("RECC : EXITED BIG WHILE !!\n");
	ft_printf("RECC : tec moves : %p, tec moves arr : %p\n", tec->moves, tec->moves->arr);
	ft_printf("RECC : path found at end of branch (depth %d, side %s): \n", depth, side);
	varr_print(tec->moves);

//	tec_clear(&tec1, tec1.moves != tec->moves);
//	tec_clear(&tec2, tec2.moves != tec->moves);
	return (tec_clear(tec, 0));
//	return (tec->moves);
*/
}

t_varr	*optimal_push_a_to_b(t_ps *ps)
{
	t_tec	tec;
	t_varr	*shortest_path;

	if (!ps || ps->stack_max <= 5 || !tec_init(ps, &tec, ps->A))
		return (NULL);
	varr_clear(ps->shortest);
	varr_clear(ps->shortest + 1);
	ft_printf("\n\n\noptimal push a to b : init stack nb_moves : %d\n", tec.nb_moves);
	print_single_stack(tec.ts);
	shortest_path = recursive_pathfinder_chks(&tec, ps->shortest, 0, "root");
	if (!shortest_path)
		return (tec_clear(&tec));
	ft_printf("path to n highest : shortest path found : %p\n", shortest_path);
	varr_print(shortest_path);
	tec_print(&tec);
	ft_printf("\n\n\noptimal push a to b : optimal nb of moves : %d\n", tec.nb_moves);
	tec_clear(&tec);
	return (shortest_path);
}

t_varr	*path_to_n_extreme(t_ps *ps, t_stk *s, size_t n, int find_lowest)
{
	t_stk	*ext;
	t_te	te;
//	t_varr	*shortest_path;

//	ft_printf("path to n highest : entered\n");
	if (!ps || !s || n > s->len)
		return (NULL);
	varr_clear(ps->shortest);
	varr_clear(ps->shortest + 1);
	n = n + (s->len - n) * (n > s->len);
	if (find_lowest)
		ext = get_n_lowest_members(ps, s, n);
	else
		ext = get_n_highest_members(ps, s, n);
//	print_single_stack(ext);
	if (!ext || !te_init(&te, s))
		return (NULL);
	ft_printf("path to n highest : te after first init :\n");
	te_print(&te);
	if (!recursive_pathfinder(&te, ext, s->len, ps->shortest, 0, "root"))
		return (te_clear(&te));
		
	ft_printf("path to n highest : shortest path found :\n");
	varr_print(ps->shortest[0]);
	return (ps->shortest[0]);
	
	
//	shortest_path = recursive_pathfinder(&te, ext, s->len, shortest, 0, "root");
//	if (!shortest_path)
//		return (te_clear(&te, 1));
	
//	ft_printf("path to n highest : shortest path found :\n");
//	varr_print(ps->shortest[0]);

//	ft_printf("path to n highest : te.members before ps->va_temp clear :\n");
//	varr_print(te.members);
//	if (ps->va_temp)
//		varr_clear(&ps->va_temp);
//	ft_printf("path to n highest : te.members after ps->va_temp clear :\n");
//	varr_print(te.members);
//	ps->va_temp = te.members;
//	ft_printf("path to n highest : new ps->va_temp : %p\n", ps->va_temp);
//	varr_print(ps->va_temp);
//	return (shortest_path);
}
