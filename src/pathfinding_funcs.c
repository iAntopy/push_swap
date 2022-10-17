/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:34:35 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/16 21:40:22 by iamongeo         ###   ########.fr       */
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

void	te_push_all_members_at_head(t_te *te, t_stk *sub)
{
//	ft_printf("push all mbrs at head : Entered, len at start : %d, head value : %d\n", te->ts->len, stk_head(te->ts));
	while (te->ts->len && find_value_in_stack(sub, stk_head(te->ts)))
	{
//		ft_printf("REC : push ts head : %d, sub->len : %d, ts->len : %d\n", stk_head(te->ts), sub->len, te->ts->len);
		te_push(te);
	}
}

void	tec_push_all_members_at_head(t_tec *tec, t_chks *ch)
{
//	ft_printf("push all mbrs at head : Entered, len at start : %d, head value : %d\n", tec->ts->len, stk_head(tec->ts));
	while (tec->ts->len && chks_is_in_cur_chks(ch, stk_head(tec->ts), NULL))
	{
		tec_push(tec);
	}
}

void	te_find_deltas_to_surrounding_clusters(t_stk *s, t_stk *sub, int *delta1, int *delta2)
{
	int	*clst[2];
	int	dt[2];
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
//		&& ft_eprintf("te cc cluster end - 1 greater than current end : %d vs %d : end - 1 > end ? %d\n", *(clst[3] - 1), *clst[3], *(clst[3] - 1) > *clst[3]))

		clst[3]--;
//	ft_printf("find clusters deltas : clst_c values (start, end) : (%d, %d)\n", *clst[0], *clst[1]);
//	ft_printf("find clusters deltas : clst_cc values (start, end) : (%d, %d)\n", *clst[2], *clst[3]);
	dt[0] = clst[0] - s->arr;
	dt[1] = clst[1] - s->arr;
	dt[2] = s->len - (clst[2] - s->arr);
	dt[3] = s->len - (clst[3] - s->arr);
//	ft_printf("find clusters deltas : dt_c to (start, end) : (%d, %d)\n", dt[0], dt[1]);
//	ft_printf("find clusters deltas : dt_cc to (start, end): (%d, %d)\n", dt[2], dt[3]);
	does_overlap = (dt[0] <= dt[2] && dt[2] <= dt[1])
		|| (dt[2] <= dt[0] && dt[0] <= dt[3])
		|| (ft_abs(dt[0] - dt[2]) <= (s->len * PATH_THREASHOLD));
//	ft_printf("find clusters deltas : does overlap ? %d\n", does_overlap);
	*delta1 = dt[0] * (does_overlap || (dt[0] < dt[2]));
	*delta2 = -dt[3] * (does_overlap || (dt[2] < dt[0]));
//	ft_printf("find clusters deltas : deltas at exit : (%d, %d)\n", *delta1, *delta2);
}

void	tec_find_deltas_to_surrounding_clusters(t_stk *s, t_chks *ch, int *delta1, int *delta2)
{
	int	*clst[2];
	int	dt[2];
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
//		&& ft_eprintf("tec cc cluster end - 1 greater than current end : %d vs %d : end - 1 > end ? %d\n", *(clst[3] - 1), *clst[3], *(clst[3] - 1) > *clst[3]))
		clst[3]--;
//	ft_printf("find clusters deltas : clst_c values (start, end) : (%d, %d)\n", *clst[0], *clst[1]);
//	ft_printf("find clusters deltas : clst_cc values (start, end) : (%d, %d)\n", *clst[2], *clst[3]);
	dt[0] = clst[0] - s->arr;
	dt[1] = clst[1] - s->arr;
	dt[2] = s->len - (clst[2] - s->arr);
	dt[3] = s->len - (clst[3] - s->arr);
//	ft_printf("find clusters deltas : dt_c to (start, end) : (%d, %d)\n", dt[0], dt[1]);
//	ft_printf("find clusters deltas : dt_cc to (start, end): (%d, %d)\n", dt[2], dt[3]);
	does_overlap = (dt[0] <= dt[2] && dt[2] <= dt[1])
		|| (dt[2] <= dt[0] && dt[0] <= dt[3])
		|| (ft_abs(dt[0] - dt[2]) <= (s->len * PATH_THREASHOLD));
//	ft_printf("find clusters deltas : does overlap ? %d\n", does_overlap);
	*delta1 = dt[0] * (does_overlap || (dt[0] < dt[2]));
	*delta2 = -dt[3] * (does_overlap || (dt[2] < dt[0]));
//	ft_printf("find clusters deltas : deltas at exit : (%d, %d)\n", *delta1, *delta2);
}

void	te_move_delta(t_te *te, int delta)
{
	if (!te)
		return ;
//	ft_printf("te_move_delta : Entered delta : %d, ts head : %d\n", delta, stk_head(te->ts));
	while (delta > 0)
	{
		te_rotate(te, 0);
		delta--;
	}
	while (delta < 0)
	{
		te_rotate(te, 1);
		delta++;
	}
}

