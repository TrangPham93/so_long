/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:07:19 by trpham            #+#    #+#             */
/*   Updated: 2025/03/01 14:47:51 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*substr;
	size_t	substr_len;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start < len)
		substr_len = s_len - start;
	else
		substr_len = len;
	// if (s_len - start <= len)
	// 	substr = malloc(s_len - start + 1);
	// else
	substr = malloc(substr_len + 1);
	if (!substr)
		return (NULL);
	while (i < substr_len && s[start + i] != '\0')
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
// #include <stdio.h>

// int	main(void)
// {
// 	char *test1 = ft_substr("Hello, world!", 7, 5);
// 	char *test2 = ft_substr("Hello, world!", 0, 20);
// 	char *test3 = ft_substr("Hello, world!", 20, 5);
// 	char *test4 = ft_substr("Hello", 3, 10);
	
// 	printf("Test 1: %s\n", test1); // Expected: "world"
// 	printf("Test 2: %s\n", test2); // Expected: "Hello, world!"
// 	printf("Test 3: %s\n", test3); // Expected: "" (empty string)
// 	printf("Test 4: %s\n", test4); // Expected: "lo"

// 	free(test1);
// 	free(test2);
// 	free(test3);
// 	free(test4);
// }
