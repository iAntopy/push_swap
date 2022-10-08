/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:35:39 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/07 21:59:24 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	*stk_clear(t_stk *s)
{
	if (!s)
		return (NULL);
	ft_printf("stk_clear : entered, freeing s->arr %p\n", s->arr);
	ft_free_p((void **)&s->arr);
	s->len = 0;
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
