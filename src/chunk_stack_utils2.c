/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_stack_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:42:21 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/26 21:17:45 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	chks_print(t_chks *chks)
{
	int	i;

	if (!chks || !chks->chk_stk)
		return ;
	i = -1;
	ft_printf("\n*---------< CHUNK STACK >----------*\n");
	while (++i < chks->nb_chks)
	{
		ft_printf("|\t- %d : ", i);
		if (chks->chk_stk[i])
			varr_print(chks->chk_stk[i]);
		else
			ft_printf("No chunk.\n");
	}
	ft_printf("|\t---------------------------|\n");
	ft_printf("|\t- i_low = %d\n", chks->i_low);
	ft_printf("|\t- i_high = %d\n", chks->i_high);
	ft_printf("|\t- cur_low = %p\n", chks->cur_low);
	ft_printf("|\t- cur_high = %p\n", chks->cur_high);
	ft_printf("*----------------------------------*\n\n");
}

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
