#include <SPI.h>
#include <mcp_can.h> // 초음파 센서 핀 설정 
const int trigPin = 8; 
const int echoPin = 9; // CAN 통신 설정 
MCP_CAN CAN0(10); // CS 핀 설정 
void setup() { 
    Serial.begin(115200); // 초음파 센서 핀 모드 설정 
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); // CAN 통신 초기화 
    if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) { 
        //Serial.println("MCP2515 Initialized Successfully!"); 
    } 
    else { 
        //Serial.println("Error Initializing MCP2515..."); 
        while (1); 
    } CAN0.setMode(MCP_NORMAL); // CAN 모듈을 통신 모드로 설정 
} 
void loop() { 
    // 초음파 센서로 거리 측정 
    long duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPin, LOW); 
    duration = pulseIn(echoPin, HIGH); 
    distance = duration * 0.034 / 2; // cm 단위 // CAN 메시지로 전송 
    byte data[4]; 
    memcpy(data, &distance, sizeof(distance)); // 거리를 4바이트 배열에 복사 
    byte sndStat = CAN0.sendMsgBuf(0x100, 0, 4, data); // ID: 0x100, 데이터 길이: 4 
    if (sndStat == CAN_OK) { 
        //Serial.print("Sent: ");
        //Serial.println(distance); 
    } 
    else { 
        Serial.println("Error Sending Message..."); 
    } 
    delay(100); // 100ms 간격으로 전송 
} //송신