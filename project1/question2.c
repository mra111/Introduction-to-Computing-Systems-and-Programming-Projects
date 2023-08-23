#include <stdio.h>
int main() {
	/*define variables*/
	int num;
	int prime = 1;

	/*get the num from the user and check if it is prime*/
	scanf("%d", &num);
	for (int i = 2; i <= num - 1; i++) {
		if (num % i == 0) {
			prime = 0;
			break;
		}
	}

	/*check if num is prime*/
	if (prime == 1) {
		printf("YES\n");
	}
	else {
		printf("NO\n");
	}
	return 0;
}