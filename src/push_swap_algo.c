/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_algo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:36:58 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/17 17:06:23 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

const char	*get_solution_for_high_chunk(int *hc)
{
	static const char	*solver_table[24] = {
		"pppp",		"pp",		"ppps",		"p",			"p",		"p",
		"pps",		"pps",		"pp+ps-",	"ppp++ps--",	"pp+psp-",	"pp+p+ps--",
		"ppsps",	"ppsp+ps-",	"p+pps-",	"ppp+s+ps--",	"pp++pp--",	"pp++pps--",
		"p+ppp-",	"p+ppps-",	"p+ppsp-",	"p+pp+ps--",	"p+ppsps-",	"p+p+pps--"
	};

	if (!hc)
	{
		ft_printf("get solution for high chunk : hc ptr is NULL\n", hc);
		return (NULL);
	}
//	else
//		ft_printf("get solution for high chunk : hc = [%d, %d, %d, %d]\n", hc[0], hc[1], hc[2], hc[3]);
	if (hc[0] == 3 && hc[1] == 2 && hc[2] == 1 && hc[3] == 0)
		return (solver_table[0]);
	else if (hc[0] == 3 && hc[1] == 2 && hc[2] == 0 && hc[3] == 1)
		return (solver_table[1]);
	else if (hc[0] == 3 && hc[1] == 1 && hc[2] == 2 && hc[3] == 0)
		return (solver_table[2]);
	else if (hc[0] == 3 && hc[1] == 1 && hc[2] == 0 && hc[3] == 2)
		return (solver_table[3]);
	else if (hc[0] == 3 && hc[1] == 0 && hc[2] == 2 && hc[3] == 1)
		return (solver_table[4]);
	else if (hc[0] == 3 && hc[1] == 0 && hc[2] == 1 && hc[3] == 2)
		return (solver_table[5]);

	else if (hc[0] == 2 && hc[1] == 3 && hc[2] == 1 && hc[3] == 0)
		return (solver_table[6]);
	else if (hc[0] == 2 && hc[1] == 3 && hc[2] == 0 && hc[3] == 1)
		return (solver_table[7]);
	else if (hc[0] == 2 && hc[1] == 1 && hc[2] == 3 && hc[3] == 0)
		return (solver_table[8]);
	else if (hc[0] == 2 && hc[1] == 1 && hc[2] == 0 && hc[3] == 3)
		return (solver_table[9]);
	else if (hc[0] == 2 && hc[1] == 0 && hc[2] == 3 && hc[3] == 1)
		return (solver_table[10]);
	else if (hc[0] == 2 && hc[1] == 0 && hc[2] == 1 && hc[3] == 3)
		return (solver_table[11]);
	
	else if (hc[0] == 1 && hc[1] == 3 && hc[2] == 2 && hc[3] == 0)
		return (solver_table[12]);
	else if (hc[0] == 1 && hc[1] == 3 && hc[2] == 0 && hc[3] == 2)
		return (solver_table[13]);
	else if (hc[0] == 1 && hc[1] == 2 && hc[2] == 3 && hc[3] == 0)
		return (solver_table[14]);
	else if (hc[0] == 1 && hc[1] == 2 && hc[2] == 0 && hc[3] == 3)
		return (solver_table[15]);
	else if (hc[0] == 1 && hc[1] == 0 && hc[2] == 3 && hc[3] == 2)
		return (solver_table[16]);
	else if (hc[0] == 1 && hc[1] == 0 && hc[2] == 2 && hc[3] == 3)
		return (solver_table[17]);

	else if (hc[0] == 0 && hc[1] == 3 && hc[2] == 2 && hc[3] == 1)
		return (solver_table[18]);
	else if (hc[0] == 0 && hc[1] == 3 && hc[2] == 1 && hc[3] == 2)
		return (solver_table[19]);
	else if (hc[0] == 0 && hc[1] == 2 && hc[2] == 3 && hc[3] == 1)
		return (solver_table[20]);
	else if (hc[0] == 0 && hc[1] == 2 && hc[2] == 1 && hc[3] == 3)
		return (solver_table[21]);
	else if (hc[0] == 0 && hc[1] == 1 && hc[2] == 3 && hc[3] == 2)
		return (solver_table[22]);
	else if (hc[0] == 0 && hc[1] == 1 && hc[2] == 2 && hc[3] == 3)
		return (solver_table[23]);
	return (NULL);
}

