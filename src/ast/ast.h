/*
** ast.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 30 04:40:03 2006 Seblu
** Last update Fri Nov 17 14:17:02 2006 seblu
*/

#ifndef AST_H_
# define AST_H_

# include <stdio.h>
# include "../common/macro.h"

typedef struct ast_node  s_ast_node;

/*
** If ast node
*/
typedef struct		if_node
{
  s_ast_node		*cond;
  s_ast_node		*cond_true;
  s_ast_node		*cond_false;
} s_if_node;

/*
** For ast node
*/
typedef struct		for_node
{
  char			*varname;
  char			**values;
  s_ast_node		*exec;
} s_for_node;

/*
** Case item (not an ast node)
*/
typedef struct case_item s_case_item;
struct			case_item
{
  char			**pattern;
  s_ast_node		*exec;
  s_case_item		*next;
};

/*
** Case ast node
*/
typedef struct		case_node
{
  char			*word;
  s_case_item		*items;
} s_case_node;

/*
** While ast node
*/
typedef struct		while_node
{
  s_ast_node		*cond;
  s_ast_node		*exec;
} s_while_node;

/*
** Enumerate different type of redirection
*/
typedef enum		red_type
  {
    R_LESS,		/*  <   */
    R_LESSAND,		/*  <&  */
    R_GREAT,		/*  >   */
    R_GREATAND,		/*  >&  */
    R_DGREAT,		/*  >>  */
    R_LESSGREAT,	/*  <>  */
    R_CLOBBER,		/*  >|  */
    R_DLESS,		/*  <<  */
    R_DLESSDASH		/*  <<- */
  } e_red_type;

/*
** Redirection ast node
*/
typedef struct		red_node
{
  size_t		size;
  e_red_type		*type;
  int			*fd;
  char			**word;
  s_ast_node		*mhs;
} s_red_node;

/*
** Command ast node
*/
typedef struct		cmd_node
{
  char			**argv;
  char			**prefix;
} s_cmd_node;

/*
** Binary ast node
** Generic node, it's a contener for:
** T_PIPE, T_SEP, T_SEPAND , T_AND, T_OR : binary operator
** T_BANG, T_SUBSHELL : unary operator
*/
typedef struct		bin_node
{
  s_ast_node		*lhs;
  s_ast_node		*rhs;
} s_bin_node;

/*
** Funcdec node
*/
typedef struct		funcdec_node
{
  char			*name;
  s_ast_node		*body;
} s_funcdec_node;

/*
** Enumerate all node type
*/
typedef enum		node_type
  {
    T_IF,
    T_FOR,
    T_CASE,
    T_WHILE,
    T_CMD,
    T_AND,
    T_OR,
    T_SUBSHELL,
    T_FUNCDEC,
    T_BANG,
    T_PIPE,
    T_SEPAND,
    T_SEP,
    T_RED,
  } e_node_type;

/*
** Global constant of total count of node type
*/
enum { NODE_TYPE_COUNT = 14 };

/*
** This is a type for a node item
*/
typedef union		node_item
{
  s_if_node		child_if;
  s_for_node		child_for;
  s_case_node		child_case;
  s_while_node		child_while;
  s_red_node		child_red;
  s_cmd_node		child_cmd;
  s_bin_node		child_and;
  s_bin_node		child_or;
  s_bin_node		child_subshell;
  s_funcdec_node	child_funcdec;
  s_bin_node		child_bang;
  s_bin_node		child_pipe;
  s_bin_node		child_sep;
  s_bin_node		child_sepand;
} u_node_item;

/*
** Generic ast node type
*/
struct			ast_node
{
  e_node_type		type;
  u_node_item		body;
};

/*
** =================
** FILE: ast_print.c
** =================
*/

/*!
** Print an ast to @arg filename file
**
** @param ast ast to print
** @param filename filename where ast is printed. if it's NULL
** random file name is generated.
*/
void		ast_print(s_ast_node *ast, const char *filename);

/*!
** Print an ast node
**
** @param ast ast node to add to file
** @param fs file stream where print ast
** @param node_id first free node id
*/
void		ast_print_node(s_ast_node *ast, FILE *fs, unsigned int *node_id);

/*
** ====================
** FILE: ast_destruct.c
** ====================
*/

/*!
** Destroy node and all its childs
**
** @param ast mother node to destroy
**
*/
void		ast_destruct(s_ast_node *ast);

