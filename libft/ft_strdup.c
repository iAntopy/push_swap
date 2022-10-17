/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:52:47 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/16 22:39:40 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dup;
	char	*d;
	size_t	str_len;

	str_len = ft_strlen(str);
	dup = NULL;
	if (!ft_malloc_p(sizeof(char) * (str_len + 1), (void **)&dup))
		return (NULL);
	d = dup;
	while (*str)
		*(d++) = *(str++);
	dup[str_len] = '\0';
	return (dup);
}