static int	seek_rev_sorted_highs(t_ps *ps, int high)
{
	size_t	len;
	int	*arr;
	int	*max;
	int	idx;

	len = ps->B->len;
	arr = ps->B->arr;
	max = find_value_in_stack(ps->B, high);
	idx = max - arr;
//	ft_printf("seek_rev_sorted_highs : max : %d, idx : %d\n", *max, idx);
	if ((len - idx) < 4 && arr[(idx + 1) % len] == (*max - 1)
		&& arr[(idx + 2) % len] == (*max - 2)
		&& arr[(idx + 3) % len] == (*max - 3))
	{
//		ft_printf("seek_rev_sorted_highs : FULLY SEEKED \n");
		psw_move_to_vptr(ps, ps->B, max);
		psw_move(ps, M_PA);
		psw_move(ps, M_PA);
		psw_move(ps, M_PA);
		psw_move(ps, M_PA);
		return (1);
	}
	return (0);
}

static int	follow_path_and_push_a_to_b(t_ps *ps, t_varr *path)
{
	size_t	i;
	int		delta;

	if (!ps || !ps->A || !ps->B || !ps->ch)
		return (-1);
	i = -1;
	while (++i < path->len && varr_get(path, i, &delta))
	{
		if (delta > 0)
			while (delta--)
				psw_move(ps, M_RA);
		else if (delta < 0)
			while (delta++)
				psw_move(ps, M_RRA);
		if (varr_is_in(ps->ch->cur_low, stk_head(ps->A)))
		{
			psw_move(ps, M_PB);
			psw_move(ps, M_RB);
		}
		else
			psw_move(ps, M_PB);
	}
	return (0);
}

static int	follow_path_step_and_push_b_to_a(t_ps *ps, int delta)
{
	if (!ps || !ps->A || !ps->B)
		return (-1);
	if (delta > 0)
		while (delta--)
			psw_move(ps, M_RB);
	else if (delta < 0)
		while (delta++)
			psw_move(ps, M_RRB);
	psw_move(ps, M_PA);
	return (0);
}

static int	execute_recipe(t_ps *ps, t_varr *path, const char *recipe)
{
	int	i;
	int	delta_b;

	if (!ps || !path || !recipe)
		return (-1);
	i = 0;
	while (*(++recipe))
	{
		delta_b = 0;
		if (*recipe == 'p' && varr_get(path, i++, &delta_b))
			follow_path_step_and_push_b_to_a(ps, delta_b);
		else if (*recipe == 's')
			psw_move(ps, M_SA);
		else if (*recipe == '+' && varr_get(path, i, &delta_b)
				&& (delta_b > 0) && varr_set(path, i, delta_b - 1))
			psw_move(ps, M_RR);
		else if (*recipe == '+')
			psw_move(ps, M_RA);
		else if (*recipe == '-' && varr_get(path, i, &delta_b)
				&& (delta_b < 0) && varr_set(path, i, delta_b + 1))
			psw_move(ps, M_RRR);
		else if (*recipe == '-')
			psw_move(ps, M_RRA);
	}
	return (0);
}
/*
static int	psw_push_stack_a_with_opt_path(t_ps *ps, t_varr *path)
{
	size_t	i;
	int		delta;

//	ft_printf("psw_push stack a : ENTERED \n");
	if (!ps || !path)
		return (-1);
	i = -1;
	while (++i < path->len)
	{
		varr_get(path, i, &delta);
		follow_path_step_and_push_a_to_b(ps, delta);
	}
	return (0);
}
*/
/*
	{
		ft_printf("psw_push stack a : in while. Move delta : %d \n", path->arr[i]);
		ft_printf("psw_push stack a : trying to get value at path[%d]\n", i);

		if (varr_get(path, i, &delta) < 0)
			return (-1);
		ft_printf("psw_push stack a : in while. Move delta from varr_get : %d \n", delta);
		if (delta > 0)
			while (delta--)
				psw_move(ps, M_RA);
		else if (delta < 0)
			while (delta++)
				psw_move(ps, M_RRA);
		ft_printf("psw_push stack a : pushing nb %d from stack A to B \n", stk_head(ps->A));

		if (varr_is_in(ps->ch->cur_low, stk_head(ps->A)))
		{
			ft_printf("psw_push stack a : nb %d is part of cur_low so add M_RB move \n", stk_head(ps->A));
			psw_move(ps, M_PB);
			psw_move(ps, M_RB);
		}
		else
			psw_move(ps, M_PB);

		ft_printf("psw_push stack a : stacks at end of while loop %i \n", i);
		print_stacks(ps);

//		psw_push_all_cur_chks_members_to_b(ps);
	}
*/
//	ft_printf("psw_push stack a : big push DONE \n");
//}

