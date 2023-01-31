#include <iostream>

const int permution[] = {
    151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,
    21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,88,
    237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,134,139,48,27,166,77,146,158,231,
    83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,102,143,54,65,25,63,161,1,
    216,80,73,209,76,132,187,208,89,18,169,200,196,135,130,116,188,159,86,164,100,109,198,
    173,186,3,64,52,217,226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,
    47,16,58,17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,153,101,155,
    167,43,172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,112,104,218,246,97,228,
    251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,14,239,107,49,192,214,
    31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,138,236,205,93,222,114,
    67,29,24,72,243,141,128,195,78,66,215,61,156,180
};

int p[512];
char d[11] = " `'\"+*0&#@";

void init();
double perlin(double x, double y, double z);
double fade(double t);
double grad(int hash, double x, double y, double z);
double lerp(double a, double b, double x);
double OctavePerlin(double x, double y, double z, int octaves, double persistence);


void init() {
    for (int i = 0; i < 512; i++) {
        p[i] = permution[i % 256];
    }
}


double perlin(double x, double y, double z) {
    int xi = (int)x & 255; // % 256
    int yi = (int)y & 255; // % 256
    int zi = (int)z & 255; // % 256
    double xf = x - (int)x;
    double yf = y - (int)y;
    double zf = z - (int)z;

    double u = fade(xf);
    double v = fade(yf);
    double w = fade(zf);


    // hashes all 8 unit cube coordinates surrounding the input coordinate
    /// +1이 된 축을 b로 표현
    int aaa, aba, aab, abb, baa, bba, bab, bbb;
    aaa = p[p[p[ xi   ]+ yi   ]+ zi   ];
    aba = p[p[p[ xi   ]+ yi+1 ]+ zi   ];
    aab = p[p[p[ xi   ]+ yi   ]+ zi+1 ];
    abb = p[p[p[ xi   ]+ yi+1 ]+ zi+1 ];
    baa = p[p[p[ xi+1 ]+ yi   ]+ zi   ];
    bba = p[p[p[ xi+1 ]+ yi+1 ]+ zi   ];
    bab = p[p[p[ xi+1 ]+ yi   ]+ zi+1 ];
    bbb = p[p[p[ xi+1 ]+ yi+1 ]+ zi+1 ];

    double x1, x2, y1, y2;
    x1 = lerp(
        grad(aaa, xf, yf, zf), // gradient vector와 dist vector의 내적을 구한다. 어떻게????
        grad(baa, xf - 1, yf, zf),
        u);
    x2 = lerp(
        grad(aba, xf, yf - 1, zf),
        grad(bba, xf - 1, yf - 1, zf),
        u);
    y2 = lerp(x1, x2, v);

    x1 = lerp(
        grad(aab, xf, yf, zf - 1),
        grad(bab, xf - 1, yf, zf - 1),
        u);
    x2 = lerp(
        grad(abb, xf, yf - 1, zf - 1),
        grad(bbb, xf - 1, yf - 1, zf - 1),
        u);
    y2 = lerp(x1, x2, v);

    return (lerp (y1, y2, w) + 1) / 2; // [-1, 1] ==> [0, 1]

}


double fade(double t) {
    // 6t^5 - 15t^4 + 10t^3
    return t * t * t * (t * (t * 6 - 15) + 10);
}

// They pick a random vector from the following 12 vectors:
/*
(1,1,0),(-1,1,0),(1,-1,0),(-1,-1,0),
(1,0,1),(-1,0,1),(1,0,-1),(-1,0,-1),
(0,1,1),(0,-1,1),(0,1,-1),(0,-1,-1)
*/
double grad(int hash, double x, double y, double z) {
    switch (hash & 0xF)
    {
    case 0x0: return  x + y; break;
    case 0x1: return -x + y; break;
    case 0x2: return  x - y; break;
    case 0x3: return -x - y; break;
    case 0x4: return  x + z; break;
    case 0x5: return -x + z; break;
    case 0x6: return  x - z; break;
    case 0x7: return -x - z; break;
    case 0x8: return  y + z; break;
    case 0x9: return -y + z; break;
    case 0xA: return  y - z; break;
    case 0xB: return -y - z; break;
    case 0xC: return  y + x; break;
    case 0xD: return -y + z; break;
    case 0xE: return  y - x; break;
    case 0xF: return -y - z; break;
    
    default: return 0; break;
    }
}


// x의 값을 a와 b 사이에 놓는 것
double lerp(double a, double b, double x) {
    return a + x * (b - a);
}


double OctavePerlin(double x, double y, double z, int octaves, double persistence) {
    double total = 0;
    double frequency = 1;
    double amplitude = 1;
    double maxValue = 0;
    for (int i = 0; i < octaves; i++) {
        total += perlin(x * frequency, y * frequency, z * frequency) * amplitude;
        maxValue += amplitude;
        amplitude *= persistence;
        frequency *= 2;
    }

    return total / maxValue; // normalize result
}


int main(int argc, char * argv[]) {

    init();
    double r = perlin(1.0, 125.3, 0);

    std::cout << r << std::endl;

    int i = 0, j = 0, c = 0, z = 0;
    double n;
    clock_t stall;

    while(1) {
        stall = clock();
        for(i = 0; i < 50; i++) {
            for(j = 0; j < 50; j++) {
                n = OctavePerlin(j * 0.01, i * 0.01, z * 0.01, 5, 0.7);
                // std::cout << n << std::endl;
                c = (int)(n * 9);
                if(c < 0)
                    c = 0;
                if(c > 9)
                    c = 9;
                printf("%c", d[c]);
            }
            printf("\n");
        }
        printf("\n\n");
        z++;
        
        while(clock() - stall < 100000) {

        }
    }

    return 0;
}