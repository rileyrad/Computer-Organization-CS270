#include "Debug.h"
#include "iFloat.h"

/** @file iFloat.c
 * 
 *  @author Riley Radici
 */

/* declaration for useful function contained in testFloat.c */
const char* getBinary (iFloat_t value);

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetSign (iFloat_t x) {
    if((x & 0x8000) == 0) return 0;
    else return 1;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetExp (iFloat_t x) {
    return (x >> 10) & 0x1F; /* implement this */
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetVal (iFloat_t x) {
    int mantissa = x & 0x3FF;
    mantissa = mantissa | 0x400;
    if(floatGetSign(x) == 1){
        mantissa = ~mantissa + 1;
    }
    return mantissa;
}

/** @todo Implement based on documentation contained in iFloat.h */
void floatGetAll(iFloat_t x, iFloat_t* sign, iFloat_t*exp, iFloat_t* val) {
    *sign = floatGetSign(x);
    *exp = floatGetExp(x);
    *val = floatGetVal(x);
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatLeftMost1 (iFloat_t bits) {
    int pos = -1;
    if(bits < 0){
        return 15;
    }
    while(!(bits == 0)){
        pos = pos + 1;
        bits = bits >> 1;
    }
    return pos;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatAbs (iFloat_t x) {
  return x & 0x7FFF;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatNegate (iFloat_t x) {
    if(x == 0) return 0;
    return x ^ 0x8000;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatAdd (iFloat_t x, iFloat_t y) {
    debug("%s: bits of x (IEEE 754)", getBinary(x)); // example only
    debug("%s: bits of y (IEEE 754)", getBinary(y)); // example only
    if(x == 0){
        return y;
    }if(y == 0){
        return x;
    }
    iFloat_t signX, expX, manX, signY, expY, manY;
    floatGetAll(x, &signX, &expX, &manX);
    floatGetAll(y, &signY, &expY, &manY);
    debug("signX: %d, expX: %d, manX: %d", signX, expX, manX);
    debug("signY: %d, expY: %d, manY: %d", signY, expY, manY);
    int shift;
    iFloat_t expR;
    if(expX > expY){
        shift = expX - expY;
        expR = expY + shift;
        manY = manY >> shift;
    }else{
        shift = expY - expX;
        expR = expX + shift;
        manX = manX >> shift;
    }
    iFloat_t manR = manX + manY;
    iFloat_t signR = floatGetSign(manR);
    if(signR == 1){
        manR = ~manR + 1;
    }
    debug("signR: %d, manR: %d, expR: %d", signR, manR, expR);
    while(floatLeftMost1(manR) < 10){
        manR = manR << 1;
        expR = expR - 1;
    }
    while(floatLeftMost1(manR) > 10){
        manR = manR >> 1;
        expR = expR + 1;
    }
    debug("new manR: %d, expR: %d", manR, expR);
    iFloat_t answer = (signR << 15) | (expR << 10) | (manR & 0x3FF);
    return answer;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatSub (iFloat_t x, iFloat_t y) {
    return floatAdd(x, floatNegate(y));
}

