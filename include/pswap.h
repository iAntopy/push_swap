/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pswap.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 05:32:59 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/09 03:30:51 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PSWAP_H
# define PSWAP_H

# include <stdlib.h>
# include <uni>

# include "libft.h"

typedef struct s_stack
{
	int	*arr;
	int	len;
}	t_stk;

typedef struct s_pswp
{
	int		stack_max;
	int		*ref_array;	
	t_stk	stk_a;
	t_stk	stk_b;

}	t_pswp;

enum	e_err_codes
{
	ERR_OCCURED = -1
};
#endif
