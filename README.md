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

  Format string is a character sequence that is either characters as is or
  escape sequences.

Escape sequence format
----------------------

  Escape sequence starts with '%' symbol and terminates with
  one of those characters 'x' 'h' 'b' 'd' 'i' 'n'. Between % and termination
  characters 'x' 'h' 'b' 'd' 'i' 'n' must be a decimal number that states number
  of bits in a field

  'x' and 'h' terminators are equivalent

  'd' and 'i' terminators are equivalent

  There is no way to print '%' as is.


  %4x or %4h  -- 4 bits that must be converted to hexadecimal

  %1b         -- 1 bit that is represented as is

  %8d or %8i  -- 8 bits represented in signed decimal format

  %6u         -- 6 bits represented in unsigned decimal format

  %3n         -- (nihil) 3 bits are not represented and dropped away


    1 0 1  0 1  0 1 1 0 1 = 685
    -----  ---  ---------
     %3u   %2n    %5x

    >> survey -f '%3d%2n %5x' 685
    5 d

  Leftmost 3 bits are represented as unsigned decimal, next 2 bits are ignored,
  then space ( between 5 and d ) shown as is and 5 bit shown as hex.

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

  Integer decimal (e.g 123) or hexadecimal (e.g 0x453)

EXAMPLES
========

    0 0 0 0 0 0  1 0 0 1 0  0 0 1 = 145
    -----------  ---------  -----
        %6n         %5x      %3b

    >>survey -f 'foo:%6nbar=%5x haos=%3b' 145
    foo:bar=12 haos=001

BUILD
=====

  make


TODO
====

  * Allow multiple arguments (repetitive format application)
  * Allow stdin as argument source
  * Allow argument sizes that exceed format ( probably by reversing printout )
  * Allow dump formatting (with format that contains %\)
  * Allow file reading for format (-F option)
  * Allow enumeration format ( %3{111=GA, 000=TA, 001=EXA}e)
  * Make format options h<->x d<->i
