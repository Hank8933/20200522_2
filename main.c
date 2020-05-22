#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct FRAC
{
    int integer, numerator, denominator;
}frac;

int GCD(int a, int b) {
	if(b) while((a %= b) && (b %= a));
	return a + b;
}

int LCM(int a, int b) {
	return a * b / GCD(a, b);
}

frac *convert(frac *f)
{
    //printf("%d %d/%d\n", f->integer, f->numerator, f->denominator);
    if (!f->denominator){
        f->denominator = 1;
    }
    if(f->numerator >= f->denominator){
        int t = f->numerator / f->denominator;

        f->numerator -= t * f->denominator;
        f->integer += t;
    }

    int gcd = GCD(f->numerator, f->denominator);
    f->numerator /= gcd;
    f->denominator /= gcd;
    //printf("%d %d/%d\n\n", f->integer, f->numerator, f->denominator);
    return f;
}


void fracplus(frac *a, frac *b)
{
    //printf("\n%d %d/%d\n", a->integer, a->numerator, a->denominator);
    //printf("\n%d %d/%d\n", b->integer, b->numerator, b->denominator);
    int lcm = LCM(a->denominator, b->denominator);

    a->numerator *= lcm / a->denominator;
    a->denominator *= lcm / a->denominator;

    a->numerator += b->numerator * lcm / b->denominator;
    a->integer += b->integer;

    convert(a);

    //printf("\n   %d %d/%d\n", a->integer, a->numerator, a->denominator);
    //printf("\n   %d %d/%d\n", b->integer, b->numerator, b->denominator);
}

void fracarg(frac *a, frac *b, int n)
{
    b->numerator = a->integer * a->denominator + a->numerator;
    b->denominator = a->denominator * n;
    //printf("\n%d %d/%d\n", b->integer, b->numerator, b->denominator);
    convert(b);
}

int main()
{
    freopen("list", "r", stdin);
    frac list[MAX];
    frac sum = {0};
    frac arg = {0, 0, 1};
    for(int i = 0; i < MAX; i++){
        scanf("%d %d/%d", &list[i].integer, &list[i].numerator, &list[i].denominator);

        fracplus(convert(&sum), convert(list+i));
    }

    fracarg(&sum, &arg, MAX);
    printf("sum: %d %d/%d\n", sum.integer, sum.numerator, sum.denominator);
    printf("arg: %d %d/%d\n", arg.integer, arg.numerator, arg.denominator);
    return 0;
}
