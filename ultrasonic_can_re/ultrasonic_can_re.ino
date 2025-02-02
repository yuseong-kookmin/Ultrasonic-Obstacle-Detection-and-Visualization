#include <SPI.h>
#include <mcp_can.h>
MCP_CAN CAN0(10); // CS 핀 설정
void setup() { 
    Serial.begin(115200); // CAN 통신 초기화 
    if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
        //Serial.println("MCP2515 Initialized Successfully!"); 
    }
    else { 
        //Serial.println("Error Initializing MCP2515..."); 
        while (1); 
    } 
    CAN0.setMode(MCP_NORMAL); // 통신 모드로 설정 
} 
void loop() { 
    byte len = 0; 
    byte buf[8]; // CAN 메시지 수신 확인 
    unsigned long canId;
    //= CAN0.getGPI(); // 메시지 ID 확인 
    if (CAN0.checkReceive() == CAN_MSGAVAIL) { 
        CAN0.readMsgBuf(&canId, &len, buf); // 메시지 읽기 
        if (canId == 0x100) { // ID가 0x100인 메시지만 처리 
            long distance;
            memcpy(&distance, buf, sizeof(distance)); // 4바이트 배열에서 거리 값 복사 
            //Serial.print("Received: "); 
            Serial.println(distance); 
        } 
    } 
} //수신