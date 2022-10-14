/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randint_gen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:45:38 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/13 23:14:46 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_unique_randint(t_varr *va, int min, int range)
{
	int	r;

	r = ft_randint(min, range);
	while (varr_is_in(va, r))
		r = ft_randint(min, range);
	return (r);
}

void	output_array(t_varr *va)
{
	int	i;
	int	value;

	i = -1;
	while (++i < (va->len - 1))
	{
		if (varr_get(va, i, &value) == 0)
			ft_printf("%d ", value);
	}
	if (varr_get(va, i, &value) == 0)
		ft_printf("%d\n", value);
}

int	main(int argc, char **argv)
{
	int	start;
	int	end;
	t_varr	*va;
	int	i;
	size_t	n;
	int		r;

	if (argc < 4)
		return (1);
	start = ft_atoi(argv[2]);
	end = ft_atoi(argv[3]);
	n = ft_atoi(argv[1]);
	if (start >= end || !n || n > 1000)
		return (2);
	va = varr_create(n);
	while (va->len < n)
		varr_append(va, get_unique_randint(va, start, end - start));
	output_array(va);
	return (0);
}
