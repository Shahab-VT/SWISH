EESchema Schematic File Version 2
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
EELAYER 25 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "twoHall2"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Conn_01x04 J1
U 1 1 5C4A4F6F
P 2800 2100
F 0 "J1" H 2800 2300 50  0000 C CNN
F 1 "Conn_01x04" H 2800 1800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 2800 2100 50  0001 C CNN
F 3 "" H 2800 2100 50  0001 C CNN
	1    2800 2100
	-1   0    0    -1  
$EndComp
$Comp
L 2N3904 Q1
U 1 1 5C4A5005
P 4050 1950
F 0 "Q1" H 4250 2025 50  0000 L CNN
F 1 "2N3904" H 4250 1950 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Molded_Narrow" H 4250 1875 50  0001 L CIN
F 3 "" H 4050 1950 50  0001 L CNN
	1    4050 1950
	1    0    0    -1  
$EndComp
$Comp
L 2N3904 Q2
U 1 1 5C4A5047
P 4950 2700
F 0 "Q2" H 5150 2775 50  0000 L CNN
F 1 "2N3904" H 5150 2700 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Molded_Narrow" H 5150 2625 50  0001 L CIN
F 3 "" H 4950 2700 50  0001 L CNN
	1    4950 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 2150 4150 3150
Wire Wire Line
	4150 3150 5050 3150
Wire Wire Line
	5050 3150 5050 2900
Wire Wire Line
	4750 2700 3700 2700
Wire Wire Line
	3700 2700 3700 1950
Wire Wire Line
	3700 1950 3850 1950
Wire Wire Line
	3000 2000 3200 2000
Wire Wire Line
	3200 1650 3200 2950
Wire Wire Line
	3200 1650 4150 1650
Wire Wire Line
	4150 1650 4150 1750
Wire Wire Line
	3000 2100 3700 2100
Connection ~ 3700 2100
Wire Wire Line
	3000 2200 5050 2200
Wire Wire Line
	5050 2200 5050 2500
Wire Wire Line
	3000 2300 4150 2300
Connection ~ 4150 2300
$Comp
L Conn_01x04 J2
U 1 1 5C53428F
P 2800 3050
F 0 "J2" H 2800 3250 50  0000 C CNN
F 1 "Conn_01x04" H 2800 2750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 2800 3050 50  0001 C CNN
F 3 "" H 2800 3050 50  0001 C CNN
	1    2800 3050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3200 2950 3000 2950
Connection ~ 3200 2000
Wire Wire Line
	3000 3050 3300 3050
Wire Wire Line
	3300 3050 3300 2100
Connection ~ 3300 2100
Wire Wire Line
	3000 3150 3400 3150
Wire Wire Line
	3400 3150 3400 2200
Connection ~ 3400 2200
Wire Wire Line
	3000 3250 3500 3250
Wire Wire Line
	3500 3250 3500 2300
Connection ~ 3500 2300
$EndSCHEMATC
