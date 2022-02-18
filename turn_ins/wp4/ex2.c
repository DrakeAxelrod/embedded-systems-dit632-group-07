// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 4
// Exercise 2
// Submission code: BJGIKTJU

// ================================================================================================================================= //
// ========================================================= START LIBRARY ========================================================= //
// ================================================================================================================================= //
/*
 *  Interrupt and PWM utilities for 16 bit Timer1 on ATmega168/328
 *  Original code by Jesse Tane for http://labs.ideo.com August 2008
 *
 *  This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  See Google Code project http://code.google.com/p/arduino-timerone/ for latest
 */
#ifndef TIMERONE_h
#define TIMERONE_h

#include <avr/io.h>
#include <avr/interrupt.h>

#define RESOLUTION 65536 // Timer1 is 16 bit

class TimerOne
{
public:
  // properties
  unsigned int pwmPeriod;
  unsigned char clockSelectBits;
  char oldSREG; // To hold Status Register while ints disabled

  // methods
  void initialize(long microseconds = 1000000);
  void start();
  void stop();
  void restart();
  void resume();
  unsigned long read();
  void pwm(char pin, int duty, long microseconds = -1);
  void disablePwm(char pin);
  void attachInterrupt(void (*isr)(), long microseconds = -1);
  void detachInterrupt();
  void setPeriod(long microseconds);
  void setPwmDuty(char pin, int duty);
  void (*isrCallback)();
};

extern TimerOne Timer1;
#endif

#ifndef TIMERONE_cpp
#define TIMERONE_cpp

// #include "TimerOne.h"

TimerOne Timer1; // preinstatiate

ISR(TIMER1_OVF_vect) // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
  Timer1.isrCallback();
}

void TimerOne::initialize(long microseconds)
{
  TCCR1A = 0;          // clear control register A
  TCCR1B = _BV(WGM13); // set mode 8: phase and frequency correct pwm, stop the timer
  setPeriod(microseconds);
}

void TimerOne::setPeriod(long microseconds) // AR modified for atomic access
{

  long cycles = (F_CPU / 2000000) * microseconds; // the counter runs backwards after TOP, interrupt is at BOTTOM so divide microseconds by 2
  if (cycles < RESOLUTION)
    clockSelectBits = _BV(CS10); // no prescale, full xtal
  else if ((cycles >>= 3) < RESOLUTION)
    clockSelectBits = _BV(CS11); // prescale by /8
  else if ((cycles >>= 3) < RESOLUTION)
    clockSelectBits = _BV(CS11) | _BV(CS10); // prescale by /64
  else if ((cycles >>= 2) < RESOLUTION)
    clockSelectBits = _BV(CS12); // prescale by /256
  else if ((cycles >>= 2) < RESOLUTION)
    clockSelectBits = _BV(CS12) | _BV(CS10); // prescale by /1024
  else
    cycles = RESOLUTION - 1, clockSelectBits = _BV(CS12) | _BV(CS10); // request was out of bounds, set as maximum

  oldSREG = SREG;
  cli();                     // Disable interrupts for 16 bit register access
  ICR1 = pwmPeriod = cycles; // ICR1 is TOP in p & f correct pwm mode
  SREG = oldSREG;

  TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));
  TCCR1B |= clockSelectBits; // reset clock select register, and starts the clock
}

void TimerOne::setPwmDuty(char pin, int duty)
{
  unsigned long dutyCycle = pwmPeriod;

  dutyCycle *= duty;
  dutyCycle >>= 10;

  oldSREG = SREG;
  cli();
  if (pin == 1 || pin == 9)
    OCR1A = dutyCycle;
  else if (pin == 2 || pin == 10)
    OCR1B = dutyCycle;
  SREG = oldSREG;
}

void TimerOne::pwm(char pin, int duty, long microseconds) // expects duty cycle to be 10 bit (1024)
{
  if (microseconds > 0)
    setPeriod(microseconds);
  if (pin == 1 || pin == 9)
  {
    DDRB |= _BV(PORTB1);   // sets data direction register for pwm output pin
    TCCR1A |= _BV(COM1A1); // activates the output pin
  }
  else if (pin == 2 || pin == 10)
  {
    DDRB |= _BV(PORTB2);
    TCCR1A |= _BV(COM1B1);
  }
  setPwmDuty(pin, duty);
  resume(); // Lex - make sure the clock is running.  We don't want to restart the count, in case we are starting the second WGM
            // and the first one is in the middle of a cycle
}

