/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_moves_test_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 21:15:39 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/09 08:46:10 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	te_rotate(t_te *te, int rev)
{
	int	temp;
	int	len;
	int	idx_from;
	int	idx_to;
	t_stk	*ts;

//	ft_printf("te_rotate : enter. rev = %d\n", rev);
//	ft_printf("te_rotate : te->ts->len : %d, te->nb_moves : %d\n", te->ts->len, te->nb_moves);
	ts = te->ts;
	if (ts && (ts->len > 1))
	{
		len = ts->len - 1;
		idx_from = len * rev;
		idx_to = len * !rev;
		temp = ts->arr[idx_from];
		ft_memmove(ts->arr + rev, ts->arr + !rev, sizeof(int) * len);
		ts->arr[idx_to] = temp;
		te->cur_run += 1 - (2 * (rev == 1));
		te->nb_moves++;
	}
}

void	te_push(t_te *te)
{
	t_stk	*ts;
//	int		value;

	if (!te)
		return ;
//	ft_printf("te_push : te->ts->len : %d, te->nb_moves : %d\n", te->ts->len, te->nb_moves);
	ts = te->ts;
	if (ts->len == 0)
		return ;
//	value = ts->arr[0];
	varr_append(te->members, ts->arr[0]);
	if (ts->len > 1)
		ft_memmove(ts->arr, ts->arr + 1, sizeof(int) * (ts->len - 1));
	ts->len--;
//	if (te->cur_run)
	varr_append(te->moves, te->cur_run);
	te->cur_run = 0;
/*
	low = te->chks->cur_low;
	high = te->chks->cur_high;
	varr_remove(low, value);
	varr_remove(high, value);
	low -= (t_varr *)((size_t)low * (size_t)varr_is_empty(low));
	high -= (t_varr *)((size_t)high * (size_t)varr_is_empty(high));
	if (!low && te->chks->i_low > 0)
		te->chks->cur_low = te->chks->chk_stk[--te->chks->i_low];
	else if (!high && te->chks->i_high < (te->chks->nb_chks - 1))
		te->chks->cur_high = te->chks->chk_stk[++te->chks->i_high];
*/
}

void	te_move(t_te *te, int move)
{
//	ft_printf("te_move : entered \n");
	if (move == M_RA)
	{
//		ft_printf("te_move : M_RA\n");
		te_rotate(te, 0);
	}
	else if (move == M_RRA)
	{
//		ft_printf("te_move : M_RRA\n");
		te_rotate(te, 1);
	}
	else if (move == M_PA)
	{
//		ft_printf("te_move : M_PA\n");
		te_push(te);
	}
//	ft_printf("%s\n", ps->strmoves[move]);
}

void	te_recipe(t_te *te, int nb_moves, ...)
{
	va_list	ap;

//	ft_printf("psw_recipe : entered \n");
	va_start(ap, nb_moves);
	while (nb_moves--)
		te_move(te, (int)va_arg(ap, int));
	va_end(ap);
}
