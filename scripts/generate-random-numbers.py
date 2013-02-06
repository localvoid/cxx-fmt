#!/usr/bin/env python

import sys
import random

random.seed(int(sys.argv[2]))

MIN=-(2**31)-1
MAX=2**31

SIGN_NONE=0
SIGN_PLUS=1<<2
SIGN_SPACE=1<<3

ALIGN_NONE=0
ALIGN_LEFT=1

ZERO_PADDING=1<<13

SIGNS = [SIGN_NONE, SIGN_PLUS, SIGN_SPACE]
ALIGNS = [ALIGN_NONE, ALIGN_LEFT]
ZP = [0, ZERO_PADDING]

for i in range(int(sys.argv[1])):
    print(random.randint(MIN, MAX))
    print(random.randint(0, 32))

    sign = random.choice(SIGNS)
    align = random.choice(ALIGNS)
    zp = 0
    if align == ALIGN_NONE:
        zp = random.choice(ZP)
    print(sign|align|zp)
