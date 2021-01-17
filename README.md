NAME
====

  survey - represent integer in given format

SYNOPSIS
========

  survey -f FORMAT ARG

DESCRIPTION
===========

  TODO:

FORMAT
======

  Escape sequence format.

  %4x -- 4 bits that must be converted to hexadecimal

  %1b -- 1 bit that is represented as is

  %8d -- 8 bits represented

  %3n -- 3 bits are not represented

ARG
===

  Integer decimal

EXAMPLES
========

    >> survey  -f 'foo:%6n bar=%5x haos=%3b' 145
    foo: bar=12 haos=0b001


