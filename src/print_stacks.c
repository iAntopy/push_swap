/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stacks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 04:05:46 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/13 22:04:28 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap.h"

static void	print_header(void)
{
	eprintf("                           (.)\n");
	eprintf("                          ( + )\n");
	eprintf("                        @(+{ }+)@\n");
	eprintf("                      @(+{  +  }+)@\n");
	eprintf("                    @(+{  +   +  }+)@\n");
	eprintf("                 @@(+{  +  @-@  +  }+)@@\n");
	eprintf("              @@@(+)@(+{  @(+)@  }+)@(+)@@@\n");
	eprintf("         @@@@@@(+)@(+)@@   @-@   @@(+)@(+)@@@@@@\n");
	eprintf("     @@@@@@@@(+)@(+)@(+)@       @(+)@(+)@(+)@@@@@@@\n");
	eprintf("  @(@@@@@@@(+)@(+)@(+){ PUSH SWAP }(+)@(+)@(+)@@@@@@)@\n");
	eprintf(" @(@@@@@@                                      @@@@@@)@\n");
	eprintf("@(@@@~~~~~~~~~~~~~~~~~~~{ STACKS }~~~~~~~~~~~~~~~~~@@@)@\n");
	eprintf("@(@            A            ||            B          @)@\n");
	eprintf("@)@~~~~~~~~~~~~~~~~~~~~~~~~~||~~~~~~~~~~~~~~~~~~~~~~~@(@\n");
}

static void	print_bottom(void)

{
	eprintf("@(@~~~~~~~~~~~~~~~~~~~~~~~~@||@~~~~~~~~~~~~~~~~~~~~~~@)@\n");
	eprintf(" @(@@@@@~~~~~~~~~(+)~~~~~@@@@@@@~~~~~~(+)~~~~~~~~@@@@)@@\n");
	eprintf("    @@@@@@@@@~~(+) (+)~~@@@(++)@@@~~(+) (+)~~@@@@@@@@\n");
	eprintf("          @@@@@@@(+)@@@@@(+)@@(+)@@@@@(+)@@@@@@\n");
	eprintf("                @@@@@@@@@@@(++)@@@@@@@@@@@\n");
	eprintf("                         @@@@@@@@\n");
	eprintf("                           @@@@\n");
	eprintf("                            @@\n");
}

static void	print_header_single(void)
{
	ft_printf("                   (.)\n");
	ft_printf("                  ( + )\n");
	ft_printf("                @(+{ }+)@\n");
	ft_printf("              @(+{  +  }+)@\n");
	ft_printf("            @(+{  +   +  }+)@\n");
	ft_printf("          @(+{  +  @-@  +  }+)@\n");
	ft_printf("        @(+)@(+{  @(+)@  }+)@(+)@\n");
	ft_printf("     @@(+)@(+)@@   @-@   @@(+)@(+)@@\n");
	ft_printf("  @@@(+)@(+)@(+){       }(+)@(+)@(+)@@@\n");
	ft_printf("@(@(+)@(+)@(+){   STACK   }(+)@(+)@(+)@)@\n");
	ft_printf("@(@@@~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~@@@)@\n");
}

static void	print_bottom_single(void)
{
	ft_printf("@(@@@~~~~~~~~~~~~~~~@~~~~~~~~~~~~~~~~@@@)@\n");
	ft_printf(" @(@@@@~~~~(+)~~~~~@@@~~~~~(+)~~~~~@@@@)@\n");
	ft_printf("   @@@@@~(+) (+)~@@(+)@@~(+) (+)~@@@@@\n");
	ft_printf("        @@@(+)@@@(+)@(+)@@@(+)@@@\n");
	ft_printf("          @@@@@@@@@(+)@@@@@@@@@\n");
	ft_printf("                 @@@@@@@\n");
	ft_printf("                   @@@\n");
	ft_printf("                    @\n");
}

void	print_stacks(t_ps *ps)
{
	t_stk	*A;
	t_stk	*B;
	size_t	i;
	size_t	max_len;

	A = ps->A;
	B = ps->B;
	max_len = A->len + ((B->len - A->len) * (B->len > A->len));
	print_header();
	i = -1;
	while (++i < max_len)
	{
		if (i < A->len && i < B->len)
			eprintf("@%c@          %13d  ||        %13d  @%c@\n",
				')' - (int)(i % 2), A->arr[i], B->arr[i], '(' + (int)(i % 2));
		else if (i < A->len)
			eprintf("@%c@          %13d  ||        %13s  @%c@\n",
				')' - (int)(i % 2), A->arr[i], "", '(' + (int)(i % 2));
		else if (i < B->len)
			eprintf("@%c@          %13s  ||        %13d  @%c@\n",
				')' - (int)(i % 2), "", B->arr[i], '(' + (int)(i % 2));
	}
	print_bottom();
}

void	print_single_stack(t_stk *s)
{
	size_t	i;

	print_header_single();
	
	i = -1;
	while (++i < s->len)
		printf("@%c@          %10d                @%c@\n",
			')' - (int)(i % 2), s->arr[i], '(' + (int)(i % 2));
	print_bottom_single();
}
/*
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
*/
