//Using PORT A to control the gpio pins

// 1 1 0 0 is reserved unused word, used to initialize, dont use at control word
// initialize the whole connection with this keyword only
#include<avr/io.h>
#define no_of_pins 4
int control_pins[no_of_pins];
int control_word[no_of_pins];
int control_word_last_iteration[no_of_pins];
int theta_of_firebird=0;
int horizontal_theta_of_camera=0;
int vertical_theta_of_camera=0;

boolean control_word_testing(){
  for(int i=0;i<no_of_pins;i++)
    if(control_word[i]!=control_word_last_iteration[i]){
        memcpy(control_word_last_iteration,control_word,sizeof(control_word));
        return false;
    }
  return true;
}



void control_word_translation(){
  int value=(control_word[3]<<0)+(control_word[2]<<1)+(control_word[1]<<2);
  if(control_word[0]==0){
    theta_of_firebird=value*45;
  }else{
    if(value>5||value<3){
      horizontal_theta_of_camera=value*45;
    }
    else if(value==5){
      vertical_theta_of_camera=45;
    }
    else if(value==3){
      vertical_theta_of_camera=0;
    }
    
  }
  
}



void main() {
  for(int i=0;i<no_of_pins;i++){
    control_pins[i]=i;
    DDRA= (0<<control_pins[i]); //Set specific pins to input mode
    control_word[i]=1;
    control_word_last_iteration[i]=1;
  }


while(true){
for(int i=0;i<no_of_pins;i++)
    control_word[i]=(PINA & (1<<control_pins[i])) >> control_pins[i] ;

if(!control_word_testing());
  {
    delay(20);        //to test whether pin is really triggered or not
  if(control_word_testing()){
    control_word_translation();
  }
}
}

}



