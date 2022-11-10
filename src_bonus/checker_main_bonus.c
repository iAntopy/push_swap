/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_main_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 03:19:53 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/10 17:54:02 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pswap_bonus.h"

int	psw_clear(t_ps *ps, int status)
{
	stk_clear(&ps->a);
	stk_clear(&ps->b);
	return (status);
}

int	stk_issorted(t_stk *s)
{
	size_t	i;

	i = -1;
	while (++i < (s->len - 1))
		if (s->arr[i] > s->arr[i + 1])
			return (0);
	return (1);
}

int	get_move_idx(t_ps *ps, char *s_move)
{
	int	i;

	if (!ps || !s_move)
		return (-1);
	i = -1;
	while (++i < 11)
	{
		if (ft_strcmp(s_move, ps->strmoves[i]) == 0)
			return (i);
	}
	return (-1);
}

int	read_and_exec_moves(t_ps *ps)
{
	char	*s_move;
	int		i_move;
	char	*new_line_p;

	while (1)
	{
		s_move = get_next_line(0);
		if (!s_move)
			break ;
		new_line_p = ft_strrchr(s_move, '\n');
		if (new_line_p)
			*new_line_p = '\0';
		i_move = get_move_idx(ps, s_move);
		ft_free_p((void **)&s_move);
		if (i_move < 0)
			return (-1);
		psw_move(ps, i_move);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	const char	*strmoves[] = {
		"ra", "rb", "rr", "rra", "rrb", "rrr",
		"sa", "sb", "ss", "pa", "pb"};
	t_ps		ps;

	if (argc < 2)
		return (0);
	ft_memclear(&ps, sizeof(ps));
	ps.strmoves = (char **)strmoves;
	ps.nb_moves = 0;
	if (parse_inputs(&ps, argc, argv) < 0)
		return (psw_clear(&ps, repport_error()));
	if (read_and_exec_moves(&ps) < 0)
		return (psw_clear(&ps, repport_error()));
	if (ps.b->len == 0 && stk_issorted(ps.a))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	return (psw_clear(&ps, EXIT_SUCCESS));
}
