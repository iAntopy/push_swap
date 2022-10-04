/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:35:39 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/04 01:31:16 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	*stk_clear(t_stk *s)
{
	if (!s)
		return (NULL);
	ft_printf("stk_clear : entered, freeing s->arr %p\n", s->arr);
	malloc_free_p(0, (void **)&s->arr);
	s->len = 0;
	return (NULL);
}

t_stk	*stk_copy(t_stk *dst, t_stk *src)
{
	if (!dst || !src || !src->arr)
		return (NULL);
	if (!dst->arr
		&& !malloc_free_p(sizeof(int) * src->len, (void **)&dst->arr))
		return (NULL);
	ft_memcpy(dst->arr, src->arr, sizeof(int) * src->len);
	dst->len = src->len;
	return (dst);
}
