/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 03:11:01 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/26 18:02:04 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	te_rotate(t_stk *ts, int rev)
{
	int	temp;
	int	len;
	int	idx_from;
	int	idx_to;

	if (ts && (ts->len > 1))
	{
		len = ts->len - 1;
		idx_from = len * rev;
		idx_to = len * !rev;
		temp = ta->arr[idx_from];
		ft_memmove(ta->arr + rev, ta->arr + !rev, sizeof(int) * len);
		ta->arr[idx_to] = temp;
	}
}

void	psw_push_te(t_stk *dst, t_stk *src)
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
}

void	psw_move_te(t_te *te, int move)
{
	ft_printf("psw_move : entered \n");
	if (move == M_RA)
		psw_rotate(te->ta, NULL, 0);
	else if (move == M_RB)
		psw_rotate(NULL, te->tb, 0);
	else if (move == M_RR)
		psw_rotate(te->ta, te->tb, 0);
	else if (move == M_RRA)
		psw_rotate(te->ta, NULL, 1);
	else if (move == M_RRB)
		psw_rotate(te->ta, NULL, 1);
	else if (move == M_RRR)
		psw_rotate(te->ta, te->tb, 1);
	else if (move == M_SA)
		psw_swap(te->ta, NULL);
	else if (move == M_SB)
		psw_swap(NULL, te->tb);
	else if (move == M_SS)
		psw_swap(te->ta, te->tb);
	else if (move == M_PA)
		psw_push(te->ta, te->tb);
	else if (move == M_PB)
		psw_push(te->tb, te->tb);
	ps->nb_moves++;
	ft_printf("%s\n", ps->strmoves[move]);
}

void	psw_recipe_te(t_te *, int nb_moves, ...)
{
	va_list	ap;

//	ft_printf("psw_recipe : entered \n");
	va_start(ap, nb_moves);
	while (nb_moves--)
		psw_move(ps, (int)va_arg(ap, int));
	va_end(ap);
}
