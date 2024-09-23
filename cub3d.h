#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

/*	----- Libraries -----	*/
# include "mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

/*	----- Color macros -----	*/
# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define CRESET "\e[0m"

/*	----- Game macros -----	*/
# define TILE 64
# define WIDTH 720
# define HEIGHT 480
# define FOV 1.0472
# define STEP 5
# define ERR_MARG 0.000001

/*	----- Control macros -----	*/
# define KEY_ESC 53
# define KEY_EVENT_PRESS 2
# define KEY_EVENT_EXIT 17
# define R_L 123
# define R_R 124
# define W 13
# define A 0
# define S 1
# define D 2

typedef struct s_parsing
{
	int		i;
	int		j;
	int		k;
	int		l;
	int		no;
	int		so;
	int		we;
	int		ea;
	char	*eatxt;
	char	*wetxt;
	char	*notxt;
	char	*sotxt;
	int		f;
	int		c;
	int		fd;
	int		erroronthemap;
	int		atoitest;
	char	**tab;
	char	**namecheck;
	int		count;
	char	*maptmp;
	char	**tabmaptmp;
	char	**tmp;
	char	**tmpcheck;
	char	**colorcheck;
	char	*notab;
	char	*sotab;
	char	*wetab;
	char	*eatab;
	char	*ftab;
	char	*ctab;
}			t_parsing;

/*	----- MiniLibX -----	*/
typedef struct s_img
{
	void	*img;
	int		*data;
	char	*addr;
	int		bpp;
	int		line_size;
	int		endian;
}				t_img;

/*	----- Player's coordinates -----	*/
typedef struct s_plr
{
	double	x;
	double	y;
	double	agl;
}				t_plr;

/*	-----	Raycasting -----	*/
typedef struct s_ray
{
	double	ax;
	double	bx;
	double	ay;
	double	by;
	double	fin_x;
	double	fin_y;
	double	distance;
	double	height;
	int		vertical;
	double	plane;

}				t_ray;

/*	----- Textures -----	*/
typedef struct s_txt
{
	void	*no;
	void	*so;
	void	*ea;
	void	*we;
	int		*a_no;
	int		*a_so;
	int		*a_ea;
	int		*a_we;
	int		*a_fnl;
	int		img_w;
	int		img_h;
	int		bpp_2;
	int		len;
	int		end;
	int		txt_x;
	int		txt_y;
}	t_txt;

/*	----- Colors -----	*/
typedef struct s_rgb
{
	double	floor_r;
	double	floor_g;
	double	floor_b;
	double	ceil_r;
	double	ceil_g;
	double	ceil_b;
}				t_rgb;

/*	-----	Movements -----	*/
typedef struct s_moves
{
	double	d_x;
	double	d_y;
	double	i;
	double	j;
	double	len;
}				t_moves;

/*	----- Game informations -----	*/
typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			row;
	int			col;
	t_img		img;
	t_plr		plr;
	t_ray		ray[WIDTH];
	double		fin_x;
	double		fin_y;
	double		distance;
	char		player;
	t_txt		txtr;
	t_rgb		rgb;
	t_moves		moves;
	t_parsing	parsing;
}				t_game;

/*	-----	keys	-----	*/
/*	exit.c	*/
int		exit_button(void);
/*	keys.c	*/
int		key_press(int keycode, t_game *game);
/*	-----	moves	-----	*/
/*	movements.c	*/
void	forward(t_game *game);
void	backward(t_game *game);
void	left(t_game *game);
void	right(t_game *game);
/*	rotations.c	*/
double	add_angle(double start_agl, double delta_agl);
void	rotate_r(t_game *game);
void	rotate_l(t_game *game);
/*	-----	raycast	-----	*/
/*	h_walls.c	*/
int		check_h_wall(t_game *game, double angle, t_ray *ray, double *incr_y);
int		check_h_exists(t_game *game, t_ray *ray);
void	h_wall(t_game *game, double angle, t_ray *ray);
/*	v_walls.c	*/
int		check_v_wall(t_game *game, double angle, t_ray *ray, double *incr_x);
int		check_v_exists(t_game *game, t_ray *ray);
void	v_wall(t_game *game, double angle, t_ray *ray);
/*	raycast.c	*/
void	remove_fish_eye(t_game *game, t_ray *ray, double angle);
void	get_wall_height(t_ray *ray);
void	chose_right_wall(t_game *game, t_ray *ray);
void	rays(t_game *game);
void	cast_ray(t_game *game, t_ray *ray, double angle);
/*	walls.c	*/
void	wall(t_game *game, t_ray *ray, double angle, int i);
void	wall2(t_game *game, t_ray *ray, int i);
int		is_char(char c);
/*	draw3d.c	*/
void	my_mlx_pixel_put(t_game *game, int x, int y, int color);
int		rgb_hex(t_game *game, int j);
int		draw_loop(t_game *game);
void	init_3d(t_game *game);
void	draw_bg(t_game *data);

