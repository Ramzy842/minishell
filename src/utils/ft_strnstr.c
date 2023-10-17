/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 00:01:40 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/16 12:12:16 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strnstr( char *haystack, char *needle, int len)
{
	int	x;
	int	y;
	int	z;

	x = 0;
	if (!haystack && len == 0)
		return (0);
	if ((haystack[x] == '\0' && needle[x] == '\0'))
		return ((char *)(haystack + x));
	if (needle[x] == '\0')
		return ((char *)(haystack));
	while (haystack[x] != '\0' && x < len)
	{
		y = 0;
		z = x;
		while (haystack[z] == needle[y] && z < len)
		{
			if (needle[y + 1] == '\0')
				return ((char *)(haystack + x));
			y++;
			z++;
		}
		x++;
	}
	return (0);
}
