#define LED__H__
#define LED_Address_bit 8
#define LED_Data_bit    0



static volatile unsigned short Seg[16] ={
													 0          //'0'
                          ,1          //'1'
                          ,2          //'2'
                          ,3          //'3'
                          ,4          //'4'
                          ,5          //'5'
                          ,6          //'6'
                          ,7          //'7'
                          ,8          //'8'
                          ,9          //'9'
                          ,10         //'-'
                          ,11         //'E'
                          ,12         //'H'
                          ,13         //'L'
                          ,14         //'P'
                          ,15         //'blank'
};

static volatile unsigned short Add[14]={
											0        //No-Op
                     ,1        //Digit 0
                     ,2        //Digit 1
                     ,3        //Digit 2
                     ,4        //Digit 3
                     ,5        //Digit 4
                     ,6        //Digit 5
                     ,7        //Digit 6
                     ,8        //Digit 7
                     ,9        //Decode mode
                     ,10       //Intensity
                     ,11       //Scan Limit
                     ,12			 //Shutdown
										 ,15			 //Display test
                     };


	
