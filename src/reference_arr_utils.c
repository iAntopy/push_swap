/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reference_arr_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 22:53:20 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/25 23:20:26 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

static void	substitute_stack_a_values_for_indices(t_ps *ps)
{
	int	i;
	int	j;
	int	x;
	int	*arr;
	int	*refs;

	arr = ps->A->arr;
	refs = ps->ref->arr;
	i = -1;
	while (++i < ps->stack_max)
	{
		x = arr[i];
		j = -1;
		while (++j < ps->stack_max)
			if (x == refs[j])
				break ;
		arr[i] = j;
	}
}

int	build_ref_array_and_substitute_in_stack_a(t_ps *ps)
{
	if (!ps)
		return (-1);
	ft_memcpy(ps->ref->arr, ps->A->arr, sizeof(int) * ps->A->len);
	garbage_sort(ps->ref->arr, ps->ref->len);
	substitute_stack_a_values_for_indices(ps);
	return (0);
}
