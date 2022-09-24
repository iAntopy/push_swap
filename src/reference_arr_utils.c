/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reference_arr_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 22:53:20 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/24 03:00:17 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

static int	*ft_min_i(int *arr, int size)
{
	int	val;
	int	*min;

	val = INT_MAX;
	min = &val;
	while (size--)
		if (*(arr++) < *min)
			min = arr - 1;
	return (min);
}

void	garbage_sort(int *arr, int size)
{
	int	i;
	int	*min;

	i = -1;
	while (++i < (size - 1))
	{
		min = ft_min_i(arr + i + 1, size - i - 1);
		if (*min < arr[i])
			ft_swap_i(min, arr + i);
	}
}

int	build_ref_array(t_ps *ps)
{
	if (!ps)
		return (-1);
	ft_printf("Enter build ref_array\n");
	ft_printf("Copying from ptr %p to %p size %d\n", ps->ref->arr, ps->A->arr, ps->A->len);
	ft_memcpy(ps->ref->arr, ps->A->arr, sizeof(int) * ps->A->len);
	ft_printf("build ref_array : stack A copied\n");
	garbage_sort(ps->ref->arr, ps->ref->len);
	ft_printf("build ref_array : garbage in garbage out\n");
	return (0);
}
