/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_algo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:36:58 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/07 23:36:28 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

static void	psw_push_all_cur_chks_members_to_b(t_ps *ps)
{
	t_varr	*holder;

	ft_printf("push_all_cur_chks_members : entered\n");
	while (chks_is_in_cur_chks(ps->ch, stk_head(ps->A), &holder))
	{
		if (holder == ps->ch->cur_low)
		{
			psw_move(ps, M_PB);
			psw_move(ps, M_RB);
		}
		else
			psw_move(ps, M_PB);
	}
}

static int	psw_push_stack_a_with_opt_path(t_ps *ps, t_varr *path)
{
	size_t	i;
	int		delta;

	ft_printf("psw_push stack a : ENTERED \n");
	if (!ps || !path)
		return (-1);
	ft_printf("psw_push stack a : checks cleared \n");
	psw_push_all_cur_chks_members_to_b(ps);
	ft_printf("psw_push stack a : start push DONE \n");
	i = -1;
	while (++i < path->len)
	{
		ft_printf("psw_push stack a : in while. Move delta : %d \n", path->arr[0]);
		ft_printf("psw_push stack a : in while. path len %d\n", path->len);
		ft_printf("psw_push stack a : trying to get value at path[%d]\n", i);

		if (varr_get(path, i, &delta) < 0)
			return (-1);
		ft_printf("psw_push stack a : in while. Move delta from varr_get : %d \n", delta);
		if (delta > 0)
			while (delta--)
				psw_move(ps, M_RA);
		else if (delta < 0)
			while (delta++)
				psw_move(ps, M_RRA);
		psw_push_all_cur_chks_members_to_b(ps);
	}
	ft_printf("psw_push stack a : big push DONE \n");

	return (0);
}

// Called after inputs have been validated and stacks are malloced.
int	psw_algo_manager(t_ps *ps)
{
	t_varr	*opt_path;

	ft_printf("psw_algo_manager : Entered. Stack A len : %d\n", ps->A->len);
	if (ps->A->len <= 5)
	{
		ft_printf("algo man : sort 5\n");
		psw_sort5(ps);
		return (0);
	}
	ft_printf("Trying to init chks\n");
	if (!chks_init(ps->ch, ps))
		return (-1);
	ft_printf("init chks SUCCESS\n");
	chks_print(ps->ch);
	opt_path = optimal_push_a_to_b(ps);
	ft_printf("optimal path : ");
	varr_print(opt_path);
	ft_printf("Chunks before push : \n");
	chks_print(ps->ch);
	psw_push_stack_a_with_opt_path(ps, opt_path);
	psw_sort5(ps);
	ft_printf("Chunks after push : \n");
	chks_print(ps->ch);
	return (0);
}