void TimerOne::disablePwm(char pin)
{
  if (pin == 1 || pin == 9)
    TCCR1A &= ~_BV(COM1A1); // clear the bit that enables pwm on PB1
  else if (pin == 2 || pin == 10)
    TCCR1A &= ~_BV(COM1B1); // clear the bit that enables pwm on PB2
}

void TimerOne::attachInterrupt(void (*isr)(), long microseconds)
{
  if (microseconds > 0)
    setPeriod(microseconds);
  isrCallback = isr;   // register the user's callback with the real ISR
  TIMSK1 = _BV(TOIE1); // sets the timer overflow interrupt enable bit
                       // might be running with interrupts disabled (eg inside an ISR), so don't touch the global state
                       //  sei();
  resume();
}

void TimerOne::detachInterrupt()
{
  TIMSK1 &= ~_BV(TOIE1); // clears the timer overflow interrupt enable bit
                         // timer continues to count without calling the isr
}

void TimerOne::resume() // AR suggested
{
  TCCR1B |= clockSelectBits;
}

void TimerOne::restart() // Depricated - Public interface to start at zero - Lex 10/9/2011
{
  start();
}

void TimerOne::start() // AR addition, renamed by Lex to reflect it's actual role
{
  unsigned int tcnt1;

  TIMSK1 &= ~_BV(TOIE1); // AR added
  GTCCR |= _BV(PSRSYNC); // AR added - reset prescaler (NB: shared with all 16 bit timers);

  oldSREG = SREG; // AR - save status register
  cli();          // AR - Disable interrupts
  TCNT1 = 0;
  SREG = oldSREG; // AR - Restore status register
  resume();
  do
  { // Nothing -- wait until timer moved on from zero - otherwise get a phantom interrupt
    oldSREG = SREG;
    cli();
    tcnt1 = TCNT1;
    SREG = oldSREG;
  } while (tcnt1 == 0);

  //  TIFR1 = 0xff;              		// AR - Clear interrupt flags
  //  TIMSK1 = _BV(TOIE1);              // sets the timer overflow interrupt enable bit
}

void TimerOne::stop()
{
  TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12)); // clears all clock selects bits
}

unsigned long TimerOne::read() // returns the value of the timer in microseconds
{                              // rember! phase and freq correct mode counts up to then down again
  unsigned long tmp;           // AR amended to hold more than 65536 (could be nearly double this)
  unsigned int tcnt1;          // AR added

  oldSREG = SREG;
  cli();
  tmp = TCNT1;
  SREG = oldSREG;

  char scale = 0;
  switch (clockSelectBits)
  {
  case 1: // no prescalse
    scale = 0;
    break;
  case 2: // x8 prescale
    scale = 3;
    break;
  case 3: // x64
    scale = 6;
    break;
  case 4: // x256
    scale = 8;
    break;
  case 5: // x1024
    scale = 10;
    break;
  }

  do
  { // Nothing -- max delay here is ~1023 cycles.  AR modified
    oldSREG = SREG;
    cli();
    tcnt1 = TCNT1;
    SREG = oldSREG;
  } while (tcnt1 == tmp); // if the timer has not ticked yet

  // if we are counting down add the top value to how far we have counted down
  tmp = ((tcnt1 > tmp) ? (tmp) : (long)(ICR1 - tcnt1) + (long)ICR1); // AR amended to add casts and reuse previous TCNT1
  return ((tmp * 1000L) / (F_CPU / 1000L)) << scale;
}

#endif

// -------
#ifndef ServoTimer2_h
#define ServoTimer2_h

#include <inttypes.h>
// typedef uint8_t boolean;
// typedef uint8_t byte;

#define MIN_PULSE_WIDTH 750 // the shortest pulse sent to a servo

#define MAX_PULSE_WIDTH 2250 // the longest pulse sent to a servo

#define DEFAULT_PULSE_WIDTH 1500 // default pulse width when servo is attached

#define FRAME_SYNC_PERIOD 20000 // total frame duration in microseconds

#define NBR_CHANNELS 8 // the maximum number of channels, don't change this

typedef struct
{

  uint8_t nbr : 5; // a pin number from 0 to 31

  uint8_t isActive : 1; // false if this channel not enabled, pin only pulsed if true

} ServoPin_t;

typedef struct
{

  ServoPin_t Pin;

  byte counter;

  byte remainder;

} servo_t;

class ServoTimer2
{
public:
  // constructor:
  ServoTimer2();

