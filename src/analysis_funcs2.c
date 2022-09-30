/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_funcs2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:59:54 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/29 18:58:57 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

int	*find_fst_chk_member_in_stk_clockwise(t_stk *s, t_stk *chk)
{
	int	*member;
	int	i;
	
	i = -1;
	while (++i < s->len)
	{
		member = find_value_in_stack(chk, s->arr[i]);
		if (member)
			return (member);
	}
	return (NULL);
}

int	*find_fst_chk_member_in_stk_counter_clockwise(t_stk *s, t_stk *chk)
{
	int	*member;
	int	i;
	
	i = s->len;
	while (--i <= 0)
	{
		member = find_value_in_stack(chk, s->arr[i]);
		if (member)
			return (member);
	}
	return (NULL);
}
