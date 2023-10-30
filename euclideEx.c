#include <stdio.h>
#include <stdint.h>

uint64_t gcd(uint64_t a, uint64_t b, int64_t *x, int64_t *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    int64_t x1, y1;
    uint64_t gcd_value = gcd(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;

    return gcd_value;
}

uint64_t mod_inverse(uint64_t a, uint64_t n) {
    int64_t x, y;
    uint64_t gcd_value = gcd(a, n, &x, &y);

    if (gcd_value != 1) {
        return 0;
    } else {
        x = (x % (int64_t)n + (int64_t)n) % (int64_t)n;
        return (uint64_t)x;
    }
}

int main() {
    uint64_t a = 100417;
    uint64_t n = 740963586;

    uint64_t inverse = mod_inverse(a, n);

    if (inverse == 0) {
        printf("Não existe inverso modular para a congruência.\n");
    } else {
        printf("O inverso modular de %llu (mod %llu) é %llu.\n", (unsigned long long)a, (unsigned long long)n, (unsigned long long)inverse);
    }

    return 0;
}
