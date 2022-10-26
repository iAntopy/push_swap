/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 04:54:44 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/26 04:55:36 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap_bonus.h"

static int	validate_single_input(char *nb)
{
	int	i;

	i = -1;
	while (nb[++i])
		if (!(ft_isdigit(nb[i]) || ft_issign(nb[i]))
			|| (ft_issign(nb[i]) && !ft_isdigit(nb[i + 1]))
			|| (i > 0 && ft_issign(nb[i]) && !ft_isspace(i - 1)))
			return (0);
	return (1);
}

static int	duplicate_check(t_stk *A)
{
	int	i;
	int	j;
	int	stack_max;
	int	*arr;

	stack_max = A->len;
	arr = A->arr;
	i = -1;
	while (++i < stack_max)
	{
		j = i;
		if (i < (stack_max - 1))
			while (++j < stack_max)
				if (arr[i] == arr[j])
					return (-1);
	}
	return (0);
}

static int	init_push_swap_struct(t_ps *ps, char **nbs_strtab)
{
	ps->stack_max = (int)strtab_len(nbs_strtab);
	if (!ft_malloc_p(sizeof(int) * ps->stack_max, (void **)&ps->stk_a.arr)
		|| !ft_malloc_p(sizeof(int) * ps->stack_max, (void **)&ps->stk_b.arr))
		return (-1);
	ps->A = &ps->stk_a;
	ps->B = &ps->stk_b;
	ps->stk_a.len = ps->stack_max;
	ps->stk_b.len = 0;
	return (0);
}

static int	init_ps_struct_and_stacks(t_ps *ps, char **nbs_tab)
{
	int		i;
	char	*digit1;
	ssize_t	nb;

	if (!ps || !nbs_tab || !(*nbs_tab)
		|| init_push_swap_struct(ps, nbs_tab) < 0)
		return (-1);
	i = -1;
	while (++i < ps->stack_max)
	{
		if (!validate_single_input(nbs_tab[i]))
			return (-1);
		digit1 = nbs_tab[i];
		while (digit1 && *digit1 && !ft_isdigit(*digit1))
			digit1++;
		nb = ft_atol(nbs_tab[i]);
		if ((digit1 && *digit1 && *digit1 != '0' && nb == 0)
			|| (nb < INT_MIN) || (INT_MAX < nb))
			return (-1);
		ps->A->arr[i] = (int)nb;
	}
	return (duplicate_check(ps->A));
}

int	parse_inputs(t_ps *ps, int argc, char **argv)
{
	char	**nbs_strtab;

	nbs_strtab = NULL;
	if (ft_strchr(argv[1], ' ') != NULL)
	{
		if (argc > 2)
			return (-1);
		nbs_strtab = ft_split_space(argv[1]);
		if (init_ps_struct_and_stacks(ps, nbs_strtab) < 0)
		{
			strtab_clear(&nbs_strtab);
			return (-1);
		}
		strtab_clear(&nbs_strtab);
	}
	else if (init_ps_struct_and_stacks(ps, argv + 1) < 0)
		return (-1);
	return (0);
}
