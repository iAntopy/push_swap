/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:05:54 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/13 03:45:44 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

int	stk_head(t_stk *s)
{
	if (s->len)
		return (s->arr[0]);
	else
		return (-1);
}

int	stk_issorted(t_stk *s)
{
	size_t	i;

	i = -1;
	while (++i < (s->len - 1))
		if (s->arr[i] > s->arr[i + 1])
			return (0);
	return (1);
}
/*
int	stk_slice_issorted(t_stk *s, size_t start, size_t end)
{
	size_t	i;

	if ((0 <= start) && (start <= end) && (end < s->len))
		return (repport_error());
	i = start - 1;
	while (++i < (end - 1))
		if (s->arr[i] > s->arr[i + 1])
			return (0);
	return (1);
}
*/

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
