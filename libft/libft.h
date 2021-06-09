#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# ifndef DEBUG_MALLOC
#  define DEBUG_MALLOC 0
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

void					*ft_memset(void *s, int c, size_t n);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					*ft_memccpy(void *dest, const void *src,
							int c, size_t n);
void					*ft_memmove(void *dest, const void *src, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
size_t					ft_strlen(const char *s);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_strcmp(char *s1, char *s2);
size_t					ft_strlcpy(char *dest, const char *src, size_t size);
size_t					ft_strlcat(char *dest, const char *src, size_t size);
char					*ft_strnstr(const char *haystack,
							const char *needle, size_t n);
int						ft_atoi(const char *nptr);
long long				ft_atoll(const char *nptr, int *overflow);

void					*ft_calloc(size_t nmemb, size_t size);
char					*ft_strdup(const char *s);
char					*ft_substr(char const *s,
							unsigned int start, size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s, char const *set);
char					**ft_split(char const *s, char c);
void					*free_split(char **str);
char					*ft_itoa(int n);
char					*ft_strmapi(char const *s,
							char (*f)(unsigned int, char));
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);

struct					s_list
{
	void			*content;
	struct s_list	*previous;
	struct s_list	*next;
};

typedef struct s_list	t_list;

t_list					*ft_lstnew(void *content);
void					ft_lstadd_front(t_list **alst, t_list *new);
int						ft_lstsize(t_list *lst);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstadd_back(t_list **alst, t_list *new);
void					ft_lstdelone(t_list **elem, void (*del)(void*));
void					ft_lstclear(t_list **lst, void(*del)(void *));
void					ft_lstiter(t_list *lst, void(*f)(void *));

int						get_next_line(int fd, char **line);

void					*ft_alloc_mem(size_t size, int done,
							void **addr, int exit_code);
void					*ft_alloc(size_t size);
void					ft_exit_free(int exit_code);
void					ft_free_ptr(void **addr);

t_list					*ft_lstnew_alloc(void *content, t_list **arr_ptr);
void					ft_lstdelnode(t_list **elem, void (*del)(void *));
void					ft_clearallocs(t_list **lst, void (*del)(void*));
void					exit_gracefully(t_list **arr_ptr,
							int error, int exit_code);
void					*ft_malloc_err(size_t size);

int						get_next_line(int fd, char **line);

#endif
