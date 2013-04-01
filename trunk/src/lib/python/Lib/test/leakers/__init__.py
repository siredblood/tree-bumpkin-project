0023:.:0:3:14=48041e4b:16=47d21313:0039:decimaltestdata:000000000:2:14=48041e4b:16=47d21313:0031:abs.decTest:01932:1:14=48041e4b:16=47d21313:------------------------------------------------------------------------
-- abs.decTest -- decimal absolute value                              --
-- Copyright (c) IBM Corporation, 1981, 2007.  All rights reserved.   --
------------------------------------------------------------------------
-- Please see the document "General Decimal Arithmetic Testcases"     --
-- at http://www2.hursley.ibm.com/decimal for the description of      --
-- these testcases.                                                   --
--                                                                    --
-- These testcases are experimental ('beta' versions), and they       --
-- may contain errors.  They are offered on an as-is basis.  In       --
-- particular, achieving the same results as the tests here is not    --
-- a guarantee that an implementation complies with any Standard      --
-- or specification.  The tests are not exhaustive.                   --
--                                                                    --
-- Please send comments, suggestions, and corrections to the author:  --
--   Mike Cowlishaw, IBM Fellow                                       --
--   IBM UK, PO Box 31, Birmingham Road, Warwick CV34 5JL, UK         --
--   mfc@uk.ibm.com                                                   --
------------------------------------------------------------------------
version: 2.57

-- This set of tests primarily tests the existence of the operator.
-- Additon, subtraction, rounding, and more overflows are tested
-- elsewhere.

precision:   9
rounding:    half_up
maxExponent: 384
minexponent: -383
extended: 1

absx001 abs '1'      -> '1'
absx002 abs '-1'     -> '1'
absx003 abs '1.00'   -> '1.00'
absx004 abs '-1.00'  -> '1.00'
absx005 abs '0'      -> '0'
absx006 abs '0.00'   -> '0.00'
absx007 abs '00.0'   -> '0.0'
absx008 abs '00.00'  -> '0.00'
absx009 abs '00'     -> '0'

absx010 abs '-2'     -> '2'
absx011 abs '2'      -> '2'
absx012 abs '-2.00'  -> '2.00'
absx013 abs '2.00'   -> '2.00'
absx014 abs '-0'     -> '0'
absx015 abs '-0.00'  -> '0.00'
absx016 abs '-00.0'  -> '0.0'
absx017 abs '-00.00' -> '0.00'
absx018 abs '-00'    -> '0'

absx020 abs '-2000000' -> '2000000'
absx021 abs '2000000'  -> '2000000'
precision: 7
absx022 abs '-2000000' -> '2000000'
absx023 abs '2000000'  -> '2000000'
precision: 6
absx024 abs '-2000000' -> '2.00000E+6' Rounded
absx025 abs '2000000'  -> '2.00000E+6' Rounded
precision: 3
absx026 abs '-2000000' -> '2.00E+6' Rounded
absx027 abs '2000000'  -> '2.00E+6' Rounded

absx030 abs '+0.1'            -> '0.1'
absx031 abs '-0.1'            -> '0.1'
absx032 abs '+0.01'           -> '0.01'
absx033 abs '-0.01'           -> '0.01'
absx034 abs '+0.001'          -> '0.001'
absx035 abs '-0.001'          -> '0.001'
absx036 abs '+0.000001'       -> '0.000001'
absx037 abs '-0.000001'       -> '0.000001'
absx038 abs '+0.000000000001' -> '1E-12'
absx039 abs '-0.000000000001' -> '1E-12'

-- examples from decArith
precision: 9
absx040 abs '2.1'     ->  '2.1'
absx041 abs '-100'    ->  '100'
absx042 abs '101.5'   ->  '101.5'
absx043 abs '-101.5'  ->  '101.5'

-- more fixed, potential LHS swaps/overlays if done by subtract 0
precision: 9
absx060 abs '-56267E-10'  -> '0.0000056267'
absx061 abs '-56267E-5'   -> '0.56267'
absx062 abs '-56267E-2'   -> '562.67'
absx063 abs '-56267E-1'   -> '5626.7'
absx065 abs '-56267E-0'   -> '56267'

-- overflow tests
maxexponent: 999999999
minexponent: -999999999
precision: 3
absx120 abs 9.999E+999999999 -> Infinity Inexact Overflow Rounded

-- subnormals and underflow
precision: 3
maxexponent: 999
minexponent: -999
absx210 abs  1.00E-999        ->   1.00E-999
absx211 abs  0.1E-999         ->   1E-1000   Subnormal
absx212 abs  0.10E-999        ->   1.0E-1000 Subnormal
absx213 abs  0.100E-999       ->   1.0E-1000 Subnormal Rounded
absx214 abs  0.01E-999        ->   1E-1001   Subnormal
-- next is rounded to Emin
absx215 abs  0.999E-999       ->   1.00E-999 Inexact Rounded Subnormal Underflow
absx216 abs  0.099E-999       ->   1.0E-1000 Inexact Rounded Subnormal Underflow
absx217 abs  0.009E-999       ->   1E-1001   Inexact Rounded Subnormal Underflow
absx218 abs  0.001E-999       ->   0E-1001   Inexact Rounded Subnormal Underflow Clamped
absx219 abs  0.0009E-999      ->   0E-1001   Inexact Rounded Subnormal Underflow Clamped
absx220 abs  0.0001E-999      ->   0E-1001   Inexact Rounded Subnormal Underflow Clamped

absx230 abs -1.00E-999        ->   1.00E-999
absx231 abs -0.1E-999         ->   1E-1000   Subnormal
absx232 abs -0.10E-999        ->   1.0E-1000 Subnormal
absx233 abs -0.100E-999       ->   1.0E-1000 Subnormal Rounded
absx234 abs -0.01E-999        ->   1E-1001   Subnormal
-- next is rounded to Emin
absx235 abs -0.999E-9