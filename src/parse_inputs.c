/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 07:06:27 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/04 20:29:59 by iamongeo         ###   ########.fr       */
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

static char	*find_first_digit(char *str)
{
	if (!str || !(*str))
		return (NULL);
	while (*str && !ft_isdigit(*str))
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

static int	init_push_swap_struct(t_ps *ps, char **nbs_strtab)
{
	ps->stack_max = (int)strtab_len(nbs_strtab);
	malloc_free_p(sizeof(int) * ps->stack_max, (void **)&ps->stk_a.arr);
	malloc_free_p(sizeof(int) * ps->stack_max, (void **)&ps->stk_b.arr);
	malloc_free_p(sizeof(int) * ps->stack_max, (void **)&ps->stk_ref.arr);
	if (!ps->stk_a.arr || !ps->stk_b.arr || !ps->stk_ref.arr)
		return (-1);
	ps->A = &ps->stk_a;
	ps->B = &ps->stk_b;
	ps->ref = &ps->stk_ref;
	ps->temp = &ps->stk_temp;
	ps->stk_a.len = ps->stack_max;
	ps->stk_b.len = 0;
	ps->stk_ref.len = ps->stack_max;
	ps->stk_temp.len = 0;
	ps->chk_size = ft_sqrt(ps->stack_max);
	return (0);
}

static int	init_stacks(t_ps *ps, char **nbs_strtab)
{
	int	i;
	int	*arr;
	char	*digit1;
	ssize_t	nb;

	if (!ps || !nbs_strtab || init_push_swap_struct(ps, nbs_strtab) < 0)
		return (-1);
	arr = ps->stk_a.arr;
	i = -1;
	while (++i < ps->stack_max)
	{
		if (!validate_single_input(nbs_strtab[i]))
			return (-1);
		digit1 = find_first_digit(nbs_strtab[i]);
		nb = ft_atol(nbs_strtab[i]);
		if ((digit1 && *digit1 && *digit1 != '0' && !nb) || nb < INT_MIN || INT_MAX < nb)
		{
			printf("nb %zd failed ! Test1 %d, Test2 %d\n", nb, nb < INT_MIN, INT_MAX < nb);
			return (-1);
		}
		arr[i] = (int)nb;
	}
	return (0);
}

int	parse_inputs(t_ps *ps, int argc, char **argv)
{
	int		is_single_str;
	char	**nbs_strtab;
	int		status;

	nbs_strtab = NULL;
	status = 0;
	is_single_str = (ft_strchr(argv[1], ' ') != NULL);
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
