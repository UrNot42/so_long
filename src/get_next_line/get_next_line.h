/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:53:47 by ulevallo          #+#    #+#             */
/*   Updated: 2023/03/23 06:30:52 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_buff_list	t_buff_list;

struct s_buff_list
{
	char		buff[BUFFER_SIZE + 1];
	size_t		size;
	int			nwln;
	int			read;
	t_buff_list	*next;
};

char		*get_next_line(int fd);
int			gnl_size(t_buff_list *node);
t_buff_list	*gnl_new_nd(t_buff_list *node);
char		*gnl_str_set(char **s, int size);
char		*gnl_lst_str(t_buff_list **node);
int			gnl_nwln(t_buff_list *node, int rd_status);
int			gnl_str_add(char *main, t_buff_list *node, int *index, int max);

#endif
