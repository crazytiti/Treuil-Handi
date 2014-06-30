EESchema Schematic File Version 2  date 30/06/2014 12:20:45
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:arduino_shieldsNCL
LIBS:AS5048B_A
LIBS:treuil-handi-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "30 jun 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ARDUINO_MEGA_SHIELD SHIELD1
U 1 1 53B133FB
P 2650 3650
F 0 "SHIELD1" H 2250 6150 60  0000 C CNN
F 1 "ARDUINO_MEGA_SHIELD" H 2550 950 60  0000 C CNN
F 2 "" H 2650 3650 60  0000 C CNN
F 3 "" H 2650 3650 60  0000 C CNN
	1    2650 3650
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 53B1346F
P 5200 1900
F 0 "SW1" H 5350 2010 50  0000 C CNN
F 1 "calibration" H 5200 1820 50  0000 C CNN
F 2 "~" H 5200 1900 60  0000 C CNN
F 3 "~" H 5200 1900 60  0000 C CNN
	1    5200 1900
	1    0    0    -1  
$EndComp
$Comp
L AS5048B/A U2
U 1 1 53B135E2
P 6600 3650
F 0 "U2" H 6600 3550 50  0000 C CNN
F 1 "AS5048B Pot" H 6600 3100 50  0000 C CNN
F 2 "MODULE" H 6600 3650 50  0001 C CNN
F 3 "DOCUMENTATION" H 6600 3650 50  0001 C CNN
	1    6600 3650
	1    0    0    -1  
$EndComp
$Comp
L AS5048B/A U3
U 1 1 53B135F1
P 6600 5550
F 0 "U3" H 6600 5450 50  0000 C CNN
F 1 "AS5048B moteur" H 6600 5000 50  0000 C CNN
F 2 "MODULE" H 6600 5550 50  0001 C CNN
F 3 "DOCUMENTATION" H 6600 5550 50  0001 C CNN
	1    6600 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 3350 5350 5250
Wire Wire Line
	5350 3350 5850 3350
Wire Wire Line
	5350 5250 5850 5250
Wire Wire Line
	5850 3450 5550 3450
Wire Wire Line
	5550 3450 5550 5350
Wire Wire Line
	5550 5350 5850 5350
Wire Wire Line
	7350 5450 7500 5450
Wire Wire Line
	7500 5450 7500 5550
Wire Wire Line
	7500 5550 7350 5550
Wire Wire Line
	7350 3550 7500 3550
Wire Wire Line
	7500 3550 7500 3650
Wire Wire Line
	7500 3650 7350 3650
$Comp
L GND #PWR01
U 1 1 53B136B0
P 1400 2150
F 0 "#PWR01" H 1400 2150 30  0001 C CNN
F 1 "GND" H 1400 2080 30  0001 C CNN
F 2 "" H 1400 2150 60  0000 C CNN
F 3 "" H 1400 2150 60  0000 C CNN
	1    1400 2150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 53B136BF
P 3750 1400
F 0 "#PWR02" H 3750 1400 30  0001 C CNN
F 1 "GND" H 3750 1330 30  0001 C CNN
F 2 "" H 3750 1400 60  0000 C CNN
F 3 "" H 3750 1400 60  0000 C CNN
	1    3750 1400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 53B136CE
P 1400 4400
F 0 "#PWR03" H 1400 4400 30  0001 C CNN
F 1 "GND" H 1400 4330 30  0001 C CNN
F 2 "" H 1400 4400 60  0000 C CNN
F 3 "" H 1400 4400 60  0000 C CNN
	1    1400 4400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 53B136DD
P 7650 5400
F 0 "#PWR04" H 7650 5400 30  0001 C CNN
F 1 "GND" H 7650 5330 30  0001 C CNN
F 2 "" H 7650 5400 60  0000 C CNN
F 3 "" H 7650 5400 60  0000 C CNN
	1    7650 5400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 53B136EC
P 7650 3500
F 0 "#PWR05" H 7650 3500 30  0001 C CNN
F 1 "GND" H 7650 3430 30  0001 C CNN
F 2 "" H 7650 3500 60  0000 C CNN
F 3 "" H 7650 3500 60  0000 C CNN
	1    7650 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 53B136FB
P 5600 2000
F 0 "#PWR06" H 5600 2000 30  0001 C CNN
F 1 "GND" H 5600 1930 30  0001 C CNN
F 2 "" H 5600 2000 60  0000 C CNN
F 3 "" H 5600 2000 60  0000 C CNN
	1    5600 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 1900 5600 1900
Wire Wire Line
	5600 1900 5600 2000
Wire Wire Line
	7350 3450 7650 3450
Wire Wire Line
	7650 3450 7650 3500
Wire Wire Line
	7350 5350 7650 5350
Wire Wire Line
	7650 5350 7650 5400
Wire Wire Line
	1650 2100 1400 2100
Wire Wire Line
	1400 2000 1400 2150
Wire Wire Line
	1650 2000 1400 2000
Connection ~ 1400 2100
Wire Wire Line
	1650 4250 1400 4250
Wire Wire Line
	1400 4250 1400 4400
Wire Wire Line
	1650 4350 1400 4350
