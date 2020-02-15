/*****************************/
/* KIPR wallaby factory_test */
/* By Nathaniel Ashley       */
/* 10/25/2016                */
/*****************************/

#include <kipr/botball.h>
#include <math.h>
  	


// variables
int open_claw_pos = 2047;
int closed_claw_pos = 680;


// functions
void cdd(int l, int r);
void ssp(int port, int pos);

//opened

int main()
{
    create_connect();
    enable_servos();
    ssp(0, 1000);
    ssp(1, 50);
    msleep(500);
    ssp(0, open_claw_pos);
    ssp(1, 0);
    msleep(200);
	//analogTest();
    printf("try touch sensor");
    while(digital(9) == 0) {
		msleep(1);
    }
    printf("touch sensor working");

    
    //starting pos
    //ssp(0, 480); //poms arm
    ssp(1, 0); // arm
    ssp(0, open_claw_pos); //claw
    
    msleep(500);
    wait_for_light(0);
    shut_down_in(118);
    
    // turn and straighten robot
    cdd(200, 200);
    msleep(300);
    cdd(0, 0);
    msleep(300);

    cdd(150, -150);
    msleep(1250);

    cdd(0, 0);
    msleep(300);

    // cdd(200, 0);
    // msleep(1200);
    // cdd(0, 0);
    // msleep(500);
    // cdd(-150, -150);
    // msleep(2500);
    // cdd(0,0);
    
    // move forward until bump
    while (get_create_lbump() == 0) {
		cdd(250, 250);
        
    }
    
    //close claw
    ssp(0, closed_claw_pos);
    
    cdd(0, 0);
    msleep(500);
    
    // turn and straighten robot
    cdd(-200, -200);
    msleep(300);
    cdd(-150, 150);
    msleep(1200);  //1300
    cdd(200, 200);
    msleep(300);
    cdd(0, 0);
    cdd(-250, -250);
    msleep(1300); 
    cdd(0, 0);
    msleep(500);
    
    // move forward until touched at the ramp
    while(digital(9) == 0) {
     	cdd(200, 200);   
    }
    
    // changed
    cdd(-150,-150);
    msleep(250);
    //
    
    // align robot
    cdd(0, 0);
    msleep(500);
    cdd(-150, 150);
    msleep(640); // 625 
    cdd(0, 0);
    msleep(500);
    
    //open claw
    ssp(0, open_claw_pos);
    
    msleep(1000);
    
    // raise arm
    int i = 0;
    while(i <= 1750) {//1850
        ssp(1, i);
        i+=15;
        msleep(15);
    }
    
    msleep(1000);
    
    // close claw
    int j = open_claw_pos;
    while(j >= closed_claw_pos) {
        ssp(0, j);
        j-=15;
        msleep(15);
    }
    msleep(1000);
    
    // lower arm
    int n = 1750;
    while(n >=0) {
        ssp(1, n);
        n-=5;
        msleep(15);
    }
    
    // open claw
    //ssp(0,open_claw_pos);
               
    msleep(1000);
    
    cdd(-150, 0);
    msleep(1500);
    
    cdd(-150, -150);
    msleep(700);
    
    cdd(0, 0);
    msleep(500);
    
    cdd(200, 200);
    msleep(400);
    
    cdd(0, 0);
    msleep(500);
    
    cdd(0, 200);
    
    set_create_total_angle(0);
    while(get_create_total_angle(0) < 100) {
     	cdd(0, 200);   
    }
    
    cdd(0, 0);
    msleep(300);

    cdd(200, 200);
    msleep(700);

    cdd(-150, 0);
    msleep(2600);

    cdd(0, 0);
    msleep(400);

    ssp(0,open_claw_pos);
    msleep(300);

    cdd(150, 0);
    msleep(2600);

    cdd(0, 0);
    msleep(400);
    
    
    //turn robot
    //cdd(-150, 150);
    //msleep(700);

    // changed
    //cdd(100, 100);
    //msleep(550);
    //
    //close claw
  
    //cdd(-200, 200);
    //sleep(900);
    
    //cdd(0, 0);
    //msleep(500);
    
    ssp(0, 900);
    
   	// move forward until bumped
    while (get_create_lbump() == 0) {
		cdd(150, 150);
        
    }
    
    // turn and align robot
    cdd(0, 0);
    msleep(500);
    cdd(-200, -200);
    msleep(200);

    cdd(150, -150);
    msleep(1250);
    cdd(-250, -250);
    msleep(2000);
    
    // move forward until bumped
    while (get_create_lcliff_amt() >= 2000) {
		cdd(250, 250);
        
    }

    while (get_create_lbump() == 0 && get_create_rbump() == 0) {
		cdd(150, 150);
        
    }
    
    ssp(0, 900);

    cdd(0, 0);
    
    msleep(500);
    // turn and align robot
    cdd(-200, -200);
    msleep(600);
    cdd(0, 0);
    cdd(150, -150);
    msleep(1200);
    cdd(0,0);
    msleep(200);
    cdd(-250, -250);
    msleep(1000);
    cdd(0, 0);
    
    // open claw
    ssp(0, open_claw_pos);
    msleep(500);
    
    //ssp(1, 70);

    // new: using black tape
    while (get_create_lcliff_amt() >= 2000) {
        cdd(150, 150);

    }

    msleep(500);

    while (get_create_lcliff_amt() >= 2000) {
        cdd(150, 150);

    }

    msleep(200);
    cdd(0, 0);
    
    cdd(-200, -200);
    msleep(100);
    
    cdd(0, 0);
    msleep(300);
    
    
    // move to a certain distance
    /*set_create_distance(0);
    while(get_create_distance(0) < 466) {
     	cdd(200, 200);   
    }
    
    cdd(0, 0);
    msleep(300);*/
    
    // raise arm abit
    ssp(1, 110);
    msleep(500);

    cdd(0, 150);
    msleep(600);
    
    cdd(0, 0);
    msleep(400);
    
    cdd(150, 0);
    msleep(600);
    
    cdd(0, 0);
    msleep(400);
    
    cdd(-200, -200);
    msleep(250);
    
    
    cdd(0, 0);
    msleep(1400);
    
    
    //ssp(0, closed_claw_pos); //
    j = open_claw_pos;
    while(j >= closed_claw_pos) {
        ssp(0, j);
        j-=10;
        msleep(15);
    }

    cdd(0, 0);
    msleep(400);
    
    //cdd(0, -150);
    //msleep(450);
    
    //msleep(3000);

    //cdd(150, 0);
    //msleep(650);
    
    //cdd(-150, -150);
    //msleep(300);
    
    //close claw on the orange ball
    // cdd(50, -50);
    // msleep(150);
    
    //j = open_claw_pos;
    //while(j >= closed_claw_pos) {
        //ssp(0, j);
        //j-=15;
        //msleep(15);
    //}
    
    // turn 90 degrees to the right
    cdd(150, -150);
    msleep(1300);
    
    //cdd(-200, -200);
    //msleep(1000);
    
    cdd(0, 0);
    msleep(400);
    
     //move forward until bumped
     while (get_create_lbump() == 0) {
 		cdd(250, 250);
        
     }
    
     cdd(0, 0);
     msleep(500);
    
     cdd(-200, -200);
     msleep(600);
    
     //turn 90 degrees to the left
     cdd(-150, 150);
     msleep(1300);
    
     cdd(0, 0);
     msleep(1000);
    
    
    
    while(digital(9) == 0) {
     	cdd(200, 200);   
    }
    
    cdd(0, 0);
    msleep(500);
    
    cdd(-200, -200);
    msleep(300);
    
    cdd(0, 0);
    msleep(500);
    cdd(-150, 150);
    msleep(700); //675
    cdd(0, 0);
    msleep(500);
    
    
    i = 110;
    while(i <= 1550) {
        ssp(1, i);
        i+=10;
        msleep(15);
    }
    
    msleep(1000);
    
    
    ssp(1, 1675);
    
    //ssp(0, open_claw_pos);
    
    msleep(1000);
    
    /*i = 0;
    while(i <= 1600) {
        ssp(1, i);
        i+=10;
        msleep(15);
    }
    
    msleep(1000);
    
 cdd(200, 0);
    msleep(500);
    
    cdd(0, 200);
    msleep(300);*/
    
    
    
    j = closed_claw_pos;
    while(j <= open_claw_pos) {
        if (j >=1200) {
            ssp(0, j);
            j+=35;
            msleep(15);
            
        }else {
            ssp(0, j);
            j+=2;
            msleep(15);
        }
    }
    msleep(1000);
    
    i = 1650;
    while(i >= 0) {
        ssp(1, i);
        i-=15;
        msleep(15);
    }
    
    msleep(500);
    
    ssp(0, 900);
    
    
	cdd(-300, 0);
	msleep(1000);
    
    cdd(0, 0);
    msleep(200);
    
    cdd(0, -100);
    msleep(400);


    
    cdd(-150, -150);
    msleep(1000);
    
    cdd(250, 250);
    msleep(300);
        
    cdd(-150, 150);
    msleep(1300);
    
    while (get_create_lbump() == 0) {
		cdd(250, 250);
    }
    
    cdd(0, 0);
    msleep(500);
    
    cdd(-150, -150);
    msleep(300);
    
    cdd(150, -150);
    msleep(1300);
    
    cdd(-150, -150);
    msleep(1000);
    
    while (get_create_lcliff_amt() >= 2000) {
		cdd(250, 250);  
    }
    cdd(0, 0);
    msleep(500);
    
    cdd(150, -150);
    msleep(1300);
    
    cdd(-150, -150);
    msleep(500);
    
    cdd(0,0);
    msleep(500);
    
    set_create_distance(0); 
    while (get_create_distance() <= 245) {
		cdd(150, 150);
        
    }
    cdd(0, 0);
    printf("%d", get_create_distance(0));
    msleep(20);
    
    cdd(-150, 150);
    msleep(1300);
    
    cdd(100, 100);
    msleep(1200);
    
    cdd(0, 0);
    msleep(300);
    
    i = 0;
    while(i <= 2047) {
        ssp(1, i);
        i+=15;
        msleep(15);
    }
    
    msleep(1000);
    
    cdd(-200, -200);
    msleep(1600);
    
    cdd(0, 0);
    
    i = 2047;
    while(i >= 0) {
        ssp(1, i);
        i-=15;
        msleep(15);
    }
    
    msleep(1000);
    
    
    // 90
    
    
    //ssp(0, open_claw_pos); 
    disable_servos();
    create_disconnect();
    return 0;
}

void cdd(int l, int r) {
    create_drive_direct(l, r);
}

void ssp(int port, int pos) {
    set_servo_position(port, pos);

}
