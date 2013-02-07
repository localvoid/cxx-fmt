#!/usr/bin/env python

import sys
import random
import argparse

parser = argparse.ArgumentParser(description='Script for generating data to test/benchmark fmt library')
parser.add_argument('--count', type=int, default=1000,
                    help='amount of inputs to generate [default: 1000]')
parser.add_argument('--args', type=int, default=4,
                    help='amount of args that should be generated for each input [default: 4]')
parser.add_argument('--seed', type=int, default=0,
                    help='seed for random number generator [default: 0]')
parser.add_argument('--enable-printf', action='store_true',
                    help='generate printf format string')
parser.add_argument('--disable-width', action='store_true',
                    help='disable generating width option')
parser.add_argument('--disable-int-type', action='store_true',
                    help='disable generating integers')
parser.add_argument('--disable-string-type', action='store_true',
                    help='disable generating strings')
parser.add_argument('--disable-text-type', action='store_true',
                    help='disable generating texts')

args = parser.parse_args()

random.seed(args.seed)

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
        if not args.disable_width and self.width > 0:
            out += '*'
        out += 'lli'
        return out

    def to_format(self):
        out = '{'
        if self.sign or self.align or self.width or self.zero_padding:
            out += ':'

        if self.sign:
            out += self.sign
        if self.zero_padding:
            out += '0'
        if not args.disable_width and self.width > 0:
            out += 'w' + str(self.width)
        out += '}'

        return out

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


class Text(object):
    def __init__(self):
        self.value = str(random.randint(0, 2**32))

    def to_printf(self):
        return self.value

    def to_format(self):
        return self.value

    def serialize(self):
        return None


TYPE_CHOICE = []
if not args.disable_int_type:
    TYPE_CHOICE += [Int] * 20
if not args.disable_string_type:
    TYPE_CHOICE += [String] * 10
if not args.disable_text_type:
    TYPE_CHOICE += [Text] * 20

for it in range(args.count):
    result = []
    i = 0
    while i < args.args:
        t = random.choice(TYPE_CHOICE)
        if t is Text:
            i -= 1
        result.append(t())
        i += 1

    print(''.join([t.to_format() for t in result]))

    if args.enable_printf:
        print(''.join([t.to_printf() for t in result]))

    arguments = []
    for t in result:
        r = t.serialize()
        if r:
            arguments.append(r)

    print(len(arguments))
    if arguments:
        print('\n'.join(arguments))
