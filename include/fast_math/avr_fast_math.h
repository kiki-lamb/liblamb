#if !defined(LAMB_AVR_FAST_MATH_H) && defined(__AVR__) && !defined(__AVR_ATtiny85__)
#define LAMB_AVR_FAST_MATH_H

// Compared to avr-gcc 5.4.0/avr-libc, most of these are 1-2 instructions quicker than their obvious
// C equivalents (and those that are equivalent).

namespace lamb {
#define DEF_MUL_AND_RETURN_HI8(op, t1, t2) \
  inline t1 __attribute__((always_inline)) op ## _hi8  (t1 x, t2 y) { \
	  byte out;	           \
	  __asm__(               \
			#op " %1, %2 \n\t" \
	  	"mov  %0, r1 \n\t" \
  		"clr  r1     \n\t" \
  		:"=&a"(out)        \
  		:"a"(x), "a"(y)    \
  	);                   \
  	return out;          \
	}

#define DELEGATE(new_f, existing_f, t1, t2) \
  inline t1 __attribute__((always_inline)) new_f(t1 x, t2 y) { return existing_f(x,y); };
			
	DEF_MUL_AND_RETURN_HI8(fmul,       uint8_t,  uint8_t);
	DEF_MUL_AND_RETURN_HI8(fmulsu,      int8_t,  uint8_t);
	DEF_MUL_AND_RETURN_HI8(fmuls,       int8_t,   int8_t);
	DEF_MUL_AND_RETURN_HI8(mul,        uint8_t,  uint8_t);
	DEF_MUL_AND_RETURN_HI8(mulsu,       int8_t,  uint8_t);
	DEF_MUL_AND_RETURN_HI8(muls,        int8_t,   int8_t);
	
	DELEGATE(fmul_q7,      fmul_hi8,   uint8_t,  uint8_t);
	DELEGATE(fmulsu_q7,    fmulsu_hi8,  int8_t,  uint8_t);
	DELEGATE(fmuls_q7,     fmuls_hi8,   int8_t,   int8_t);
	DELEGATE(fmul_q7q8,    mul_hi8,    uint8_t,  uint8_t);
	DELEGATE(fmulsu_q7q8,  mulsu_hi8,   int8_t,  uint8_t);
	DELEGATE(fmuls_q7q8,   muls_hi8,    int8_t,   int8_t);
			
#undef DEF_MUL_AND_RETURN_HI8
#undef DELEGATE
}

#endif
