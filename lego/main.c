#include <kipr/botball.h>
#include <math.h>
void wait_next()//waits for 'C'
{
	while(!c_button_clicked()) msleep(20);
}

int is_done()
{
	return c_button_clicked();
}

void next(const char *text)
{
	console_clear();
  	//Sets text as current Test
	printf("%s\n", text);
	printf("Press \"C\" to begin.\n");
  	//waits for 'C'
	wait_next();
	printf("Starting...\n");
	msleep(1000);
}

void done_message(int small)
{
  	//clears screen
	console_clear();
	if(!small) printf("Press \"C\" once finished.\n");
}

void servoTest()
{
	next("Servo Test");
	double theta = 0.0;
  	//enables all servos
	enable_servo(0);
	enable_servo(1);
	enable_servo(2);
	enable_servo(3);
  	//oscillates the servos back and forth
    int y = 0;
    int d = 0;
	while(d<2) {
		done_message(0);
		theta += 0.2;
		const int pos = sin(theta) * 450 + 512;
		printf("Servo position: %d\n", pos);
        set_servo_position(0, 971);
		set_servo_position(1, 0);
		set_servo_position(2, 700);
		set_servo_position(3, 300);
        msleep(500);
		set_servo_position(0, 1350);
		set_servo_position(1, 400);
		set_servo_position(2, 1000);
		set_servo_position(3, 1400);
		msleep(500);
        d+=1;
        
	}
  	//disables all servos
	disable_servo(0);
	disable_servo(1);
	disable_servo(2);
	disable_servo(3);
}

void motorTest()
{
	next("Motor Test");
	double theta = 0.0;
  	//oscillates all motors back and forth
	while(!is_done()) {
		done_message(0);
		theta += 0.2;
		const int vel = sin(theta) * 100;
		printf("Motor velocity: %d\n", vel);
		motor(0, vel);
		motor(1, vel);
		motor(2, vel);
		motor(3, vel);
		msleep(20);
	}
  	//turns off all motors
	ao();
}

void analogTest()
{
	next("Analog Test");
  	int i=0;
  	//prints out 'Digital 0-9:'
  	for(;i<10;++i){
      	display_printf(0,i,"Digital %d: ",i);
    }
  	i=0;
  	//prints out 'Analog 0-5:'
  	for(;i<6;++i){
      	display_printf(15,i,"Analog %d: ",i);
    }
  	//prints out 'Accel X:        Y:      Z: '    
  	display_printf(0,11,"Accel X: ");
  	display_printf(15,11," Y: ");
  	display_printf(23,11," Z: ");
  	//prints out 'Left:   Right: '
  	display_printf(0,12,"Left: ");
  	display_printf(8,12,"Right: ");
	while(!is_done()) {
		done_message(1);
		publish();
      	i=0;
      	//prints out all digital values
      	for(;i<10;++i){
      		display_printf(11,i,"%d",digital(i));
    	}
      	i=0;
      	//prints out all analog values
      	for(;i<6;++i){
      		display_printf(25,i,"%d   ",analog(i));
    	}
      	//prints out all accelerometer values
      	display_printf(8,11,"%d  ",accel_x());
  		display_printf(18,11,"%d  ",accel_y());
  		display_printf(26,11,"%d  ",accel_z());
      	//prints out Left and Right button values
      	display_printf(6,12,"%d",left_button());
      	display_printf(15,12,"%d",right_button());
		msleep(20);
	}
	ao();
}


// servo variables
int claw_servo = 0;
int main_arm_servo = 1;
int lift_arm_servo = 2;
int pvc_arm_servo = 3;

// motor variables
int lm = 0;
int rm = 1;

// sensor variables
int touch_sensor = 9; // digital
int button_sensor = 0; //digital
// analog
int rear_light_sensor = 2;
int front_light_sensor = 0;

// functions
void ssp(int port, int position){
    set_servo_position(port, position);
}

void stop_motors() {
    motor(lm, 0);
    motor(rm, 0);
    msleep(200);
}

