/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_3_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 05:04:50 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/17 23:53:33 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	psw_sort2(t_ps *ps, t_stk *s)
{
	int	is_b;

	if (!ps || !s || stk_issorted(s) || s->len != 2)
		return ;
	is_b = (s == ps->B);
	psw_move(ps, M_SA + is_b);
}

void	psw_sort3(t_ps *ps, t_stk *s)
{
	int	*low;
	int	*high;
	int	is_b;

	if (!ps || !s || stk_issorted(s) || s->len > 3)
		return ;
	if (s->len < 3)
	{
		psw_sort2(ps, s);
		return ;
	}
	is_b = (s == ps->B);
	low = find_lowest(s);
	high = find_highest(s);
	if ((s->arr + 1) == high && s->arr != low)
		psw_recipe(ps, 1, M_RRA + is_b);
	else if (s->arr == high && (s->arr + 1) == low)
		psw_recipe(ps, 1, M_RA + is_b);
	else if ((s->arr + 1) == low && s->arr != high)
		psw_recipe(ps, 1, M_SA + is_b);
	else if (s->arr == low && (s->arr + 1) == high)
		psw_recipe(ps, 2, M_RRA + is_b, M_SA + is_b);
	else if (s->arr == high && (s->arr + 1) != low)
		psw_recipe(ps, 2, M_RA + is_b, M_SA + is_b);
}

void	psw_sort4(t_ps *ps, t_stk *s)
{
	int	*low;
	int	is_b;

	if (!ps || !s || s->len > 4 || stk_issorted(s)
		|| stk_seek_sorted_phase(ps, s))
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
	psw_move(ps, M_PB - is_b);
	psw_sort3(ps, s);
	psw_move(ps, M_PA + is_b);
}

// Assumes sort stack A
int	psw_sort5(t_ps *ps)
{
	ft_printf("sort5 : entered \n");
	if (!ps || ps->A->len > 5)
		return (-1);
	if (stk_issorted(ps->A) || stk_seek_sorted_phase(ps, ps->A))
		return (0);
	if (ps->A->len < 5)
	{
		psw_sort4(ps, ps->A);
		return (0);
	}
	if (!path_to_n_extreme(ps, ps->A, 2, 1))
		return (-1);
	psw_move_delta_push(ps, ps->A, ps->shortest_mvs->arr[0]);
	psw_move_delta_push(ps, ps->A, ps->shortest_mvs->arr[1]);
	psw_sort3(ps, ps->A);
	if (ps->B->arr[0] < ps->B->arr[1])
		psw_recipe(ps, 3, M_SB, M_PA, M_PA);
	else
		psw_recipe(ps, 2, M_PA, M_PA);
	return (0);
}
