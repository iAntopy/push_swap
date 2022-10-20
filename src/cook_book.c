/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recipe_book.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:39:03 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/18 17:46:07 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

static const char	*recipe_finder_chapter1(const char *book[24], int *hc)
{
	if (hc[0] == 3 && hc[1] == 2 && hc[2] == 1 && hc[3] == 0)
		return (book[0]);
	else if (hc[0] == 3 && hc[1] == 2 && hc[2] == 0 && hc[3] == 1)
		return (book[1]);
	else if (hc[0] == 3 && hc[1] == 1 && hc[2] == 2 && hc[3] == 0)
		return (book[2]);
	else if (hc[0] == 3 && hc[1] == 1 && hc[2] == 0 && hc[3] == 2)
		return (book[3]);
	else if (hc[0] == 3 && hc[1] == 0 && hc[2] == 2 && hc[3] == 1)
		return (book[4]);
	else if (hc[0] == 3 && hc[1] == 0 && hc[2] == 1 && hc[3] == 2)
		return (book[5]);
	else if (hc[0] == 2 && hc[1] == 3 && hc[2] == 1 && hc[3] == 0)
		return (book[6]);
	else if (hc[0] == 2 && hc[1] == 3 && hc[2] == 0 && hc[3] == 1)
		return (book[7]);
	else if (hc[0] == 2 && hc[1] == 1 && hc[2] == 3 && hc[3] == 0)
		return (book[8]);
	else if (hc[0] == 2 && hc[1] == 1 && hc[2] == 0 && hc[3] == 3)
		return (book[9]);
	else if (hc[0] == 2 && hc[1] == 0 && hc[2] == 3 && hc[3] == 1)
		return (book[10]);
	else if (hc[0] == 2 && hc[1] == 0 && hc[2] == 1 && hc[3] == 3)
		return (book[11]);
	return (NULL);
}

static const char	*recipe_finder_chapter2(const char *book[24], int *hc)
{
	if (hc[0] == 1 && hc[1] == 3 && hc[2] == 2 && hc[3] == 0)
		return (book[12]);
	else if (hc[0] == 1 && hc[1] == 3 && hc[2] == 0 && hc[3] == 2)
		return (book[13]);
	else if (hc[0] == 1 && hc[1] == 2 && hc[2] == 3 && hc[3] == 0)
		return (book[14]);
	else if (hc[0] == 1 && hc[1] == 2 && hc[2] == 0 && hc[3] == 3)
		return (book[15]);
	else if (hc[0] == 1 && hc[1] == 0 && hc[2] == 3 && hc[3] == 2)
		return (book[16]);
	else if (hc[0] == 1 && hc[1] == 0 && hc[2] == 2 && hc[3] == 3)
		return (book[17]);
	else if (hc[0] == 0 && hc[1] == 3 && hc[2] == 2 && hc[3] == 1)
		return (book[18]);
	else if (hc[0] == 0 && hc[1] == 3 && hc[2] == 1 && hc[3] == 2)
		return (book[19]);
	else if (hc[0] == 0 && hc[1] == 2 && hc[2] == 3 && hc[3] == 1)
		return (book[20]);
	else if (hc[0] == 0 && hc[1] == 2 && hc[2] == 1 && hc[3] == 3)
		return (book[21]);
	else if (hc[0] == 0 && hc[1] == 1 && hc[2] == 3 && hc[3] == 2)
		return (book[22]);
	else if (hc[0] == 0 && hc[1] == 1 && hc[2] == 2 && hc[3] == 3)
		return (book[23]);
	return (NULL);
}

const char	*get_solution_for_high_chunk(t_varr *high_chk)
{
	static const char	*cook_book[24] = {
		"pppp", "pp", "ppps", "p", "p", "p",
		"pps", "pps", "pp+ps-",	"ppp++ps--", "pp+psp-", "pp+p+ps--",
		"ppsps", "ppsp+ps-", "p+pps-", "ppp+s+ps--", "pp++pp--", "pp++pps--",
		"p+ppp-", "p+ppps-", "p+ppsp-", "p+pp+ps--", "p+ppsps-", "p+p+pps--"
	};
	const char			*recipe;

	recipe = recipe_finder_chapter1(cook_book, high_chk->arr);
	if (!recipe)
		return (recipe_finder_chapter2(cook_book, high_chk->arr));
	else
		return (recipe);
}