//===================GNL=====================
//[			**get_next_line_utils.c		    ]
//===========================================
int		ft_strlen(const char *str);
char	*strdupgnl(char *buffer);
int		comparegnl(char *box);
char	*strjoingnl(char *box, char *buffer);
//===================GNL=====================
//[			**get_next_line.c		    	]
//===========================================
char	*writeligne(char *box);
char	*newbox(char *box);
char	*gnlbis(int fd, char *box);
char	*get_next_line(int fd);
//===================Utils===================
//[				**ft_atoi.c         	   	]
//===========================================
int		ft_atoi(const char *str);
//===================Utils===================
//[				**ft_isdigit.c       	   	]
//===========================================
int		ft_isdigit(int c);
//===================Utils===================
//[				**ft_split.c	    	   	]
//===========================================
char	**ft_split(char *s, char c);
//===================Utils===================
//[				**ft_putstr_fd.c	    	]
//===========================================
void	ft_putstr_fd(char *s, int fd);
//===================Utils===================
//[				**ft_strcmp.c	    	   	]
//===========================================
int		ft_strcmp(const char *s1, const char *s2);
//===================Utils===================
//[				**ft_strdup.c	    	   	]
//===========================================
char	*ft_strdup(const char *src);
char	*ft_strdupwen(const char *src);
//===================Utils===================
//[				**ft_strjoin.c	    	   	]
//===========================================
char	*ft_strjoin(char *s1, char *s2);
//===================Utils===================
//[				**ft_colorcheck.c      	   	]
//===========================================
int		colorcheck(char *str);
//===================Error===================
//[				**errormsg.c	     	   	]
//===========================================
int		errormsg(int nb);
//===================Error===================
//[				**errormsgmap.c	     	]
//===========================================
int		errormsgmap(int nb, t_game *game);
//===================Parsing=================
//[				**setarg.c	     	   		]
//===========================================
int		addvaluetorighttab(char **str, t_game *game);
int		checkandfillrgbvalue(char *str, t_game *game, char s);
int		setvalueforcolorbis(t_game *game, char s, int i);
void	freetabcf(t_game *game, char s);
//===================Parsing=================
//[				**setargbis.c	     	   	]
//===========================================
int		checkparsing(char **av, int ac, t_game *game);
int		takethefile(char **av, t_game *game);
int		takethefilebis(t_game *game, char **av);
int		prepbeforemap(t_game *game);
int		setvaluepremap(t_game *game);
//===================Parsing=================
//[				**setargbistwo.c	     	]
//===========================================
int		checkifitexist(char *str);
int		addeano(char **str, t_game *game, int fd);
int		addsowe(char **str, t_game *game, int fd);
int		addfc(char **str, t_game *game);
void	setgamevalue(t_game *game);
//===================Parsing=================
//[				**mapprep.c	     			]
//===========================================
int		prepamap(t_game *game);
int		checkerforforbidden(char c, t_game *game, int i, int j);
int		checkforbiddencharonmap(t_game *game);
int		checkifclose(t_game *game, int i, int j);
void	set_angle(t_game *game);
//===================Parsing=================
//[				**namecheck.c     	   		]
//===========================================
int		namecheck(char **av, t_game *game);
int		freenamecheck(t_game *game);

char	*ft_strncpy(char *dest, const char *src, size_t n);
void	set_row_col(t_game *game);
void	set_col(t_game *game);
void	set_row(t_game *game);
void	alloc_mem(t_game *game, char **tmp_map);
void	free_map(t_game *game);
void	fix_map(t_game *game);

#endif
