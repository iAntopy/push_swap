/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_stack_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:42:21 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/06 23:51:38 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

t_varr	*chks_is_in_cur_chks(t_chks *chks, int value)
{
	t_varr	*holder;

	if (!chks)
		return (NULL);
	holder = NULL;
	if (varr_is_in(chks->cur_low, value))
		holder = chks->cur_low;
	else if (varr_is_in(chks->cur_high, value))
		holder = chks->cur_high;
	return (holder);
}

int	chks_are_empty(t_chks *chks)
{
	return (!chks->cur_low && !chks->cur_high);
}
