#include <stdio.h>
#include <string.h>



int Parse_string_to_int(int var_array[], unsigned int number_of_vars,char* string, const char init_char, const char seperating_char, const char end_char);


int main(int argc, char *argv[])
{
char* string="12312312sdadasdas$23,2123u,#1tr*";
int var[20]={0};
int var_found=0;

var_found= Parse_string_to_int(var,5,string,'$',',','*');	
if(var_found)
{
	for(int i=0;i<var_found;i++)
	{
	printf("%i\n\r",var[i]);
	}
}
}

/**
 * int Parse_string_to_int
 *
 * @param var_array The array that the extracted integers will be placed.
 * @param number_of_vars The number of variables requested
 * @param string The string that will be parsed
 * @param init_char the char that the parsing will start from
 * @param seperating_char the char that seperates each number
 * @param end_char the char that signals the end of parsing
 * 
 * @note a string example is: $1,2,3,4,5* where '$' is the init_char, ',' is the seperating char and '*' is the end char
 * 
 * @return The number of integers found in the string 
 */
int Parse_string_to_int(int var_array[], unsigned int number_of_vars,char* string, const char init_char, const char seperating_char, const char end_char)
{
	unsigned long string_length=strlen(string);
	char Char_number_array[5]={0}; //5= maximum amount of digits for an int16_t (int on avr-gcc)
	char string_index=0;
	char Char_number_array_index=0;
	unsigned int int_array_index=0;
	
	while(string[string_index++]!='$') //find the initial char
	{
		if(string_index>=string_length)//if not found return 0
		{
			return 0; 
		}
	}
		while( int_array_index<number_of_vars) 
		{
			do
			{
				if(string[string_index]>='0'&& string[string_index]<='9') //if char is a number
				{
				Char_number_array[Char_number_array_index++]=string[string_index]; 
				}	
				string_index++;
			}
			while(string[string_index]!=seperating_char && string[string_index]!=end_char && string_index<=string_length);
			
			Char_number_array[Char_number_array_index]='\0'; //add a null termination char so the char array becomes a string

			if(Char_number_array_index<6) //if the number of digits is smaller than the one of a  avr-gcc int (+-32768) plus the null terminator
			{
				var_array[int_array_index]=atoi(Char_number_array);  //convert to int
			}
			else
			{
				var_array[int_array_index]=0;
			}
			Char_number_array_index=0;
			int_array_index++; //advance to the next integer
			
			if(string[string_index]=='*') //if the end char is found, end the parsing/
			{
				break;
			}
			string_index++; 
		}
	return int_array_index--; //return the number of integers found, minus an extra step taken at the end of the while loop
}

