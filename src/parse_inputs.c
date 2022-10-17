/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 07:06:27 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/17 04:16:18 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

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
	ps->temp = &ps->stk_temp;
	ps->ch = &ps->chks;
	ps->stk_a.len = ps->stack_max;
	ps->stk_b.len = 0;
	ps->stk_temp.len = 0;
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
	/*
	if (!status && init_stacks(ps, nbs_strtab) < 0)
	{
		ft_eprintf("parse input : init_stack_failed\n");
		status = -1;
	}
	if (!status && doublon_check(&ps->stk_a) < 0)
	{
		ft_eprintf("parse input : doublon limit failed\n");
		status = -1;
	}
	if (is_single_str)
		strtab_clear(&nbs_strtab);
	ft_printf("parse input : Exit. status : %d\n", status);
	return (status);
	*/
//}
