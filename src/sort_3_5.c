/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_3_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 05:04:50 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/12 18:12:35 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	psw_sort2(t_ps *ps, t_stk *s)
{
	int	is_b;

	ft_printf("Entered sort 2\n");
	if (!ps || !s || stk_issorted(s) || s->len != 2)
		return ;
	printf("sort2 : Up to good start\n");
	is_b = (s == ps->B);
	psw_move(ps, M_SA + is_b);
}

void	psw_sort3(t_ps *ps, t_stk *s)
{
	int	*arr;
	int	*low;
	int	*high;
	int	is_b;

	ft_printf("Entering sort 3 : ps ? %d : stack len ? %d, sorted ? %d\n", !!ps, s->len, stk_issorted(s));
	if (!ps || !s || stk_issorted(s) || s->len > 3)
		return ;
	printf("sort3 : Up to good start\n");
	if (s->len < 3)
	{
		psw_sort2(ps, s);
		return ;
	}
	arr = s->arr;
	is_b = (s == ps->B);
	low = find_lowest(s);
	high = find_highest(s);
	ft_printf("Sort3 : arr[0] = %d, arr[1] = %d \n", arr[0], arr[1]);
	if ((arr + 1) == high && arr != low)//arr[0] == 1 && arr[1] == 2)
		psw_recipe(ps, 1, M_RRA + is_b);
	else if (arr == high && (arr + 1) == low)//arr[0] == 2 && arr[1] == 0)
		psw_recipe(ps, 1, M_RA + is_b);
	else if ((arr + 1) == low && arr != high)//arr[0] == 1 && arr[1] == 0)
		psw_recipe(ps, 1, M_SA + is_b);
	else if (arr == low && (arr + 1) == high)//arr[0] == 0 && arr[1] == 2)
		psw_recipe(ps, 2, M_RRA + is_b, M_SA + is_b);
	else if (arr == high && (arr + 1) != low)//arr[0] == 2 && arr[1] == 1)
		psw_recipe(ps, 2, M_RA + is_b, M_SA + is_b);
}
/*

	ft_printf("Sort3 : arr[0] = %d, arr[1] = %d \n", arr[0], arr[1]);
	if (arr[0] == 1 && arr[1] == 2)
		psw_recipe(ps, 1, M_RRA + is_b);
	else if (arr[0] == 2 && arr[1] == 0)
		psw_recipe(ps, 1, M_RA + is_b);
	else if (arr[0] == 1 && arr[1] == 0)
		psw_recipe(ps, 1, M_SA + is_b);
	else if (arr[0] == 0 && arr[1] == 2)
		psw_recipe(ps, 2, M_RRA + is_b, M_SA + is_b);
	else if (arr[0] == 2 && arr[1] == 1)
		psw_recipe(ps, 2, M_RA + is_b, M_SA + is_b);
}
*/

void	psw_sort4(t_ps *ps, t_stk *s)
{
	int	*low;
	int	is_b;

//	int	*seq_start;
//	int	longest_seq;

//	ft_printf("Entering sort 4 : ps ? %d : stack len ? %d, sorted ? %d\n", !!ps, s->len, stk_issorted(s));
//	longest_seq = find_longest_sorted_sequence(s, &seq_start);
//	ft_printf("longest sorted seq len : %d, ptr : %p, value at ptr : %d\n", longest_seq, seq_start, *seq_start);
	if (!ps || !s || s->len > 4 || stk_issorted(s) || stk_seek_sorted_phase(ps, s))
		return ;
	printf("sort4 : Up to good start\n");
	if (s->len < 4)
	{
		psw_sort3(ps, s);
		return ;
	}
	is_b = (s == ps->B);
	low = find_lowest(s);
	psw_move_to_vptr(ps, s, low);
//	ft_printf("sort4 : len A, len B before first push : %d, %d\n", ps->A->len, ps->B->len);
	psw_move(ps, M_PB - is_b);
//	ft_printf("sort4 : len A, len B after first push : %d, %d\n", ps->A->len, ps->B->len);
	psw_sort3(ps, s);
//	ft_printf("sort4 : len A, len B after sort3 : %d, %d\n", ps->A->len, ps->B->len);
	psw_move(ps, M_PA + is_b);
//	ft_printf("sort4 : len A, len B last first push : %d, %d\n", ps->A->len, ps->B->len);
}

// Assumes sort stack A
int	psw_sort5(t_ps *ps)//, t_stk *s)
{
	int		move;
	t_varr	*shortest_path;
	t_varr	*shortest_members;

	if (!ps || ps->A->len > 5 || stk_issorted(ps->A) || stk_seek_sorted_phase(ps, ps->A))
		return (-1);
	if (ps->A->len < 5)
	{
		psw_sort4(ps, ps->A);
		return (0);
	}
	if (!path_to_n_extreme(ps, ps->A, 2, 1))
		return (-1);
	shortest_path = ps->shortest[0];
	shortest_members = ps->shortest[1];
	ft_printf("sort5 : shortest path found to 2 lowest : \n");
	varr_print(shortest_path);
//	while (find_value_in_stack(ps->temp, stk_head(ps->A)))
//		psw_move(ps, M_PB);
	while (ps->A->len > 3 && !varr_isempty(shortest_path))
	{
		if(varr_pop_front(shortest_path, &move) < 0)
			return (-1);
		ft_printf("sort5 : moves to exec : %d, path len left : %d\n", move, shortest_path->len);
		if (move < 0)
			while (move++)
				psw_move(ps, M_RRA);
		else if (move > 0)
			while (move--)
				psw_move(ps, M_RA);
//		while (find_value_in_stack(ps->temp, stk_head(ps->A)))
//			psw_move(ps, M_PB);
	}
	ft_printf("sort5 : stacks after push 2 lowest :\n");
	print_stacks(ps);
	psw_sort3(ps, ps->A);
	psw_move(ps, M_PA);
	psw_move(ps, M_PA);
	if (ps->A->arr[0] > ps->A->arr[1])
		psw_move(ps, M_SA);
	varr_clear(ps->shortest);
	varr_clear(ps->shortest + 1);
	ft_printf("sort5 : EXIT\n");
	return (0);
}
