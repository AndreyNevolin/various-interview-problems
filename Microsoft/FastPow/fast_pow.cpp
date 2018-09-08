/**
 * Implement exponentiation function "float Pow( float base, int n)"
 * Complexity requirement: execution time must be proportional to log(n)
 *
 * The exponentiation algorithm implemented here is the following:
 *     1) n = BIT(n, k)*2^k + BIT(n, k-1)*2^(k-1) + ... + BIT(n, 0), where
 *        BIT(n, k) is a k-th bit of n
 *     2) base^n = base^(BIT(n, k)*2^k + BIT(n, k-1)*2^(k-1) + ... + BIT(n, 0))
 *        base^n = base^(((...((BIT(n, k)*2 + BIT(n, k-1))*2 + BIT(n, k-2)*2) + ...)*2 +
 *                 + BIT(n, 1))*2 + BIT(n, 0))
 *        base^n = ((...((base^BIT(n, k))^2 * base^BIT(n, k-1))^2...)^2 * base^BIT(n, 1))^
 *                 ^2 * base^BIT(n, 0)
 *     3) thus:
 *            result = 1;
 *            
 *            for ( i = k; i<= 0; i-- )
 *                if ( BIT(n, i) )
 *                    result = result * result * base;
 *                else
 *                    result = result * result
 */
#include <iostream>
#include <math.h>

using namespace std;

bool BIT( int n, int m)
{
    return (n >> m) & 1;
}

/**
 * The case of 0^0 requires special consideration. According to the code below, it will
 * be zero. But it's better to ask an interviewer what is expected for 0^0. By asking
 * you demonstrate that you're aware of this corner case
 */
float Pow( float base, int n)
{
    int ind = 0;
    float epsilon = 0.000000001;

    if ( fabs( base) < epsilon )
        return 0;

    if ( !n )
        return 1;

    while ( n >> ind )
        ind++;

    float result = 1.0;

    for ( int i = ind - 1; i >= 0; i-- )
    {
        result = result * result;

        if ( BIT( n, i) )
            result *= base;
    }

    return result;
}

int main()
{
    float base = 7.89;
    int n = 20;

    cout << Pow( base, n);

    return 0;
}