void	tec_move_delta(t_tec *tec, int delta)
{
	if (!tec)
		return ;
//	ft_printf("te_move_delta : Entered delta : %d, ts head : %d\n", delta, stk_head(tec->ts));
	while (delta > 0)
	{
		tec_rotate(tec, 0);
		delta--;
	}
	while (delta < 0)
	{
		tec_rotate(tec, 1);
		delta++;
	}
}

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
//	ft_printf("REC : te->nb_moves : %d\n", te->nb_moves);
	ft_memclear(&te1, sizeof(te1));
	ft_memclear(&te2, sizeof(te2));
	winner = NULL;
	te_push_all_members_at_head(te, sub);
	while (te->members->len < sub->len)
	{
//		ft_printf("\nREC : Big loopadoop !\n");
		te_find_deltas_to_surrounding_clusters(te->ts, sub, &delta1, &delta2);
//		te->near_c = find_fst_chk_member_in_stk_clockwise(te->ts, sub);
//		te->near_cc = find_fst_chk_member_in_stk_counter_clockwise(te->ts, sub);
//		if (!te->near_c)
//			break ;
//		delta1 = te->near_c - te->ts->arr;
//		delta2 = te->ts->len - (te->near_cc - te->ts->arr);

//		ft_printf("REC : delta1, delta2 : %d, %d\n", delta1, delta2);
		if ((te->members->len < (sub->len - 1)) && delta1 && delta2)//(ft_abs(delta2 + delta1)) <= (te->ts->len * PATH_THREASHOLD))//te->threashold)
		{
//			ft_printf("\nREC : Split\n");
			if (!te_copy(&te1, te) || te_clear(te) || !te_copy(&te2, &te1))
//			{
//				ft_printf("REC : te copies or clear FAILED !\n");
				return (te_clear_all(te, &te1, &te2));
//			}
//			ft_printf("REC : copy DONE\n");
			te_move_delta(&te1, delta1);
			te_push_all_members_at_head(&te1, sub);
//			te_move_to_vptr(&te1, te1.near_c);
//			while (find_value_in_stack(sub, stk_head(te1.ts)))
//				te_push(&te1);
//			ft_printf("REC : return if te1 stack len == sub len : %d =? %d, quit ? %d\n", te1.members->len, sub->len, te1.members->len == sub->len);
			if (te1.members->len == sub->len)
			{
				winner = &te1;
				break ;
			}
//			ft_printf("REC : move te1 len != sub len. Continue moving te2 to near_cc.\n");
			te_move_delta(&te2, delta2);
			te_push_all_members_at_head(&te2, sub);

//			te_move_to_vptr(&te2, te2.near_cc);
//			te_push(&te2);
//			ft_printf("REC : te2 move and push DONE\n");
			if (!recursive_pathfinder(&te1, sub, ori_len, depth + 1) || !recursive_pathfinder(&te2, sub, ori_len, depth + 1))
				return (te_clear_all(te, &te1, &te2));
//			ft_printf("REC : Returned from recursions at depth %d\n", depth);
//			winner = &te1 + (&te2 - &te1) * (te2.nb_moves < te1.nb_moves);
			if (te2.nb_moves < te1.nb_moves)
				winner = &te2;
			else
				winner = &te1;
			break ;
		}
		else
		{
//			ft_printf("\nREC : No Split\n");
//			te_move_to_vptr(te, te->near_c + (te->near_cc - te->near_c) * (delta1 > delta2));
			if (delta1 && delta2)
				te_move_delta(te, delta1);
			else
				te_move_delta(te, delta1 + delta2);

			te_push_all_members_at_head(te, sub);
//			while (te->ts->len && find_value_in_stack(sub, stk_head(te->ts)))
//			{
//				ft_printf("REC : push ts head : %d, sub->len : %d, ts->len : %d\n", stk_head(te->ts), sub->len, te->ts->len);
//				te_push(te);
//			}
		}
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
//	ft_printf("RECC : tec->nb_moves : %d\n", tec->nb_moves);
	ft_memclear(&tec1, sizeof(tec1));
	ft_memclear(&tec2, sizeof(tec2));
	winner = NULL;
	while (tec->ts->len > 5)
	{
		tec_find_deltas_to_surrounding_clusters(tec->ts, tec->ch, &delta1, &delta2);
//		ft_printf("current tec stack : \n");
//		print_single_stack(tec->ts);
//		tec->near_c = find_fst_chks_member_in_stk_clockwise(tec->ts, tec->ch);
//		tec->near_cc = find_fst_chks_member_in_stk_counter_clockwise(tec->ts, tec->ch);
//		if (!tec->near_c)
//			break ;
//		ft_printf("RECC : near_c and near_cc found : %d, %d\n", *tec->near_c, *tec->near_cc);
//		delta1 = tec->near_c - tec->ts->arr;
//		delta2 = tec->ts->len - (tec->near_cc - tec->ts->arr);
//		while ((tec->near_cc > tec->ts->arr) && chks_is_in_cur_chks(tec->ch, *(tec->near_cc - 1), NULL))
//			tec->near_cc--;

//		ft_printf("RECC : delta1, delta2 : %d, %d\n", delta1, delta2);
		if (tec->ts->len > 6 && delta1 && delta2)//&& (ft_abs(delta2 - delta1)) <= (tec->ts->len * PATH_THREASHOLD))//tec->threashold))
		{
//			ft_printf("\nRECC : Split\n");
			if (!tec_copy(&tec1, tec) || tec_clear(tec) || !tec_copy(&tec2, &tec1))
//			{
//				ft_printf("\nRECC : TEC COPY FAILED\n");
				return (tec_clear_all(tec, &tec1, &tec2));
//			}
//			ft_printf("RECC : post split clearing original tec\n");
//			ft_printf("RECC : post split moving tec1 to near_c\n");
//			tec_move_to_vptr(&tec1, tec1.near_c);
			tec_move_delta(&tec1, delta1);
			tec_push_all_members_at_head(&tec1, tec->ch);
			while (chks_is_in_cur_chks(tec->ch, stk_head(tec1.ts), NULL))
				tec_push(&tec1);
			if (tec1.ts->len <= 5)
			{
				winner = &tec1;
				break ;
			}
			tec_move_delta(&tec2, delta2);
			tec_push_all_members_at_head(&tec2, tec2.ch);
//			ft_printf("RECC : post split moving tec2 to near_cc\n");
///			tec_move_to_vptr(&tec2, tec2.near_cc);
//			tec_push(&tec2);
//			ft_printf("RECC : post split going recursive baby !\n");
			if (!recursive_pathfinder_chks(&tec1, depth + 1)//, "left")
				|| !recursive_pathfinder_chks(&tec2, depth + 1))//, "right"))
				return (tec_clear_all(tec, &tec1, &tec2));
//			ft_printf("RECC : Returned from recursions at depth %d\n", depth);
			if (tec2.nb_moves < tec1.nb_moves)
				winner = &tec2;
			else
				winner = &tec1;
			break ;
		}
		else
		{
//			ft_printf("\nRECC : No Split\n");
			if (delta1 && delta2)
				tec_move_delta(tec, delta1);
			else
				tec_move_delta(tec, delta1 + delta2);
			tec_push_all_members_at_head(tec, tec->ch);
//			tec_move_to_vptr(tec, tec->near_c + (tec->near_cc - tec->near_c) * (delta1 > delta2));
//			while (chks_is_in_cur_chks(tec->ch, stk_head(tec->ts), NULL))
//				tec_push(tec);
		}
	}

	if (!winner)
		return (tec->moves);
	if (!varr_copy(winner->moves, &tec->moves))
		return (tec_clear_all(tec, &tec1, &tec2));
	tec->nb_moves = winner->nb_moves;
	tec_clear_all(NULL, &tec1, &tec2);
	return (tec->moves);


//	if (!winner)
//		winner = tec;
//		return ((t_varr *)((size_t)te_clear(&te1) | (size_t)te_clear(&te2)));
//	if (!varr_copy(winner->moves, ret))
//		return (tec_clear_all(tec, &tec1, &tec2));
//	tec_clear_all(tec, &tec1, &tec2);

//	return (ret[0]);
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

	if (!ps || ps->stack_max <= 5 || !tec_init(ps, &tec, ps->A))
		return (NULL);
///	ft_printf("\n\noptimal push a to b : Entered\n");
//	print_single_stack(tec.ts);
	varr_clear(&ps->shortest_mvs);
	varr_clear(&ps->shortest_mbrs);
	if (!recursive_pathfinder_chks(&tec, 0))//, "root"))
		return (tec_clear(&tec));
	ps->shortest_mvs = tec.moves;
//	ft_printf("path to n highest : shortest path found : %p\n", tec.moves);
//	varr_print(tec.moves);
//	tec_print(&tec);
//	ft_printf("\n\n\noptimal push a to b : optimal nb of moves : %d\n", tec.nb_moves);
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
//	print_single_stack(ext);
	if (!ext || !te_init(&te, s))
		return (NULL);
//	ft_printf("path to n highest : te after first init :\n");
//	te_print(&te);
	if (!recursive_pathfinder(&te, ext, s->len, 0))//, "root"))
		return (te_clear(&te));
	ps->shortest_mvs = te.moves;
	ps->shortest_mbrs = te.members;
//	ft_printf("path to n highest : shortest path found :\n");
//	varr_print(te.moves);
	stk_clear(&te.ts);
	ft_memclear(&te, sizeof(te));
	return (ps->shortest_mvs);
	
	
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