/*!
** Destroy node and only this node. All childs will survive.
**
** @param ast mother node to destroy
**
*/
void		ast_destruct_node(s_ast_node *ast);

/*
** ===========
** ast_if.c
** ===========
*/

/*!
** Create an if ast node
**
** @param cond if condition
** @param cond_true tree if condition is true
** @param cond_false tree if condition is false
**
** @return the node
*/
s_ast_node	*ast_if_create(s_ast_node *cond,
			       s_ast_node *cond_true,
			       s_ast_node *cond_false);
/*!
** Print an if ast node
**
** @param ast ast node to add to file
** @param fs file stream where print ast
** @param node_id first free node id
*/
void		ast_if_print(s_ast_node *node, FILE *fs, unsigned int *node_id);

/*!
** Destruct an if ast node. Don't destruct child nodes.
**
** @param node node to free
*/
void		ast_if_destruct_node(s_ast_node *node);

/*!
** Destruct an if ast node. Destruct child nodes.
**
** @param node node to destroy
*/
void		ast_if_destruct(s_ast_node *node);

/*
** ===============
** FILE: ast_for.c
** ===============
*/

/*!
** Create a for ast node
**
** @param varname variable name
** @param values word list that var @value varname will take.
** @warning values is a NULL termined list of string
** @param exec tree to execute with @value varname correctly set
**
** @return the node
*/
s_ast_node	*ast_for_create(char		*varname,
				char		**values,
				s_ast_node	*exec);

/*!
** Print a for ast node
**
** @param ast ast node to add to file
** @param fs file stream where print ast
** @param node_id first free node id
*/
void		ast_for_print(s_ast_node *node, FILE *fs, unsigned *node_id);

/*!
** Destruct a for ast node. Don't destruct child nodes.
**
** @param node node to free
*/
void		ast_for_destruct_node(s_ast_node *node);

/*!
** Destruct a for ast node. Destruct child nodes.
**
** @param node node to destroy
*/
void		ast_for_destruct(s_ast_node *node);

/*
** ================
** FILE: ast_case.c
** ================
*/

/*!
** Create a case ast node
**
** @param word reference word
**
** @return the node
*/
s_ast_node	*ast_case_create(char *word);

/*!
** Add a case item into a case node. An item is counpound of a set of word
** which match with reference word an case node and the corresponding
**
** @param node node where item will be added
** @param pattern list of word that can match to reference
** @param exec exec corresponding with match
*/
void		ast_case_add_item(s_ast_node	*node,
				  char		**pattern,
				  s_ast_node	*exec);

/*!
** Print a case ast node
**
** @param ast ast node to add to file
** @param fs file stream where print ast
** @param node_id first free node id
*/
void		ast_case_print(s_ast_node *node, FILE *fs, unsigned *node_id);

/*!
** Destruct a case ast node. Don't destruct child nodes.
**
** @param node node to free
*/
void		ast_case_destruct_node(s_ast_node *node);

/*!
** Destruct a case ast node. Destruct child node.
**
** @param node node to destroy
*/
void		ast_case_destruct(s_ast_node *node);

/*
** =================
** FILE: ast_while.c
** =================
*/

/*!
** Create a while ast node
**
** @param cond poursuit condition
** @param exec tree to execute if cond is true
**
** @return the node
*/
s_ast_node	*ast_while_create(s_ast_node *cond, s_ast_node *exec);

/*!
** Print an ast while (while) node
**
** @param ast ast node to add to file
** @param fs file stream where print ast
** @param node_id first free node id
*/
void		ast_while_print(s_ast_node *node, FILE *fs, unsigned int *node_id);

/*!
** Destruct a while ast node. Don't destruct child nodes.
**
** @param node node to free
*/
void		ast_while_destruct_node(s_ast_node *node);

/*!
** Destruct a while ast node. Destruct all child nodes.
**
** @param node node to destroy
*/
void		ast_while_destruct(s_ast_node *node);

/*
** ===============
** FILE: ast_red.c
** ===============
*/

/*!
** Create a redirection ast node
**
** @return the node
*/
s_ast_node	*ast_red_create(void);

/*!
** Add a redirection to a redirection node
**
** @param node node where add
** @param type type of redirection
** @param fd fd parameter of redirection
** @param word file or word parameter of redirection
*/
void		ast_red_add(s_ast_node		*node,
			    e_red_type		type,
			    int			fd,
			    char		*word);

