/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pswap.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 05:32:59 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/23 23:41:46 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PSWAP_H
# define PSWAP_H

# include <stdlib.h>
# include <unistd.h>

# include "libft.h"

typedef struct s_stack
{
	int	*arr;
	int	len;
}	t_stk;

typedef struct s_push_swap
{
	int		stack_max;
	int		*ref_array;	
	t_stk	stk_a;
	t_stk	stk_b;
	t_stk	stk_ref;
	t_stk	*A;
	t_stk	*B;
	t_stk	*ref;
	int		*__stk_mem;
}	t_ps;

enum	e_err_codes
{
	ERR_OCCURED = -1
};

int	parse_inputs(t_ps *ps, int argc, char **argv);
void	print_stacks(t_ps *ps);
void	print_ref_array(t_ps *ps);

////// REFFERENCE ARRAY FUNCS ////////// 
int	build_ref_array(t_ps *ps);

////// CHECKER FUNCS /////////
int	stk_issorted(t_stk *s);
int	stk_slice_issorted(t_stk *s, int start, int end);

////// REGULAR SORTING ALGOS //////////
void	garbage_sort(int *arr, int size);

///// STACK_MOVES ///////
void	psw_swap(t_stk *A, t_stk *B);
void	psw_push(t_stk *dst, t_stk *src);
void	psw_rotate(t_stk *A, t_stk *B, int reverse);

///// CLEAR FUNCS and ERROR HANDLING //////////
int	clear_ps(t_ps *ps, int status);
int	repport_error(void);

#endif
