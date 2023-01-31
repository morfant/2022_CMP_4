#include <stdio.h>
#include <math.h>

struct polar {
    double mag;
    double ang;
};

#define M 2
#define N 2
#define K 32

struct polar zero[M+1];
struct polar pole[N+1];

int main () {

    double PI = 4.*atan(1.); // atan(1) = PI/4
    double omin = 0.;
    double omax = PI;
    double ostep = (omax - omin) / K;
    double omega, length();
    double gain, amp, num, den;
    int i;

    gain = 1.;

    pole[1].mag = 0.8;
    pole[1].ang = 0.25*PI;
    pole[2].mag = pole[1].mag;
    pole[2].ang = -pole[1].ang;

    zero[1].mag = 1;
    zero[1].ang = 0.;
    zero[2].mag = -1;
    zero[2].ang = 0.;

    for (omega = omin; omega <= omax; omega += ostep) {
        for (num = 1., i = 0; i <= M; i++) {
            num *= length(omega, zero[i]); // num(분자): numerator
        }
        for (den = 1., i = 1; i <= N; i++) {
            den *= length(omega, pole[i]); // den(분모): denominator
        }
        num *= gain;
    
        if (den != 0.) {
            amp = num/den;
        } else if (num >= 0.) {
            amp = HUGE;
        } else {
            amp = -HUGE;
        }

        printf("%f %f\n", omega, amp);
    }

    return 0;
}

double length(double omega, struct polar point) {
    double a, b;
    a = point.mag*cos(point.ang) - cos(omega);
    b = point.mag*sin(point.ang) - sin(omega);
    return (sqrt(a*a + b*b));
}