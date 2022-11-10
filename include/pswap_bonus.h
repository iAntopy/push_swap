/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pswap_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:56:51 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/10 17:57:15 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PSWAP_BONUS_H
# define PSWAP_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_stack
{
	int		*arr;
	size_t	len;
}	t_stk;

typedef struct s_push_swap
{
	int			stack_max;
	t_stk		stk_a;
	t_stk		stk_b;
	t_stk		*a;
	t_stk		*b;
	t_stk		*temp;
	char		**strmoves;
	int			nb_moves;
}	t_ps;

enum	e_decoder
{
	M_RA = 0,
	M_RB = 1,
	M_RR = 2,
	M_RRA = 3,
	M_RRB = 4,
	M_RRR = 5,
	M_SA = 6,
	M_SB = 7,
	M_SS = 8,
	M_PA = 9,
	M_PB = 10
};

////// MANAGER FUNCS ////////
int			parse_inputs(t_ps *ps, int argc, char **argv);

////// CHECKER FUNCS /////////
int			stk_issorted(t_stk *s);
int			stk_seek_sorted_phase(t_ps *ps, t_stk *s);
int			stk_seek_rev_sorted_phase(t_ps *ps, t_stk *s);
int			stk_seek_rev_sorted_highs(t_ps *ps, int high);

///// STACK_MOVES ///////
void		psw_swap(t_stk *A, t_stk *B);
void		psw_push(t_stk *dst, t_stk *src);
void		psw_rotate(t_stk *A, t_stk *B, int reverse);
void		psw_move(t_ps *ps, int move);
void		psw_move_delta(t_ps *ps, t_stk *s, int delta);
void		psw_move_delta_push(t_ps *ps, t_stk *s, int delta);
void		psw_move_to(t_ps *ps, t_stk *s, int value);
void		psw_move_to_vptr(t_ps *ps, t_stk *s, int *vptr);
void		psw_recipe(t_ps *ps, int nb_moves, ...);

////// STACK UTILS ////////
int			stk_head(t_stk *s);
void		*stk_clear(t_stk **s);
t_stk		*stk_copy(t_stk *dst, t_stk *src);
//////////////////////////

///// CLEAR FUNCS and ERROR HANDLING //////////
int			psw_clear(t_ps *ps, int status);
int			repport_error(void);

#endif
