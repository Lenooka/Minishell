/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:15:23 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/08 18:16:10 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_lstadd_front_b(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

char	*ft_strncpy(char *dest, char *s, int n)
{
	int	i;

	i = 0;
	while ((s[i] != '\0') && (i < n))
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strndupe(t_mini *mnshll, char *s, int n)
{
	char	*cs;

	cs = (char *)malloc(sizeof(char) * (n + 1));
	if (!cs)
	{
		mnshll->exit = 1;
		printf("Error: Malloc error!\n");
		return (NULL);
	}
	cs = ft_strncpy(cs, s, n);
	return (cs);
}
