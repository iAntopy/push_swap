/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env_chunks_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:59:32 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/21 18:34:34 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	tec_print(t_tec *tec)
{
	ft_printf("\no-----------< test stack chunks env >------------o\n");
	ft_printf("o-\tstack arr\t: %p\no-\tstack len\t: %d\no-\tts\t\t: %p\n",
		tec->stk_ts.arr, tec->stk_ts.len, tec->ts);
	ft_printf("o-\tcur run\t\t: %d\no-\tnb moves\t: %d\n", tec->cur_run,
		tec->nb_moves);
	chks_print(tec->ch);
	ft_printf("o-----------------------------------------o\n\n");
}
void	*tec_clear(t_tec *tec)
{
	if (!tec)
		return (NULL);
	stk_clear(&tec->ts);
	chks_clear(&tec->ch);
	tec->ts = NULL;
	tec->ch = NULL;
	varr_clear(&tec->moves);
	return (NULL);
}

void	*tec_clear_all(t_tec *tec, t_tec *tec1, t_tec *tec2)
{
	if (tec)
		tec_clear(tec);
	if (tec1)
		tec_clear(tec1);
	if (tec2)
		tec_clear(tec2);
	return (NULL);
}

// Creates copy of some reference stack to test hypothetical moves and
// find optimal paths.
t_tec	*tec_init(t_ps *ps, t_tec *tec, t_stk *s)
{
	if (!tec || !s)
		return (NULL);
	ft_memclear(tec, sizeof(*tec));
	tec->ts = &tec->stk_ts;
	tec->ch = &tec->chks;
	if (!stk_copy(tec->ts, s))
		return (tec_clear(tec));
	if (!chks_init(tec->ch, ps))
		return (tec_clear(tec));
	tec->moves = varr_create(1);
	if (!tec->moves)
		return (tec_clear(tec));
	return (tec);
}

void	*tec_copy(t_tec *dst, t_tec *src)
{
	if (!dst || !src)
		return (NULL);
	ft_memclear(dst, sizeof(*dst));
	dst->ts = &dst->stk_ts;
	dst->ch = &dst->chks;
	if (!stk_copy(dst->ts, src->ts))
		return (NULL);
	if (!chks_copy(dst->ch, src->ch))
		return (tec_clear(dst));
	if (!varr_copy(src->moves, &dst->moves))
		return (tec_clear(dst));
	dst->cur_run = src->cur_run;
	dst->nb_moves = src->nb_moves;
	return (dst);
}
