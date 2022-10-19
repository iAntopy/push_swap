/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_stack_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:28:32 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/18 17:42:19 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

/*
void	chks_print(t_chks *chks)
{
	int	i;

	if (!chks || !chks->chk_stk)
		return ;
	i = -1;
	ft_printf("\n*---------< CHUNK STACK >----------*\n");
	while (++i < chks->nb_chks)
	{
		ft_printf("|\t- %d : ", i);
		if (chks->chk_stk[i])
			varr_print(chks->chk_stk[i]);
		else
			ft_printf("No chunk.\n");
	}
	ft_printf("|\t---------------------------|\n");
	ft_printf("|\t- i_low = %d\n", chks->i_low);
	ft_printf("|\t- i_high = %d\n", chks->i_high);
	ft_printf("|\t- cur_low = %p\n", chks->cur_low);
	ft_printf("|\t- cur_high = %p\n", chks->cur_high);
	ft_printf("*----------------------------------*\n\n");
}
*/

void	*chks_clear(t_chks **chks_p)
{
	int		i;
	t_chks	*chks;

	if (!chks_p)
		return (NULL);
	chks = *chks_p;
	if (!chks || !chks->chk_stk)
		return (NULL);
	i = -1;
	while (++i < chks->nb_chks)
		varr_clear(chks->chk_stk + i);
	ft_free_p((void **)&chks->chk_stk);
	ft_memclear(chks, sizeof(t_chks));
	chks->cur_high = NULL;
	chks->cur_low = NULL;
	*chks_p = NULL;
	return (NULL);
}

t_chks	*chks_copy(t_chks *dst, t_chks *src)
{
	int		i;

	if (!dst || !src || !src->chk_stk)
		return (NULL);
	ft_memclear(dst, sizeof(*dst));
	if (!ft_calloc_p(sizeof(t_varr *) * src->nb_chks, (void **)&dst->chk_stk))
		return (NULL);
	i = -1;
	while (++i < src->nb_chks)
		if (!varr_copy(src->chk_stk[i], dst->chk_stk + i))
			return (chks_clear(&dst));
	dst->i_high = src->i_high;
	dst->i_low = src->i_low;
	dst->cur_low = dst->chk_stk[dst->i_low];
	dst->cur_high = dst->chk_stk[dst->i_high];
	dst->nb_chks = src->nb_chks;
	dst->chk_size = src->chk_size;
	dst->last_chk_size = src->last_chk_size;
	return (dst);
}

static t_varr	*chks_init_single_chk(t_varr **chk, size_t i, size_t n)
{
	t_varr	*c;

	if (!chk)
		return (NULL);
	c = varr_create(n);
	if (!c)
		return (NULL);
	while (n--)
		varr_append(c, i++);
	*chk = c;
	return (c);
}

static void	chks_init_data(t_chks *chks, t_ps *ps)
{
	size_t	n;
	size_t	sq_nb_chks;

	n = ps->stack_max - 5;
	chks->nb_chks = ft_sqrt(n);
	sq_nb_chks = chks->nb_chks * chks->nb_chks;
	chks->nb_chks -= (sq_nb_chks > n);
	chks->chk_size = n / chks->nb_chks;
	chks->last_chk_size = n - (chks->nb_chks * chks->chk_size);
	chks->nb_chks += (chks->last_chk_size > 0);
	chks->last_chk_size += (chks->last_chk_size == 0) * chks->chk_size;
	chks->i_low = chks->nb_chks / 2;
	chks->i_low -= (chks->i_low > 0);
	chks->i_high = chks->i_low + 1;
	chks->i_high -= (chks->i_high >= chks->nb_chks);
}

// Assumes stack A len > 5
t_chks	*chks_init(t_chks *chks, t_ps *ps)
{
	int		i;

	if (!chks || !ps)
		return (NULL);
	ft_memclear(chks, sizeof(t_chks));
	chks_init_data(chks, ps);
	if (!ft_calloc_p(sizeof(t_varr *) * chks->nb_chks, (void **)&chks->chk_stk))
		return (NULL);
	i = -1;
	while (++i < (chks->nb_chks - 1))
	{
		if (!chks_init_single_chk(chks->chk_stk + i,
				(i * chks->chk_size), chks->chk_size))
			return (chks_clear(&chks));
	}
	if (!chks_init_single_chk(chks->chk_stk + i,
			(i * chks->chk_size), chks->last_chk_size))
		return (chks_clear(&chks));
	chks->cur_low = chks->chk_stk[chks->i_low];
	chks->cur_high = chks->chk_stk[chks->i_high];
	return (chks);
}
//	while (++i < (ps->nb_chks - 1))
//	{
//		c = varr_create(ps->chk_size);
//		if (c)
//			return (chks_clear(chks));
//		chks->chk_stk[i] = c;
//		chks_copy_refs_in_chk(c, ref->arr + (i * ps->));
//		j = -1;
//		while (++j < ps->chk_size)
//			c->arr[j] = ref-;
//}
