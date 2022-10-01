/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pswap.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 05:32:59 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/30 23:39:46 by iamongeo         ###   ########.fr       */
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

typedef struct s_test_stacks_env
{
	t_stk	stk_ts;
	t_stk	*ts;
	t_varr	*moves;
	int		*near_c;
	int		*near_cc;
	int		cur_run;
	int		nb_moves;
}	t_te;

typedef struct s_push_swap
{
	int			stack_max;
	t_stk		stk_a;
	t_stk		stk_b;
	t_stk		stk_ref;
	t_stk		stk_temp;
	t_stk		*A;
	t_stk		*B;
	t_stk		*ref;
	t_stk		*temp;
	char		**strmoves;
	int			nb_moves;
}	t_ps;

enum	e_err_codes
{
	ERR_OCCURED = -1
};

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

int	parse_inputs(t_ps *ps, int argc, char **argv);
void	print_stacks(t_ps *ps);
void	print_single_stack(t_stk *s);
//void	print_ref_array(t_ps *ps);

////// REFFERENCE ARRAY FUNCS ////////// 
int	build_ref_array_and_substitute_in_stack_a(t_ps *ps);

////// CHECKER FUNCS /////////
int	stk_issorted(t_stk *s);
int	stk_seek_sorted_phase(t_ps *ps, t_stk *s);
int	stk_slice_issorted(t_stk *s, int start, int end);

////// REGULAR SORTING ALGOS //////////
void	garbage_sort(int *arr, int size);

////// PUSH SWAP SORTING ALGOS //////////
void	psw_sort2(t_ps *ps, t_stk *s);
void	psw_sort3(t_ps *ps, t_stk *s);
void	psw_sort4(t_ps *ps, t_stk *s);

////// ANALYSIS FUNCTION //////////
int	*find_value_in_stack(t_stk *s, int value);
int	*find_lowest(t_stk *s);
int	*find_highest(t_stk *s);
int	*find_in_stack(t_stk *s, int value);
int	*find_fst_chk_member_in_stk_clockwise(t_stk *s, t_stk *chk);
int	*find_fst_chk_member_in_stk_counter_clockwise(t_stk *s, t_stk *chk);

int	distance_from_head(t_stk *s, int value);
int	distance_from_head_to_vptr(t_stk *s, int *vptr);
int	find_longest_sorted_sequence(t_stk *s, int **seq_start);
t_stk	*get_n_lowest_members(t_ps *ps, t_stk *s, int n);

///// STACK UTILS ///////
void	*stk_clear(t_stk *s);
t_stk	*st_copy(t_stk *dst, t_stk *src);
/////////////////////////

///// STACK_MOVES ///////
void	psw_swap(t_stk *A, t_stk *B);
void	psw_push(t_stk *dst, t_stk *src);
void	psw_rotate(t_stk *A, t_stk *B, int reverse);
void	psw_move(t_ps *ps, int move);
void	psw_move_to(t_ps *ps, t_stk *s, int value);
void	psw_move_to_vptr(t_ps *ps, t_stk *s, int *vptr);
void	psw_recipe(t_ps *ps, int nb_moves, ...);

////// STACK UTILS ////////
void	*stk_clear(t_stk *s);
t_stk	*stk_copy(t_stk *dst, t_stk *src);
//////////////////////////

///// TEST ENV FUNCS /////////
void	te_rotate(t_te *te, int rev);
void	te_push(t_te *te);
void	te_move(t_te *te, int move);
void	te_recipe(t_te *te, int nb_move, ...);
void	te_move_to(t_te *te, int value);
void	te_move_to_vptr(t_te *te, int *vptr);


///// CLEAR FUNCS and ERROR HANDLING //////////
int	clear_ps(t_ps *ps, int status);
int	repport_error(void);

#endif
