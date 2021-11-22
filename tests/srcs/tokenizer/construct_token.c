#include "test_utils.h"
#include "break_input/token.h"

void	construct_token_copy_string(void)
{
	t_token			*token;
	char const		*str = "whatever";

	token = construct_token(str, '\0');
	CU_ASSERT_PTR_NOT_EQUAL(token->str, str);
	CU_ASSERT_STRING_EQUAL(token->str, str);
}

void	construct_io_number_token(void)
{
	t_token			*token;
	char const		*numbers = "1234";

	token = construct_token(numbers, '<');
	CU_ASSERT_EQUAL(token->type->id, IO_NUMBER_TOKID);
	delete_token(&token);

	token = construct_token(numbers, '>');
	CU_ASSERT_EQUAL(token->type->id, IO_NUMBER_TOKID);
	delete_token(&token);
}
