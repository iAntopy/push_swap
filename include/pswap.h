/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pswap.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 05:32:59 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/19 21:41:55 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PSWAP_H
# define PSWAP_H

# include <stdlib.h>
# include <unistd.h>

# include "libft.h"

//# define eprintf(args...) fprintf(stderr, ##args)

# define PATH_THREASHOLD 2.0f / 100.0f

typedef struct	s_stack
{
	int		*arr;
	size_t	len;
}	t_stk;

typedef struct	s_chunk_stack
{
	t_varr	**chk_stk;
	t_varr	*cur_high;
	t_varr	*cur_low;
	int		i_high;
	int		i_low;
	int		nb_chks;
	int		chk_size;
	int		last_chk_size;
}	t_chks;

typedef struct s_test_stacks_env
{
	t_stk	stk_ts;
	t_stk	*ts;
	t_varr	*moves;
	t_varr	*members;
//	int		*near_c;
//	int		*near_cc;
	int		cur_run;
	int		nb_moves;
}	t_te;

typedef struct s_test_stacks_chunks_env
{
	t_chks	chks;
	t_stk	stk_ts;
	t_stk	*ts;
	t_chks	*ch;
	t_varr	*moves;
//	int		*near_c;
//	int		*near_cc;
	int		cur_run;
	int		nb_moves;
}	t_tec;

