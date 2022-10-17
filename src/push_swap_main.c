/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 07:424246:24 by iamongeo      #+#    #+#             */
/*   Updated: 2022/10/17 04:23:19 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

int	psw_clear(t_ps *ps, int status)
{
	stk_clear(&ps->A);
	stk_clear(&ps->B);
	stk_clear(&ps->temp);
	chks_clear(&ps->ch);
	varr_clear(&ps->shortest_mvs);
	varr_clear(&ps->shortest_mbrs);
	return (status);
}

int	replace_nbs_with_indices(t_stk *s)
{
	size_t	i;
	size_t	j;
	size_t	idx;
	int		*new;

	new = NULL;
	if (!s || !ft_calloc_p(sizeof(int) * s->len, (void **)&new))
		return (-1);
	i = -1;
	while (++i < s->len)
	{
		idx = 0;
		j = -1;
		while (++j < s->len)
			if (s->arr[j] < s->arr[i])
				idx++;
		new[i] = idx;
	}
	ft_free_p((void **)&s->arr);
	s->arr = new;
	return (0);
}

int	main(int argc, char **argv)
{
	const char	*strmoves[] = {
		"ra", "rb", "rr", "rra", "rrb", "rrr",
		"sa", "sb", "ss", "pa", "pb"};
	t_ps		ps;

	ft_memclear(&ps, sizeof(ps));
	ps.strmoves = (char **)strmoves;
	ps.nb_moves = 0;
	if (parse_inputs(&ps, argc, argv) < 0
		|| replace_nbs_with_indices(ps.A) < 0)
		return (psw_clear(&ps, repport_error()));
	print_stacks(&ps);
	if (psw_algo_manager(&ps) < 0)
		return (psw_clear(&ps, repport_error()));
	if (stk_issorted(ps.A))
		ft_printf("main : Is Stack A (%d) sorted after %d moves : %s\n",
			ps.stack_max, ps.nb_moves, GREEN_BC"TRUE"WHITE_C);
	else
		ft_printf("main : Is Stack A (%d) sorted after %d moves : %s\n",
			ps.stack_max, ps.nb_moves, RED_BC"FALSE"WHITE_C);
	return (psw_clear(&ps, EXIT_SUCCESS));
}
