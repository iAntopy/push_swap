/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_moves_tec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:55:00 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/24 21:21:07 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	tec_rotate(t_tec *tec, int rev)
{
	int		temp;
	int		len;
	int		idx_from;
	int		idx_to;
	t_stk	*ts;

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
	ts = tec->ts;
	if (ts->len == 0)
		return ;
	value = ts->arr[0];
	if (ts->len > 1)
		ft_memmove(ts->arr, ts->arr + 1, sizeof(int) * (ts->len - 1));
	ts->len--;
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
	if (move == M_RA)
		tec_rotate(tec, 0);
	else if (move == M_RRA)
		tec_rotate(tec, 1);
	else if (move == M_PA)
		tec_push(tec);
}

void	tec_move_delta(t_tec *tec, int delta)
{
	if (!tec)
		return ;
	while (delta > 0)
	{
		tec_rotate(tec, 0);
		delta--;
	}
	while (delta < 0)
	{
		tec_rotate(tec, 1);
		delta++;
	}
}

void	tec_move_delta_and_push_all_members(t_tec *tec, t_chks *ch, int delta)
{
	tec_move_delta(tec, delta);
	while (tec->ts->len && chks_is_in_cur_chks(ch, stk_head(tec->ts), NULL))
		tec_push(tec);
}
