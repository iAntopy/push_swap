/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 04:55:54 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/26 04:56:10 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap_bonus.h"

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
