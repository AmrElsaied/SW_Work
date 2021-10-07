#ifndef _TIMER_
#define _TIMER_

class Timer
{
  private:
    unsigned long timerPeriod = 0;
    unsigned long timerCurTime = 0;
    unsigned long timerRecTime = 0;
    bool timerFinishFlag = false;
    bool timerStartFlag = false;
    String timerMode = "";
  public:
    Timer(String copyTimerMode , unsigned long copyTime);
    void voidTimerChangePeriod(unsigned long copyTimerPeriod);
    void voidTimerStart();
    void voidTimerStop();
    void voidTimerReset();
    void voidTimerLoop();
    bool voidTimerFinishState();
    bool voidTimerWorkState();
};


#endif
