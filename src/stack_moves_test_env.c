/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_moves_test_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 21:15:39 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/18 20:17:38 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	te_rotate(t_te *te, int rev)
{
	int		temp;
	int		len;
	int		idx_from;
	int		idx_to;
	t_stk	*ts;

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

	if (!te)
		return ;
	ts = te->ts;
	if (ts->len == 0)
		return ;
	varr_append(te->members, ts->arr[0]);
	if (ts->len > 1)
		ft_memmove(ts->arr, ts->arr + 1, sizeof(int) * (ts->len - 1));
	ts->len--;
	varr_append(te->moves, te->cur_run);
	te->cur_run = 0;
}

void	te_move(t_te *te, int move)
{
	if (move == M_RA)
		te_rotate(te, 0);
	else if (move == M_RRA)
		te_rotate(te, 1);
	else if (move == M_PA)
		te_push(te);
}

void	te_move_delta(t_te *te, int delta)
{
	if (!te || !delta)
		return ;
	while (delta > 0)
	{
		te_rotate(te, 0);
		delta--;
	}
	while (delta < 0)
	{
		te_rotate(te, 1);
		delta++;
	}
}

void	te_move_delta_and_push_all_members(t_te *te, t_stk *sub, int delta)
{
	te_move_delta(te, delta);
	while (te->ts->len && find_value_in_stack(sub, stk_head(te->ts)))
		te_push(te);
}
