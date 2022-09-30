/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_length_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:49:37 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/29 20:23:17 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Variable length array that somewhat acts like a linked list. Can be indexed,
// appended to other varrs, split, copied. int type only.
//
//
#define	VARR_CHUNK_LEN 256

typedef struct	s_variable_len_array
{
	int		*arr;
	size_t	len;
	size_t	__alloced_chks;
	size_t	__max_len;
	size_t	__curr_size;
}	t_varr;

// declare t_varr struct in some previous function and give ptr to this func.
t_varr	*varr_create(size_t n)
{
	t_varr	*va;
	int		div;
	int		mod;
	size_t	size;

	if (n < 1)
		return (NULL);
	div = n / VARR_CHUNK_LEN;
	mod = n % VARR_CHUNK_LEN;
	div += !!mod;
	size = sizeof(int) * VARR_CHUNK_LEN * div;
	if (!malloc_free_p(sizeof(t_varr), (void **)&va)
		|| !malloc_free_p(size, (void **)&va->arr))
		return (varr_clear(va));
	va->len = 0;
	va->__alloced_chunks = div;
	va->__max_len = div * VARR_CHUNK_LEN;
	va->__curr_size = size;
	return (va);
}

t_varr	*varr_clear(t_varr *va)
{
	if (!va)
		return (NULL);
	malloc_free_p(0, (void **)&va->arr);
	malloc_free_p(0, (void **)&va);
	return (NULL);
}

t_varr	*varr_copy(t_varr *src)
{
	t_varr	*va;

	va = varr_create(src->len);
	if (!va)
		return (NULL);
	ft_memcpy(va->arr, src->arr, src->__cur_size);
	return (va);
}

t_varr	*varr_append_int(t_varr *va, int n)
{
	int		*new_arr;
	size_t	new_size;
	size_t	old_size;

	if ((va->len + 1) > va->__max_len)
	{
		old_size = va->__curr_size;
		va->__alloced_chunks++;
		va->__max_len += VARR_CHUNK_LEN;
		new_size = va->__max_len * sizeof(int);
		if (!malloc_free_p(new_size, (void **)&new_arr))
			return (NULL);
		ft_memcpy(new_arr, va->arr, old_size);
		malloc_free_p(0, (void **)&va->arr);
		va->arr = new_arr;
		va->__curr_size = new_size;
	}
	va->arr[va->len++] = n;
	return (va);
}

t_varr	*varr_remove(t_varr *va, int i)
{
	int	*new_arr;
	size_t	new_size;
	size_t	old_size;

	old_size = va->__curr_size;
	new_size = old_size - sizeof(int) * VARR_CHUNK_LEN;
	if ((va->len - 2) < (old_size / sizeof(int)))
	{
		old_size = sizeof(int) * va->__alloced_chks * VARR_CHUNK_LEN;
		va->__alloced_chunks--;
		new_size = old_size - sizeof(int) * VARR_CHUNK_LEN;
		if (!malloc_free_p(sizeof(int) * va->__alloced_chks * VARR_CHUNK_LEN,
				(void **)&new_arr))
			return (NULL);
		va->arr = new_arr;
		va->__curr_size = new_size;
	}
	va->arr[va->len] = n;
	return (va);
}
