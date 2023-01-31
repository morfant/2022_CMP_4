#include <stdio.h>
#include <math.h>

struct polar {
    double mag;
    double ang;
};

#define M 2
#define N 2

struct polar zero[M+1];
struct polar pole[N+1];
struct polar acoef[M+1];
struct polar bcoef[N+1];
double PI;

void getcoef();
struct polar cadd(), cnegmult();

int main () {
    int i;

    PI = 4.*atan(1.); // atan(1) = PI/4

    pole[1].mag = 0.9;
    pole[1].ang = 0.25*PI;
    pole[2].mag = pole[1].mag;
    pole[2].ang = -pole[1].ang;

    // elements of computer music, p.124 단위원 그림 참조
    zero[1] = pole[1];
    zero[1].mag = 1./zero[1].mag; // negate pole[1]
    zero[2] = pole[2];
    zero[2].mag = 1./zero[2].mag; // negate pole[2]

    getcoef(acoef, zero, M);
    getcoef(bcoef, pole, N);
    printf("             1.");

    for (i = 1; i <= M; i++) {
        if (acoef[i].mag != 0.) {
            printf(" %+fz[-%d]", acoef[i].mag, i); // %+f : 양수일 경우 +를 붙여 출력하도록
        }
    }
    printf("\nH(z) = a[0] --------------------------- \n");
    printf("             1.");
    for (i = 1; i <= N; i++) {
        if (bcoef[i].mag != 0.) {
            printf(" %+fz[-%d]", bcoef[i].mag, i);
        }
    }
    printf("\n");

}



/*
 * P(x) = AnXn + An-1Xn-1 + An-2Xn-2+... +A1X + A0
 * The polynomial can be written as:
 * P(x) = A0 + X(A1 + X(A2 + X(A3 + X(Q4 + X(...X(An-1 + XAn))))
 * and evaluated starting from the inner loop
 */
void getcoef(struct polar coef[], struct polar root[], int Nroots) {
    int i, j;

    for (i = 0; i <= N; i++) {
        coef[i].mag = coef[i].ang = 0.;
    }
    coef[0].mag = 1.;

    for (i = 1; i <= Nroots; i++) {
        // 전달 함수에 zero/pole 값을 적용한다는 것은 해당 다항식의 계산 결과가 0이 된다는 의미
        // 0 = X(A1 + X(A2 + X(A3 + X(Q4 + X(...X(An-1 + XAn))))
        // 예를 들면 A1 =  - 1 * X(A2 + X(A3 + X(Q4 + X(...X(An-1 + XAn)));
        coef[i] = cnegmult(root[i], coef[i - 1]);
        for (j = i - 1; j >= 1; j--) {
            coef[j] = cadd(coef[j], cnegmult(root[i], coef[j - 1]));
        }
    }
}


// 복소수의 곱셈 (polar form): mag 끼리 곱하고 ang 끼리 더한다
struct polar cnegmult(struct polar a, struct polar b) { // return -a * b
    static struct polar v;
    v.mag = -a.mag * b.mag;
    v.ang = a.ang + b.ang;

    if (fabs(fabs(v.ang) - PI) < 1.e-6) { // 1 * (10**-6)
        v.mag = -v.mag;
        v.ang = 0.;
    }
    return (v);
}

struct polar cadd(struct polar a, struct polar b) { // complex sum
    static struct polar v;
    double x, y;
    x = a.mag * cos(a.ang);
    y = a.mag * sin(a.ang);
    x += b.mag * cos(b.ang);
    y += b.mag * sin(b.ang);
    v.mag = sqrt(x*x + y*y);
    v.ang = atan2(y, x);
    if (fabs(fabs(v.ang) - PI) < 1.e-6) {
        v.mag = -v.mag;
        v.ang = 0.;
    }

    return (v);
}