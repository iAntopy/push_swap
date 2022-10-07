/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:59:32 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/06 23:39:01 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	te_print(t_te *te)
{
	ft_printf("\no-----------< test stack env >------------o\n");
	ft_printf("o-\tstack arr\t: %p\no-\tstack len\t: %d\no-\tts\t\t: %p\n", te->stk_ts.arr, te->stk_ts.len, te->ts);
	ft_printf("o-\tnear_c\t\t: %p (%d)\no-\tnear_cc\t\t: %p (%d)\n", te->near_c, (te->near_c) ? *te->near_c : -1, te->near_cc, (te->near_cc) ? *te->near_cc : -1);
	ft_printf("o-\tcur run\t\t: %d\no-\tnb moves\t: %d\n", te->cur_run, te->nb_moves);
	ft_printf("o-\tmoves\t\t: ");
	varr_print(te->moves);
	ft_printf("\no-----------------------------------------o\n\n");
}

void	*te_clear(t_te *te, int clear_moves)
{
	if (!te)
		return (NULL);
	ft_printf("te_clear : entered, attempting to stk_clear. clear_moves : %d\n", clear_moves);
	te_print(te);
	stk_clear(te->ts);
	if (clear_moves)
		varr_clear(&te->moves);
	ft_memclear(te, sizeof(*te));
	return (NULL);
}

// Creates copy of some reference stack to test hypothetical moves and
// find optimal paths.
t_te	*te_init(t_te *te, t_stk *s)
{
	if (!te || !s)
		return (NULL);
	ft_memclear(te, sizeof(*te));
	te->ts = &te->stk_ts;
	te->threashold = (int)(s->len * (2.0f/100.0f));
	if (!stk_copy(te->ts, s))
		return (te_clear(te, 1));
	te->moves = varr_create(1);
	if (!te->moves)
		return (te_clear(te, 1));
	return (te);
}

void	*te_copy(t_te *dst, t_te *src)
{
	ft_printf("\n\nte_copy : Entered\n");
	if (!dst || !src)
		return (NULL);
	ft_memclear(dst, sizeof(*dst));
	dst->ts = &dst->stk_ts;
	dst->threashold = src->threashold;
	if (!stk_copy(dst->ts, src->ts))
		return (NULL);
	dst->moves = varr_copy(src->moves);
	if (!dst->moves)
		return (stk_clear(dst->ts));
	dst->near_c = src->near_c;
	dst->near_cc = src->near_cc;
	if (src->near_c)
		dst->near_c = dst->stk_ts.arr + (src->near_c - src->stk_ts.arr);
	if (dst->near_cc)
		dst->near_cc = dst->stk_ts.arr + (src->near_cc - src->stk_ts.arr);
	dst->cur_run = src->cur_run;
	dst->nb_moves = src->nb_moves;
	return (dst);
}
