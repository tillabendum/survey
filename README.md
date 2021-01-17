NAME
====

  survey - represent integer at given format

SYNOPSIS
========

  survey -f FORMAT ARG

DESCRIPTION
===========

  Integer argument is viewed as binary value. Then this value is splitted and
  represented according to format.

FORMAT
======

  Format string is a character sequence that is either charcters as is or escape
  sequences. Escape sequence starts with '%' symbol and terminates with one of
  those characters 'x' 'b' 'd' 'n'. Between % and termination character there is
  a decimal that state number of bits.

  There is no way print '%' as is.

Escape sequence format
----------------------

  %4x -- 4 bits that must be converted to hexadecimal

  %1b -- 1 bit that is represented as is

  %8d -- 8 bits represented

  %3n -- (nihil) 3 bits are not represented and dropped away


    1 0 1  0 1  0 1 1 0 1 = 685
    -----  ---  ---------
     %3d   %2n    %5x

    >> survey -f '%3d%2n %5x' 685
    5 d

  Leftmost 3 bits are represented as decimal, next 2 bits are ignored, then
  space ( between 5 and d ) shown as is and 5 bit shown as hex.

  If argument binary representation takes less bits than format demands, missing
  leftmost digits are padded with zeros.

    0 0 0  0 1  0 1 1 0 1 = 45
    -----  ---  ---------
     %3d   %2n    %5x

    >> survey -f '%3d%2n %5x' 45
    0 d

Limitations
-----------

  If argument size in binary form exceeds number of bits that format claims,
  result is inconsistent.

    >> survey '%2d' 4
    2

ARG
===

  Integer decimal

EXAMPLES
========

    0 0 0 0 0 0  1 0 0 1 0  0 0 1 = 145
    -----------  ---------  -----
        %6n         %5x      %3b

    >>survey -f 'foo:%6nbar=%5x haos=%3b' 145
    foo:bar=12 haos=001

TODO
====

  * Allow argument sizes that exceed format
  * Allow non-decimal argument
  * Allow multiple arguments

