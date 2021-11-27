/*
** getln.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 01:06:25 2006 Seblu
** Last update Tue Aug 29 02:20:16 2006 Seblu
*/

#ifndef GETLINE_H_
# define GETLINE_H_

# define GETLINE_BUF_SIZE 1024

typedef struct	getline
{
  int           fd;
  char          data[GETLINE_BUF_SIZE];
  unsigned      offset;
  int           size;
} s_getline;

/*!
** Read a line from fd. This read is bufferised !
**
** @param buf struct getln
**
** @return malloced readded line
*/
char            *getline(s_getline *buf);

/*!
** Correctly close an getline struct and if @arg closefd is true
** close the fd of getline struct
**
** @param buf structure getline to close
** @param closefd if true (!0), close fd of getline struct
*/
void            getline_close(s_getline *buf, int closefd);

/*!
** Create a getline struct associed with @arg fd
**
** @param fd fd associed with struct
**
** @return new struct
*/
s_getline		*getline_open(int fd);

#endif
