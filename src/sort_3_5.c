/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_3_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 05:04:50 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/24 08:21:15 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	psw_sort3(t_ps *ps)
{
	int	*arr;

	ft_printf("Entering sort 3 : ps ? %d : stack A len ? %d, sorted ? %d\n", !!ps, ps->A->len, stk_issorted(ps->A));
	if (!ps || ps->A->len != 3 || stk_issorted(ps->A))
		return ;
	arr = ps->A->arr;
	ft_printf("Sort3 : arr[0] = %d, arr[1] = %d \n", arr[0], arr[1]);
	if (arr[0] == 1 && arr[1] == 2)
		psw_recipe(ps, 1, M_RRA);
	else if (arr[0] == 2 && arr[1] == 0)
		psw_recipe(ps, 1, M_RA);
	else if (arr[0] == 1 && arr[1] == 0)
		psw_recipe(ps, 1, M_SA);
	else if (arr[0] == 0 && arr[1] == 2)
		psw_recipe(ps, 2, M_RRA, M_SA);
	else if (arr[0] == 2 && arr[1] == 1)
		psw_recipe(ps, 2, M_RA, M_SA);
}
