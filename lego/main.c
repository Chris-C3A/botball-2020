// includes
#include <kipr/botball.h>
#include <math.h>
#include "startup.h"
#include "main.h"

// main function
int main()
{
    // set servos to starting pos
    starting_pos()
    msleep(400);
    // move backwards to starting box
    motor(0, -70);
    motor(1,-70);
    msleep(2500);
    ao();
	//motorTest(); // runs motor test
	analogTest(); // runs sensor test

    enable_servos();
    // starting pos
    starting_pos();
    msleep(400);
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
    
    motor(lm, -50);
    motor(rm, 0);
    msleep(1350);
    
    motor(lm, 50);
    motor(rm, 50);
    msleep(250);

    while(analog(front_light_sensor) <= 3200) {
        motor(lm, 10); // 10
        motor(rm, 50);
    }

    motor(lm, 7);
    motor(rm, 50);
    msleep(400); // change in testijg
    stop_motors();
    
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
    j = 1900;
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
    stop_motors();

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
        } else {
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
    
    motor(lm, 40);
    motor(rm, 40);
    msleep(300);
    stop_motors();
    
    cmpc(1);
    while(gmpc(1) < 800) {
        motor(lm, 0);
        motor(rm, 40);
    }
    
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
    stop_motors();
    
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
