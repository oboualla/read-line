/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 03:43:41 by oboualla          #+#    #+#             */
/*   Updated: 2019/11/14 19:05:41 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_LINE_H
# define READ_LINE_H
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include <dirent.h>
# define KP 4283163
# define KD 4348699
# define KL 4479771
# define KR 4414235
# define BS 127
# define HM 4741915
# define ED 4610843
# define READ_SIZE	1000
# define LINE_SIZE	1024
# define ALT_L		1146821403
# define ALT_R		1130044187
# define ALT_P		1096489755
# define ALT_D		1113266971

typedef struct winsize t_winsize;
typedef struct termios t_termios;
typedef struct s_readl t_readl;
typedef unsigned short ushort;
typedef struct s_capab t_capab;
typedef struct s_curpos t_curpos;
typedef struct dirent t_dirent;
typedef struct stat t_stat;
typedef struct s_objet t_objet;
typedef struct s_hist t_hist;

struct s_hist
{
	char	*line;
	t_hist	*next;
	t_hist	*back;
};

struct s_readl
{
	ushort          ws_col;
	ushort          ws_row;
	size_t          prompt_len;
	size_t          curpos;
};

struct s_capab
{
	char *move_left;
	char *move_right;
	char *move_up;
	char *move_down;
	char *show_curs;
	char *hide_curs;
	char *begin_curs;
	char *clear_line;
};

struct s_objet
{
	char	line[LINE_SIZE];
	char	*prompt;
	t_readl	rd;
	t_capab *tc;
};

struct s_curpos
{
	ushort	x;
	ushort	y;
};

char *ft_readline(const char *prompt);

t_objet **save_objet(t_objet *objet);

//signal 
void    init_sig(void);

//termcap 
int init_tc(t_capab **tc);
int init_mode(void);

//init struct objet
t_objet *init_objet(const char *prompt);
char    *exit_readline(t_objet **objet, t_hist **lst, int flag);

//history
void    init_hist(t_hist **lst);
void    stock_hist(t_hist **lst);
void    add_hist(char *line, t_hist **lst);
void    kp(t_hist **lst, t_objet *obj);
void    kd(t_hist **lst, t_objet *obj);
t_hist	*make_node(char *line);

//auto_complition
int     auto_c(t_objet *obj);

//key
void 	kl(t_objet *obj);
void	kr(t_objet *obj);
void    hm(t_objet *obj);
void    ed(t_objet *obj);
void    bs(t_objet *obj);
void    to_next_line(t_capab *tc, ushort flag);
void    to_up_line(t_capab *tc);
int		alt_key(t_objet *obj, unsigned int cast);
int		arrow_key(t_objet *objet, t_hist **lst, unsigned int cast);
int		other_key(t_objet *objet, unsigned int cast);

//cursor position
t_curpos	get_curpos(t_readl rd);
void	curs_newpos(t_curpos curpos, t_curpos newpos, t_capab *tc);

//re affiche
void    bs_print(char *line, t_readl rd, t_capab *tc);
void    l_print(char *line, t_readl *rd, t_capab *tc, size_t bufsize);
void    reprint(char *line, t_readl rd, t_capab *tc);
#endif
