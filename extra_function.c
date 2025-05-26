#include "mini.h"

int     is_set(char c, char *set)
{
    while (*set)
    {
        if (c == *set)
            return (1);
        set++;
    }
    return (0);
}

char        *ft_remove_space(char   *s1, char *set)
{
    int     i;
    int     end;
    int     start;
    char        *new_str;
    i = 0;
    start = 0;
    end = 0;
    while (s1[start] && is_set(s1[start], SEP))
        start++;
    end = ft_strlen(s1);
    while (end > start && is_set(s1[start], SEP))
        end--;
    new_str = malloc(sizeof(char) * (end - start + 1));
    if (!new_str)
        return (NULL);
    while (end > start)
        new_str[i++] = s1[start++];
    new_str[i] = '\0';
    return (new_str);
}

int is_sep(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
    unsigned int count;
    unsigned int i;

    count = 0;
    i = 0;
    while (src[count] != '\0')
        count++;
    while (src[i] != '\0' && i < size - 1)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (count);
}

char	*ft_substr(char *s, unsigned int start, int	len)
{
	char	*new_str;
	int	legnth_s;
	int	li_bghina_yb9aw;

	legnth_s = 0;
	if (!s)
		return (NULL);
	while (s[legnth_s])
		legnth_s++;
	li_bghina_yb9aw = 0;
	if (legnth_s > start)
		li_bghina_yb9aw = legnth_s - start;
	if (li_bghina_yb9aw > len)
		li_bghina_yb9aw = len;
	new_str = (char *)malloc(sizeof(char) * (li_bghina_yb9aw + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s + start, li_bghina_yb9aw + 1);
	return (new_str);
}

int ft_strlen(char *s)
{
	if (!s)
		return (0);
	int i = 0;
	while (s[i])
		i++;
	return i;
}




e_token get_token(char c, char next)
{
	if (c == '|')
		return PIPE;
	else if (c == '<' && next == '<')
		return HERDOK;
	else if (c == '>' && next == '>')
		return APPEND;
	else if (c == '<')
		return IN;
	else if (c == '>')
		return OUT;
	else if (c == '\0')
		return END;
    else
	    return NOT;
}

char	*ft_strchr(const char	*s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

int	skip_quotes(char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			return (i + 1);
		i++;
		s++;
	}
	return (0);
}

static void        ft_pustsr(char *s)
{
    write (1, s, ft_strlen(s));
}

void	add_redir_back(t_redir *node, t_redir **list)
{
	t_redir *tmp;

	if (!*list) 
    {
		*list = node;
		return;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

void add_node_back(t_token *new, t_token **list) 
{
	t_token *tmp;

	if (!*list) 
    {
		*list = new;
		return;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	ft_strncmp(const char	*s1, const char	*s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] -s2[i]);
}

void        print_token(t_token *curr)
{
    if (curr->type == PIPE)
        printf("PIPE\n");
    else if (curr->type == IN)
        printf ("<\n");
    else if (curr->type == OUT)
        printf(">\n");
    else if (curr->type == NOT)
        printf ("NOT\n");
    else if (curr->type == APPEND)
        printf ("APPEND\n");
    else if (curr->type == HERDOK)
        printf ("HERDOOK\n");
    else
        printf("UKNOW\n");
}

int     q_handler(char  *cmd)
{
    char        q;
    while (*cmd)
    {
        if (*cmd == '"' || *cmd == '\'')
        {
            q = *cmd++;
            while (*cmd && *cmd != q)
                cmd++;
            if (!(*cmd))
                return (0);
        }
        cmd++;
    }
    return (1);
}

static	int	is_char(char c, char charset)
{
	return (c == charset);
}

static	char	*ft_strcat(char *src, int start, int end)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (end - start + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < end - start)
	{
		res[i] = src[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	**ft_split(char *str, char charset)
{
	char	**res;
	int		start;
	int		i;
	int		k;

	i = 0;
	start = 0;
	k = 0;
	res = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	while (str[i])
	{
		while (str[i] && is_char(str[i], charset))
			i++;
		start = i;
		while (str[i] && !is_char(str[i], charset))
			i++;
		if (start < i)
			res[k++] = ft_strcat(str, start, i);
	}
	res[k] = NULL;
	return (res);
}

char	*ft_strjoin(char	*s1, char *s2)
{
	char	*str;
	int 	len1;
	int		len2;

	if (!s1 && !s2)
		return (NULL);
	if (s1)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	if (s2)
		len2 = ft_strlen(s2);
	else
		len2 = 0;
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);

	if (s1)
		ft_strlcpy(str, s1, len1 + 1);
	if (s2)
		ft_strlcpy(str + len1, s2, len2 + 1);
	return (str);
}
