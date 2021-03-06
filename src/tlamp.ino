#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(2, 3); // RX, TX

#define W_PIN 6
#define RED_PIN 9
#define GRN_PIN 10
#define BLU_PIN 11

String data;
byte RED, GREEN, BLUE;
byte RED_A = 0;
byte GREEN_A = 0;
byte BLUE_A = 0;
int led_delay = 0;
byte colour_count = 1;
#define colour_count_max 7
#define colour_delay 4000
#define time_at_colour 1000

unsigned long TIME_LED = 0;
unsigned long TIME_COLOUR = 0;

//Blue
#define C1_R 0
#define C1_G 0
#define C1_B 255
//Red
#define C2_R 255
#define C2_G 0
#define C2_B 0
//White
#define C3_R 255
#define C3_G 255
#define C3_B 255
//Orange
#define C4_R 255
#define C4_G 186
#define C4_B 0
//Light Blue
#define C5_R 0
#define C5_G 168
#define C5_B 255
//Purple
#define C6_R 255
#define C6_G 0
#define C6_B 255
//Yellow
#define C7_R 255
#define C7_G 250
#define C7_B 0


void setup() {
    Bluetooth.begin(9600);
    Serial.begin(9600);

    RED = C1_R;
    GREEN = C1_G;
    BLUE = C1_B;
    led_delay = (colour_delay - time_at_colour) / 255;

    setRGBColor(0,0,0);
}


void fadeRGBRandom()
{
    if(millis() - TIME_LED >= led_delay){
        TIME_LED = millis();
        led();
    }

    if(millis() - TIME_COLOUR >= colour_delay){
        TIME_COLOUR = millis();
        color();
    }
}


void setRGBColor(int red, int green, int blue)
{
    analogWrite( RED_PIN, red );
    analogWrite( GRN_PIN, green );
    analogWrite( BLU_PIN, blue );
}


void setWhiteIntensity(int intensity)
{
    analogWrite( W_PIN, intensity );
}

void loop() {
    handleBTData();
}

void handleBTData()
{
    if (Bluetooth.available()) {
        data = Bluetooth.readString();

        Serial.println(data);
        Bluetooth.println(data);

        char copy[50];
        data.toCharArray(copy, 50);

        int w, r, g, b;
        int n = sscanf(copy, "W;%d;RGB;%d;%d;%d", &w, &r, &g, &b);

        setWhiteIntensity(w);
        setRGBColor(r,g,b);
    }
}

void led()
{
    //Check Values and adjust "Active" Value
    if(RED != RED_A) {
        if(RED_A > RED) RED_A = RED_A - 1;
        if(RED_A < RED) RED_A++;
    }
    if(GREEN != GREEN_A) {
        if(GREEN_A > GREEN) GREEN_A = GREEN_A - 1;
        if(GREEN_A < GREEN) GREEN_A++;
    }
    if(BLUE != BLUE_A) {
        if(BLUE_A > BLUE) BLUE_A = BLUE_A - 1;
        if(BLUE_A < BLUE) BLUE_A++;
    }

    //Assign modified values to the pwm outputs for each colour led
    analogWrite(RED_PIN, RED_A);
    analogWrite(GRN_PIN, GREEN_A);
    analogWrite(BLU_PIN, BLUE_A);

}

void color()
{
    //Increment the color by one or go back to 1 if maxed out
    if(colour_count < colour_count_max) colour_count++;
    else colour_count = 1;

    if(colour_count == 1){
        RED = C1_R;
        GREEN = C1_G;
        BLUE = C1_B;
    } else if(colour_count == 2){
        RED = C2_R;
        GREEN = C2_G;
        BLUE = C2_B;
    } else if(colour_count == 3){
        RED = C3_R;
        GREEN = C3_G;
        BLUE = C3_B;
    } else if(colour_count == 4){
        RED = C4_R;
        GREEN = C4_G;
        BLUE = C4_B;
    } else if(colour_count == 5){
        RED = C5_R;
        GREEN = C5_G;
        BLUE = C5_B;
    } else if(colour_count == 6){
        RED = C6_R;
        GREEN = C6_G;
        BLUE = C6_B;
    } else if(colour_count == 7){
        RED = C7_R;
        GREEN = C7_G;
        BLUE = C7_B;
    }
}
