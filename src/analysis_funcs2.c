/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_funcs2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:59:54 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/10 19:11:23 by iamongeo         ###   ########.fr       */
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
//		if (chks_is_in_cur_chks(chks, s->arr[i]))
		if (find_value_in_stack(chk, s->arr[i]))
			return (s->arr + i);
	}
	return (NULL);
}

int	*find_fst_chk_member_in_stk_counter_clockwise(t_stk *s, t_stk *chk)
{
	size_t	i;

//	ft_printf("find counter_clock member : Entered\n");
	if (!s || !chk)
		return (NULL);
//	ft_printf("find counter_clock member : Passed checks\n");
	i = s->len;
//	ft_printf("find counter_clock member : init len : %d, %d\n", s->len, i);
	while (--i >= 0)
	{
//		ft_printf("find counter_clock member : looking for %d in chunk\n", s->arr[i]);
		if (find_value_in_stack(chk, s->arr[i]))
//		if (chks_is_in_cur_chks(chks, s->arr[i]))
			return (s->arr + i);
	}
//	ft_printf("find counter_clock member : no member found\n");
	return (NULL);
}

int	*find_fst_chks_member_in_stk_clockwise(t_stk *s, t_chks *chks)
{
	size_t	i;
	
//	ft_printf("find clock member : Entered\n");
	if (!s || !chks)
		return (NULL);
//	chks_print(chks);
//	ft_printf("find clock member : Passed checks\n");
	i = -1;
	while (++i < s->len)
	{
//		ft_printf("find clock member : looking for %d in chunk\n", s->arr[i]);
		if (chks_is_in_cur_chks(chks, s->arr[i], NULL))
//		if (find_value_in_stack(chk, s->arr[i]))
			return (s->arr + i);
	}
	return (NULL);
}

int	*find_fst_chks_member_in_stk_counter_clockwise(t_stk *s, t_chks *chks)
{
	size_t	i;

//	ft_printf("find counter_clock member : Entered\n");
	if (!s || !chks)
		return (NULL);
//	chks_print(chks);
//	ft_printf("find counter_clock member : Passed checks\n");
	i = s->len;
//	ft_printf("find counter_clock member : init len : %d, %d\n", s->len, i);
	while (--i >= 0)
	{
//		ft_printf("find counter_clock member : looking for %d in chunk\n", s->arr[i]);
//		if (find_value_in_stack(chk, s->arr[i]))
		if (chks_is_in_cur_chks(chks, s->arr[i], NULL))
			return (s->arr + i);
	}
//	ft_printf("find counter_clock member : no member found\n");
	return (NULL);
}
