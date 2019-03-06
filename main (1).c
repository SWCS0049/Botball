#include <kipr/botball.h>

//constants
const int LM_PORT=1;    //left motor port
const int RM_PORT=0;   //right motor port
const int S0_PORT=0;   //claw servo0 port     //open-people=789, close=664, open-alltheway=1082			 //declarations
const int S3_PORT=3;    // arm servo3 port    //upalltheway=5, downalltheway=1000, upblocks=930
 
//variables
int dist;
int pos;
int speedL;
int speedR;
int trns;
int ssr;
int ssl;


//functions
void onward(int dist,int ssr,int ssl);                                                                  // functions
void position_claw(int pos);
void position_lift(int pos);
void backward(int dist, int trns);
void turn(int dist,int ssl,int trns);			//turn right
void turnl(int dist,int ssr,int trns);        //turn left
void follow_black_line(int dist,int speedL,int speedR);



int main()
{
 //  wait_for_light(2);
                speedL=89;          // speed for blackline
                speedR=67;			// speed for blackline
				trns=-68;			// turn speed
    			ssr=76;         //straight speed for right motor
    			ssl=76;         //striaght speed for left motor
   								 //open-people=1649, close=1573, open-alltheway=1998		
 							    //upalltheway=5, downalltheway=1000, upblocks=930
    enable_servos();   
   
        pos=0; 								//arm up
    position_lift(pos); 
    
       pos=1648;        
      position_claw(pos);            //claw open 
    
    
  //   msleep(7500);

  
        dist=3200;
  onward(dist,ssr,ssl);             //straight to black and grey lines

    
      dist=850;
    trns=-18;
    turn(dist,ssl,trns);                 //turn  right 
    
   
         dist=4500;
    follow_black_line(dist,speedL,speedR);       //blackline to 1st people

    
    dist=900;
    trns=-18;
    turnl(dist,ssr,trns);        //turn left towards people

     dist=1000;
     trns=-78;
    backward(dist,trns);    //back up 
    
       pos=1000; 
    position_lift(pos);    //arm down
    
    
      dist=1700;
  onward(dist,ssr,ssl);             //straight to people
    
   pos=1555;        
      position_claw(pos);            //claw closed around people
    
      dist=1000;
     trns=-78;
    backward(dist,trns);    //back up with peple 
    
      msleep(1000);
   
    dist=880;
    trns=-18;
    turn(dist,ssl,trns);                 //turn  right 
    
      dist=1000;
     trns=-78;
    backward(dist,trns);    //back up with peple 
    
    
    msleep(1000);
    
      pos=1848;        
      position_claw(pos);            //claw open 
    
    msleep(1000);
    
      pos=0; 								//arm up
    position_lift(pos); 
    
    msleep(1000);
    
    dist=1850;
    trns=-18;
    turnl(dist,ssr,trns);        //turn left 180

             dist=1500;
    follow_black_line(dist,speedL,speedR);       //blackline 2nd people

      dist=900;
    trns=-18;
    turn(dist,ssl,trns);                 //turn  right 
    
     dist=1000;
     trns=-78;
    backward(dist,trns);    //back up
    
       pos=1648;        
      position_claw(pos);            //claw open 
    
      pos=1000; 
    position_lift(pos);    //arm down
    
       pos=1618;        
      position_claw(pos);            //claw open 
    
          dist=1700;
  onward(dist,ssr,ssl);             //straight to people
    
       pos=1555;        
      position_claw(pos);            //claw closed around people
    
      dist=1000;
     trns=-78;
    backward(dist,trns);    //back up with peple 
    
      msleep(1000);
   
    dist=880;
    trns=-18;
    turn(dist,ssl,trns);                 //turn  right 
    
    
    
    return 0;
}

//*********************************************************************/
//*                    Function Name: onward                          */
//* Description of Function: tells robot to move foward               */
//*                                                                   */
//* Variables to Pass: dist                                           */
//* Author- Chloe Nason                                               */
//*********************************************************************/
 
void onward(int dist,int ssr,int ssl)                     //go straight                
{
                motor(RM_PORT,ssr);
                motor(LM_PORT,ssl);      
                msleep(dist);
                ao();
}


 
//*********************************************************************/
//*                    Function Name:turn                             */
//* Description of Function: tells robot to turn                      */
//*                                                                   */
//* Variables to Pass: dist                                        */
//* Author- Chloe Nason                                               */
//*********************************************************************/
void turn(int dist,int ssl,int trns)                         //turn right
{
    motor(RM_PORT,trns);           
    motor(LM_PORT,ssl);             
    msleep(dist);
                ao();
}
 
//*********************************************************************/
//*                    Function Name:turn                             */
//* Description of Function: tells robot to turn                      */
//*                                                                   */
//* Variables to Pass: dist                                           */
//* Author- Chloe Nason                                               */
//*********************************************************************/
void turnl(int dist,int ssr,int trns)                         //turn left
{
    motor(RM_PORT,ssr);           
    motor(LM_PORT,trns);             
    msleep(dist);
                ao();
}
 
//*********************************************************************/
//*                    Function Name                                  */
//* Description of Function: tells robot to follow the black line     */
//*                                                                   */
//* Variables to Pass: dist,speedL,speedR                         */
//* Author- Chloe Nason                                               */
//*********************************************************************/
 
void follow_black_line(int dist,int speedL,int speedR)
{
clear_motor_position_counter(1);
                while(get_motor_position_counter(1)<dist)      // follow black line
 {
                                if(analog10(1)>512)
                                {
                                                motor(RM_PORT,speedL);
                                                motor(LM_PORT,speedR);     //turn right
                                }
                                else
                                {
                                                motor(RM_PORT,59);
                                                motor(LM_PORT,speedL);  // turn left
                                }
               
}
}    
    
    
 
//*********************************************************************/
//*                    Function Name                                  */
//* Description of Function: raises and lowers claw                   */
//*                                                                   */
//* Variables to Pass: pos                                      */
//* Author- Chloe Nason                                               */
//*********************************************************************/
 
void position_lift(int pos)
{
   set_servo_position(S3_PORT,pos);   //  arm lift up
}
 
 
 
//*********************************************************************/
//*                    Function Name                                  */
//* Description of Function: opens and closes claw                    */
//*                                                                   */
//* Variables to Pass: pos                                            */
//* Author- Chloe Nason                                               */
//*********************************************************************/
void position_claw(int pos)
{
   set_servo_position(S0_PORT,pos);                // claw
}
    
    
void backward(int dist,int trns);    
    
    
 
//*********************************************************************/
//*                    Function Name: backward                          */
//* Description of Function: tells robot to move backward             */
//*                                                                   */
//* Variables to Pass: dist                                           */
//* Author- Chloe Nason                                               */
//*********************************************************************/
 void backward(int dist,int trns)    
           
{
                motor(RM_PORT,trns);                   				// backward
                motor(LM_PORT,trns);      
                msleep(dist);
                ao();
}   
    
    
    
    