/*!
** Print an ast red node
**
** @param ast ast node to add to file
** @param fs file stream where print ast
** @param node_id first free node id
*/
void		ast_red_print(s_ast_node *node, FILE *fs, unsigned int *node_id);

/*!
** Destruct a red ast node. Don't destruct child nodes.
**
** @param node node to free
*/
void		ast_red_destruct_node(s_ast_node *node);

/*!
** Destruct a red ast node. Destruct child nodes.
**
** @param node node to destroy
*/
void		ast_red_destruct(s_ast_node *node);

/*
** ===============
** FILE: ast_cmd.c
** ===============
*/

/*!
** Create a cmd ast node
**
** @return the node
*/
s_ast_node	*ast_cmd_create(void);

/*!
** Add a arg vector to a cmd node
**
** @param node node where add
** @param argv new arg vector
*/
void		ast_cmd_add_argv(s_ast_node *node, char *argv);

/*!
** Add a prefix to a cmd node
**
** @param node node for addition
** @param assignment_word word to add
*/
void		ast_cmd_add_prefix(s_ast_node *node, char *assignment_word);

/*!
** Print an ast cmd node
**
** @param ast ast node to add to file
** @param fs file stream where print ast
** @param node_id first free node id
*/
void		ast_cmd_print(s_ast_node *node, FILE *fs, unsigned int *node_id);

/*!
** Destruct a cmd ast node. Don't destruct child nodes.
**
** @param node node to free
*/
void		ast_cmd_destruct_node(s_ast_node *node);

/*!
** Destruct a cmd node. All child nodes will be destruct.
**
** @param node node to destroy
*/
void		ast_cmd_destruct(s_ast_node *node);

/*
** ===============
** FILE: ast_and.c
** ===============
*/

/*!
** Create an and (&&) ast node
**
** @param lhs left child
** @param rhs right child
**
** @return the node
*/
s_ast_node	*ast_and_create(s_ast_node *lhs, s_ast_node *rhs);

/*!
** Print an ast and (&&) node
**
** @param ast ast node to add to file
** @param fs file stream where print ast
** @param node_id first free node id
*/
void		ast_and_print(s_ast_node *node, FILE *fs, unsigned int *node_id);

/*!
** Destruct an and ast node. Don't destruct child nodes.
**
** @param node node to free
*/
void		ast_and_destruct_node(s_ast_node *node);

/*!
** Destruct an and (&&) node. Destruct all child nodes.
**
** @param node node to destroy
*/
void		ast_and_destruct(s_ast_node *node);

/*
** ==============
** FILE: ast_or.c
** ==============
*/

/*!
** Create an or (||) ast node
**
** @param lhs left child
** @param rhs right child
**
** @return the node
*/
s_ast_node	*ast_or_create(s_ast_node *lhs, s_ast_node *rhs);

/*!
** Print an ast or (||) node
**
** @param ast ast node to add to file
** @param fs file stream where print ast
** @param node_id first free node id
*/
void		ast_or_print(s_ast_node *node, FILE *fs, unsigned int *node_id);

/*!
** Destruct an or ast node. Don't destruct child nodes.
**
** @param node node to free
*/
void		ast_or_destruct_node(s_ast_node *node);

/*!
** Destruct an or (||) ast node. Destruct child nodes.
**
** @param node node to destroy
*/
void		ast_or_destruct(s_ast_node *node);

/*
** ====================
** FILE: ast_subshell.c
** ====================
*/

/*!
** Create a subshell (()) ast node
**
** @param child subshell tree
**
** @return the node
*/
s_ast_node	*ast_subshell_create(s_ast_node *child);

/*!
** Print an ast subshell (()) node
**
** @param ast ast node to add to file
** @param fs file stream where print ast
** @param node_id first free node id
*/
void		ast_subshell_print(s_ast_node *node, FILE *fs, unsigned int *node_id);

/*!
** Destruct a subshell (()) ast node. Don't destruct child nodes.
**
** @param node node to free
*/
void		ast_subshell_destruct_node(s_ast_node *node);

/*!
** Destruct a subshell (()) ast node. Destruct child nodes.
**
** @param node node to destroy
*/
void		ast_subshell_destruct(s_ast_node *node);

