#include <mbed.h>

struct ControlStatus{
  float target_speed;
  float current_speed;
  float iterm;
  float output;
  void print(){
    printf("o: %+5.3f, t: %+7.1f, c: %+7.1f i: %7.1f\n", output, target_speed, current_speed, iterm);
  }
};

struct ControlParameter{
  float f;
  float p;
  float i;
};

class PwmMotor{
public:
  PwmMotor(PinName p_mot_a, PinName p_mot_b, PinName p_enc_a, PinName p_enc_b): mot_a_(p_mot_a), mot_b_(p_mot_b), enc_a_(p_enc_a), enc_b_(p_enc_b){
    counter_ = 0;
    last_counter_ = 0;
    notify_ = false;
    mode_ = Mode::FREE;

    enc_a_.mode(PullUp);
    enc_b_.mode(PullUp);

    enc_a_.rise([&](){
      if(enc_b_.read())counter_++;
      else counter_--;
    });
    enc_a_.fall([&](){
      if(enc_b_.read())counter_--;
      else counter_++;
    });
    enc_b_.rise([&](){
      if(enc_a_.read())counter_--;
      else counter_++;
    });
    enc_b_.fall([&](){
      if(enc_a_.read())counter_++;
      else counter_--;
    });
  }

  void setSpeedTarget(float target){
    mode_=Mode::SPEED;
    target_speed_ = target;
  }
  void setPwmTarget(float target){
    
  }
  void setFree(){
    
  }
  void setTarget(float target){
  }
  int getPisition(void){
    return counter_;
  }

  int control(float dt){
    float diff = (counter_ - last_counter_) / dt - target_speed_;
    result_.iterm = result_.iterm + diff * dt;
    float output_raw = param_.f * target_speed_ - param_.p * diff - param_.i * result_.iterm;
    float output = std::min(std::max(output_raw, -1.0f), 1.0f);
    if(output>0){
      mot_a_ = output;
      mot_b_ = 0;
    }
    else{
      mot_a_ = 0;
      mot_b_ = -output;
    }

    result_.target_speed = target_speed_;
    result_.current_speed = (counter_ - last_counter_)  / dt;
    result_.output = output;

    if(result_.target_speed == 0 && result_.current_speed == 0){
      result_.iterm /= 2.0;
    }

    int delta = counter_ - last_counter_;
    last_counter_ = counter_;
    return delta;
  }
  void print(){
    if(notify_)result_.print();
  }
  void setParam(float f, float p, float i){
    param_.f = f;
    param_.p = p;
    param_.i = i;
  }

  ControlStatus result_;
  ControlParameter param_;
  PwmOut mot_a_;
  PwmOut mot_b_;
  InterruptIn enc_a_;
  InterruptIn enc_b_;
  float target_speed_;
  int counter_;
  int last_counter_;
  bool notify_;
  enum class Mode{FREE, PWM, SPEED} mode_;
};
