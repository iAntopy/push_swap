/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:22:14 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/26 23:16:22 by iamongeo         ###   ########.fr       */
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
