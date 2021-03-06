/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_and_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:57:43 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 17:04:43 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell42.h"
#include "get_input.h"

static void	free_get_input(t_edit *e)
{
	ft_strdel(&e->tmp);
	if (!e->hist)
		return ;
	while (e->hist->prev)
		e->hist = e->hist->prev;
	ft_strdel(&e->hist->s);
	if (e->hist->next)
		e->hist->next->prev = NULL;
	free(e->hist);
}

void		reset_tedit(t_edit *e)
{
	e->curr = 0;
	e->pos = 0;
	e->select = -1;
	e->select_pos = 0;
	e->edit = 1;
	e->pos_y = 0;
	e->pos_z = 0;
	e->hist->s = ft_strnew(3);
}

void		reset_get_input(t_edit *e)
{
	t_shell		*sh;

	sh = ft_get_set_shell(NULL);
	sh->env = ft_new_envv_int(sh->env, "?", 130, IN);
	ft_strdel(&e->tmp);
	if (!e->hist)
		return ;
	while (e->hist->prev)
		e->hist = e->hist->prev;
	ft_strdel(&e->hist->s);
	if (e->hist->next)
		e->hist->next->prev = NULL;
	free(e->hist);
}

void		gi_clear(t_edit *e)
{
	if (e->mode == 0 && e->tmp == NULL
		&& ft_get_set_shell(NULL)->heredoc == FALSE)
	{
		ft_delete_line(e);
		term_actions("ho");
		term_actions("cd");
		ft_disp(ft_get_set_shell(NULL));
		e->print_modes[e->mode](e);
	}
}

void		just_exit(t_edit *e)
{
	t_shell *sh;

	sh = ft_get_set_shell(NULL);
	if (e->edit == 1)
		return ;
	if ((!e->hist || !e->hist->s || !*e->hist->s))
	{
		if (sh->heredoc == 1)
		{
			sh->heredoc = 0;
			sh->e.edited = TRUE;
		}
		if (e->hist)
			free_get_input(e);
		e->hist = NULL;
	}
}
