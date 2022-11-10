/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randint_gen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:45:38 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/10 17:18:07 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
*	Creates an executable that generates random ints in a range that takes:
*		- 1. nb of ints to generate.
*		- 2. range lower limit
*		- 3. range higher limit.
*/
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
	size_t	i;
	int		value;

	i = -1;
	while (++i < (va->len - 1))
		if (varr_get(va, i, &value) == 0)
			ft_printf("%d ", value);
	if (varr_get(va, i, &value) == 0)
		ft_printf("%d\n", value);
}

int	main(int argc, char **argv)
{
	int		lims[2];
	t_varr	*va;
	size_t	n;

	if (argc < 4)
		return (1);
	lims[0] = ft_atoi(argv[2]);
	lims[1] = ft_atoi(argv[3]);
	n = ft_atoi(argv[1]);
	if (lims[0] >= lims[1] || !n || n > 1000 || n > (size_t)(lims[1] - lims[0]))
		return (2);
	va = varr_create(n);
	while (va->len < n)
		varr_append(va, get_unique_randint(va, lims[0], lims[1] - lims[0]));
	output_array(va);
	return (0);
}
