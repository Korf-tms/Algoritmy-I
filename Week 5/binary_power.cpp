double power(double x, int n) {
    if( n == 0) return 1; // 0^0 == 1, but this might depend on the context
    if( n < 0) {
        x = 1/x;
        n = -n;
    }

    double result = 1.0;
    double base = x;

    // pretty much the same as conversion to binary
    while(n > 0) {
        if( n % 2 == 1) {
            result *= base; // "add" the current binary power if needed
        }
        base *= base; // compute all binary powers
        n /= 2; 
    }
    return result;
}