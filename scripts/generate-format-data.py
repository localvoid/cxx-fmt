#!/usr/bin/env python

import sys
import random

random.seed(10)

MIN=-(2**31)-1
MAX=2**31

SIGNS = [None, '+', ' ']
ALIGNS = [None, '<']
ZERO_PADDING = [False, True]

class Int(object):
    def __init__(self):
        self.value = random.randint(MIN, MAX)
        self.width = random.randint(0, 32)
        self.sign = random.choice(SIGNS)
        self.align = random.choice(ALIGNS)
        self.zero_padding = random.choice(ZERO_PADDING) if self.align == None else False

    def to_printf(self):
        out = '%'
        if self.sign:
            out += self.sign
        if self.zero_padding:
            out += '0'
        if self.width > 0:
            out += '*'
        out += 'lld'

        return '%i'

    def to_format(self):
        out = '{'
        if self.sign or self.align or self.width or self.zero_padding:
            out += ':'

        if self.sign:
            out += self.sign
        if self.zero_padding:
            out += '0'
        if self.width > 0:
            out += 'w' + str(self.width)
        out += '}'

        return '{}'

    def serialize(self):
        return 'i64:' + str(self.value)


class Float(object):
    def __init__(self):
        self.value = random.uniform(MIN, MAX)

    def to_printf(self):
        return '%f'

    def to_format(self):
        return '{}'

    def serialize(self):
        return 'f64:' + str(self.value)


class String(object):
    def __init__(self):
        self.value = str(random.randint(0, 2**32))

    def to_printf(self):
        return '%s'

    def to_format(self):
        return '{}'

    def serialize(self):
        return 'str:' + self.value


class Pointer(object):
    def __init__(self):
        self.value = random.randint(0, 2**32)
        self.width = random.randint(0, 32)
        self.align = random.choice(ALIGNS)
        self.zero_padding = random.choice(ZERO_PADDING) if self.align == None else False

    def to_printf(self):
        return '%x'

    def to_format(self):
        return '{}'

    def serialize(self):
        return 'ptr:' + str(self.value)


class Text(object):
    def __init__(self):
        self.value = str(random.randint(0, 2**32))

    def to_printf(self):
        return self.value

    def to_format(self):
        return self.value

    def serialize(self):
        return None


#TYPE_CHOICE = [Int] * 10 + [Float] * 4 + [String] * 10 + [Pointer] * 4 + [Text] * 20
TYPE_CHOICE = [Int] * 20 + [String] * 10 + [Pointer] * 4 + [Text] * 20

for it in range(int(sys.argv[1])):
    result = []
    for i in range(random.randint(3, 8)):
        t = random.choice(TYPE_CHOICE)
        result.append(t())

    printf_fmt = ''.join([t.to_printf() for t in result])
    format_fmt = ''.join([t.to_format() for t in result])
    arguments = []
    for t in result:
        r = t.serialize()
        if r:
            arguments.append(r)

    print(printf_fmt)
    print(format_fmt)
    print(len(arguments))
    print('\n'.join(arguments))
