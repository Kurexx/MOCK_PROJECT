#define LED__H__
#define LED_Address_bit 8
#define LED_Data_bit    0

static volatile unsigned short Seg[16] ={126           //'0'
                          ,48           //'1'
                          ,109          //'2'
                          ,121          //'3'
                          ,51           //'4'
                          ,91           //'5'
                          ,95           //'6'
                          ,112          //'7'
                          ,127          //'8'
                          ,123          //'9'
                          ,1            //'-'
                          ,79           //'E'
                          ,55           //'H'
                          ,14           //'L'
                          ,103          //'P'
                          ,0            //'blank'
};

static volatile unsigned short Add[16]={1        //Digit 0
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
                     ,12       //Shutdown
                     ,15       //Display test
                     };

#define Test int ((Add[16]<<8)|(15u<<0))
	