int main()
{
    ssp(0, 971);
    ssp(1, 0);
    ssp(2, 700);
    ssp(3, 500);
    msleep(400);
    
    motor(0, -70);
    motor(1,-70);
    msleep(2500);
    ao();
	//motorTest();//runs motor test
	analogTest();//runs sensor test
    
    enable_servos();
    
    // starting pos

    ssp(claw_servo, 971);
    ssp(main_arm_servo, 0);
    ssp(lift_arm_servo, 700);
    ssp(pvc_arm_servo, 300);
    msleep(500);
    // inital--
    wait_for_light(5);
    shut_down_in(119);

    // move until black tape
    
    /*cmpc(0);
    cmpc(1);
    while (analog(rear_light_sensor)<=3700)
    {
        if(gmpc(0) > gmpc(1)) {
          motor(1, 70);
          motor(0, 67);
        } else if (gmpc(0) < gmpc(1)) {
           motor(1, 67);
           motor(0, 70);
        } else {
            motor(1, 70);
          	motor(0, 70);
        }
        
    }
    stop_motors();*/
    
    while (analog(rear_light_sensor)<=2700)
    {
        motor(0, 70);
        motor(1, 70);
        
    }
    stop_motors();
    
    
 
    
    motor(lm,-50);
    motor(rm,-50);
    msleep(400);
    stop_motors();
   
  

    // lower pvc arm to get pvc
    int s = 300;
    while (s <= 1700){
        ssp(pvc_arm_servo, s);
        s += 20;
        msleep(5);
    }
    
     msleep(150);

    
    stop_motors();
    
    // go back until black tape
    
    cmpc(0);
    while (analog(front_light_sensor) <= 2950 || gmpc(0) > -4000){
        motor(lm, -50);
        motor(rm, -50);
    }

    // continue going back for 1.5 seconds
    motor(lm, -50);
    motor(rm, -50);
    msleep(1150);
    
    motor(lm, -5);
    motor(rm, -5);
    msleep(1400);
    
    
    

    stop_motors();
    
    /*motor(lm, 50);
    motor(rm, -50);
    msleep(150);
    stop_motors();*/

    motor(lm,50);
    motor(rm,-50);
    msleep(150);
    ao();  

    motor(lm,50);
    motor(rm,50);
    msleep(300);

    motor(lm,-50);
    motor(rm,50);
    msleep(200);




    
    

    // move forward until black tape
    while (analog(rear_light_sensor)<=2700)
    {
     motor(lm,50);
     motor(rm,50);   
        
    }
    stop_motors();
    
    /*motor(lm, -50);
    motor(rm, 50);
    msleep(300);
    stop_motors();*/
    
    /*motor(lm, 30);
    motor(rm, 30);
    msleep(1000);*/


    motor(lm, 50);
    motor(rm, -50);
    msleep(1000);//950
    
    stop_motors();

    motor(lm, 15);
    motor(rm, 15);
    msleep(3000);
    stop_motors();


    
    ssp(pvc_arm_servo, 300);
    msleep(400);
    
    
    /*motor(lm, -50);
    motor(rm, -50);
    msleep(450);*/
    
    motor(lm, -50);
    motor(rm, 0);
    msleep(1350);
    
    
    motor(lm, 50);
    motor(rm, 50);
    msleep(250);
    
    /*motor(lm, 10); // 10
    motor(rm, 50);
    msleep(3000);*/

    while(analog(front_light_sensor) <= 3200) {
        motor(lm, 10); // 10
        motor(rm, 50);
    }


    
    motor(lm, 7);
    motor(rm, 50);
    msleep(400); // change in testijg


    
    
    stop_motors();
    
    
    /*motor(lm, 0);
    motor(rm, 25);
    msleep(500);
    
    while(analog(front_light_sensor) > 3100) {
        motor(lm, 0);
    	motor(rm, 10);
    }*/
    
    stop_motors();
    /*motor(lm, 100);
    motor(rm, 98);
    msleep(1000);*/
    cmpc(0);
    while(gmpc(0) <700){
        if (analog(front_light_sensor) > 2900){
           motor(lm, 20);
            motor(rm,50);
        } else {
           motor(rm,20);
           motor(lm, 50);
               
        }
    }
    
    
    //follow the line up the ramp until touched
    cmpc(0);
    while (digital(touch_sensor) == 0){
        if (analog(front_light_sensor) > 3600){
            if(gmpc(0) < 1000){
                motor(lm, 95);
                motor(rm, 100);
            } else {
                motor(lm, 95);
                motor(rm, 100);
            }
        }
        else {
            
            
            if(gmpc(0) < 1000){
                motor(lm, 100);
                motor(rm, 80);
            } else {
                motor(lm, 100);
                motor(rm, 80);
            }
        }
    }

    
    
    


    

    stop_motors();
    
    motor(lm, -25);
    motor(rm, -25);
    msleep(250);
    
    stop_motors();
    
    motor(lm, 50);
    motor(rm, -50);
    msleep(1100);
    



    while(analog(rear_light_sensor) < 3700) {
           motor(lm, 30);
           motor(rm, -30);
    }

    stop_motors();

    while(digital(touch_sensor) == 0) {
        motor(lm, 30);
        motor(rm, 30);
    }

    stop_motors();

    cmpc(0);
    motor(lm, -100);
    motor(rm, -70);
    msleep(700);
    
    cmpc(0);

    while (gmpc(0) > -5500){
        if(gmpc(0) > -5400){
            if (analog(rear_light_sensor) > 3700 && analog(rear_light_sensor) < 3900){
                motor(lm, -100);
                motor(rm, -60);
            }
            else {
                motor(lm, -60);
                motor(rm, -100);
            }
        } else {
            if (analog(rear_light_sensor) > 3700 && analog(rear_light_sensor) < 3900){
                motor(lm, -10);
                motor(rm, -5);
            }
            else {
                motor(lm, -5);
                motor(rm, -10);
            }
        }
    }
    stop_motors();





    







    

    // follow the line on the platform until the mine

    
    // align on black line to be straight
    while (analog(rear_light_sensor) < 3900){
        if (analog(rear_light_sensor) > 3700){
            motor(lm, 0);
            motor(rm, 0);
            break;
        }
        else {
            motor(lm, -15);
            motor(rm, -50);
        }
    }
    

    enable_servos();

    int i = 700;
    int n = 0;
    int j = 971;

    int done = 0;
    while(n <= 2000) {
        if (i <= 2047) {
            ssp(lift_arm_servo, i);
            i+= 20;
        }
        
        if (i >= 1150) { ///////
            ssp(main_arm_servo, n);
            n += 15;
            
             if (n > 1250 && j <= 1950) {
                 
                 while(j <= 1800){
                     ssp(claw_servo, j);
                     j += 30;
                     msleep(15);
                 }
                 
                ssp(claw_servo, j);
                j += 5;
                msleep(15);
                 
                 
                 if(done == 0) {
                     motor(lm, 50);
                     motor(rm, 50);
                     msleep(20);
                     ao();
                     motor(lm, -20);
                     motor(rm, -20);
                     msleep(1600);
                     ao();
                     done = 1;
                 }
                 

            }
        }
        
        msleep(15);
    }
    
    


    stop_motors();
    
    // close claw
    int d = 5;
    while(d < 1) {
        msleep(500);
        while(j >= 900) {
            ssp(claw_servo, j);
            j -= 55;
            msleep(15);
        }
        
        int f = 1950;
        while(f >= 1200){
            ssp(1, f);
            f -= 5;
            msleep(15);
        }

        msleep(500);
        while(j <= 1800) {
            ssp(claw_servo, j);
            j += 55;
            msleep(15);
        }
        d += 1;
        f = 1200;
        while(f <= 1950){
            ssp(1, f);
            f += 5;
            msleep(15);
        }
    }
    msleep(300);
    
    while(j >= 900) {
       ssp(claw_servo, j);
       j -= 45; //85
       msleep(15);
    }
    msleep(500);
    
    ssp(claw_servo, 1900);
    
    msleep(1000);
    j= 1900;
    
    while(j >= 900) {
       ssp(claw_servo, j);
       j -= 65; //85
       msleep(15);
    }
    
    motor(lm, 50);
    motor(rm, 50);
    msleep(50);
    
    stop_motors();
    int movedback = 0;
    
    while(n > 0) {
         ssp(main_arm_servo, n);
         n -= 10; 
        
        if (i >= 700 && n <= 500) {
            ssp(lift_arm_servo, i);
            i-= 35;
        }
        
        if(n <= 500 && movedback == 0) {
            motor(lm, 50);
            motor(rm, 45);
            msleep(200);
            movedback = 1;
            
        }
       
        
        msleep(15);
    }
    
    stop_motors();
    
    ssp(lift_arm_servo, 700);
    msleep(300);
    
    
    
    cmpc(0);
    while (gmpc(0) < 750){
        if(analog(front_light_sensor) > 3600){
            motor(lm, 100);
            motor(rm, 5);
        } else {
         motor(lm,5);
         motor(rm, 100);
     }
      
    }
    
    while (gmpc(0) < 2700){
        if(analog(front_light_sensor) > 3600){
            motor(lm, 100);
            motor(rm, 75);
        } else {
         motor(lm, 75);
         motor(rm, 100);
     }
      
    }
    
    stop_motors();
    
    while(digital(touch_sensor) == 0) {
        motor(lm, 100);   
        motor(rm, 96);
    }
    
    ao();
    msleep(400);
    
    motor(lm, -50);
    motor(rm, -50);
    msleep(1550);
    
    motor(lm, 50);
    motor(rm, -5);
    msleep(1300);
    
    while(analog(front_light_sensor) < 3600) {
        motor(lm, 50);
    	motor(rm, 0);
    }
    
    motor(lm, 50);
    motor(rm, -5);
    msleep(400);
    
    /*cmpc(0);
    
    while(gmpc(0) < 2700) {
        
        motor(lm, 50);
        motor(rm, -5);
    }
    stop_motors();*/

    
    cmpc(0);
    while (analog(front_light_sensor) > 2300){ //1000
        if(analog(front_light_sensor) > 3450){
            if(gmpc(0) > 3000) {
                motor(rm, 70);
                motor(lm, 75);
            } else {
                motor(rm, 5);
                motor(lm, 75);
            }
        } 
        else {
            if(gmpc(0) > 3000) {
                motor(rm, 75);
                motor(lm, 70);
            } else {
                motor(rm, 75);
                motor(lm, 5);
            }
     }
      
    }
    
    cmpc(0);
    cmpc(1);
    int f = 0;
    while(gmpc(0) < 700) {
        if(gmpc(0) > gmpc(1)) {
          motor(1, 70);
          motor(0, 65);
        } else if (gmpc(0) < gmpc(1)) {
           motor(1, 70);
          motor(0, 65);
        } else {
            motor(1, 70);
          	motor(0, 70);
        }
        
    }
    
    
    
    /*motor(lm, 40);
    motor(rm, 40);
    msleep(2300);*/
    stop_motors();
    
    
    cmpc(0);
    while(gmpc(0) < 2450) {
        motor(lm, 40);
        motor(rm, 0);
    }
    
    stop_motors();
    
    while (analog(front_light_sensor) <= 3700){
        motor(lm, 50);
        motor(rm, 50);
    }
    stop_motors();
    
    ssp(2, 1200); //1100
    msleep(500);
    
    cmpc(1);
    while(gmpc(1) > -800) {
        motor(lm, 0);
        motor(rm, -40);
    }
    
    stop_motors();
    
    
    motor(lm, -10);
    motor(rm, -10);
    msleep(3500);
    stop_motors();
    
    
    
    int u = 0;
    while(u < 375) {
        ssp(1, u);
        u += 15;
        msleep(15);
    }
    
    u = 720;
    while(u > 300) {
        ssp(2, u);
        u -= 15;
        msleep(15);
    }

    
    
    /*ssp(2, 622);
    ssp(1, 320);
    
    msleep(400);
    
    ssp(2, 400);
    ssp(1, 350);*/
    
    
    msleep(1000);
    
    motor(lm, 40);
    motor(rm, 40);
    msleep(300);
    
    stop_motors();
    
    cmpc(1);
    while(gmpc(1) < 800) {
        motor(lm, 0);
        motor(rm, 40);
    }
    
    
    
    /*cmpc(0);
    cmpc(1);
    while(analog(front_light_sensor) < 3800) {
        if(analog(rear_light_sensor) < 3800) {
        	motor(0, 90);
        	motor(1, 90);
        } else {
            
        }
    }*/
    while(analog(front_light_sensor) < 3800) {
        motor(0, 60);
        motor(1, 60);
    }
    motor(0, 60);
    motor(1, 60);
    msleep(600);

    stop_motors();


    ssp(1, 320);
    ssp(2, 1300);// 1300
    msleep(500);

    stop_motors();
    motor(0, 20);
    motor(1, 20);
    msleep(1500);
    
    ao();
    int h = 0;
    int z;
    while(h < 1) {
        msleep(300);
        z  = 971;
        while(z < 1200) {
            ssp(claw_servo, z);
            z += 1;
            msleep(15);
        }
        
        msleep(300);

        z  = 1200;
        while(z > 970) {
            ssp(claw_servo, z);
            z -= 35;
            msleep(15);
        }
        h += 1;
    }
    
    msleep(300);
    z  = 971;
    while(z < 1400) {
        ssp(claw_servo, z);
        z += 40;
        msleep(15);
    }
    msleep(500);
    
    z  = 1400;
        while(z > 970) {
            ssp(claw_servo, z);
            z -= 35;
            msleep(15);
        }
    ssp(claw_servo, 1800);
    
    
    // ssp(2, 1500);
    // msleep(500);
    
    ssp(claw_servo, 971);
    msleep(400);


    cmpc(0);
    while(gmpc(0) > -2100) {
     	motor(0, -30);
        motor(1, 30);
    }

    stop_motors();

    motor(0, 30);
    motor(1, 30);
    msleep(1300);

    stop_motors();

    int g = 400;
    while(g < 1600) {
        ssp(3, g);
        g += 30;
        msleep(15);
    }
    
    msleep(400);
    
    motor(0, -30);
    motor(1, 30);
    msleep(500);
    
    stop_motors();
    
    motor(0, -60);
    motor(1, -60);
    msleep(5000);
    stop_motors();

    
    ao();
    disable_servos();
    return 0;
}
