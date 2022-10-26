/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 23:16:35 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/26 14:52:44 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	malloc_free_p(size_t size, void **ptr)
{	
	if (size)
	{
		if (!ptr)
			return (0);
		*ptr = malloc(size);
		return (*ptr != NULL);
	}
	else if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (1);
}

int	ft_malloc_p(size_t size, void **ptr)
{
	void	*p;

	if (!ptr || !size)
		return (0);
	if (*ptr)
	{
		ft_eprintf("ft_malloc_p can only malloc if *ptr is NULL.");
		ft_eprintf(" Clear ptr then malloc\n");
	}
	p = malloc(size);
	*ptr = p;
	return (p != NULL);
}

// ft_malloc_p with safe ptr. The void **ptr given MUST be NULL or returns error.
int	ft_malloc_sp(size_t size, void **ptr)
{
	void	*p;

	if (!ptr || !size)
		return (0);
	p = NULL;
	if (*ptr)
	{
		ft_eprintf("ft_malloc_p can only malloc if *ptr is NULL.");
		ft_eprintf(" Clear ptr then malloc\n");
		return (0);
	}
	p = malloc(size);
	*ptr = p;
	return (p != NULL);
}

int	ft_free_p(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (1);
}
