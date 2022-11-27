#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)
#pragma warning(disable:6387)

int main()
{
	//read a file
	FILE* file = fopen("morse.txt", "r");
	char text[] = "MORSE";
	int nbcaractere = 0;
	char letter[2];
	char *morse = NULL;
	if (file == NULL)
	{
		printf("Error opening file");
		return 1;
	}
	//une chaine dico donnant le chemin vers le dictionnaire à utiliser (128 caractères maxi)
	char *dico[128];
	for (int i = 0; i < 128; i++)
	{
		dico[i] = '\0';
	}
	char* translate = calloc((strlen(text))*8, sizeof(char));
	int res = fscanf(file, "%d", &nbcaractere);
	for (int i = 0; i < nbcaractere; i++)
	{
		morse = calloc(8, sizeof(char));
		res = fscanf(file, "%s%s", letter, morse);
		dico[(int)letter[0]] = morse;
	}
	for (int i = 0; i < strlen(text); i++)
	{
		if (text[i] != ' ' && text[i] != NULL)
		{
			
			res = strcat(translate, dico[(int)text[i]]);
			res = strcat(translate, " ");
			
		}
		if (text[i] == ' ')
			res = strcat(translate, "/ ");
	}
	printf("translate = %s", translate);
	free(morse);
	free(translate);
	fclose(file);
	return 0;
}