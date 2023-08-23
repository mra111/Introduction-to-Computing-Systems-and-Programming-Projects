#include <stdio.h>
/*define function kmm*/
int kmm(int num1, int num2) {
	int max;
	int i;
	int result;

	/*check if num1 bigger than num2*/
	if (num1 > num2) {
		max = num1;
	}
	else {
		max = num2;
	}
	i = max;

	/*find the result and return the result*/
	while (1 == 1) {
		if (i % num1 == 0 && i % num2 == 0) {
			result = i;
			break;
		}
		i = i + 1;
	}
	return result;
}


int main() {
	/* [x](A[a]B[b]) + [y](C[c]D[d]) --> [z](A[e]D[f]) + [t](C[g]B[h]) */

	/*define the variables*/
	int a, b, c, d, e, f, g, h;
	int x, y, z, t;
	int item_a;
	int item_b;
	int item_c;
	int n1;
	int n2;

	/*get the variables from the user*/
	scanf("%d %d %d %d %d %d %d %d", &a, &b, &c, &d, &e, &f, &g, &h);

	/*balance base on A*/
	item_a = kmm(a, e);
	x = item_a / a;
	z = item_a / e;

	/*balance base on C*/
	item_c = kmm(c, g);
	y = item_c / c;
	t = item_c / g;

	/*balance base on B*/
	item_b = kmm(x * b, t * h);
	n1 = x * b;
	n2 = t * h;
	x = x * (item_b / n1);
	z = z * (item_b / n1);
	t = t * (item_b / n2);
	y = y * (item_b / n2);

	/*check if D is balanced and equation is balanced*/
	if (y * d == z * f) {
		printf("%d %d %d %d\n", x, y, z, t);
	}
	else {
		printf("-1\n");
	}
	return 0;
}