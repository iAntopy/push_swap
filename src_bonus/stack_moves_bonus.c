/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_moves_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 05:19:27 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/26 17:11:21 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap_bonus.h"

void	psw_rotate(t_stk *A, t_stk *B, int rev)
{
	int	temp;
	int	len;
	int	idx_from;
	int	idx_to;

	if (A && (A->len > 1))
	{
		len = A->len - 1;
		idx_from = len * rev;
		idx_to = len * !rev;
		temp = A->arr[idx_from];
		ft_memmove(A->arr + rev, A->arr + !rev, sizeof(int) * len);
		A->arr[idx_to] = temp;
	}
	if (B && (B->len > 1))
	{
		len = B->len - 1;
		idx_from = len * rev;
		idx_to = len * !rev;
		temp = B->arr[idx_from];
		ft_memmove(B->arr + rev, B->arr + !rev, sizeof(int) * len);
		B->arr[idx_to] = temp;
	}
}

void	psw_swap(t_stk *A, t_stk *B)
{
	if (A && (A->len > 1))
		ft_swap_i(A->arr, A->arr + 1);
	if (B && (B->len > 1))
		ft_swap_i(B->arr, B->arr + 1);
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
		psw_rotate(ps->A, NULL, 0);
	else if (move == M_RB)
		psw_rotate(NULL, ps->B, 0);
	else if (move == M_RR)
		psw_rotate(ps->A, ps->B, 0);
	else if (move == M_RRA)
		psw_rotate(ps->A, NULL, 1);
	else if (move == M_RRB)
		psw_rotate(NULL, ps->B, 1);
	else if (move == M_RRR)
		psw_rotate(ps->A, ps->B, 1);
	else if (move == M_SA)
		psw_swap(ps->A, NULL);
	else if (move == M_SB)
		psw_swap(NULL, ps->B);
	else if (move == M_SS)
		psw_swap(ps->A, ps->B);
	else if (move == M_PA)
		psw_push(ps->A, ps->B, NULL);
	else if (move == M_PB)
		psw_push(ps->B, ps->A, ps->ch);
	ps->nb_moves++;
}

void	psw_recipe(t_ps *ps, int nb_moves, ...)
{
	va_list	ap;

	va_start(ap, nb_moves);
	while (nb_moves--)
		psw_move(ps, (int)va_arg(ap, int));
	va_end(ap);
}
