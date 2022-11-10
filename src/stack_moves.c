/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 03:11:01 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/10 17:11:31 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	psw_rotate(t_stk *a, t_stk *b, int rev)
{
	int	temp;
	int	len;
	int	idx_from;
	int	idx_to;

	if (a && (a->len > 1))
	{
		len = a->len - 1;
		idx_from = len * rev;
		idx_to = len * !rev;
		temp = a->arr[idx_from];
		ft_memmove(a->arr + rev, a->arr + !rev, sizeof(int) * len);
		a->arr[idx_to] = temp;
	}
	if (b && (b->len > 1))
	{
		len = b->len - 1;
		idx_from = len * rev;
		idx_to = len * !rev;
		temp = b->arr[idx_from];
		ft_memmove(b->arr + rev, b->arr + !rev, sizeof(int) * len);
		b->arr[idx_to] = temp;
	}
}

void	psw_swap(t_stk *a, t_stk *b)
{
	if (a && (a->len > 1))
		ft_swap_i(a->arr, a->arr + 1);
	if (b && (b->len > 1))
		ft_swap_i(b->arr, b->arr + 1);
}

void	psw_push(t_stk *dst, t_stk *src, t_chks *chks)
{
	int	val;

	if (src->len == 0)
		return ;
	val = src->arr[0];
	if (src->len > 1)
		ft_memmove(src->arr, src->arr + 1, sizeof(int) * (src->len - 1));
	if (dst->len)
		ft_memmove(dst->arr + 1, dst->arr, sizeof(int) * dst->len);
	dst->arr[0] = val;
	src->len--;
	dst->len++;
	if (!chks)
		return ;
	varr_remove(chks->cur_low, val);
	varr_remove(chks->cur_high, val);
	if (varr_is_empty(chks->cur_low))
		chks->cur_low = NULL;
	if (varr_is_empty(chks->cur_high))
		chks->cur_high = NULL;
	if (!chks->cur_low && chks->i_low > 0)
		chks->cur_low = chks->chk_stk[--chks->i_low];
	else if (!chks->cur_high && chks->i_high < (chks->nb_chks - 1))
		chks->cur_high = chks->chk_stk[++chks->i_high];
}

void	psw_move(t_ps *ps, int move)
{
	if (move == M_RA)
		psw_rotate(ps->a, NULL, 0);
	else if (move == M_RB)
		psw_rotate(NULL, ps->b, 0);
	else if (move == M_RR)
		psw_rotate(ps->a, ps->b, 0);
	else if (move == M_RRA)
		psw_rotate(ps->a, NULL, 1);
	else if (move == M_RRB)
		psw_rotate(NULL, ps->b, 1);
	else if (move == M_RRR)
		psw_rotate(ps->a, ps->b, 1);
	else if (move == M_SA)
		psw_swap(ps->a, NULL);
	else if (move == M_SB)
		psw_swap(NULL, ps->b);
	else if (move == M_SS)
		psw_swap(ps->a, ps->b);
	else if (move == M_PA)
		psw_push(ps->a, ps->b, NULL);
	else if (move == M_PB)
		psw_push(ps->b, ps->a, ps->ch);
	ps->nb_moves++;
	ft_printf("%s\n", ps->strmoves[move]);
}

void	psw_recipe(t_ps *ps, int nb_moves, ...)
{
	va_list	ap;

	va_start(ap, nb_moves);
	while (nb_moves--)
		psw_move(ps, (int)va_arg(ap, int));
	va_end(ap);
}