  uint8_t attach(int);           // attach the given pin to the next free channel, sets pinMode, returns channel number or 0 if failure
                                 // the attached servo is pulsed with the current pulse width value, (see the write method)
  uint8_t attach(int, int, int); // as above but also sets min and max values for writes.
  void detach();
  void write(int);    // store the pulse width in microseconds (between MIN_PULSE_WIDTH and MAX_PULSE_WIDTH)for this channel
  int read();         // returns current pulse width in microseconds for this servo
  boolean attached(); // return true if this servo is attached
private:
  uint8_t chanIndex; // index into the channel data for this servo
};

// the following ServoArrayT2 class is not implemented in the first version of this library
class ServoArrayT2
{
public:
  // constructor:
  ServoArrayT2();

  uint8_t attach(int);   // attach the given pin to the next free channel, sets pinMode, returns channel number or 0 if failure
                         // channels are assigned consecutively starting from 1
                         // the attached servo is pulsed with the current pulse width value, (see the write method)
  void detach(int);      // detach the servo on the given channel
  void write(int, int);  // store the pulse width in microseconds (between MIN_PULSE_WIDTH and MAX_PULSE_WIDTH)for the given channel
  int read(int);         // returns current pulse width in microseconds for the given channel
  boolean attached(int); // return true if the servo on the given channel is attached
private:
  uint8_t chanIndex; // index into the channel data for this servo
};

#endif

extern "C"
{
// AVR LibC Includes
#include <inttypes.h>
#include <avr/interrupt.h>
  // #include "WConstants.h"
}
// #include <Arduino.h>
// #include "ServoTimer2.h"
static void initISR();
static void writeChan(uint8_t chan, int pulsewidth);

#define FRAME_SYNC_INDEX 0                                                                  // frame sync delay is the first entry in the channel array
#define FRAME_SYNC_PERIOD 20000                                                             // total frame duration in microseconds
#define FRAME_SYNC_DELAY ((FRAME_SYNC_PERIOD - (NBR_CHANNELS * DEFAULT_PULSE_WIDTH)) / 128) // number of iterations of the ISR to get the desired frame rate
#define DELAY_ADJUST 8                                                                      // number of microseconds of calculation overhead to be subtracted from pulse timings

static servo_t servos[NBR_CHANNELS + 1]; // static array holding servo data for all channels

static volatile uint8_t Channel;  // counter holding the channel being pulsed
static volatile uint8_t ISRCount; // iteration counter used in the interrupt routines;
uint8_t ChannelCount = 0;         // counter holding the number of attached channels
static boolean isStarted = false; // flag to indicate if the ISR has been initialised

ISR(TIMER2_OVF_vect)
{
  ++ISRCount;                              // increment the overlflow counter
  if (ISRCount == servos[Channel].counter) // are we on the final iteration for this channel
  {
    TCNT2 = servos[Channel].remainder; // yes, set count for overflow after remainder ticks
  }
  else if (ISRCount > servos[Channel].counter)
  {
    // we have finished timing the channel so pulse it low and move on
    if (servos[Channel].Pin.isActive == true)     // check if activated
      digitalWrite(servos[Channel].Pin.nbr, LOW); // pulse this channel low if active

    Channel++;    // increment to the next channel
    ISRCount = 0; // reset the isr iteration counter
    TCNT2 = 0;    // reset the clock counter register
    if ((Channel != FRAME_SYNC_INDEX) && (Channel <= NBR_CHANNELS))
    {                                                // check if we need to pulse this channel
      if (servos[Channel].Pin.isActive == true)      // check if activated
        digitalWrite(servos[Channel].Pin.nbr, HIGH); // its an active channel so pulse it high
    }
    else if (Channel > NBR_CHANNELS)
    {
      Channel = 0; // all done so start over
    }
  }
}

ServoTimer2::ServoTimer2()
{
  if (ChannelCount < NBR_CHANNELS)
    this->chanIndex = ++ChannelCount; // assign a channel number to this instance
  else
    this->chanIndex = 0; // todo	// too many channels, assigning 0 inhibits this instance from functioning
}

uint8_t ServoTimer2::attach(int pin)
{
  if (isStarted == false)
    initISR();
  if (this->chanIndex > 0)
  {
    // debug("attaching chan = ", chanIndex);
    pinMode(pin, OUTPUT); // set servo pin to output
    servos[this->chanIndex].Pin.nbr = pin;
    servos[this->chanIndex].Pin.isActive = true;
  }
  return this->chanIndex;
}

void ServoTimer2::detach()
{
  servos[this->chanIndex].Pin.isActive = false;
}

void ServoTimer2::write(int pulsewidth)
{
  writeChan(this->chanIndex, pulsewidth); // call the static function to store the data for this servo
}

