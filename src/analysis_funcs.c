/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:22:14 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/10 18:10:04 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

int	*find_lowest(t_stk *s)
{
	int		val;
	int		*low;
	int		*arr;
	size_t	i;

	val = INT_MAX;
	low = &val;
	arr = s->arr;
	i = -1;
	while (++i < s->len)
		if (arr[i] <= *low)
			low = arr + i;
	return (low);
}

int	*find_highest(t_stk *s)
{
	int		val;
	int		*high;
	int		*arr;
	size_t	i;

	val = INT_MIN;
	high = &val;
	arr = s->arr;
	i = -1;
	while (++i < s->len)
		if (arr[i] >= *high)
			high = arr + i;
	return (high);
}

int	*find_value_in_stack(t_stk *s, int value)
{
	int		*arr;
	size_t	i;

	arr = s->arr;
	i = -1;
	while (++i < s->len)
		if (arr[i] == value)
			return (arr + i);
	return (NULL);
}

int	distance_from_head(t_stk *s, int value)
{
	int	*vptr;
	int	half_turn;
	int	raw_dist;

	vptr = find_value_in_stack(s, value);
	if (!vptr)
		return (-1);
	half_turn = s->len / 2 + 1;
	raw_dist = vptr - s->arr;
	return (raw_dist - (s->len * (raw_dist >= half_turn)));
}

int	distance_from_head_to_vptr(t_stk *s, int *vptr)
{
	int	half_turn;
	int	raw_dist;

	half_turn = s->len / 2 + 1;
	raw_dist = vptr - s->arr;
	return (raw_dist - (s->len * (raw_dist >= half_turn)));
}
