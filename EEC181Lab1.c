// Hello UUorld Program 
// Digital Alliance: Chris Bird, Lillian Deas, Kaila Balancio 

int main(void)
{
//********************************************************************************
//
//		Initializing each value ADDRESS so we can access and change them
//
//********************************************************************************
	//WRITE TO 
	//volatile int* led = 		(int*)0xFF200040;		//Reded LED address
	volatile int* hex3_0 = 		(int*)0xFF200020;		//HEX3_HEX0 address
	volatile int* hex5_4 = 		(int*)0xFF200010;		//HEX5_HEX4 address
	
	//READ FROM
	volatile int* switchptr = 	(int*)0xFF200030;		//SW Slider switch address
	volatile int* pushptr = 	(int*)0xFF200000;		//KEY push button address

//********************************************************************************
//
//	Initializing each integer value to manipulate while/before reading/writing 
//
//********************************************************************************	
	
	int switch_value; 		//Int value for Switch positions
	int push_value = 0; 		//Int value for Buttons pressed
	int toggleScroll = 1; 	//Binary value for HelloUUorld vs Specific Segment
	int hex30 = 0; 	//32-Bit int for HEX3 - HEX0
	int hex3 = 0;
	int hex2 = 0;
	int hex1 = 0;
	int hex0 = 0;
	int hex54 = 0; 				// 32-Bit int for HEX5 - HEX4
	int hex5 = 0;
	int hex4 = 0;
	int specificScrollInt = 0;
	int delay_count = 1000000;
	int infiniteDelay = 0;
	int bullshitVariable;
	int KEY0 = 1;
	int KEY1 = 2;
	int KEY2 = 4;
	int KEY3 = 8;
	int helloUuorld[11] = {118, 121, 56, 56, 63, 62, 62, 63, 80, 56, 94}; //2nd was 121
	int uuorldIter = 0;

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
		
		push_value = *(pushptr);
		if(push_value == KEY3)
			{
				//Starts at scrolling
				if(toggleScroll == 1) //Faster scroll pressed
				{
					//Set to Specific Segments
					toggleScroll = 0;
				}
				else if(toggleScroll == 0)
				{
					//Set to HelloUUorld
					toggleScroll = 1;
				}
			}
	//********************************************************************************
	//
	//							HELLO UUORLD Message
	//
	//********************************************************************************		

		if(toggleScroll == 1) //Scrolling Message
		{
			//DON'T USE EXPONENTS, THEY WILL BREAK EVERYTHING
			//2^0 = 1, 2^8 = 256, 2^16 = 65,536, 2^24 = 16,777,216
			hex5 = helloUuorld[(uuorldIter)%12];
			hex4 = helloUuorld[(uuorldIter+1)%12];
			hex3 = helloUuorld[(uuorldIter+2)%12];
			hex2 = helloUuorld[(uuorldIter+3)%12];
			hex1 = helloUuorld[(uuorldIter+4)%12];
			hex0 = helloUuorld[(uuorldIter+5)%12];
			uuorldIter++;
			if(uuorldIter==12)
			{
				uuorldIter = 0;
			}

			//HELLOU -> ELLOUU -> LLOUUO -> etc

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
			hex0 = 0;
			hex1 = 0;
			hex0 = switch_value; //hex0 holds ALL bits, too many to be useful
			hex0 = hex0 << 25; //Had 10 bits, only want 7, 32-7 = 25, shift left 25 bits, then back to right to 'clear' upper bits
			hex0 = hex0 >> 25; //Now holds 0000_0000_0000_0000_0000_0000_0xxx_xxxx
			//Try using AND when I have the time
			hex1 = switch_value;
			hex1 = hex1 >> 7; //Had 10 bits, only want 3 in places 7-9, 'clear' lower 7 bits
			hex1 = hex1 << 1; //Lower 10 bits went from aa_bbbb_bbbb -> aaab -> aaab_0000_0000
			
			if(specificScrollInt == 0)
			{
				hex30 = (hex1 * 256) + (hex0); //Should now hold 0000_0000_0000_0000_0000_0111_0222_2222
				*(hex3_0) = hex30;
				hex54 = 0;
				*(hex5_4) = hex54; //I AM THE STUPIDEST PERSON EVER
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
				hex30 = 0;
				*(hex3_0) = hex30;
				hex54 = (hex1 * 256) + (hex0);
				*(hex5_4) = hex54;
				specificScrollInt++;
			}
			else if(specificScrollInt == 5)
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
			delay_count = delay_count + 200000;
			//Set delay value to 3 (longer delay time... aka slower);
		}
		
		if (push_value == KEY1) //as soon as button 3 value is low do this
		{
			delay_count = delay_count - 200000;
			//set delay value to 1 (shorter delay time... aka faster);
		}
		bullshitVariable = 0;
		while(bullshitVariable++ < delay_count);
		
	//********************************************************************************
	//
	//					Pause everything until button is pressed
	//
	//********************************************************************************	
		
		if (push_value == KEY0) //as soon as button 4 value is low do this
		{
			infiniteDelay = 1;
			while(infiniteDelay == 1)
			{
				bullshitVariable = 0;
				while(bullshitVariable++ < (delay_count+10000)){};
				

				push_value = *(pushptr); //This is needed! This fixes our problem.
				if(push_value == KEY0)
				{
					infiniteDelay = 0;
				}
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
0 --- 0011_1111 --- 63
H --- 0111_0110 --- 55 -> 118
E --- 0111_1001--- 79 -> 121
L --- 0011_1000--- 14 -> 56
U --- 0011_1110--- 62 -> 62
R --- 0101_0000--- 5 -> 80 //Is lowercase r
D --- 0101_1110--- 61 -> 94 //Is lowercase d
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