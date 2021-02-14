#include <Mouse.h>
#include <Adafruit_NeoPixel.h>
#include <DebounceEvent.h>
/*
 *  NAME: Arduino Mouse Jiggler
 *  DATE: 2019-09-18
 *  DESC: Arduino based mouse emulator
 *  VERSION: 1.0
 */

/* -------------------------------------- 
 *             C O L O R S
 * -------------------------------------- 
 */

#define COLOR_OFF_IDLE      COLOR(255,0,0)
#define BRIGHTNESS_OFF_IDLE 0

#define COLOR_OFF           COLOR(255,0,0)
#define BRIGHTNESS_OFF      20

#define COLOR_IDLE          COLOR(0,255,0)
#define BRIGHTNESS_IDLE     25

#define COLOR_ACTIVE        COLOR(0,255,0)
#define BRIGHTNESS_ACTIVE   255

/* -------------------------------------- 
 *          B E H A V I O R 
 * -------------------------------------- 
 */

/* Interval of movement in seconds */
#define INTERVAL 10
/* Time after activation for the first jiggle */
#define FIRST_JIGGLE 1
/* Time, after which the system switches from state "OFF" to state "OFF_IDLE" */
#define TIME_IDLE 60

/* Distance (Pixel) to travel */
#define DISTANCE 10
/* Time (ms) between back- and forth movement */
#define TIME 150


/* -------------------------------------- 
 *           H A R D W A R E
 * -------------------------------------- 
 */

/* Pin of Switch */
#define SW_PIN 6
#define CUSTOM_DEBOUNCE_DELAY   50
#define CUSTOM_REPEAT_DELAY     500

/* Neopixel Pin */
#define NP_PIN 4

/* Internals */

//#define DEBUG

#define COLOR(R, G, B) (((uint32_t)R<<16)|((uint32_t)G<<8)|((uint32_t)B<<8))
#define TIME_PASSED(evt, len) ((millis() - evt) > len)

typedef enum {
  OFF_IDLE_st,
  OFF_st,
  IDLE_st,
  ACTIVE_ENTER_st,
  ACTIVE_st,
  ACTIVE_LEAVE_st
} state_te;

state_te state;
unsigned long millis_evt;

Adafruit_NeoPixel pixels(1, NP_PIN, NEO_GRB + NEO_KHZ800);
DebounceEvent * button;

void setup()
{
  /* Set up pins */
  pinMode(SW_PIN, INPUT_PULLUP);
  pinMode(NP_PIN, OUTPUT);

  button = new DebounceEvent(SW_PIN, BUTTON_PUSHBUTTON | BUTTON_DEFAULT_HIGH | BUTTON_SET_PULLUP, CUSTOM_DEBOUNCE_DELAY, CUSTOM_REPEAT_DELAY);

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear(); // Set all pixel colors to 'off'
  
  /* Enable Mouse */
  Mouse.begin();

  #ifdef DEBUG
  Serial.begin(115200);
  #endif;

  state = OFF_IDLE_st;
}

void LED_off_idle(void)
{
  //pixels.clear(); // Set all pixel colors to 'off'
  pixels.setBrightness(BRIGHTNESS_OFF_IDLE);
  pixels.setPixelColor(0, COLOR_OFF_IDLE);
  pixels.show();   // Send the updated pixel colors to the hardware.
}

void LED_off(void)
{
  //pixels.clear(); // Set all pixel colors to 'off'
  pixels.setBrightness(BRIGHTNESS_OFF);
  pixels.setPixelColor(0, COLOR_OFF);
  pixels.show();   // Send the updated pixel colors to the hardware.
}

void LED_idle(void)
{
  pixels.setBrightness(BRIGHTNESS_IDLE);
  pixels.setPixelColor(0, COLOR_IDLE);
  pixels.show();   // Send the updated pixel colors to the hardware.
}

void LED_active(void)
{
  pixels.setBrightness(BRIGHTNESS_ACTIVE);
  pixels.setPixelColor(0, COLOR_ACTIVE);  
  pixels.show();   // Send the updated pixel colors to the hardware.
}

