#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING 255

void string_double(char *str, char *response)
{
	int length = strlen(str);
	int position = 0;

	for (int count = 0; count < 2; ++count) {
		for (int i = 0; i < length; ++i, ++position)
		{
			response[position] = str[i];
		}
	}
	response[position] = '\0';
}

void string_reverse(char *str, char *response)
{
	int length = strlen(str);

	for (int i = 0; i < length; ++i)
	{
		response[i] = str[length - i - 1];
	}
	response[length] = '\0';
}


void string_trim(char *str) 
{
	char *start = str;
	int length = strlen(str);
	int i;

	for (i = length - 1; i >= 0; --i)
	{
		if (isspace(str[i]))
			length--;
		else
			break;	
	}
	str[length] = '\0';

	for (i = 0; i < length; ++i)
	{
		if (isspace(str[i]))
			start++;
		else
			break;
	}

	for (int i = 0; i < length; ++i)
		str[i] = start[i];

}

int string_split(char *str, char *delimeter, char **tokens)
{
	int length = strlen(str);
	int count = 0;
	char *token, *saveptr, *listptr;

	for (listptr = str; ; ++count, listptr = NULL)
	{
		token = strtok_r(listptr, delimeter, &saveptr);
		if (token == NULL) break;
		string_trim(token);
		tokens[count] = token;
	}
	return count;
}

void string_delete(char *str, char *token_str, char *response)
{
	int length = strlen(str);
	char *tokens[24];
	int count = string_split(token_str, ", ", tokens);
	int ch = 0;

	for (int i = 0; i < length; ++i)
	{
		int in_list = 0;
		for (int x = 0; x < count; ++x)
		{
			int pos = atoi(tokens[x]) - 1;
			if (i == pos) {
				in_list = 1;
				break;
			}
		}

		if (in_list) continue;
		response[ch] = str[i];
		ch++;
	}
	response[ch] = '\0';
}

void string_replace(char *str, char *token_str, char *response)
{
	int length = strlen(str);
	char *tokens[24], *num_token[2];
	int count = string_split(token_str, ", ", tokens);

	strcpy(response, str);

	for (int i = 0; i < count; ++i)
	{
		string_split(tokens[i], "-", num_token);
		int pos = atoi(num_token[0]) - 1;
		response[pos] = num_token[1][0];
	}
}

int get_letter_value(char c)
{
	if (c >= 97 && c <= 122)
		return (c - 96);
	else if (c >= 65 && c <= 90)
		return (c - 38);
	else
		return -1;
}

char get_letter(int value) 
{
	if (value < 27)
		return (value + 96);
	else if (value >= 27)		
		return (value + 38);
	else
		return '\0';
}

void string_encrypt(char *str, char *response)
{
	int length = strlen(str);
	int chvals[10];
	int pos = 0;

	for (int i = 0; i < length; ++i) {
		int count = 0, mid = 0;
		int chval = get_letter_value(str[i]);

		while (chval > 9) {
			chvals[count] = chval;
			chval -= 9;
			count++;
		}

		if (count < 1) {
			response[pos++] = toupper(get_letter(chval));
			continue;
		}

		for (int n = 0; n < count; ++n) {
			response[pos++] = (chvals[n] / 10) + '0';

			if (n == count - 1) {
				response[pos++] = toupper(get_letter(chval));
			}
			response[pos++] = tolower(get_letter(chvals[n] - 1));
		}

		for (int n = count-1; n >= 0; --n) {
			response[pos++] = (chvals[n] % 10) + '0';
		}

	}
	response[pos] = '\0';
}

void string_decrypt(char *str, char *response)
{
	int length = strlen(str);
	int spos = 0, rpos = 0;

	while (spos < length)
	{
		int hops = 0;
		int chval;
		while isdigit(str[spos])
		{
			spos += 2;
			hops++;
		}
		if (islower(str[spos]) && isupper(str[spos - 1]))
			chval = get_letter_value(tolower(str[spos - 1]));
		else if (isupper(str[spos]))
			chval = get_letter_value(tolower(str[spos]));
		else break;

		chval += (hops * 9);

		response[rpos++] = get_letter(chval);
		spos += hops + 1;

	}

	response[rpos] = '\0';

}


