/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

int bitOr(int x, int y) {
    int res = ~(~x&~y);
    return res;
}

/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
    int equ = !(x^y);
    return equ;
}

/* 
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyEvenBit(int x) {
    int key = 0x55 | (0x55<<8) | (0x55<<16) | (0x55<<24);
    return !(!(x&key));
}

/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
        int key = 0x55 | (0x55<<8) | (0x55<<16) | (0x55<<24);
        int mid = x^key;
        return !(mid&key);
}

/* 
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) {
    int result = (x << n) + (x >> (32+(~n+1)) & ~((~1+1) << n));
    return result;
}

/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
    x = x << 31;
    x = x >> 31;
    return x;
}

/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    int sol, res;
    sol = !(~x);
    res = !((~(x+1)^x)|sol);
    return res;
}

/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
    int sol = ~(~x+1);
    int mid = (((~x)&sol)>>31);
    int res = mid & 1;
    return res;
}

/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
    int subt = x + (~y+1);
    int solx = (x >> 31) & 1;
    int soly = (y >> 31) & 1;
    int solsub = (subt >> 31) & 1;

    return !((!solx & soly & solsub) | (solx & !soly & !solsub));
}

/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
        int solx = (x >> 31) & 1;
        int soly = (y >> 31) & 1;
        int key = solx^soly;
        int solsub = ((~x + 1) + y) >> 31;
        return (key & solx) | (!(key | solsub));
}

/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *  Examples: satMul3(0x10000000) = 0x30000000
 *            satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *            satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
int satMul3(int x) {
    int msbx = (x>>31 & 1);
    int sum1 = x+x;
    int msb1 = (sum1>>31 & 1);
    int sum2 = sum1+x;
    int msb2 = (sum2>>31 & 1);
    int key1 = (((msbx ^ msb1)|(msbx ^ msb2))<< 31) >> 31;
    int tmin = 1 << 31;
    int key2 = (msbx << 31) >> 31;
    int con1 = sum2 & ~key1;
    int con2 = ~key2&(~tmin);
    int con3 = key2&tmin;
    return con1 | (key1 & (con2 | con3));
}

/* 
 * tc2sm - Convert from two's complement to sign-magnitude 
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: tc2sm(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int tc2sm(int x) {
    int MSB = (x>>31)<<31;
    int sign = x>>31;
    int resm = MSB | ~(x+(~1+1));
    return (sign&resm) | (~sign&x);
}

/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
    unsigned NaN = 0x7F800001;
    unsigned res = uf&0x7FFFFFFF;

    if(res < NaN)
        return res;
    else
        return uf;
}

/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
    unsigned NaN = 0x7F800001;
    unsigned key1 = 1 << 31;
    unsigned rem = uf&(~key1);
    unsigned key2 = ((uf >> 31)^1)<<31;
    unsigned res = rem + key2;

    if((uf&(~key1)) >= NaN)
        return uf;
    else
        return res;
}

/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
    unsigned NaN = 0x7F800000;
    unsigned MSB = 1<<31;
    if(uf == 0 || uf == MSB)
        return uf;
    if((uf&NaN) == NaN)
        return uf;
    if((uf&NaN) == 0)
        return ((uf&MSB) | uf<<1);

    return uf + (1<<23);
}

