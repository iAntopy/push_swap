/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_sorting_alogs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:58:15 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/25 21:38:22 by iamongeo         ###   ########.fr       */
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