int ServoTimer2::read()
{
  unsigned int pulsewidth;
  if (this->chanIndex > 0)
    pulsewidth = servos[this->chanIndex].counter * 128 + ((255 - servos[this->chanIndex].remainder) / 2) + DELAY_ADJUST;
  else
    pulsewidth = 0;
  return pulsewidth;
}

boolean ServoTimer2::attached()
{
  return servos[this->chanIndex].Pin.isActive;
}

static void writeChan(uint8_t chan, int pulsewidth)
{
  // calculate and store the values for the given channel
  if ((chan > 0) && (chan <= NBR_CHANNELS)) // ensure channel is valid
  {
    if (pulsewidth < MIN_PULSE_WIDTH) // ensure pulse width is valid
      pulsewidth = MIN_PULSE_WIDTH;
    else if (pulsewidth > MAX_PULSE_WIDTH)
      pulsewidth = MAX_PULSE_WIDTH;

    pulsewidth -= DELAY_ADJUST; // subtract the time it takes to process the start and end pulses (mostly from digitalWrite)
    servos[chan].counter = pulsewidth / 128;
    servos[chan].remainder = 255 - (2 * (pulsewidth - (servos[chan].counter * 128))); // the number of 0.5us ticks for timer overflow
  }
}

static void initISR()
{
  for (uint8_t i = 1; i <= NBR_CHANNELS; i++)
  {                                    // channels start from 1
    writeChan(i, DEFAULT_PULSE_WIDTH); // store default values
  }
  servos[FRAME_SYNC_INDEX].counter = FRAME_SYNC_DELAY; // store the frame sync period

  Channel = 0;  // clear the channel index
  ISRCount = 0; // clear the value of the ISR counter;

  /* setup for timer 2 */
  TIMSK2 = 0;          // disable interrupts
  TCCR2A = 0;          // normal counting mode
  TCCR2B = _BV(CS21);  // set prescaler of 8
  TCNT2 = 0;           // clear the timer2 count
  TIFR2 = _BV(TOV2);   // clear pending interrupts;
  TIMSK2 = _BV(TOIE2); // enable the overflow interrupt

  isStarted = true; // flag to indicate this initialisation code has been executed
}
// =============================================================================================================================== //
// ========================================================= END LIBRARY ========================================================= //
// =============================================================================================================================== //

// Function Definitions
void updateTime();
void printTime();


// 750 - 2250 step 25 (range for the ServoTimer2)
const int START_VAL = 750; // ServoTimer2 starting position is 750
const int END_VAL = 2250;  // ServoTimer2 starting position is 2250
const int INC = 25; // step to increment (2250 - 750) / 60
ServoTimer2 seconds; // create sservo object to track seconds
ServoTimer2 minutes; // create servo object to track minutes
ServoTimer2 hours;   // create servo object to track hours

int secs = START_VAL; // init secs
int mins = START_VAL; // init mins
int hrs = START_VAL; // init hrs

// set up function to connect pins/attach motors/init the interrupt
void setup()
{
  Serial.begin(9600); // init serial
  Timer1.initialize(); // Initialize Timer default is 1000000us
  Timer1.attachInterrupt(updateTime);
  seconds.attach(5); // attaches the servo on pin 10
  minutes.attach(6); // attaches the servo on pin 11
  hours.attach(7);   // attaches the servo on pin 12
}

void loop() {} // do nothing to show that our timer works correctly

// updates the respective servos and increments the var representations of sec,min,hrs
void updateTime()
{
  seconds.write(secs); // write current secs to sec seconds servo
  minutes.write(mins); // write current mins to minutes servo
  hours.write(hrs);    // write current hrs to hours servo
  secs += INC; // increment seconds
  if (secs == END_VAL) // if seconds hits END_VAL reset to START_VAL
  {
    secs = START_VAL; // reset secs
    mins += INC; // inc mins since we hit END_VAL for secs
  }
  if (mins == END_VAL) // if mins hits END_VAL reset to START_VAL
  {
    mins = START_VAL; // reset mins
    hrs += INC;       // inc hrs since we hit END_VAL for mins
  }
  printTime(); // calls function to print the time
}

// function to print the current time since start to serial
void printTime() // function to print the elapsed time (timer)
{
  int s = (secs - START_VAL) / INC; // seconds passed since start
  int m = (mins - START_VAL) / INC; // minutes passed since start
  int h = (hrs - START_VAL) / INC; // hours passed since start
  Serial.print("Time: "); // prints the time preface
  Serial.print(h); // value of the hours to be printed
  Serial.print("h"); // to print the hours
  Serial.print(m); // value of the minutes to be printed
  Serial.print("m"); // to print the minutes
  Serial.print(s); // value of the seconds to be printed
  Serial.print("s\n"); // to print the seconds
}