Connection ~ 1400 4350
$Comp
L 3V3 #PWR07
U 1 1 53B1380B
P 1400 1800
F 0 "#PWR07" H 1400 1900 40  0001 C CNN
F 1 "3V3" H 1400 1925 40  0000 C CNN
F 2 "" H 1400 1800 60  0000 C CNN
F 3 "" H 1400 1800 60  0000 C CNN
	1    1400 1800
	1    0    0    -1  
$EndComp
$Comp
L 3V3 #PWR08
U 1 1 53B1381A
P 7750 3600
F 0 "#PWR08" H 7750 3700 40  0001 C CNN
F 1 "3V3" H 7750 3725 40  0000 C CNN
F 2 "" H 7750 3600 60  0000 C CNN
F 3 "" H 7750 3600 60  0000 C CNN
	1    7750 3600
	1    0    0    -1  
$EndComp
$Comp
L 3V3 #PWR09
U 1 1 53B13829
P 7750 5500
F 0 "#PWR09" H 7750 5600 40  0001 C CNN
F 1 "3V3" H 7750 5625 40  0000 C CNN
F 2 "" H 7750 5500 60  0000 C CNN
F 3 "" H 7750 5500 60  0000 C CNN
	1    7750 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 5500 7500 5500
Connection ~ 7500 5500
Wire Wire Line
	7750 3600 7500 3600
Connection ~ 7500 3600
Wire Wire Line
	1650 1800 1400 1800
Wire Wire Line
	5850 3550 5750 3550
Wire Wire Line
	5750 3550 5750 3750
Wire Wire Line
	5750 3650 5850 3650
$Comp
L GND #PWR?
U 1 1 53B13A34
P 5750 3750
F 0 "#PWR?" H 5750 3750 30  0001 C CNN
F 1 "GND" H 5750 3680 30  0001 C CNN
F 2 "" H 5750 3750 60  0000 C CNN
F 3 "" H 5750 3750 60  0000 C CNN
	1    5750 3750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 53B13A43
P 5400 5550
F 0 "#PWR?" H 5400 5550 30  0001 C CNN
F 1 "GND" H 5400 5480 30  0001 C CNN
F 2 "" H 5400 5550 60  0000 C CNN
F 3 "" H 5400 5550 60  0000 C CNN
	1    5400 5550
	1    0    0    -1  
$EndComp
$Comp
L 3V3 #PWR?
U 1 1 53B13A52
P 5550 5700
F 0 "#PWR?" H 5550 5800 40  0001 C CNN
F 1 "3V3" H 5550 5825 40  0000 C CNN
F 2 "" H 5550 5700 60  0000 C CNN
F 3 "" H 5550 5700 60  0000 C CNN
	1    5550 5700
	1    0    0    -1  
$EndComp
Connection ~ 5750 3650
Wire Wire Line
	5850 5450 5400 5450
Wire Wire Line
	5400 5450 5400 5550
Wire Wire Line
	5850 5550 5650 5550
Wire Wire Line
	5650 5550 5650 5700
Wire Wire Line
	5650 5700 5550 5700
$Comp
L CONN_3 K1
U 1 1 53B13AF2
P 6800 1400
F 0 "K1" V 6750 1400 50  0000 C CNN
F 1 "PPM" V 6850 1400 40  0000 C CNN
F 2 "" H 6800 1400 60  0000 C CNN
F 3 "" H 6800 1400 60  0000 C CNN
	1    6800 1400
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 53B13B0D
P 1300 1900
F 0 "#PWR?" H 1300 1990 20  0001 C CNN
F 1 "+5V" H 1300 1990 30  0000 C CNN
F 2 "" H 1300 1900 60  0000 C CNN
F 3 "" H 1300 1900 60  0000 C CNN
	1    1300 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 1900 1300 1900
$Comp
L +5V #PWR?
U 1 1 53B13B82
P 6150 1400
F 0 "#PWR?" H 6150 1490 20  0001 C CNN
F 1 "+5V" H 6150 1490 30  0000 C CNN
F 2 "" H 6150 1400 60  0000 C CNN
F 3 "" H 6150 1400 60  0000 C CNN
	1    6150 1400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 53B13B91
P 6300 1300
F 0 "#PWR?" H 6300 1300 30  0001 C CNN
F 1 "GND" H 6300 1230 30  0001 C CNN
F 2 "" H 6300 1300 60  0000 C CNN
F 3 "" H 6300 1300 60  0000 C CNN
	1    6300 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 1400 6150 1400
Wire Wire Line
	3550 3700 5350 3700
Connection ~ 5350 3700
Wire Wire Line
	3550 3800 5550 3800
Connection ~ 5550 3800
Wire Wire Line
	6450 1500 3550 1500
Wire Wire Line
	6450 1300 6450 1200
Wire Wire Line
	6450 1200 6300 1200
Wire Wire Line
	6300 1200 6300 1300
Wire Wire Line
	3550 1400 3650 1400
Wire Wire Line
	3650 1400 3650 1350
Wire Wire Line
	3650 1350 3750 1350
Wire Wire Line
	3750 1350 3750 1400
Wire Wire Line
	3550 1600 4900 1600
Wire Wire Line
	4900 1600 4900 1900
$EndSCHEMATC
