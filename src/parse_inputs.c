/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 07:06:27 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/13 17:27:36 by iamongeo         ###   ########.fr       */
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
	ft_printf("init push swap struct : entered\n");
	ps->stack_max = (int)strtab_len(nbs_strtab);
	if (!ft_malloc_p(sizeof(int) * ps->stack_max, (void **)&ps->stk_a.arr)
		|| !ft_malloc_p(sizeof(int) * ps->stack_max, (void **)&ps->stk_b.arr)
		|| !ft_malloc_p(sizeof(int) * ps->stack_max, (void **)&ps->stk_ref.arr))
		return (-1);
	ft_printf("init push swap struct : checks passed \n");
//	if (!ps->stk_a.arr || !ps->stk_b.arr || !ps->stk_ref.arr)
//		return (-1);
	ps->A = &ps->stk_a;
	ps->B = &ps->stk_b;
	ps->ref = &ps->stk_ref;
	ps->temp = &ps->stk_temp;
	ps->ch = &ps->chks;
	ps->stk_a.len = ps->stack_max;
	ps->stk_b.len = 0;
	ps->stk_ref.len = ps->stack_max;
	ps->stk_temp.len = 0;
	/*
	ps->nb_chks = ft_sqrt(ps->stack_max);
	ft_printf("init_ps_struct : ft_sqrt(stack_max) : %d\n", ps->nb_chks);
	ps->nb_chks -= ((ps->nb_chks * ps->nb_chks) > ps->stack_max);
	ps->chk_size = ps->stack_max / ps->nb_chks;
	ft_printf("init_ps_struct : chk size : %d\n", ps->chk_size);
	ps->last_chk_size = ps->stack_max - (ps->nb_chks * ps->chk_size);
	ps->nb_chks += (ps->last_chk_size > 0);
	ps->last_chk_size += (ps->last_chk_size == 0) * ps->chk_size;
	ft_printf("init_ps_struct : chk size : %d\n", ps->chk_size);
	ft_printf("init_ps_struct : last chk size : %d\n", ps->last_chk_size);
	ft_printf("init_ps_struct : ft_sqrt(stack_max) : %d\n", ps->stack_max);
	*/
	return (0);
}

static int	init_stacks(t_ps *ps, char **nbs_strtab)
{
	int	i;
	int	*arr;
	char	*digit1;
	ssize_t	nb;

	ft_printf("init stack : entered \n");
	if (!ps || !nbs_strtab || init_push_swap_struct(ps, nbs_strtab) < 0)
		return (-1);
	ft_printf("init stack : checks passed \n");
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

	ft_printf("parse input : Entered \n");
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
	{
		ft_printf("parse input : init_stack_failed\n");
		status = -1;
	}
	if (!status && doublon_and_limit_check(&ps->stk_a) < 0)
	{
		ft_printf("parse input : doublon limit failed\n");
		status = -1;
	}
	if (is_single_str)
		strtab_clear(&nbs_strtab);
	ft_printf("parse input : Exit. status : %d\n", status);
	return (status);
}
