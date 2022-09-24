/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stacks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 04:05:46 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/24 08:17:13 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

static void	print_header(void)
{
	ft_printf("                           (.)                          \n");
	ft_printf("                          ( + )                         \n");
	ft_printf("                        @(+{ }+)@                       \n");
	ft_printf("                      @(+{  +  }+)@                     \n");
	ft_printf("                    @(+{  +   +  }+)@                   \n");
	ft_printf("                 @@(+{  +  @-@  +  }+)@@                \n");
	ft_printf("              @@@(+)@(+{  @(+)@  }+)@(+)@@@             \n");
	ft_printf("         @@@@@@(+)@(+)@@   @-@   @@(+)@(+)@@@@@@        \n");
	ft_printf("     @@@@@@@@(+)@(+)@(+)@       @(+)@(+)@(+)@@@@@@@     \n");
	ft_printf("  @(@@@@@@@(+)@(+)@(+){ PUSH SWAP }(+)@(+)@(+)@@@@@@)@  \n");
	ft_printf(" @(@@@@@@                                      @@@@@@)@ \n");
	ft_printf("@(@@@~~~~~~~~~~~~~~~~~~~{ STACKS }~~~~~~~~~~~~~~~~~@@@)@\n");
	ft_printf("@(@            A            ||            B          @)@\n");
	ft_printf("@)@~~~~~~~~~~~~~~~~~~~~~~~~~||~~~~~~~~~~~~~~~~~~~~~~~@(@\n");
//	ft_printf("@(@                         ||                       @)@\n");
}

static void	print_bottom(void)
{
//	ft_printf("@)@                         ||                       @(@\n");
	ft_printf("@(@~~~~~~~~~~~~~~~~~~~~~~~~@||@~~~~~~~~~~~~~~~~~~~~~~@)@\n");
	ft_printf(" @(@@@@@~~~~~~~~~(+)~~~~~@@@@@@@~~~~~~(+)~~~~~~~~@@@@)@@\n");
	ft_printf("    @@@@@@@@@~~(+) (+)~~@@@(++)@@@~~(+) (+)~~@@@@@@@@   \n");
	ft_printf("          @@@@@@@(+)@@@@@(+)@@(+)@@@@@(+)@@@@@@         \n");
	ft_printf("                @@@@@@@@@@@(++)@@@@@@@@@@@              \n");
	ft_printf("                         @@@@@@@@                       \n");
	ft_printf("                           @@@@                         \n");
	ft_printf("                            @@                          \n");
}

void	print_stacks(t_ps *ps)
{
	t_stk	*A;
	t_stk	*B;
	int	i;
	int	max_len;

	A = ps->A;
	B = ps->B;
	max_len = A->len + ((B->len - A->len) * (B->len > A->len));
	print_header();
	i = -1;
	while (++i < max_len)
	{
		if (i < A->len && i < B->len)
			printf("@%c@          %13d  ||        %13d  @%c@\n",
				')' - (i % 2), A->arr[i], B->arr[i], '(' + (i % 2));
		else if (i < A->len)
			printf("@%c@          %13d  ||        %13s  @%c@\n",
				')' - (i % 2), A->arr[i], "", '(' + (i % 2));
		else if (i < B->len)
			printf("@%c@          %13s  ||        %13d  @%c@\n",
				')' - (i % 2), "", B->arr[i], '(' + (i % 2));
	}
	print_bottom();
}

void	print_ref_array(t_ps *ps)
{
	int	*arr;
	int	len;

	ft_printf("\nReference array :\n\t[ ");
	arr = ps->ref->arr;
	len = ps->stack_max;
	while (--len)
		ft_printf("%d, ", *(arr++));
	ft_printf("%d ]\n", *arr);
}
