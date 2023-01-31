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
    double omega, angle();
    double gain, pha;
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
        for (pha = 0., i = 0; i <= M; i++) {
            pha += angle(omega, zero[i]);
        }
        for (i = 1; i <= N; i++) {
            pha -= angle(omega, pole[i]);
        }
        printf("%f %f\n", omega, pha);
    }

    return 0;
}

double angle(double omega, struct polar point) {
    double x = sin(omega) - point.mag*sin(point.ang);
    double y = cos(omega) - point.mag*cos(point.ang);
    double result = atan2(x, y);
    return result;
}