// Called after inputs have been validated and stacks are malloced.
int	psw_algo_manager(t_ps *ps)
{
	t_varr	*opt_path;
//	t_varr	*opt_mbrs;

//	ft_printf("psw_algo_manager : Entered. Stack A len : %d\n", ps->A->len);
	if (ps->A->len <= 5)
	{
//		ft_printf("psw_algo_manager algo : sort 5\n");
		psw_sort5(ps);
		return (0);
	}
	opt_path = NULL;
//	opt_mbrs = NULL;
/*
///////////////////////// STAGE 1 \\\\\\\\\\\\\\\\\\\\\\\\\\
//	- Push all stack A members except 5 in stack B
//	- organized in chunks, so that chunks are organized 
//	- from greatest membered chunk first to smallest.
//	- Then sort5 on stack A which will now hold 
//	- the greatest numbers from input. At the end of
//	- this stage stack A will be sorted with the highest
//	- nbs and stack B organized in chunks from greatest to
//	- smallest with head of stack being at the top of the 
//	- greatest chunk ready to push back.
*/
//	ft_printf("Trying to init chks\n");
//	ft_printf("Algo manager : chks ptr ps->ch vs chks ptr &ps->chks : %p vs %p\n", ps->ch, &ps->chks);
	if (!chks_init(ps->ch, ps))
		return (-1);
//	ft_printf("init chks SUCCESS\n");
//	chks_print(ps->ch);
	if (!optimal_push_a_to_b(ps))
	{
		ft_printf("Algo manager : recursive pathfinder failed !\n");
		return (-1);
	}
//	opt_path = NULL;
//	opt_mbrs = NULL;
	opt_path = ps->shortest_mvs;
//	opt_mbrs = ps->shortest_mbrs;
	ft_printf("optimal path : ");
	varr_print(opt_path);
//	print_stacks(ps);
//	ft_printf("Chunks before push : \n");
//	chks_print(ps->ch);
//	if (psw_push_stack_a_with_opt_path(ps, opt_path) < 0)
	if (follow_path_and_push_a_to_b(ps, opt_path) < 0)
		return (-1);
//	varr_clear(&opt_path);
//	ft_printf("Chunks after push A to B: \n");
//	chks_print(ps->ch);
//	ft_printf("Stacks after push A to B: \n");
//	print_stacks(ps);

	chks_clear(&ps->ch);
	varr_clear(&ps->shortest_mvs);
	varr_clear(&ps->shortest_mbrs);

	if (psw_sort5(ps) < 0)
	{
		ft_printf("Algo manager : pre Stage 2 sort5 has FAILED! \n");
		return (-1);
	}

/*
///////////////////////// STAGE 2 \\\\\\\\\\\\\\\\\\\\\\\\\\
//	-	Push stack B members from greatest to smallest in 
//	- chunks of the 4 greatest members of stack B at a 
//	- time. This chunk of 4 is passed through the recursive
//	- pathfinder to check the optimal path in which to push
//	- them.
//	- 	If the 2 closest chunk members are the two greatest 
//	- members of the 4, only push those 2 in the optimal order
//	- and swap A if HEAD is greater than the first
//	- value pushed, then delete the chunk, find current 4 greatest
//	- check recursive pathfinder again.
//	-	Else if 2 closest are NOT the greatest in the chunk,
//	- push the 4 members of chunk in optimal order found by
//	- recursive pathfinder. When one of the 2 smallest in the
//	- chunk is pushed do M_RA move (rotate A) so that the smallest
//	- members are behind the head. After all 4 are push, Swap A 
//	- if A-head > A-head + 1. Then M_RRA twice so that the two 
//	- smallest members pushed are at A-head and A-head + 1.
//	- Then again, swap A, if A-head > A-head + 1. 
//	-	Continue this process while stack B length is > 3.


	Highest chunk arrangments solver table (excluding rotates) :
0	- [3, 2, 1, 0] : PA * 4						4 mvs
1	- [3, 2, 0, 1] : PA * 2, <reset>.				+2 mvs (miss 2)
2	- [3, 1, 2, 0] : PA * 3, SA, <reset>.				+4 mvs (miss 1)
3	- [3, 1, 0, 2] : PA, <reset>					+1 mv (miss 3)
4	- [3, 0, 2, 1] : PA, <reset>					+1 mvs (miss 3)
5	- [3, 0, 1, 2] : PA, <reset>					+1 mvs (miss 3)

6	- [2, 3, 1, 0] : PA * 2, SA, <reset>.				+3 mvs (miss 2)
7	- [2, 3, 0, 1] : PA * 2, SA, <reset>.				+3 mvs (miss 2)
8	- [2, 1, 3, 0] : PA, PA, RA, PA, SA, RRA, <reset>		+6 mvs (miss 1)
9	- [2, 1, 0, 3] : PA, PA, PA, RA, RA, PA, SA, RRA, RRA		9 mvs
10	- [2, 0, 3, 1] : PA, PA, RA, PA, SA, PA, RRA			7 mvs
11	- [2, 0, 1, 3] : PA, PA, RA, PA, RA, PA, SA, RRA, RRA		9 mvs

12	- [1, 3, 2, 0] : PA, PA, SA, PA, SA, <reset>			+5 mvs (miss 1)
13	- [1, 3, 0, 2] : PA, PA, SA, PA, RA, PA, SA, RRA		8 mvs
14	- [1, 2, 3, 0] : PA, RA, PA, PA, SA, RRA, <reset>		+6 mvs (miss 1)
15	- [1, 2, 0, 3] : PA, PA, PA, RA, SA, RA, PA, SA, RRA, RRA	10 mvs
16	- [1, 0, 3, 2] : PA, PA, RA, RA, PA, PA, RRA, RRA		8 mvs
17	- [1, 0, 2, 3] : PA, PA, RA, RA, PA, PA, SA, RRA, RRA		9 mvs

18	- [0, 3, 2, 1] : PA, RA, PA, PA, PA, RRA			6 mvs
19	- [0, 3, 1, 2] : PA, RA, PA, PA, PA, SA, RRA			7 mvs
20	- [0, 2, 3, 1] : PA, RA, PA, PA, SA, PA, RRA			7 mvs
21	- [0, 2, 1, 3] : PA, RA, PA, PA, RA, PA, SA, RRA, RRA		9 mvs
22	- [0, 1, 3, 2] : PA, RA, PA, PA, SA, PA, SA, RRA		8 mvs
23	- [0, 1, 2, 3] : PA, RA, PA, RA, PA, PA, SA, RRA, RRA		9 mvs

{
	"pppp",		"pp",		"ppps",		"p",			"p",		"p",
	"pps",		"pps",		"pp+ps-",	"ppp++ps--",	"pp+psp-",	"pp+p+ps--",
	"ppsps",	"ppsp+ps-",	"p+pps-",	"ppp+s+ps--",	"pp++pp--",	"pp++pps--",
	"p+ppp-",	"p+ppps-",	"p+ppsp-",	"p+pp+ps--",	"p+ppsps-",	"p+p+pps--"
}


*/
//	Solver string legend. Each char of a string from left to right is the series
//	of moves to execute in order to sort a chunk of the 4 highest values in the order
//	found by recursive pathfinder. eg.: {10, 9, 8, 7} are the current highest values,
//	recursive pathfinder finds that the quickest order in which to gather these values
//	in stack B is [9, 10, 7, 8]. By negating the chunk minimum -> [2, 3, 0, 1], we
//	find its identity in the table above and find its the index. Index the solver_table
//	with the identity index and get the solving recipe, then execute recipe. If a reset 
//	has to be made, recalculate a new chunk of the 4 highest values in stack B, send
//	them through recursive_pathfinder(). subtract min from ordered list of closest members
//	and find the new recipe with its identity again. Do this while stack B len > 3.

//	'p' = M_PA
//	's' = M_SA
//	'+' = M_RA
//	'-' = M_RRA

//	const char	*solver_table[24] = {	"pppp", "pp", "ppps", "p", "p", "p", 
//						"pps", "pps", "pp+ps-", "pp+psp-", "pp+p+ps--", "ppp++ps--",
//						"ppspsr", "ppsp+ps-", "p+pps", "ppp+s+ps--", "pp++pp--", "pp++pps--",
//						"p+ppp-", "p+ppps-", "p+ppsp-", "p+pp+ps--", "p+ppsps-", "p+p+pps--"};

	
	const char	*recipe;

	while (ps->B->len >= 4)
	{
//		ft_printf("Algo manager : stacks while pushing B to A :\n");
//		print_stacks(ps);
		if (stk_seek_rev_sorted_phase(ps, ps->B))
		{
			while (ps->B->len)
				psw_move(ps, M_PA);
			break ;
		}
		if (!path_to_n_extreme(ps, ps->B, 4, 0))
			return (-1);			
		if (seek_rev_sorted_highs(ps, varr_max(ps->shortest_mbrs)))
			continue ;
		
//		ft_printf("Algo manager : ps->shortest_mvs : %p\n", ps->shortest_mvs);
//		varr_print(ps->shortest_mvs);

//		ft_printf("Algo manager : members found in order : %p\n", ps->shortest_mbrs);
//		varr_print(ps->shortest_mbrs);
		
		varr_isub(ps->shortest_mbrs, varr_min(ps->shortest_mbrs));
//		ft_printf("Algo manager : members path identity (after sub min) : \n");
//		varr_print(ps->shortest_mbrs);
		
		recipe = get_solution_for_high_chunk(ps->shortest_mbrs->arr);
		if (!recipe)
			return (-1);
		
//		ft_printf("Algo manager : solution found for high path : %s\n", recipe);
		execute_recipe(ps, ps->shortest_mvs, recipe - 1);
		varr_clear(&ps->shortest_mvs);
		varr_clear(&ps->shortest_mbrs);
	}

//	ft_printf("Algo manager : stack before last 3 :\n");
//	print_stacks(ps);
	if (ps->B->len == 1)
		psw_move(ps, M_PA);
	else if (ps->B->len == 2)
	{
		if (ps->B->arr[0] < ps->B->arr[1])
			psw_move(ps, M_SB);
		psw_move(ps, M_PA);
		psw_move(ps, M_PA);
	}
	else if (ps->B->len == 3)
	{
		if ((ps->B->arr[0] < ps->B->arr[1]) && (ps->B->arr[0] < ps->B->arr[2]))
		{
			ft_printf("Algo manager : M_RB to but smallest (at idx 0) at the bottom of stack B\n");
			psw_move(ps, M_RB);
		}
		else if ((ps->B->arr[1] < ps->B->arr[0]) && (ps->B->arr[1] < ps->B->arr[2]))
		{
			ft_printf("Algo manager : M_RB to but smallest (at idx 1) at the bottom of stack B\n");
			psw_move(ps, M_RRB);
		}
//		ft_printf("Algo manager : stack before last 3 :\n");
		print_stacks(ps);
		psw_move(ps, M_PA);
		psw_move(ps, M_PA);
		if (ps->A->arr[0] > ps->A->arr[1])
			psw_move(ps, M_SA);
		psw_move(ps, M_PA);
	}

	return (0);
}
