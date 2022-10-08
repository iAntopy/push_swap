/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_stack_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:42:21 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/07 23:12:47 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

t_varr	*chks_is_in_cur_chks(t_chks *chks, int value, t_varr **holder)
{
	t_varr	*hld;

	hld = NULL;
	if (!chks)
		return (NULL);
	if (varr_is_in(chks->cur_low, value))
		hld = chks->cur_low;
	else if (varr_is_in(chks->cur_high, value))
		hld = chks->cur_high;
	if (holder)
		*holder = hld;
	return (hld);
}

int	chks_are_empty(t_chks *chks)
{
	return (!chks->cur_low && !chks->cur_high);
}
