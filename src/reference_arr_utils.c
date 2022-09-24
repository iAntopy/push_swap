/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reference_arr_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 22:53:20 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/24 08:05:12 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	garbage_sort(int *arr, int size)
{
	int	i;
	int	j;
	int	imax;
	int	*min;

	imax = INT_MAX;
	i = -1;	
	while (++i < (size - 1))
	{
		min = &imax;
		j = i;
		while (++j < size)
			if (arr[j] < *min)
				min = arr + j;
		if (*min < arr[i])
			ft_swap_i(min, arr + i);
	}
}
/*
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
*/
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
	print_ref_array(ps);
	garbage_sort(ps->ref->arr, ps->ref->len);
	print_ref_array(ps);
	substitute_stack_a_values_for_indices(ps);
	print_ref_array(ps);
	return (0);
}
