/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 07:424246:24 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/24 08:18:45 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

int	clear_ps(t_ps *ps, int status)
{
	if (ps->stk_a.arr)
		malloc_free_p(0, (void **)&ps->stk_a.arr);
	if (ps->stk_b.arr)
		malloc_free_p(0, (void **)&ps->stk_b.arr);
	if (ps->stk_ref.arr)
		malloc_free_p(0, (void **)&ps->stk_ref.arr);
	return (status);
}

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

int	main(int argc, char **argv)
{
	const char	*strmoves[] = {
		"ra", "rb", "rr", "rra", "rrb", "rrr",
		"sa", "sb", "ss", "pa", "pb"};
	t_ps		ps;

	ft_memclear(&ps, sizeof(t_ps));
	if (parse_inputs(&ps, argc, argv) < 0)
		return (clear_ps(&ps, repport_error()));
	ps.strmoves = (char **)strmoves;
	ft_printf("\nInit stacks :\n");
	print_stacks(&ps);
	build_ref_array_and_substitute_in_stack_a(&ps);
	ft_printf("\n\nPost build refs print : \n");
	print_ref_array(&ps);
	print_stacks(&ps);
	print_ref_array(&ps);
	psw_sort3(&ps);
	ft_printf("\n\nPost sort3 print : \n");
	print_stacks(&ps);
	print_ref_array(&ps);
	return (clear_ps(&ps, EXIT_SUCCESS));
}
