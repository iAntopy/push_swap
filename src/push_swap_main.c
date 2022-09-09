/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 07:46:24 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/09 03:31:59 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

int	clear_pswp(t_pswp *ps, int status)
{
	if (ps->stk_a.arr)
		malloc_free_p(0, (void **)&ps->stk_a.arr)
	if (ps->stk_b.arr)
		malloc_free_p(0, (void **)&ps->stk_b.arr)
	if (ps->ref_array)
		malloc_free_p(0, (void **)&ps->ref_array);

	return (status);
}

int	main(int argc, char **argv)
{
	t_pswp	ps;

	ft_memclear(&ps, sizeof(t_pswp));
	return (clear_pswp(&ps, EXIT_SUCCESS));
}
