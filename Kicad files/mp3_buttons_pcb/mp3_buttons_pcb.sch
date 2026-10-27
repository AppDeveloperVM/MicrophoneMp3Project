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
Text Notes 7650 5050 0    50   ~ 0
Btn 3
Text Notes 8750 5150 1    50   ~ 0
Potentiometer Value
Wire Wire Line
	8250 3400 8250 3900
Connection ~ 7600 3400
Connection ~ 7600 4250
Wire Wire Line
	7600 4250 7600 3400
Wire Wire Line
	7250 3400 7600 3400
$Comp
L power:+5V #PWR0101
U 1 1 610388B3
P 7250 3900
F 0 "#PWR0101" H 7250 3750 50  0001 C CNN
F 1 "+5V" H 7265 4073 50  0000 C CNN
F 2 "" H 7250 3900 50  0001 C CNN
F 3 "" H 7250 3900 50  0001 C CNN
	1    7250 3900
	1    0    0    -1  
$EndComp
Connection ~ 7600 4950
Wire Wire Line
	8550 4950 8550 3400
Connection ~ 7600 4600
Wire Wire Line
	7600 4950 7600 4600
Wire Wire Line
	7850 4950 7600 4950
Wire Wire Line
	8450 4600 8450 3400
Wire Wire Line
	7600 4600 7750 4600
Wire Wire Line
	7600 4250 7600 4600
Wire Wire Line
	7600 4250 7650 4250
$Comp
L Connector:Conn_01x06_Female J1
U 1 1 6103738E
P 8350 3200
F 0 "J1" V 8288 2812 50  0000 R CNN
F 1 "Conn_01x06_Female" V 8197 2812 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 8350 3200 50  0001 C CNN
F 3 "~" H 8350 3200 50  0001 C CNN
	1    8350 3200
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 61036A24
P 7250 3400
F 0 "#PWR0102" H 7250 3150 50  0001 C CNN
F 1 "GND" H 7255 3227 50  0000 C CNN
F 2 "" H 7250 3400 50  0001 C CNN
F 3 "" H 7250 3400 50  0001 C CNN
	1    7250 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 4600 8450 4600
$Comp
L Switch:SW_DIP_x02 SW3
U 1 1 6107981E
P 8150 4950
F 0 "SW3" H 8150 5225 50  0000 C CNN
F 1 "SW_DIP_x02" H 8150 5226 50  0001 C CNN
F 2 "Button_Switch_THT:SW_TH_Tactile_Omron_B3F-10xx" H 8150 4950 50  0001 C CNN
F 3 "~" H 8150 4950 50  0001 C CNN
	1    8150 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 4950 8550 4950
Wire Wire Line
	8350 4250 8250 4250
$Comp
L Switch:SW_DIP_x02 SW1
U 1 1 61070D1D
P 7950 4250
F 0 "SW1" H 7950 4617 50  0000 C CNN
F 1 "SW_DIP_x02" H 7950 4526 50  0001 C CNN
F 2 "Button_Switch_THT:SW_TH_Tactile_Omron_B3F-10xx" H 7950 4250 50  0001 C CNN
F 3 "~" H 7950 4250 50  0001 C CNN
	1    7950 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 3400 8350 4250
Wire Wire Line
	7600 3400 8150 3400
NoConn ~ 7850 4850
NoConn ~ 8450 4850
NoConn ~ 8350 4500
NoConn ~ 8250 4150
Connection ~ 7400 3900
Wire Wire Line
	7400 3900 8250 3900
Wire Wire Line
	7250 3900 7400 3900
Text Notes 7450 5850 0    50   ~ 0
VCC
$Comp
L Switch:SW_DIP_x02 SW2
U 1 1 61077E0B
P 8050 4600
F 0 "SW2" H 8050 4875 50  0000 C CNN
F 1 "SW_DIP_x02" H 8050 4876 50  0001 C CNN
F 2 "Button_Switch_THT:SW_TH_Tactile_Omron_B3F-10xx" H 8050 4600 50  0001 C CNN
F 3 "~" H 8050 4600 50  0001 C CNN
	1    8050 4600
	1    0    0    -1  
$EndComp
Text Notes 7650 4700 0    50   ~ 0
Btn 2
Wire Wire Line
	7400 3900 7400 5900
Wire Wire Line
	7400 5900 9200 5900
Text Notes 8300 5500 0    50   ~ 0
GND
$Comp
L Connector:Conn_01x03_Male J2
U 1 1 6106E8E0
P 9500 5600
F 0 "J2" H 9472 5532 50  0000 R CNN
F 1 "Conn_01x03_Male" H 9472 5623 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 9500 5600 50  0001 C CNN
F 3 "~" H 9500 5600 50  0001 C CNN
	1    9500 5600
	-1   0    0    1   
$EndComp
Wire Wire Line
	9200 5900 9200 5500
Wire Wire Line
	9200 5500 9300 5500
Wire Wire Line
	9300 5600 8650 5600
Wire Wire Line
	8650 5600 8650 3400
Wire Wire Line
	9300 5700 7600 5700
Wire Wire Line
	7600 4950 7600 5700
NoConn ~ 7750 4500
NoConn ~ 7650 4150
$EndSCHEMATC
