/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:05:54 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/18 17:43:44 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

int	stk_issorted(t_stk *s)
{
	size_t	i;

	i = -1;
	while (++i < (s->len - 1))
		if (s->arr[i] > s->arr[i + 1])
			return (0);
	return (1);
}

int	stk_seek_sorted_phase(t_ps *ps, t_stk *s)
{
	int		*low;
	size_t	start;
	size_t	end;

	if (!ps || !s)
		return (-1);
	low = find_lowest(s);
	start = low - s->arr;
	end = start + s->len;
	while (++start < (end - 1))
		if (s->arr[start % s->len] > s->arr[(start + 1) % s->len])
			return (0);
	psw_move_to_vptr(ps, s, low);
	return (1);
}

int	stk_seek_rev_sorted_phase(t_ps *ps, t_stk *s)
{
	int		*high;
	size_t	start;
	size_t	end;

	if (!ps || !s)
		return (-1);
	high = find_highest(s);
	start = high - s->arr;
	end = start + s->len;
	while (++start < (end - 1))
		if (s->arr[start % s->len] < s->arr[(start + 1) % s->len])
			return (0);
	psw_move_to_vptr(ps, s, high);
	return (1);
}

// Assumes seeking in stack B
int	stk_seek_rev_sorted_highs(t_ps *ps, int high)
{
	size_t	len;
	int		*arr;
	int		*max;
	int		idx;

	len = ps->B->len;
	arr = ps->B->arr;
	max = find_value_in_stack(ps->B, high);
	idx = max - arr;
	if ((len - idx) < 4 && arr[(idx + 1) % len] == (*max - 1)
		&& arr[(idx + 2) % len] == (*max - 2)
		&& arr[(idx + 3) % len] == (*max - 3))
	{
		psw_move_to_vptr(ps, ps->B, max);
		psw_move(ps, M_PA);
		psw_move(ps, M_PA);
		psw_move(ps, M_PA);
		psw_move(ps, M_PA);
		return (1);
	}
	return (0);
}
