/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_funcs2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:59:54 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/18 17:43:07 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

int	*find_fst_chk_member_in_stk_clockwise(t_stk *s, t_stk *chk)
{
	size_t	i;

	if (!s || !chk)
		return (NULL);
	i = -1;
	while (++i < s->len)
	{
		if (find_value_in_stack(chk, s->arr[i]))
			return (s->arr + i);
	}
	return (NULL);
}

int	*find_fst_chk_member_in_stk_counter_clockwise(t_stk *s, t_stk *chk)
{
	size_t	i;

	if (!s || !chk)
		return (NULL);
	i = s->len;
	while (--i)
	{
		if (find_value_in_stack(chk, s->arr[i]))
			return (s->arr + i);
	}
	if (find_value_in_stack(chk, s->arr[0]))
		return (s->arr);
	return (NULL);
}

int	*find_fst_chks_member_in_stk_clockwise(t_stk *s, t_chks *chks)
{
	size_t	i;

	if (!s || !chks)
		return (NULL);
	i = -1;
	while (++i < s->len)
		if (chks_is_in_cur_chks(chks, s->arr[i], NULL))
			return (s->arr + i);
	return (NULL);
}

int	*find_fst_chks_member_in_stk_counter_clockwise(t_stk *s, t_chks *chks)
{
	size_t	i;

	if (!s || !chks)
		return (NULL);
	i = s->len;
	while (--i)
		if (chks_is_in_cur_chks(chks, s->arr[i], NULL))
			return (s->arr + i);
	if (chks_is_in_cur_chks(chks, s->arr[0], NULL))
		return (s->arr);
	return (NULL);
}
