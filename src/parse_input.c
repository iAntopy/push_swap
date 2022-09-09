/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 07:06:27 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/09 03:19:32 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

int	validate_single_input(char *nb)
{
	int	i;

	i = -1;
	while (nb[++i])
	   if (!(ft_isdigit(nb[i]) || ft_issign(nb[i])))
		   return (0);
//	if (i > 9 || )
	return (1);
}

int	init_stacks(t_pswp *ps, char **nbs_strtab, int is_single_str)
{
	int	i;
	int	*arr;

	if (!ps || !nbs_strtab)
		return (-1);
	ps->stack_max = (int)strtab_len(nbs_strtab);
	if (!malloc_free_p(sizeof(int) * ps->stack_max, (void **)&ps->stk_a.arr))
		return (-1);
	if (!malloc_free_p(sizeof(int) * ps->stack_max, (void **)&ps->stk_b.arr))
		return (-1);
	arr = ps->stk_a.arr;
	i = -1;
	while (++i < ps->stack_max)
	{
		if (!validate_single_input(nbs_strtab[i]))
			return (-1);
		arr[i] = ft_atoi(nbs_strtab[i]);		
	}
	ps->stk_a.len = ps->stack_max;
	ps->stk_b.len = 0;
}

int	parse_inputs(t_pswp *ps, int argc, char **argv)
{
	int		is_single_str;
	char	**nbs_strtab;
	int		status;

	nb_strtab = NULL;
	status = 0;
	is_single_str = (ft_strchr(argv[1], ' ') != 0);
	if (is_single_str)
	{
		if (argc > 2)
			return(report_error());

		nbs_strtab = ft_split_space(argv[1]);
		if (!nbs_strtab || !(*(nbs_strtab)))
			status = -1;
	}
	else
		nbs_strtab = argv + 1;
	if (!status && init_stacks(ps, nbs_strtab, is_single_str) < 0)
		status = -1;
	if (is_single_str)
		strtab_clear(&nbs_strtab);
	if (status == -1)
		return (repport_error());
	return (0);
}