void loop()
{
  boolean btn_pressed = false;
  
  /* Read button */
  if (unsigned int event = button->loop()) {
      if (event == EVENT_RELEASED) {
        btn_pressed = true;
      }
  }

  switch (state) 
  {
      /* OFF IDLE ---------------------------------------- */
      case OFF_IDLE_st: 
      {
        /* Handle LED in this state */
        LED_off_idle();

        /* Transition OFF -> On */
        if (btn_pressed)
        {
          state = IDLE_st;
          /* Timestamp in the past, to have next event in FIRST_JIGGLE seconds */
          millis_evt = millis() - ((INTERVAL - FIRST_JIGGLE)*1000);
          
          #ifdef DEBUG
          Serial.println("OFF_Idle -> Idle");
          #endif;
        }
        break;
      }
      
      /* OFF --------------------------------------------- */
      case OFF_st:
      {
        /* Handle LED in this state */
        LED_off();

        /* Transition OFF -> On */
        if (btn_pressed)
        {
          state = IDLE_st;
          /* Timestamp in the past, to have next event in FIRST_JIGGLE seconds */
          millis_evt = millis() - ((INTERVAL - FIRST_JIGGLE)*1000);

          #ifdef DEBUG
          Serial.println("OFF -> Idle");
          #endif;
        }

        #ifdef DEBUG
        uint32_t diff = millis()-millis_evt;
        if (diff % 1000 == 0)
        {
          Serial.print("Idle since ");
          Serial.println(diff/1000);
        }
        #endif;

        /* Transition Off -> Off_Idle */
        if (TIME_PASSED(millis_evt, ((uint32_t)TIME_IDLE)*1000))
        {
          state = OFF_IDLE_st;
          
          #ifdef DEBUG
          Serial.println("OFF -> Off_Idle");
          #endif;
        }
        break;
      }
      
      /* IDLE -------------------------------------------- */
      case IDLE_st:
      {
        LED_idle();
        
        /* Transition On -> Off */
        if (btn_pressed)
        {
          state = OFF_st;
          /* Timestamp now, for OFF -> Off_Idle transition */
          millis_evt = millis();

          #ifdef DEBUG
          Serial.println("Idle -> Off");
          #endif;
        }

        /* Transition Off -> Off_Idle */
        if (TIME_PASSED(millis_evt, INTERVAL*1000))
        {
          state = ACTIVE_ENTER_st;
          #ifdef DEBUG
          Serial.println("Idle -> Active_Enter");
          #endif;
        }
        break;
      }
      
      /* ACTIVE --------------------------------------- */
      case ACTIVE_ENTER_st:
      {
        LED_active();

        Mouse.move(DISTANCE, 0, 0);

        state = ACTIVE_st;
        millis_evt = millis();

        #ifdef DEBUG
        Serial.println("Active_Enter -> Active");
        #endif;
          
        break;
      }

      /* ACTIVE --------------------------------------- */
      case ACTIVE_st:
      {
        LED_active();
        
        /* Transition On -> Off */
        if (btn_pressed)
        {
          state = OFF_st;
          /* Timestamp now, for OFF -> Off_Idle transition */
          millis_evt = millis();
        }

        /* Wait specified time to move mouse back */
        if(TIME_PASSED(millis_evt, TIME))
        {
          state = ACTIVE_LEAVE_st;

          #ifdef DEBUG
          Serial.println("Active -> Active_Leave");
          #endif;
        }
        break;
      }

      /* ACTIVE --------------------------------------- */
      case ACTIVE_LEAVE_st:
      {
        LED_active();

        Mouse.move(DISTANCE*-1, 0, 0);

        state = IDLE_st;
        millis_evt = millis();

        #ifdef DEBUG
        Serial.println("Active_Leave -> Idle");
        #endif;
        break;
      }

      /* Default ---------------------------------------- */
      default:
      {
        state = OFF_IDLE_st;
        break;
      }
  }

  delay(1);
}
