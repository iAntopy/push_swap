/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:05:54 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/23 21:19:08 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

int	stk_issorted(t_stk *s)
{
	int	i;

	i = -1;
	while (++i < (s->len - 1))
		if (s->arr[i] > s->arr[i + 1])
			return (0);
	return (1);
}

int	stk_slice_issorted(t_stk *s, int start, int end)
{
	int	i;

	if ((0 <= start) && (start <= end) && (end < s->len))
		return (repport_error());
	i = start - 1;
	while (++i < (end - 1))
		if (s->arr[i] > s->arr[i + 1])
			return (0);
	return (1);
}
