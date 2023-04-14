/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 03:40:23 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/14 09:53:32 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buff_list	*gnl_new_nd(t_buff_list *node)
{
	if (node)
	{
		node->next = malloc(sizeof(t_buff_list));
		if (!node->next)
			return (NULL);
		node = node->next;
	}
	else
	{
		node = malloc(sizeof(t_buff_list));
		if (!node)
			return (NULL);
	}
	node->next = NULL;
	node->nwln = -1;
	node->size = 0;
	node->read = 0;
	return (node);
}

int	gnl_nwln(t_buff_list *node, int skip)
{
	size_t	index;
	int		i;

	i = 0;
	index = 0;
	if (skip < 0)
		return (0);
	while (index < node->size)
		if (node->buff[index++] == '\n')
			if (i++ == skip)
				return (index);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_buff_list	*head = NULL;
	t_buff_list			*node;
	int					rd_size;

	if (fd < 0)
		return (free(head), NULL);
	if (!head)
		head = gnl_new_nd(head);
	node = head;
	if (node->nwln <= 0)
		node = gnl_new_nd(head);
	while (node->nwln <= 0)
	{
		rd_size = read(fd, node->buff, BUFFER_SIZE);
		if (rd_size <= 0 || fd < 0)
			return (free(head->next), free(head), head = NULL, NULL);
		node->size = rd_size;
		node->nwln = gnl_nwln(node, 0);
		node->buff[rd_size] = '\0';
		if (node->nwln <= 0)
			node = gnl_new_nd(node);
	}
	return (gnl_lst_str(&head));
}
/*
//#include "time_files/nl_time.h"

int	main(int ac, char **av)
{
	char	*test;
	int		fd;

	if (ac != 2)
		fd = open("bible4.txt", O_RDONLY);
	else
		fd = open(av[1], O_RDONLY);
	// nl_time(NLT_START);
	// test = get_next_line(fd);
	// nl_time(NLT_PRINT | NLT_MICRO);
	test = get_next_line(fd);
	while (test)
	{
		printf("%s", test);
		free(test);
		test = get_next_line(fd);
	}
	free(test);
}
*/
