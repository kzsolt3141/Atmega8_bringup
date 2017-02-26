///*
 //* hcsr04.c
 //*
 //* created: 1/25/2017 11:54:53 pm
 //*  author: zsolt
 //*/ 
//
///*
//c program for distance measurement using ultrasonic sensor and avr microocntroller
 //*/ 
//
//
//static volatile int pulse = 0;
//static volatile int i = 0;
//
//int main(void)
//{
//
    //_delay_ms(50);
    //
    //gicr|=(1<<int0);   // enable int0 interrupt sensing
    //mcucr|=(1<<isc00); // any logical change triggers the interrupt
    //tccr1a = 0;        // normal counter operation
    //
    //sei();
    //
    //while(1)
    //{
       //
    //}
//}
//isr(int0_vect)
//{
    //if (i==1)
    //{
        //tccr1b=0;
        //pulse=tcnt1;
        //tcnt1=0;
        //i=0;
    //}
    //if (i==0)
    //{
        //tccr1b|=(1<<cs10);
        //i=1;
    //}
//}
//