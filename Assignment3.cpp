#include<iostream>
#include<iomanip>
#include<cstdint>

int get_degree(uint32_t poly){
    if (poly ==0) return -1; 
    int deg = 0;
    while (poly >>=1) deg++; 
    return deg;
}

uint32_t poly_multiple(uint32_t a, uint32_t b){
    uint32_t res = 0;
    while (b>0){
    if (b&1) res ^=a;
    a<<=1;
    b>>=1;
    }
    return res;
} uint32_t poly_dividend(uint32_t div, uint32_t divsr, uint32_t *rem){
    uint32_t q = 0;
    *rem = div;
    int deg_rem = get_degree(*rem);
    int deg_div = get_degree(divsr);
    while (deg_rem >= deg_div && deg_rem>=0){
        int shift = deg_rem - deg_div;
        q ^= (1<<shift);
        *rem^= (divsr<< shift);
        deg_rem = get_degree(*rem);
    }
    return q;
}
uint32_t extendGcd_GF2_Array(uint32_t a, uint32_t m) {
    uint32_t r[20], q[20], t[20];
    
    r[0] = m; t[0] = 0;
    r[1] = a; t[1] = 1;
    std::cout << "i  | r[i] (Remainder) | q[i-1] (Quotient) | t[i] (Inversion)\n";
    std::cout << "---------------------------------------------------------\n";
    std::cout << "0  | " << std::setw(12) << r[0] << " | " << std::setw(15) << "-" << " | " << t[0] << "\n";
    std::cout << "1  | " << std::setw(12) << r[1] << " | " << std::setw(15) << "-" << " | " << t[1] << "\n";
    int i = 2;
    while (true) {
        //Tính q[i-1] = r[i-2] / r[i-1] và r[i] = r[i-2] % r[i-1]
        q[i-1] = poly_dividend(r[i-2], r[i-1], &r[i]);
        
        if (r[i] == 0) {
            std::cout << i << "  | " << std::setw(12) << r[i] << " | " << std::setw(15) << q[i-1] << " | -\n";
            return t[i-1];
        }

        t[i] = t[i-2] ^ poly_multiple(q[i-1], t[i-1]);

        std::cout << i << "  | " << std::setw(12) << r[i] << " | " << std::setw(15) << q[i-1] << " | " << t[i] << "\n";
        
        i++;
    }
}
int main() {
    uint32_t m = 1033; // Đa thức tối giản m(x) = x^10 + x^3 + 1
    uint32_t a = 523;  // Test vector 1
    uint32_t b = 1015; // Test vector 2
    std::cout << "=== Find invension of a = " <<  a << "===\n";
    std::cout << "---------------------------------------------------------\n";
    uint32_t inv1 = extendGcd_GF2_Array(a,m);
    std::cout << "The invension of " << a << " in GF(2^10) is: " << inv1 << "\n";
    std::cout << "=== Find invension of b = " <<  b << "===\n";
    std::cout << "---------------------------------------------------------\n";
    uint32_t inv2 = extendGcd_GF2_Array(b,m);
    std::cout << "The invension of " << b << " in GF(2^10) is: " << inv2 << "\n";
    return 0;
}