/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_stack_utils.c                    
chks_init_single_chk : Entered            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:08:49 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/05 19:42:15 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

void	chks_print(t_chks *chks)
{
	int	i;

	ft_printf("chks print : chks ptr %p, chk stk ptr %p\n", chks, chks->chk_stk);
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

void	*chks_clear(t_chks *chks)
{
	int		i;

	if (!chks || !chks->chk_stk)
		return (NULL);
	i = -1;
	while (++i < chks->nb_chks)
		varr_clear(chks->chk_stk + i);
	malloc_free_p(0, (void **)&chks->chk_stk);
	chks->cur_high = NULL;
	chks->cur_low = NULL;
	return (NULL);
}

t_chks	*chks_copy(t_chks *dst, t_chks *src)
{
	int		i;

	if (!dst || !src || !src->chk_stk)
		return (NULL);
	ft_printf("chks_copy : entered\n");
	ft_memclear(dst, sizeof(*dst));
	ft_printf("chks_copy : attempt malloc chk_stk\n");
	if (!malloc_free_p(sizeof(t_varr *) * src->nb_chks, (void **)&dst->chk_stk))
		return (NULL);
	ft_printf("chks_copy : malloc SUCCESSFULL\n");
	i = -1;
	while (++i < src->nb_chks)
	{
		dst->chk_stk[i] = varr_copy(src->chk_stk[i]);
		ft_printf("chks_copy : i = %d, varr_copy result ptr : %p\n", i, dst->chk_stk[i]);
		if (!dst->chk_stk[i])
			return (chks_clear(dst));
	}
	ft_printf("chks_copy : all varr_copy SUCCESSFULL\n");
	dst->i_high = src->i_high;
	dst->i_low = src->i_low;
	dst->cur_low = dst->chk_stk[dst->i_low];
	dst->cur_high = dst->chk_stk[dst->i_high];
	dst->nb_chks = src->nb_chks;
	dst->chk_size = src->chk_size;
	dst->last_chk_size = src->last_chk_size;
	return (dst);
}

static t_varr	*chks_init_single_chk(t_varr **chk, int *refs, int n)
{
	int		i;
	t_varr	*c;

	if (!chk || !refs)
		return (NULL);
	ft_printf("chks_init_single_chk : Entered\n");
	ft_printf("chks_init_single_chk : n = %d\n", n);
	c = varr_create(n);
	if (!c)
		return (NULL);
	ft_printf("chks_init_single_chk : varr (%p) creation SUCCESSFULL\n", c);
	i = -1;
	while (++i < n)
		varr_append(c, refs[i]);
	ft_printf("chks_init_single_chk : End of single init success :\n");
	varr_print(c);
	*chk = c;
	return (c);
}

t_chks	*chks_init(t_chks *chks, t_ps *ps)
{
	int		i;
	t_stk	*ref;

	ft_printf("chks_init : Entered \n");
	ft_printf("chks_init : nb_chks = %d, chk_size = %d \n", ps->nb_chks, ps->chk_size);
	if (!chks || !ps
		|| !malloc_free_p(sizeof(t_varr *) * ps->nb_chks, (void **)&chks->chk_stk))
		return (NULL);
	ft_printf("chks_init : malloced chk_stk (%p) SUCCESSFULL\n", chks->chk_stk);
	ft_printf("chks_init : clearing chk_stk\n");
	ft_memclear(chks->chk_stk, sizeof(t_varr *) * ps->nb_chks);
	ft_printf("chks_init : chk_stk after clear : %p\n", chks->chk_stk);
	ref = ps->ref;
	chks->nb_chks = ps->nb_chks;
	chks->chk_size = ps->chk_size;
	chks->last_chk_size = ps->last_chk_size;
	chks->i_low = (chks->nb_chks - 1) / 2;
	chks->i_high = chks->i_low + 1;
	i = -1;
	while (++i < (ps->nb_chks - 1))
		if (!chks_init_single_chk(chks->chk_stk + i,
				ref->arr + (i * ps->chk_size), ps->chk_size))
			return (chks_clear(chks));
	if (!chks_init_single_chk(chks->chk_stk + (chks->nb_chks - 1),
			ref->arr + ((chks->nb_chks - 1) * ps->chk_size), ps->last_chk_size))
		return (chks_clear(chks));
	chks->cur_low = chks->chk_stk[chks->i_low];
	chks->cur_high = chks->chk_stk[chks->i_high];
	ft_printf("chks_init : chk_stk at exit : %p\n", chks->chk_stk);
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
