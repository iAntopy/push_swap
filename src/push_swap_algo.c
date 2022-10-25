/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_algo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:36:58 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/24 21:20:31 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

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
		if (*recipe == 'p' && varr_get(path, i++, &delta_b) == 0)
			psw_move_delta_push(ps, ps->B, delta_b);
		else if (*recipe == 's')
			psw_move(ps, M_SA);
		else if (*recipe == '+' && varr_get(path, i, &delta_b) == 0
			&& (delta_b > 0) && varr_set(path, i, delta_b - 1) == 0)
			psw_move(ps, M_RR);
		else if (*recipe == '+')
			psw_move(ps, M_RA);
		else if (*recipe == '-' && varr_get(path, i, &delta_b) == 0
			&& (delta_b < 0) && varr_set(path, i, delta_b + 1) == 0)
			psw_move(ps, M_RRR);
		else if (*recipe == '-')
			psw_move(ps, M_RRA);
	}
	return (0);
}

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
////////////////////////////////////////////////////////////
static int	psw_algo_stage1_a_to_b(t_ps *ps)
{
	size_t	i;
	int		delta;
	t_varr	*path;

	if (!optimal_push_a_to_b(ps))
		return (-1);
	i = -1;
	path = ps->shortest_mvs;
	while (++i < path->len && varr_get(path, i, &delta) == 0)
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

//	Highest chunk arrangments solver table (excluding rotates) :
//0	- [3, 2, 1, 0] : PA * 4						4 mvs
//1	- [3, 2, 0, 1] : PA * 2, <reset>.				+2 mvs (miss 2)
//2	- [3, 1, 2, 0] : PA * 3, SA, <reset>.				+4 mvs (miss 1)
//3	- [3, 1, 0, 2] : PA, <reset>					+1 mv (miss 3)
//4	- [3, 0, 2, 1] : PA, <reset>					+1 mvs (miss 3)
//5	- [3, 0, 1, 2] : PA, <reset>					+1 mvs (miss 3)
//
//6	- [2, 3, 1, 0] : PA * 2, SA, <reset>.				+3 mvs (miss 2)
//7	- [2, 3, 0, 1] : PA * 2, SA, <reset>.				+3 mvs (miss 2)
//8	- [2, 1, 3, 0] : PA, PA, RA, PA, SA, RRA, <reset>		+6 mvs (miss 1)
//9	- [2, 1, 0, 3] : PA, PA, PA, RA, RA, PA, SA, RRA, RRA		9 mvs
//10	- [2, 0, 3, 1] : PA, PA, RA, PA, SA, PA, RRA			7 mvs
//11	- [2, 0, 1, 3] : PA, PA, RA, PA, RA, PA, SA, RRA, RRA		9 mvs
//
//12	- [1, 3, 2, 0] : PA, PA, SA, PA, SA, <reset>			+5 mvs (miss 1)
//13	- [1, 3, 0, 2] : PA, PA, SA, PA, RA, PA, SA, RRA		8 mvs
//14	- [1, 2, 3, 0] : PA, RA, PA, PA, SA, RRA, <reset>		+6 mvs (miss 1)
//15	- [1, 2, 0, 3] : PA, PA, PA, RA, SA, RA, PA, SA, RRA, RRA	10 mvs
//16	- [1, 0, 3, 2] : PA, PA, RA, RA, PA, PA, RRA, RRA		8 mvs
//17	- [1, 0, 2, 3] : PA, PA, RA, RA, PA, PA, SA, RRA, RRA		9 mvs
//
//18	- [0, 3, 2, 1] : PA, RA, PA, PA, PA, RRA			6 mvs
//19	- [0, 3, 1, 2] : PA, RA, PA, PA, PA, SA, RRA			7 mvs
//20	- [0, 2, 3, 1] : PA, RA, PA, PA, SA, PA, RRA			7 mvs
//21	- [0, 2, 1, 3] : PA, RA, PA, PA, RA, PA, SA, RRA, RRA		9 mvs
///22	- [0, 1, 3, 2] : PA, RA, PA, PA, SA, PA, SA, RRA		8 mvs
//23	- [0, 1, 2, 3] : PA, RA, PA, RA, PA, PA, SA, RRA, RRA		9 mvs
//
//	LEGEND :
//	'p' = M_PA
//	's' = M_SA
//	'+' = M_RA or M_RR
//	'-' = M_RRA or M_RRR
//
// Recipes (according to indices above)
//{
//	"pppp",		"pp",		"ppps",		"p",			"p",		"p",
//	"pps",		"pps",		"pp+ps-",	"ppp++ps--",	"pp+psp-",	"pp+p+ps--",
//	"ppsps",	"ppsp+ps-",	"p+pps-",	"ppp+s+ps--",	"pp++pp--",	"pp++pps--",
//	"p+ppp-",	"p+ppps-",	"p+ppsp-",	"p+pp+ps--",	"p+ppsps-",	"p+p+pps--"
//}
//
//	Each char of a string from left to right is the series
//	of moves to execute in order to sort a chunk of the 4 highest values in
//	the order found by recursive pathfinder. eg.: {10, 9, 8, 7} are the current
//	highest values, recursive pathfinder finds that the quickest order in which
//	to gather these values in stack B is [9, 10, 7, 8]. By negating the chunk
//	minimum -> [2, 3, 0, 1], we find its identity in the table above and find
//	its the index. Index the solver_table with the identity index and get the
//	solving recipe, then execute recipe. If a reset has to be made, recalculate
//	a new chunk of the 4 highest values in stack B, send them through
//	recursive_pathfinder(). Subtract min from ordered list of closest members
//	and find the new recipe with its identity again.
//	Do this while stack B len >= 4.
int	psw_algo_stage2_b_to_a(t_ps *ps)
{
	const char	*recipe;

	if (!ps)
		return (-1);
	while (ps->B->len >= 4)
	{
		if (stk_seek_rev_sorted_phase(ps, ps->B))
		{
			while (ps->B->len)
				psw_move(ps, M_PA);
			break ;
		}
		if (!path_to_n_extreme(ps, ps->B, 4, 0))
			return (-1);
		if (stk_seek_rev_sorted_highs(ps, varr_max(ps->shortest_mbrs)))
			continue ;
		varr_isub(ps->shortest_mbrs, varr_min(ps->shortest_mbrs));
		recipe = get_solution_for_high_chunk(ps->shortest_mbrs);
		if (!recipe)
			return (-1);
		execute_recipe(ps, ps->shortest_mvs, recipe - 1);
	}
	return (0);
}

// Push back the last 1, 2 or 3 nbs in stack B in reverse order.
int	psw_algo_finale(t_ps *ps)
{
	if (!ps)
		return (-1);
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
		psw_move_to_vptr(ps, ps->B, find_highest(ps->B));
		if (ps->B->arr[1] < ps->B->arr[2])
			psw_recipe(ps, 4, M_PA, M_SB, M_PA, M_PA);
		else
			psw_recipe(ps, 3, M_PA, M_PA, M_PA);
	}
	return (0);
}

// Called after inputs have been validated and stacks are malloced.
int	psw_algo_manager(t_ps *ps)
{
	if (ps && ps->A && ps->A->len <= 5)
	{
		if (psw_sort5(ps) < 0)
			return (-1);
		return (0);
	}
	if (!ps || !ps->A || !ps->B || !chks_init(ps->ch, ps))
		return (-1);
	if (psw_algo_stage1_a_to_b(ps) < 0
		|| psw_sort5(ps) < 0
		|| psw_algo_stage2_b_to_a(ps) < 0
		|| psw_algo_finale(ps) < 0)
		return (-1);
	if (stk_issorted(ps->A))
		return (0);
	return (-1);
}
