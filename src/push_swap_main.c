/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 07:424246:24 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/10 22:38:02 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

int	psw_clear(t_ps *ps, int status)
{
	stk_clear(ps->A);
	stk_clear(ps->B);
	stk_clear(ps->ref);
	stk_clear(ps->temp);
	varr_clear(&ps->shortest[0]);
	varr_clear(&ps->shortest[1]);
	chks_clear(&ps->chks);
	return (status);
}
/*
void	unittest_pswap_moves(t_ps *ps)
{
	ft_printf("\nInit stacks :\n");
	print_stacks(ps);
	
	psw_rotate(ps->A, NULL, 0);
	ft_printf("\nstacks after ra :\n");
	print_stacks(ps);
	
	psw_rotate(ps->A, NULL, 1);
	ft_printf("\nstacks after rra:\n");
	print_stacks(ps);
	
	psw_swap(ps->A, NULL);
	ft_printf("\nstacks after sa:\n");
	print_stacks(ps);
	
	psw_swap(ps->B, NULL);
	ft_printf("\nstacks after sb on empty b :\n");
	print_stacks(ps);
	
	psw_push(ps->B, ps->A);
	psw_push(ps->B, ps->A);
	psw_push(ps->B, ps->A);
	psw_push(ps->B, ps->A);
	ft_printf("\nstacks after multiple  pb on empty b :\n");
	print_stacks(ps);

	psw_swap(ps->A, ps->B);
	ft_printf("\nstacks after ss :\n");
	print_stacks(ps);
	
	psw_rotate(ps->A, ps->B, 0);
	ft_printf("\nstacks after rr :\n");
	print_stacks(ps);

	psw_rotate(ps->A, ps->B, 1);
	ft_printf("\nstacks after rrr :\n");
	print_stacks(ps);
}
*/
int	main(int argc, char **argv)
{
	const char	*strmoves[] = {
		"ra", "rb", "rr", "rra", "rrb", "rrr",
		"sa", "sb", "ss", "pa", "pb"};
	t_ps		ps;

	ft_printf("argv [1] : %s\n", argv[1]);
//	return (0);
	ft_memclear(&ps, sizeof(t_ps));
	if (parse_inputs(&ps, argc, argv) < 0)
		return (psw_clear(&ps, repport_error()));
	ft_printf("main : parse inputs SUCCESS\n");
	ps.strmoves = (char **)strmoves;
	ps.nb_moves = 0;
	ft_printf("\nInit stacks :\n");
	print_stacks(&ps);

	if (build_ref_array_and_substitute_in_stack_a(&ps) < 0)
		return (psw_clear(&ps, repport_error()));
	ft_printf("\n\nPost build refs print : \n");

//	print_ref_array(&ps);
	print_single_stack(ps.ref);
	if (psw_algo_manager(&ps) < 0)
		return (psw_clear(&ps, repport_error()));

	ft_printf("main : nb moves at exit : %d, to sort %d nbs.\n", ps.nb_moves, ps.stack_max);
	ft_printf("main : stacks at exit : \n");
	print_stacks(&ps);
	if (stk_issorted(ps.A))
		ft_printf("main : Is Stack A sorted : %s\n", GREEN_BC"TRUE"WHITE_C);
	else	
		ft_printf("main : Is Stack A sorted ? %s\n", RED_BC"FALSE"WHITE_C);
	return (psw_clear(&ps, EXIT_SUCCESS));
}
//	ft_printf("\n\nPre sort print : \n");
//	if (ps.stack_max == 3)
//		psw_sort3(&ps, ps.A);
//	else
//		psw_sort4(&ps, ps.A);
//	ft_printf("\n\nPost sort print : \n");
//	print_stacks(&ps);
//	ft_printf("nb moves at exit : %d\n", ps.nb_moves);

/*
	t_stk	*s;
	const int	n_lows = 2;

	s = get_n_lowest_members(&ps, ps.A, n_lows);
	ft_printf("get_n_lowest_members returned with ptr : %p\n", s);
	if (s)
	{
		ft_printf("print %d lowerest members of stack A : \n", n_lows);
		print_single_stack(ps.temp);
	}
	else
		ft_printf("get_n_lowest_members FAILED \n", s);
*/

/*
	psw_sort5(&ps);
	ft_printf("Stacks after sort5 : \n");
	print_stacks(&ps);
	ft_printf("Nb moves : %d\n", ps.nb_moves);
*/
/*
	if (!chks_init(&ps.chks, &ps))
	{
		ft_printf("main : chks_init FAILED\n");
		return (1);
	}
	ft_printf("main : chks init\n");
	chks_print(&ps.chks);

	t_chks	chks2;
	if (!chks_copy(&chks2, &ps.chks))
	{
		ft_printf("main : chks_copy FAILED\n");
		return (1);
	}
	ft_printf("main : chks copy : \n");
	chks_print(&chks2);

	t_varr	*optimal_path;
//	t_varr	*optimal_path = path_to_n_extreme(&ps, ps.A, 5, 0);
//	ft_printf("optimal_path ptr : %p \n", optimal_path);
//	varr_print(optimal_path);
//	varr_clear(&optimal_path);
	
	optimal_path = optimal_push_a_to_b(&ps);
	ft_printf("optimal push a to b path %p :\n", optimal_path);
	varr_print(optimal_path);
	varr_clear(&optimal_path);
//	ft_printf("dist from head to ref 0 : %d\n", distance_from_head(ps.A, 0));
//	ft_printf("dist from head to ref 1 : %d\n", distance_from_head(ps.A, 1));
//	ft_printf("dist from head to ref 2 : %d\n", distance_from_head(ps.A, 2));
//	ft_printf("dist from head to ref 3 : %d\n", distance_from_head(ps.A, 3));
//	ft_printf("dist from head to ref 4 : %d\n", distance_from_head(ps.A, 4));

	return (psw_clear(&ps, EXIT_SUCCESS));
}
*/