typedef struct s_push_swap
{
	int			stack_max;
	t_stk		stk_a;
	t_stk		stk_b;
	t_stk		stk_temp;
	t_chks		chks;
	t_stk		*A;
	t_stk		*B;
//	t_stk		*ref;
	t_stk		*temp;
	t_chks		*ch;
	t_varr		*shortest_mvs;
	t_varr		*shortest_mbrs;
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

////// MANAGER FUNCS ////////
int		psw_algo_manager(t_ps *ps);
int		parse_inputs(t_ps *ps, int argc, char **argv);
const char	*get_solution_for_high_chunk(t_varr *high_chk);

////// PATHFINDING FUNCS //////


////// PRINTER FUNCS ////////
void	print_stacks(t_ps *ps);
void	print_single_stack(t_stk *s);

////// CHECKER FUNCS /////////
int		stk_issorted(t_stk *s);
int		stk_seek_sorted_phase(t_ps *ps, t_stk *s);
int		stk_seek_rev_sorted_phase(t_ps *ps, t_stk *s);
int		stk_seek_rev_sorted_highs(t_ps *ps, int high);

////// PUSH SWAP BASIC SORTING ALGOS //////////
void	psw_sort2(t_ps *ps, t_stk *s);
void	psw_sort3(t_ps *ps, t_stk *s);
void	psw_sort4(t_ps *ps, t_stk *s);
int		psw_sort5(t_ps *ps);

////// ANALYSIS FUNCTION //////////
int		*find_value_in_stack(t_stk *s, int value);
int		*find_lowest(t_stk *s);
int		*find_highest(t_stk *s);
int		*find_in_stack(t_stk *s, int value);
int		*find_fst_chk_member_in_stk_clockwise(t_stk *s, t_stk *chk);
int		*find_fst_chk_member_in_stk_counter_clockwise(t_stk *s, t_stk *chk);
int		*find_fst_chks_member_in_stk_clockwise(t_stk *s, t_chks *chks);
int		*find_fst_chks_member_in_stk_counter_clockwise(t_stk *s, t_chks *chks);

int		distance_from_head(t_stk *s, int value);
int		distance_from_head_to_vptr(t_stk *s, int *vptr);
int		find_longest_sorted_sequence(t_stk *s, int **seq_start);
t_stk	*get_n_lowest_members(t_ps *ps, t_stk *s, size_t n);
t_stk	*get_n_highest_members(t_ps *ps, t_stk *s, size_t  n);
//int		get_nb_members_intersect(t_stk *large, t_stk *small);

///// STACK_MOVES ///////
void	psw_swap(t_stk *A, t_stk *B);
void	psw_push(t_stk *dst, t_stk *src, t_chks *chks);
void	psw_rotate(t_stk *A, t_stk *B, int reverse);
void	psw_move(t_ps *ps, int move);
void	psw_move_delta(t_ps *ps, t_stk *s, int delta);
void	psw_move_delta_push(t_ps *ps, t_stk *s, int delta);
void	psw_move_to(t_ps *ps, t_stk *s, int value);
void	psw_move_to_vptr(t_ps *ps, t_stk *s, int *vptr);
void	psw_recipe(t_ps *ps, int nb_moves, ...);

////// STACK UTILS ////////
int		stk_head(t_stk *s);
void	*stk_clear(t_stk **s);
t_stk	*stk_copy(t_stk *dst, t_stk *src);
//////////////////////////

///// CHUNK STACK UTILS ///////
t_chks	*chks_init(t_chks *chks, t_ps *ps);
t_chks	*chks_copy(t_chks *dst, t_chks *src);
void	*chks_clear(t_chks **chks);
void	chks_print(t_chks *chks);
t_varr	*chks_is_in_cur_chks(t_chks *chks, int value, t_varr **holder);
int		chks_are_empty(t_chks *chks);
///////////////////////////////

///// TEST STACK ENV FUNCS /////////
t_te	*te_init(t_te *te, t_stk *s);
void	te_print(t_te *te);
void	*te_clear(t_te *te);
void	*te_clear_all(t_te *te, t_te *te1, t_te *te2);
void	*te_copy(t_te *dst, t_te *src);
void	te_rotate(t_te *te, int rev);
void	te_push(t_te *te);
void	te_push_all_members_at_head(t_te *te, t_stk *sub);
void	te_move(t_te *te, int move);
//void	te_recipe(t_te *te, int nb_move, ...);
void	te_move_to(t_te *te, int value);
void	te_move_to_vptr(t_te *te, int *vptr);
void	te_move_delta(t_te *te, int delta);
void	te_move_delta_and_push_all_members(t_te *te, t_stk *sub, int delta);
void	te_find_deltas_to_addj_clusters(t_stk *stk, t_stk *sub, int *d1, int *d2);

///// TEST STACK CHUNKS ENV FUNCS /////////
t_tec	*tec_init(t_ps *ps, t_tec *tec, t_stk *s);
void	tec_print(t_tec *tec);
void	*tec_clear(t_tec *tec);
void	*tec_clear_all(t_tec *tec, t_tec *tec1, t_tec *tec2);
void	*tec_copy(t_tec *dst, t_tec *src);
void	tec_rotate(t_tec *tec, int rev);
void	tec_push(t_tec *tec);
void	tec_push_all_members_at_head(t_tec *tec, t_chks *ch);
void	tec_move(t_tec *tec, int move);
//void	tec_recipe(t_tec *tec, int nb_move, ...);
void	tec_move_to(t_tec *tec, int value);
void	tec_move_to_vptr(t_tec *tec, int *vptr);
void	tec_move_delta(t_tec *tec, int delta);
void	tec_move_delta_and_push_all_members(t_tec *tec, t_chks *ch, int delta);
void	tec_find_deltas_to_addj_clusters(t_stk *stk, t_chks *ch, int *d1, int *d2);

/////// PUSH_SWAP ALGORITHM FUNCS //////////
t_te	*te_seek_nearest_neighbors(t_te *te, t_te *te1, t_te *te2, int ori_len, int depth);
t_tec	*tec_seek_nearest_neighbors(t_tec *tec, t_tec *tec1, t_tec *tec2, int ori_len, int depth);
t_varr	*te_recursive_pathfinding(t_te *te, t_stk *sub, int ori_len, int depth);
t_varr	*tec_recursive_pathfinding(t_tec *tec, int depth);
t_varr	*path_to_n_extreme(t_ps *ps, t_stk *s, size_t n, int find_lowest);
t_varr	*optimal_push_a_to_b(t_ps *ps);
///////////////////////////////////////////

///// CLEAR FUNCS and ERROR HANDLING //////////
int		psw_clear(t_ps *ps, int status);
int		repport_error(void);

#endif
