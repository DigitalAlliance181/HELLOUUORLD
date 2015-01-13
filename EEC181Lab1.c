//Created by CBird on 1-12 at 11:00pm
//Some parts finished by CBird on 1-13 at 3 am
//Completely finished, aside from debugging, by CBird on 1-13 at 3pm

// Hello UUorld Program 
// Digital Alliance: Chris Bird, Lillian Deas, Kaila Balancio 


int main(void)
{

//********************************************************************************
//
//		Initializing each value ADDRESS so we can access and change them
//
//********************************************************************************
	//Pointers to HW that we WRITE TO 
	volatile int* led = 		(int*)0xFF200040;		//Reded LED address
	volatile int* hex3_0 = 		(int*)0xFF200020;		//HEX3_HEX0 address
	volatile int* hex5_4 = 		(int*)0xFF200010;		//HEX5_HEX4 address
	
	//Pointers to HW that we READ FROM
	volatile int* switchptr = 	(int*)0xFF200030;		//SW Slider switch address
	volatile int* pushptr = 	(int*)0xFF200000;		//KEY push button address

//********************************************************************************
//
//	Initializing each integer value to manipulate while/before reading/writing 
//
//********************************************************************************	
	
	int switch_value; 		//Int value for Switch positions
	int push_value; 		//Int value for Buttons pressed
	int toggleScroll = 1; 	//Binary value for HelloUUorld vs Specific Segment
	int hex30; 	//32-Bit int for HEX3 - HEX0
	int hex3;
	int hex2;
	int hex1;
	int hex0;
	int hex54; 				// 32-Bit int for HEX5 - HEX4
	int hex5;
	int hex4;
	int LBit = 2;			//Bits to determine which part of the scrolling it's on
	int OBit = 1;
	int UBit = 1;
	int specificScrollInt = 0;
	int delaycount = 1000000000;
	int infiniteDelay = 0;
	
//********************************************************************************
//
//			Main loop that checks for changes in buttons presses/switches
//
//********************************************************************************

	while(1)
	{
	
//********************************************************************************
//
//			Scrolling HEX vs Scrolling Specific Segments
//
//********************************************************************************
	
	push_value = *(pushptr)
	//Figure out how to read button values from single int (maybe 8 bits each?) and set to someCorrectValue
	if(push_value == KEY3)
		{
			//Starts at scrolling
			if(push_value == KEY1) //Faster scroll pressed
			{
				//WAS HelloUUorld, NOW Specific Segments
				toggleScroll == 0;
			}
			else
			{
				//WAS Speceific Segments, NOW HelloUUorld
				toggleScroll == 1;
			}
		}
	if(toggleScroll == 1) //Scrolling Message
	{
		//DON'T USE EXPONENTS, THEY WILL BREAK EVERYTHING
		//2^0 = 1, 2^8 = 256, 2^16 = 65,536, 2^24 = 16,777,216
		
		/*//Set HEX5-1 to the values of HEX4-0
		hex5 = hex4;
		hex4 = hex3;
		hex3 = hex2;
		hex2 = hex1;
		hex1 = hex0;
		
		//Deconstruct hex30 and hex54 to their separate parts and store in hex0, hex1 etc
		hex5 = hex5_4();
		hex4 = hex5_4();
		hex3 = hex3_0();
		hex2 = hex3_0();
		hex1 = hex3_0();
		hex0 = hex3_0();*/

		//Then determine next value for HEX 0 and load that
		//This could be much nicer, but I'm tired
		if(hex0 == 200) //Prev was H, will now display ORLDHE
		{
			hex5 = 129;
			hex4 = 246;
			hex3 = 241;
			hex2 = 192;
			hex1 = 200;
			hex0 = 176;
		}
		else if(hex0 == 176) //Prev was E, will now display RLDHEL
		{
			hex5 = 246;
			hex4 = 241;
			hex3 = 192;
			hex2 = 200;
			hex1 = 176;
			hex0 = 241;
		}
		else if(hex0 == 241 && LBit == 2) //Prev was L and bit is 2, will now display LDHELL
		{
			hex5 = 241;
			hex4 = 192;
			hex3 = 200;
			hex2 = 176;
			hex1 = 241;
			hex0 = 241;
			LBit--; //Set to 1
		}
		else if(hex0 == 241 && LBit == 1) //Prev was L and bit is 1, will now display DHELLO
		{
			hex5 = 192;
			hex4 = 200;
			hex3 = 176;
			hex2 = 241;
			hex1 = 241;
			hex0 = 129;
			LBit--; //Set to 0
		}
		else if(hex0 == 129 && OBit == 1) //Prev was 0 and bit is 1, will now display HELLOU
		{
			hex5 = 200;
			hex4 = 176;
			hex3 = 241;
			hex2 = 241;
			hex1 = 129;
			hex0 = 206;
			OBit--; //Set to 0
		}
		else if(hex0 == 206 && UBit == 1) //Prev was U and bit is 1, will now display ELLOUU
		{
			hex5 = 176;
			hex4 = 241;
			hex3 = 241;
			hex2 = 129;
			hex1 = 206;
			hex0 = 206;
			UBit--; //Set to 0
		}
		else if(hex0 == 206 && UBit == 0) //Prev was U and bit is 0, will now display LLOUUO
		{
			hex5 = 241;
			hex4 = 241;
			hex3 = 129;
			hex2 = 206;
			hex1 = 206;
			hex0 = 129;
			UBit = 1;
		}
		else if(hex0 == 129 && OBit == 0) //Prev was 0 and bit is 0, will now display LOUUOR
		{
			hex5 = 241;
			hex4 = 129;
			hex3 = 206;
			hex2 = 206;
			hex1 = 129;
			hex0 = 246;
			OBit = 1;
		}
		else if(hex0 == 246) //Prev was R, will now display OUUORL
		{
			hex5 = 129;
			hex4 = 206;
			hex3 = 206;
			hex2 = 129;
			hex1 = 246;
			hex0 = 241;
		}
		else if(hex0 == 241 && LBit == 0) //Prev was L and bit is 0, will now display UUORLD
		{
			hex5 = 206;
			hex4 = 206;
			hex3 = 129;
			hex2 = 246;
			hex1 = 241;
			hex0 = 192;
			LBit = 2;
		}
		else if(hex0 == 192) //Prev was D, will now display UORLDH
		{
			hex5 = 206;
			hex4 = 129;
			hex3 = 246;
			hex2 = 241;
			hex1 = 192;
			hex0 = 200;
		}
		
		//Add them all together to make correct hex displays
		hex30 = (hex3 * 16777216) + (hex2 * 65536) + (hex1 * 256) + (hex0);
		hex54 = (hex5 * 256) + (hex4);
		
		//Set new values to hex displays
		*(hex3_0) = hex30;
		*(hex5_4) = hex54;
		
	}
	if(toggleScroll == 0) //Specific Segment Display
	//THIS NEEDS TO BE DONE
	{
		//Take switch values, and correspond them to specific segments
		//SW0 controls top segment, and continues clockwise with SW1, 2, 3, 4, and 5
		//SW6 controls middle segment of first display
		//SW7 controls top segment of second display, SW8 and SW9 control right side
		//0000_0000_0000_0000_1xxx_xxxx_1xxx_xxxx
		//When Switch is DOWN (off) segment is off
		
		//Load current values of the switches into the 32-bit int
		switch_value = *(switchptr);
		hex0 = switch_value; //hex0 holds ALL bits, too many to be useful
		hex0 = hex0 << 25; //Had 10 bits, only want 7, 32-7 = 25, shift left 25 bits, then back to right to 'clear' upper bits
		hex0 = hex0 >> 25; //Now holds 0000_0000_0000_0000_0000_0000_0xxx_xxxx
		hex1 = switch_value; //hex1 holds ALL bits, too many to be useful
		hex1 = hex1 >> 7; //Had 10 bits, only want 3 in places 7-9, 'clear' lower 7 bits
		hex1 = hex1 << 8; //Lower 10 bits went from aa_bbbb_bbbb -> aaab -> aaab_0000_0000
		//Hex1 now holds the proper value to show on hex1
		
		if(specificScrollInt == 0)
		{
			hex30 = (hex1 * 256) + (hex0); //Should now hold 0000_0000_0000_0000_0000_0111_0222_2222
			*(hex3_0) = hex30; //Write back to hex displays
			//THIS WILL DISPLAY ON HEX1 AND HEX0 WITH THE CORRECT THINGS SHOWN ON THE SWITCHES
			specificScrollInt++;
		}
		else if(specificScrollInt == 1)
		{
			hex30 = (hex1 * 65536) + (hex0*256); 
			*(hex3_0) = hex30;
			specificScrollInt++;
		}
		else if(specificScrollInt == 2)
		{
			hex30 = (hex1 * 16777216) + (hex0*65536); 
			*(hex3_0) = hex30;
			specificScrollInt++;
		}
		else if(specificScrollInt == 3)
		{
			hex30 = (hex0 *16777216); 
			*(hex3_0) = hex30;
			hex54 = (hex1);
			*(hex5_4) = hex54;
			specificScrollInt++;
		} 
		else if(specificScrollInt == 4)
		{
			hex54 = (hex0 * 256) + (hex1);
			*(hex5_4) = hex54;
			specificScrollInt++;
		}
		else(specificScrollInt == 5)
		{
			hex30 = (hex1); 
			*(hex3_0) = hex30;
			hex54 = (hex0 * 256);
			*(hex5_4) = hex54;
			specificScrollInt = 0;
		}
		
		//Only need 01, 12, 23, 34, 45, 51 6 different scroll sections
		
		//setSpecificBit of specificSegmentDisplay to 0 = switch_value;
	}

	
//********************************************************************************
//
//						Scroll Speed Changers (+ or -)
//
//********************************************************************************
	
	//Scroll Speed Variance
	
	if (push_value == KEY2) //as soon as button 2 value is low do this
	{
		delay_count = delay_count + 200000000;
		//Set delay value to 3 (longer delay time... aka slower);
	}
	
	if (push_value == KEY1) //as soon as button 3 value is low do this
	{
		delay_count = delay_count - 200000000;
		//set delay value to 1 (shorter delay time... aka faster);
	}
	bullshitVariable = 0;
	while(bullshitVariable++ < delay_count);
	
//********************************************************************************
//
//					Pause everything until button is pressed
//
//********************************************************************************	
	
	else if (push_vaule == KEY0) //as soon as button 4 value is low do this
	{
		infiniteDelay = 1;
		while(infiniteDelay == 1)
		{
			if(push_value == KEY0)
			{
				infiniteDelay = 0;
			}
		}
	}
}

//********************************************************************************
//
//			BASIC LOGIC FOR HEX BIT-CODE MANIPULATION IN DECIMAL
//
//********************************************************************************
/*Basic Facts:
- HEX3-HEX0 is stored in one 32-bit integer
- HEX5_HEX4 is stored in one 32-bit integer
- Each hex display gets 8 bits of that 32-bit integer
- HEX5_HEX4 has it's first 16 bits as 0 since there are only 2 displays there
- HEX3_HEX0 is arranged like this: 3333_3333_2222_2222_1111_1111_0000_0000
- HEX5_HEX4 is arranged like this: xxxx_xxxx_xxxx_xxxx_5555_5555_4444_4444
- Scrolling increments to the left, so HEX0 gets put onto HEX1, HEX1 onto HEX2 etc
BUT HOW TO PUT THESE VALUES IN WHEN WE CANNOT WORK WITH BITS BUT MUST WORK WITH DECIMAL?
1. Storing a number in decimal values but treating it as binary works perfectly
2. Say we want to store value 3 (0000_0011) in HEX3, we cannot just mask rest with 0000s and add 
3. Treat it like binary, if we want to turn 0000_0011 into 0000_0011_0000_0000_0000_0000_0000_0000, just multiply by 2^24
4. So we can have our function say int HEX30 = 3 * (2^24) and it will give us the equivalent of the above result
5. What this means, is if we want HEX3 to have 3, HEX2 to have 2, HEX1 to have 9, and HEX0 to have 1, we simply do the following
(134 * 2^24) + (146 * 2^16) + (140 * 2^8) + (207 * 2^0) = HEX30 and it will display properly
6. What this means, is we must convert each displayed digit to it's corresponding 8-bit binary code, see below 

ALL ACTIVE LOW
To Display _____ use binary code ______ which in decimal is ________	
0 --- 1000_0001 --- 129
1 --- 1100_1111 --- 207
2 --- 1001_0010 --- 146
3 --- 1000_0110 --- 134
4 --- 1100_1100 --- 204
5 --- 1010_0100 --- 164
6 --- 1010_0000 --- 160
7 --- 1000_1111 --- 143
8 --- 1000_0000 --- 128
9 --- 1000_1100 --- 140
H --- 1100_1000 --- 200
E --- 1011_0000 --- 176
L --- 1111_0001 --- 241
U --- 1100_1110 --- 206
R --- 1111_0110 --- 246 //Is lowercase r
D --- 1100_0000 --- 192 //Is lowercase d
*/

//********************************************************************************
//
//					How to use Delay for scroll speeds
//
//********************************************************************************
/*-We will be delaying our scroll using "useless" loops that take up time
-For pause, we will have an endless loop that is constantly checking if the pause button has been pressed again
-We will increase or decrease the number of useless loop iterations based on how fast a speed we want
-If we have no delay, it will change every cycle, which is very fast
*/