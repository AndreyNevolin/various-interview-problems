/**
 * A number expressed in the septenary numeral system and stored as a string is given.
 * For example, "3450634132".
 * Write code that outputs the same number but expressed in the ternary numeral system.
 * The input number can be arbitrarily long.
 *
 * Solution:
 * 1) all arithmetic operations described in further items are base-3 operations
 * 2) first, the most significant digit of the septenary notation is taken
 * 3) it is multiplied by 7 and the second most significant digit of the septenary
 *    notation is added to the result
 * 4) then the result is multiplied by 7 and the third most significant digit of the
 *    septenary notation is added
 * 5) so on. While there remain non-processed digits:
 *        - multiply the current value of the result by 7
 *        - add the next digit to it
 */
#include <iostream>
#include <string.h>
#include <assert.h>

using namespace std;

void printNum( char *num, int size)
{
    if ( !num ) return;

    int ind = size - 1;

    while ( ind >= 0 && !num[ind] )
        ind--;

    while ( ind >= 0 )
        cout << char_traits<char>::to_int_type( num[ind--]);

    cout << "\n";
}

/**
 * Perform base-3 multiplication of a number by 7
 *
 * Just for fun it's done in the following way:
 * 1) 7 = 2*3 + 1
 * 2) the initial number is shifted one digit to the left
 * 3) the result is multiplied by 2
 * 4) the initial number is added
 */
void mul7( char *num, int size)
{
    int carry = 0;
    int prev_num_digit = 0;

    for ( int i = 0; i < size; i++ )
    {
        int temp = prev_num_digit * 2 + num[i] + carry;

        prev_num_digit = num[i];
        num[i] = temp % 3;
        /* "carry" cannot grow indefinitely. In fact, it cannot be bigger than 2.
            Assume the opposite: carry >= 3. Hence, temp >= 9, Hence, the previous
            value of carry was bigger or equal to 3 (since prev_num_digit <= 2 and
            num[i] <= 2). Applying the same logic again, we conclude that carry was
            always bigger or equal to 3. But that's not true. We know that the initial
            value of carry was zero */
        carry = temp / 3;
    }
}

/**
 * Add a septenary digit to a base-3 number
 *
 * Septenary digit expressed in base-3 notation has at maximum 2 non-zero base-3 digits.
 * These digits are first added to the two least significant digits of the number. And
 * then the carry is propagated from the least significant digit to the most significant
 * one
 */
void addDigit( char *num, char digit, int size)
{
    num[0] += digit % 3;
    num[1] += digit / 3;

    int carry = 0;

    for ( int i = 0; i < size; i++ )
    {
        int temp = num[i] + carry;

        num[i] = temp % 3;
        /* "carry" cannot be bigger than 1 */
        carry = temp / 3;
    }
}

void septenaryToTernary( string input_num, char *output_num)
{
    if ( !output_num ) return;

    for ( int i = 0; i < input_num.size(); i++ )
    {
        mul7( output_num, input_num.size() * 2);
        assert( input_num[i] - '0' <= 6);
        addDigit( output_num, input_num[i] - '0', input_num.size() * 2);
    }
}

int main()
{
    string input_num = "360215430666265401152334012626631";
    /* Base-3 notation of the number will be log3(7) times longer than its base-7
       notation. But log3(7) < 2. Thus, if we reserve memory to keep twice as many
       digits as the base-7 representation has, that will be enough for sure */
    char *output_num = new char[input_num.size() * 2];

    memset( output_num, 0, sizeof( char) * input_num.size() * 2);
    cout << "Septenary representation: " << input_num << '\n';
    septenaryToTernary( input_num, output_num);
    cout << "Ternary representation: ";
    printNum( output_num, input_num.size() * 2);

    delete[] output_num;

    return 0;
}