/*
** ===================
** FILE: ast_funcdec.c
** ===================
*/

/*!
** Create a funcdec (function declaration) ast node
**
** @param name function name
** @param body function body
**
** @return the node
*/
s_ast_node	*ast_funcdec_create(char *name, s_ast_node *body);

/*!
** Print an function declaration node
**
** @param ast ast node to add to file
** @param fs file stream where print ast
** @param node_id first free node id
*/
void		ast_funcdec_print(s_ast_node *node, FILE *fs, unsigned *node_id);

/*!
** Destruct a funcdec ast node. Don't destruct child nodes.
**
** @param node node to free
*/
void		ast_funcdec_destruct_node(s_ast_node *node);

/*!
** Destruct a funcdec ast node. Destruct child nodes.
**
** @param node node to destroy
*/
void		ast_funcdec_destruct(s_ast_node *node);

/*
** ================
** FILE: ast_bang.c
** ================
*/

/*!
** Create a bang (!) ast node
**
** @param child under bang tree
**
** @return the node
*/
s_ast_node	*ast_bang_create(s_ast_node *child);

/*!
** Print an ast bang (!) node
**
** @param ast ast node to add to file
** @param fs file stream where print ast
** @param node_id first free node id
*/
void		ast_bang_print(s_ast_node *node, FILE *fs, unsigned int *node_id);

/*!
** Destruct a bang (!) ast node. Don't destruct child nodes.
**
** @param node node to destroy
*/
void		ast_bang_destruct_node(s_ast_node *node);

/*!
** Destruct a bang (!) ast node. Destruct child nodes.
**
** @param node node to destroy
*/
void		ast_bang_destruct(s_ast_node *node);

/*
** ================
** FILE: ast_pipe.c
** ================
*/

/*!
** Create a pipe (|) ast node
**
** @param lhs left child
** @param rhs right child
**
** @return the node
*/
s_ast_node	*ast_pipe_create(s_ast_node *lhs, s_ast_node *rhs);

/*!
** Print an ast pipe (|) node
**
** @param ast ast node to add to file
** @param fs file stream where print ast
** @param node_id first free node id
*/
void		ast_pipe_print(s_ast_node *node, FILE *fs, unsigned int *node_id);

/*!
** Destruct a pipe (|) ast node. Don't destruct child nodes.
**
** @param node node to destroy
*/
void		ast_pipe_destruct_node(s_ast_node *node);
/*!
** Destruct a pipe (|) node
**
** @param node node to destroy
*/
void		ast_pipe_destruct(s_ast_node *node);

/*
** ===============
** FILE: ast_sep.c
** ===============
*/

/*!
** Create a separtor (;) ast node
**
** @param lhs left child
** @param rhs right child
**
** @return the node
*/
s_ast_node	*ast_sep_create(s_ast_node *lhs, s_ast_node *rhs);

/*!
** Print an ast sep (;) node
**
** @param ast ast node to add to file
** @param fs file stream where print ast
** @param node_id first free node id
*/
void		ast_sep_print(s_ast_node *node, FILE *fs, unsigned int *node_id);

/*!
** Destruct a sep (;) ast node. Don't destruct child nodes.
**
** @param node node to destroy
*/
void		ast_sep_destruct_node(s_ast_node *node);
/*!
** Destruct a sep (;) ast node. Destruct child nodes.
**
** @param node node to destroy
*/
void		ast_sep_destruct(s_ast_node *node);

/*
** ==================
** FILE: ast_sepand.c
** ==================
*/

/*!
** Create a sepand (&) ast node
**
** @param lhs left child
** @param rhs right child
**
** @return the node
*/
s_ast_node	*ast_sepand_create(s_ast_node *lhs, s_ast_node *rhs);

/*!
** Print an ast sepand (&) node
**
** @param ast ast node to add to file
** @param fs file stream where print ast
** @param node_id first free node id
*/
void		ast_sepand_print(s_ast_node *node, FILE *fs, unsigned int *node_id);

/*!
** Destruct a sepand (&) ast node. Don't destruct child nodes.
**
** @param node node to destroy
*/
void		ast_sepand_destruct_node(s_ast_node *node);

/*!
** Destruct a sepand (&) ast node. Destruct child nodes.
**
** @param node node to destroy
*/
void		ast_sepand_destruct(s_ast_node *node);

#endif /* !AST_H_ */
