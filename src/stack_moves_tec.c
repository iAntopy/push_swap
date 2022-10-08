/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_moves_tec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:55:00 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/07 19:31:49 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	tec_rotate(t_tec *tec, int rev)
{
	int	temp;
	int	len;
	int	idx_from;
	int	idx_to;
	t_stk	*ts;

	ft_printf("tec_rotate : enter. rev = %d\n", rev);
	ft_printf("tec_rotate : tec->ts->len : %d, tec->nb_moves : %d\n", tec->ts->len, tec->nb_moves);
	ts = tec->ts;
	if (ts && (ts->len > 1))
	{
		len = ts->len - 1;
		idx_from = len * rev;
		idx_to = len * !rev;
		temp = ts->arr[idx_from];
		ft_memmove(ts->arr + rev, ts->arr + !rev, sizeof(int) * len);
		ts->arr[idx_to] = temp;
		tec->cur_run += 1 - (2 * (rev == 1));
		tec->nb_moves++;
	}
}

void	tec_push(t_tec *tec)
{
	t_stk	*ts;
	int		value;

	if (!tec)
		return ;
	ft_printf("<=== TEC PUSH ACTIVATE !! PUSH VALUE : %d ===>\n", tec->ts->arr[0]);
	ft_printf("tec_push : tec->ts->len : %d, tec->nb_moves : %d\n", tec->ts->len, tec->nb_moves);
	ts = tec->ts;
	if (ts->len == 0)
		return ;
	value = ts->arr[0];
	if (ts->len > 1)
		ft_memmove(ts->arr, ts->arr + 1, sizeof(int) * (ts->len - 1));
	ts->len--;
	if (tec->cur_run)
		varr_append(tec->moves, tec->cur_run);
	tec->cur_run = 0;

	varr_remove(tec->ch->cur_low, value);
	varr_remove(tec->ch->cur_high, value);
	if (varr_is_empty(tec->ch->cur_low))
		tec->ch->cur_low = NULL;
	if (varr_is_empty(tec->ch->cur_high))
		tec->ch->cur_high = NULL;
	if (!tec->ch->cur_low && tec->ch->i_low > 0)
		tec->ch->cur_low = tec->ch->chk_stk[--tec->ch->i_low];
	else if (!tec->ch->cur_high && tec->ch->i_high < (tec->ch->nb_chks - 1))
		tec->ch->cur_high = tec->ch->chk_stk[++tec->ch->i_high];
}

void	tec_move(t_tec *tec, int move)
{
	ft_printf("tec_move : entered \n");
	if (move == M_RA)
	{
		ft_printf("tec_move : M_RA\n");
		tec_rotate(tec, 0);
	}
	else if (move == M_RRA)
	{
		ft_printf("tec_move : M_RRA\n");
		tec_rotate(tec, 1);
	}
	else if (move == M_PA)
	{
		ft_printf("tec_move : M_PA\n");
		tec_push(tec);
	}
//	ft_printf("%s\n", ps->strmoves[move]);
}

void	tec_recipe(t_tec *tec, int nb_moves, ...)
{
	va_list	ap;

//	ft_printf("psw_recipe : entered \n");
	va_start(ap, nb_moves);
	while (nb_moves--)
		tec_move(tec, (int)va_arg(ap, int));
	va_end(ap);
}
