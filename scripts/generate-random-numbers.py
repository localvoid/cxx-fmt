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

INTEGER = 1
FLOAT = 2
STRING = 3
POINTER = 4

TYPE_CHOICE = [INTEGER] * 10 + [FLOAT] * 2 + [STRING] * 2 + [POINTER] * 2

def build_printf_str(width, sign, align, zp):
    out = '%'
    if sign > 0:
        if sign == SIGN_PLUS:
            out += '+'
        elif sign == SIGN_SPACE:
            out += ' '
    if zp > 0:
        out += '0'
    if width > 0:
        out += '*'
    out += 'lld'
    print(width)
    print(out)

def build_fmt_str(width, sign, align, zp):
    out = '{'
    if (sign > 0 or zp > 0 or width > 0):
        out += ':'

    if sign > 0:
        if sign == SIGN_PLUS:
            out += '+'
        elif sign == SIGN_SPACE:
            out += ' '
    if zp > 0:
        out += '0'
    if width > 0:
        out += 'w' + str(width)
    out += '}'
    print(out)

def generate_integer():
    i = random.randint(MIN, MAX)
    width = random.randint(0, 32)
    sign = random.choice(SIGNS)
    align = random.choice(ALIGNS)
    zp = 0
    if align == ALIGN_NONE:
        zp = random.choice(ZP)
    print(i)
    build_printf_str(width, sign, align, zp)
    build_fmt_str(width, sign, align, zp)

def generate_float():
    pass

def generate_string():
    pass

def generate_pointer():
    pass

def generate():
    t = random.choice(TYPE_CHOICE)
    if t == INTEGER:
        generate_integer()
    elif t == FLOAT:
        generate_float()
    elif t == STRING:
        generate_string()
    elif t == POINTER:
        generate_pointer()


for i in range(int(sys.argv[1])):
    generate()
