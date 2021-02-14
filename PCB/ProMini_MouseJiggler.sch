EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LED:Inolux_IN-PI554FCH D1
U 1 1 6011B94E
P 6450 4000
F 0 "D1" H 6794 4046 50  0000 L CNN
F 1 "Inolux_IN-PI554FCH" H 6794 3955 50  0000 L CNN
F 2 "LED_SMD:LED_Inolux_IN-PI554FCH_PLCC4_5.0x5.0mm_P3.2mm" H 6500 3700 50  0001 L TNN
F 3 "http://www.inolux-corp.com/datasheet/SMDLED/Addressable%20LED/IN-PI554FCH.pdf" H 6550 3625 50  0001 L TNN
	1    6450 4000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 6011C52D
P 6400 2750
F 0 "SW1" H 6400 3035 50  0000 C CNN
F 1 "SW_Push" H 6400 2944 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_Push_1P1T_NO_6x6mm_H9.5mm" H 6400 2950 50  0001 C CNN
F 3 "~" H 6400 2950 50  0001 C CNN
	1    6400 2750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 6011E055
P 6750 2850
F 0 "#PWR0101" H 6750 2600 50  0001 C CNN
F 1 "GND" H 6755 2677 50  0000 C CNN
F 2 "" H 6750 2850 50  0001 C CNN
F 3 "" H 6750 2850 50  0001 C CNN
	1    6750 2850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 6011F0B9
P 6450 4400
F 0 "#PWR0102" H 6450 4150 50  0001 C CNN
F 1 "GND" H 6455 4227 50  0000 C CNN
F 2 "" H 6450 4400 50  0001 C CNN
F 3 "" H 6450 4400 50  0001 C CNN
	1    6450 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 6011F1B2
P 2900 4500
F 0 "#PWR0103" H 2900 4250 50  0001 C CNN
F 1 "GND" H 2905 4327 50  0000 C CNN
F 2 "" H 2900 4500 50  0001 C CNN
F 3 "" H 2900 4500 50  0001 C CNN
	1    2900 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 2750 6750 2750
Wire Wire Line
	6750 2750 6750 2850
Wire Wire Line
	6450 4300 6450 4400
$Comp
L power:+5V #PWR0105
U 1 1 60121443
P 2750 2450
F 0 "#PWR0105" H 2750 2300 50  0001 C CNN
F 1 "+5V" H 2765 2623 50  0000 C CNN
F 2 "" H 2750 2450 50  0001 C CNN
F 3 "" H 2750 2450 50  0001 C CNN
	1    2750 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 2750 6200 2750
Wire Wire Line
	5950 4000 6150 4000
Wire Wire Line
	6450 3700 6450 3600
Text GLabel 5900 2750 0    50   Input ~ 0
SW
Text GLabel 5950 4000 0    50   Input ~ 0
LED
Text GLabel 4550 3150 2    50   Input ~ 0
SW
Text GLabel 4550 2900 2    50   Input ~ 0
LED
$Comp
L Device:C_Small C1
U 1 1 6012A43E
P 5300 3950
F 0 "C1" H 5392 3996 50  0000 L CNN
F 1 "C_Small" H 5392 3905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 5300 3950 50  0001 C CNN
F 3 "~" H 5300 3950 50  0001 C CNN
	1    5300 3950
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR01
U 1 1 6012C86C
P 5300 3850
F 0 "#PWR01" H 5300 3700 50  0001 C CNN
F 1 "+5V" H 5315 4023 50  0000 C CNN
F 2 "" H 5300 3850 50  0001 C CNN
F 3 "" H 5300 3850 50  0001 C CNN
	1    5300 3850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR03
U 1 1 6012CB04
P 6450 3600
F 0 "#PWR03" H 6450 3450 50  0001 C CNN
F 1 "+5V" H 6465 3773 50  0000 C CNN
F 2 "" H 6450 3600 50  0001 C CNN
F 3 "" H 6450 3600 50  0001 C CNN
	1    6450 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 6012CEE1
P 5300 4050
F 0 "#PWR02" H 5300 3800 50  0001 C CNN
F 1 "GND" H 5305 3877 50  0000 C CNN
F 2 "" H 5300 4050 50  0001 C CNN
F 3 "" H 5300 4050 50  0001 C CNN
	1    5300 4050
	1    0    0    -1  
$EndComp
$Comp
L Arduino_ProMicro:Arduino_ProMicro U1
U 1 1 60136A2B
P 3600 3350
F 0 "U1" H 3650 4465 50  0000 C CNN
F 1 "Arduino_ProMicro" H 3650 4374 50  0000 C CNN
F 2 "Arduino_ProMicro:Arduino Pro Micro" H 3150 4350 50  0001 C CNN
F 3 "" H 3150 4350 50  0001 C CNN
	1    3600 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 2600 2750 2600
Wire Wire Line
	2750 2600 2750 2450
Wire Wire Line
	3000 4200 2900 4200
Wire Wire Line
	2900 4200 2900 4300
Wire Wire Line
	3000 4300 2900 4300
Connection ~ 2900 4300
Wire Wire Line
	2900 4300 2900 4400
Wire Wire Line
	3000 4400 2900 4400
Connection ~ 2900 4400
Wire Wire Line
	2900 4400 2900 4500
Wire Wire Line
	4300 2900 4550 2900
Wire Wire Line
	4300 3150 4550 3150
$EndSCHEMATC