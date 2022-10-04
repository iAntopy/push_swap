/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:32:06 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/04 01:20:56 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

int	*find_lowest_excluding(t_stk *s, t_stk *exclusions)
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
	{
		if((arr[i] <= *low) && !find_value_in_stack(exclusions, arr[i]))
			low = arr + i;
	}
	return (low);
}

// mallocs new stack array
t_stk	*get_n_lowest_members(t_ps *ps, t_stk *s, int n)
{
	int	*low;

	ft_printf("get_n_lowest_members : Start \n");
	ft_printf("get_n_lowest_members : ps, s, n : %p, %p, %d \n", ps, s, n);
	if (!ps || !s || n < 1 || n > s->len
			|| !malloc_free_p(0, (void **)&ps->temp->arr)
			|| !malloc_free_p(sizeof(int) * n, (void **)&ps->temp->arr))
		return (NULL);
	ft_printf("get_n_lowest_members : passed if checks \n");
	ps->temp->len = 0;

	while (ps->temp->len < n)
	{
		ft_printf("get_n_lowest_members : while at temp len %d\n", ps->temp->len);
		low = find_lowest_excluding(s, ps->temp);
		if (low)
			ps->temp->arr[ps->temp->len++] = *low;

	}
//	garbage_sort(ps->temp->arr, ps->temp->len);
	return (ps->temp);
}

int	get_nb_members_intersect(t_stk *large, t_stk *small)
{
	int	i;
	int	j;
	int	n;

	n = 0;
	i = -1;
	while ((n < small->len) && (++i < large->len))
	{
		j = -1;
		while (++j < small->len)
		{
			if (large->arr[i] == small->arr[j])
			{
				n++;
				break ;
			}
		}
	}
	ft_printf("get_nb_members_intersect : nb members in common between large (len %d) stk and small (len %d) stk given : %d\n", large->len, small->len, n);
	return (n);
}
