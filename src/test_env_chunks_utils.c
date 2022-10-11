/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env_chunks_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:59:32 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/10 23:45:36 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	tec_print(t_tec *tec)
{
	ft_printf("\no-----------< test stack chunks env >------------o\n");
	ft_printf("o-\tstack arr\t: %p\no-\tstack len\t: %d\no-\tts\t\t: %p\n", tec->stk_ts.arr, tec->stk_ts.len, tec->ts);
	ft_printf("o-\tnear_c\t\t: %p (%d)\no-\tnear_cc\t\t: %p (%d)\n", tec->near_c, (tec->near_c) ? *tec->near_c : -1, tec->near_cc, (tec->near_cc) ? *tec->near_cc : -1);
	ft_printf("o-\tcur run\t\t: %d\no-\tnb moves\t: %d\n", tec->cur_run, tec->nb_moves);
	chks_print(tec->ch);
	ft_printf("o-----------------------------------------o\n\n");
}

void	*tec_clear(t_tec *tec, int clear_moves)
{
	if (!tec)
		return (NULL);
	ft_printf("tec_clear : entered, attempting to stk_clear. clear_moves : %d\n", clear_moves);
//	tec_print(tec);
	stk_clear(tec->ts);
	chks_clear(tec->ch);
	tec->ts = NULL;
	tec->ch = NULL;
	tec->near_c = NULL;
	tec->near_cc = NULL;
	if (clear_moves)
	{
		ft_printf("tec clear : clearing tec moves at ptr %p \n", tec->moves);
		varr_clear(&tec->moves);
		ft_printf("tec clear : tec->moves ptr after clear : %p\n", tec->moves);
		return (NULL);
	}
	else
	{
		ft_printf("tec clear : returning moves %p : \n", tec->moves);
		varr_print(tec->moves);
		return (tec->moves);
	}
//	ft_memclear(tec, sizeof(*tec));
//	ft_printf("tec clear : tec post clear : \n");
//	tec_print(tec);
//	return (NULL);
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
//	tec->threashold = (int)(s->len * (2.0f/100.0f));
	if (!stk_copy(tec->ts, s))
		return (tec_clear(tec, 1));
	if (!chks_init(tec->ch, ps))
		return (tec_clear(tec, 1));
	tec->moves = varr_create(1);
	if (!tec->moves)
		return (tec_clear(tec, 1));
	return (tec);
}

void	*tec_copy(t_tec *dst, t_tec *src)
{
//	ft_printf("\n\ntec_copy : Entered\n");
//	ft_printf("\n\ntec_copy : trying to copy :\n");
//	tec_print(src);

	if (!dst || !src)
		return (NULL);
	ft_memclear(dst, sizeof(*dst));
	dst->ts = &dst->stk_ts;
	dst->ch = &dst->chks;
//	dst->threashold = src->threashold;
//	ft_printf("tec_copy : stk copy attempt\n");
	if (!stk_copy(dst->ts, src->ts))
		return (NULL);
//	ft_printf("tec_copy : stk copy SUCCESS\n");
//	ft_printf("tec_copy : chk copy attempt\n");
//	chks_print(src->ch);
	if (!chks_copy(dst->ch, src->ch))
		return (tec_clear(dst, 1));
//	ft_printf("tec_copy : chk copy SUCCESS\n");
//	ft_printf("tec_copy : varr copy attempt\n");
//	varr_print(src->moves);
	if (!varr_copy(src->moves, &dst->moves))
		return (tec_clear(dst, 1));
//	if (!dst->moves)
//		return (tec_clear(dst, 1));
//	ft_printf("tec_copy : varr copy SUCCESS\n");
	dst->near_c = src->near_c;
	dst->near_cc = src->near_cc;
	if (dst->near_c)
		dst->near_c = dst->stk_ts.arr + (src->near_c - src->stk_ts.arr);
	if (dst->near_cc)
		dst->near_cc = dst->stk_ts.arr + (src->near_cc - src->stk_ts.arr);
	dst->cur_run = src->cur_run;
	dst->nb_moves = src->nb_moves;
//	ft_printf("tec_copy : exit SUCCESS\n");
	return (dst);
}
