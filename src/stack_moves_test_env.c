/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_moves_test_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 21:15:39 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/30 23:19:02 by iamongeo         ###   ########.fr       */
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
	int		val;
	t_stk	*ts;

	ts = te->ts;
	if (ts->len == 0)
		return ;
	val = ts->arr[0];
	if (ts->len > 1)
		ft_memmove(ts->arr, ts->arr + 1, sizeof(int) * (ts->len - 1));
	ts->len--;
	varr_append(te->moves, te->cur_run);
	te->cur_run = 0;
}

void	te_move(t_te *te, int move)
{
	ft_printf("te_move : entered \n");
	if (move == M_RA)
		te_rotate(te, 0);
	else if (move == M_RRA)
		te_rotate(te, 1);
	else if (move == M_PA)
		te_push(te);
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
