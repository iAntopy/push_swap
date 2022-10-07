/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:22:14 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/06 16:52:19 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

int	*find_lowest(t_stk *s)
{
	int	val;
	int	*low;
	int	*arr;
	int	i;

	val = INT_MAX;
	low = &val;
	arr = s->arr;
	i = -1;
	while (++i < s->len)
		if (arr[i] <= *low)
			low = arr + i;
	return (low);
}

int	*find_highest(t_stk *s)
{
	int	val;
	int	*high;
	int	*arr;
	int	i;

	val = INT_MIN;
	high = &val;
	arr = s->arr;
	i = -1;
	while (++i < s->len)
		if (arr[i] >= *high)
			high = arr + i;
	return (high);
}
/*
int	find_longest_sorted_sequence(t_stk *s, int **seq_start)
{
	int	*arr;
	int	i;
	int	seq_len;
	int	longest_seq;
	int	*best_seq_p;
	int	*seq_p;

	ft_printf("\n\nEntered find longest seq :\n");
	arr = s->arr;
	longest_seq = 0;
	seq_p = NULL;
	best_seq_p = NULL;
	i = -1;
	while (i < (s->len - 1))
	{
		seq_len = 0;
		seq_p = arr + ((i + 1) % s->len);
		ft_printf("Starting new seq at value : %d\n", *seq_p);//arr[(i + 1) % s->len]);
		while ((++seq_len < s->len) && (++i >= 0))
		{
			if (arr[i % s->len] > arr[(i + 1) % s->len])
			{
				ft_printf("seq broken at i = %d,  idx1 %d, idx2 %d\n", i, i % s->len, (i + 1) % s->len);
				break ;
			}
		}
		ft_printf("seq found : len %d, value at start : %d\n", seq_len, *seq_p);
		if (seq_len > longest_seq)
		{
			longest_seq = seq_len;
			best_seq_p = seq_p;
		}
	}
	*seq_start = best_seq_p;
	return (longest_seq);
}
*/
