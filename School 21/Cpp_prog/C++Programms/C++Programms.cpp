#include <stdio.h>
#include <stdlib.h>

int main() {
	int* mas = (int*) malloc(2 * sizeof(int));
	int counter = 0;
	scanf_s("%d", &mas[counter]);
	while (mas[counter] != -1) {
		counter++;
		scanf_s("%d", &mas[counter]);
		mas = (int*) realloc(mas, (counter + 2) * sizeof(int));
	}
	for (int i = 0; i < counter; i++) {
		printf("%d ", mas[i]);
	}
	free(mas);
}