/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:59:32 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/21 18:34:54 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"


void	te_print(t_te *te)
{
	ft_printf("\no-----------< test stack env >------------o\n");
	ft_printf("o-\tstack arr\t: %p\no-\tstack len\t: %d\no-\tts\t\t: %p\n",
		te->stk_ts.arr, te->stk_ts.len, te->ts);
	ft_printf("o-\tcur run\t\t: %d\no-\tnb moves\t: %d\n",
		te->cur_run, te->nb_moves);
	ft_printf("o-\tmoves\t\t: ");
	varr_print(te->moves);
	ft_printf("o-\tmembers\t\t: ");
	varr_print(te->members);
	ft_printf("\no-----------------------------------------o\n\n");
}

void	*te_clear(t_te *te)
{
	if (!te)
		return (NULL);
	stk_clear(&te->ts);
	te->ts = NULL;
	varr_clear(&te->moves);
	varr_clear(&te->members);
	return (NULL);
}

void	*te_clear_all(t_te *te, t_te *te1, t_te *te2)
{
	if (te)
		te_clear(te);
	if (te1)
		te_clear(te1);
	if (te2)
		te_clear(te2);
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
	if (!stk_copy(te->ts, s))
		return (te_clear(te));
	te->moves = varr_create(1);
	te->members = varr_create(1);
	if (!te->moves)
		return (te_clear(te));
	return (te);
}

void	*te_copy(t_te *dst, t_te *src)
{
	if (!dst || !src)
		return (NULL);
	ft_memclear(dst, sizeof(*dst));
	stk_clear(&dst->ts);
	dst->ts = &dst->stk_ts;
	if (!stk_copy(dst->ts, src->ts))
		return (NULL);
	varr_clear(&dst->moves);
	varr_clear(&dst->members);
	if (!varr_copy(src->moves, &dst->moves)
		|| !varr_copy(src->members, &dst->members))
		return (te_clear(dst));
	dst->cur_run = src->cur_run;
	dst->nb_moves = src->nb_moves;
	return (dst);
}
