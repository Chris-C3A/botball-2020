// constants
// servo variables
#define claw_servo  0
#define main_arm_servo  1
#define lift_arm_servo  2
#define pvc_arm_servo  3
// motor variables
#define lm  0
#define rm  1
// sensor variables
#define touch_sensor  9 // digital
#define button_sensor  0 //digital
// analog
#define rear_light_sensor  2
#define front_light_sensor  0

// custom functions
void ssp(int port, int position){
    set_servo_position(port, position);
}
void stop_motors() {
    motor(lm, 0);
    motor(rm, 0);
    msleep(200);
}
void starting_pos() {
    ssp(claw_servo, 971);
    ssp(main_arm_servo, 0);
    ssp(lift_arm_servo, 700);
    ssp(pvc_arm_servo, 300);
}
