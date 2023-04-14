/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 03:41:17 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/07 01:46:02 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_str_set(char **s, int size)
{
	*s = malloc(sizeof(char) * (size + 1));
	if (!(size - 1) || !(*s))
		return (NULL);
	(*s)[size - 1] = '\0';
	return (*s);
}

int	gnl_size(t_buff_list *node)
{
	t_buff_list	*cur;
	int			size;

	size = 0;
	cur = node;
	while (cur)
	{
		if (cur->nwln > 0)
			size += cur->nwln - gnl_nwln(cur, cur->read - 1);
		else if ((cur->nwln) == 0 && cur->read > 0)
			size += cur->size - gnl_nwln(cur, cur->read - 1);
		else
			size += cur->size;
		cur = cur->next;
	}
	return (size);
}

int	gnl_str_add(char *main, t_buff_list *node, int *index, int max)
{
	int	i;
	int	size;

	i = 0;
	size = node->size * (node->nwln <= 0) + node->nwln * (node->nwln > 0);
	if (node->read)
		i = gnl_nwln(node, node->read - 1);
	while (i < size)
	{
		main[*index] = node->buff[i++];
		if ((*index)++ == max)
			return (*index);
	}
	return (*index);
}

char	*gnl_lst_str(t_buff_list **node)
{
	char		*str;
	t_buff_list	*cur;
	t_buff_list	*old;
	int			index;
	int			size;

	size = gnl_size(*node);
	if (!gnl_str_set(&str, size + 1))
		return (free(str), NULL);
	cur = *node;
	index = 0;
	while (cur)
	{
		gnl_str_add(str, cur, &index, size - 1);
		cur->nwln = gnl_nwln(cur, cur->read + 1);
		cur->read++;
		old = cur;
		cur = cur->next;
		if (old->next)
			free(old);
	}
	*node = old;
	return (str);
}
