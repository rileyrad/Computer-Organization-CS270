/**
 *  @author  Riley Radici
 */

#include <stdio.h>

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
char int_to_char (int value, int radix) {
	if((value >= 0) && (value < radix)){
		if(value < 10){
			return value + '0';
		}
		else{
			return value + '7';
		}
	}
	return '?';
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int char_to_int (char digit, int radix) {
	int value = (int)(digit);
	if(('0' <= digit) && (digit <= '9')){
		value = value - 48;
	}
	else if(('A' <= digit) && (digit <= 'Z')){
		value = value - 55;
	}
	else if(('a' <= digit) && (digit <= 'z')){
		value = value - 87;
	}
	if((value >= 0) && (value < radix)){
		return value;
	}
	else{
		return -1;
	}
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void div_rem (int numerator, int divisor, int* remainder, int* quotient) {
	*quotient = numerator / divisor;
	*remainder = numerator % divisor;
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int ascii_to_int (int valueOfPrefix, int radix) {
	char digit = getchar();
	if(digit == '\n'){
		return valueOfPrefix;
	}
	return ascii_to_int(valueOfPrefix * radix + char_to_int(digit, radix), radix);
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void int_to_ascii (int value, int radix) {
	int remainder, quotient;
	if(value > 0){
		div_rem(value, radix, &remainder, &quotient);
		int_to_ascii(quotient, radix);
		printf("%c", int_to_char(remainder, radix));
	}
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
double frac_to_double (int radix) {
  return -1.0;
}

