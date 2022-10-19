/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:35:39 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/17 23:45:30 by iamongeo         ###   ########.fr       */
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

int	stk_tail(t_stk *s)
{
	if (s->len)
		return (s->arr[s->len - 1]);
	else
		return (-1);
}

void	*stk_clear(t_stk **stk_p)
{
	t_stk	*s;

	if (!stk_p || !(*stk_p))
		return (NULL);
	s = *stk_p;
	ft_free_p((void **)&s->arr);
	s->len = 0;
	*stk_p = NULL;
	return (NULL);
}

t_stk	*stk_copy(t_stk *dst, t_stk *src)
{
	if (!dst || !src || !src->arr)
		return (NULL);
	if (!dst->arr
		&& !ft_malloc_p(sizeof(int) * src->len, (void **)&dst->arr))
		return (NULL);
	ft_memcpy(dst->arr, src->arr, sizeof(int) * src->len);
	dst->len = src->len;
	return (dst);
}
