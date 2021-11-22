/*
** constant.h for 42sh
**
** Made by Seblu
** Login   <Seblu@epita.fr>
**
** Started on  Fri Aug 25 03:39:03 2006 Seblu
** Last update Fri Nov 17 13:16:09 2006 seblu
*/

#ifndef CONSTANT_H_
# define CONSTANT_H_

typedef enum error
  {
    ERROR_RED = 1, //redirection error
    ERROR_PARSE = 2, //parser or lex error
    ERROR_MEM = 42, //no memory left
    ERROR_FORK = 128, //error in fork
    ERROR_PIPE = 128, // error in pipe
  } e_error;

typedef enum prompt {
  PROMPT_PS1 = 1,
  PROMPT_PS2 = 2,
  PROMPT_PS4 = 4
} e_prompt;

#endif
