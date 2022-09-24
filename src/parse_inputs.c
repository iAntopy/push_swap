/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 07:06:27 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/23 22:52:20 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

static int	validate_single_input(char *nb)
{
	int	i;

	i = -1;
	while (nb[++i])
	   if (!(ft_isdigit(nb[i]) || ft_issign(nb[i])))
		   return (0);
	return (1);
}

static char	*find_first_digit(char *str)
{
	while (!ft_isdigit(*str))
		str++;
	return (str);
}

static int	doublon_and_limit_check(t_stk *A)
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
		if (arr[i] < INT_MIN || INT_MAX < arr[i])
			return (-1);
		j = i;
		if (i != (stack_max - 1))
			while (++j < stack_max)
				if (arr[i] == arr[j])
					return (-1);
	}
	return (0);
}

static int	init_stacks(t_ps *ps, char **nbs_strtab)
{
	int	i;
	int	*arr;
	char	*digit1;

	if (!ps || !nbs_strtab)
		return (-1);
	ps->stack_max = (int)strtab_len(nbs_strtab);
	if (!malloc_free_p(3 * sizeof(int) * ps->stack_max, (void **)&ps->__stk_mem))//stk_a.arr))
		return (-1);
	ps->stk_a.arr = ps->__stk_mem;
	ps->stk_b.arr = ps->__stk_mem + (sizeof(int) * ps->stack_max);
	ps->stk_ref.arr = ps->__stk_mem + (2 * sizeof(int) * ps->stack_max);
	ps->A = &ps->stk_a;
	ps->B = &ps->stk_b;
	arr = ps->stk_a.arr;
	i = -1;
	while (++i < ps->stack_max)
	{
		if (!validate_single_input(nbs_strtab[i]))
			return (-1);
		digit1 = find_first_digit(nbs_strtab[i]);
		arr[i] = ft_atol(nbs_strtab[i]);
		if (*digit1 && !arr[i])
			return (-1);
	}
	ps->stk_a.len = ps->stack_max;
	ps->stk_b.len = 0;
	ps->stk_ref.len = ps->stack_max;
	return (0);
}

int	parse_inputs(t_ps *ps, int argc, char **argv)
{
	int		is_single_str;
	char	**nbs_strtab;
	int		status;

	nbs_strtab = NULL;
	status = 0;
	is_single_str = (ft_strchr(argv[1], ' ') != 0);
	if (is_single_str)
	{
		if (argc > 2)
			return(repport_error());

		nbs_strtab = ft_split_space(argv[1]);
		if (!nbs_strtab || !(*(nbs_strtab)))
			status = -1;
	}
	else
		nbs_strtab = argv + 1;
	if (!status && init_stacks(ps, nbs_strtab) < 0)
		status = -1;
	if (!status && doublon_and_limit_check(&ps->stk_a) < 0)
		status = -1;
	if (is_single_str)
		strtab_clear(&nbs_strtab);
	return (status);
}
