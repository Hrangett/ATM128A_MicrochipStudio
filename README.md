# ATM128A_MicrochipStudio
ATM128A 와 MicrochipStudio 를 활용한 실습

## Day 1
- MicrochipStudio 설치
- led 제어
  - shift 연산자를 활용한 led 제어
  - button을 이용한 led 제어
- Fnd 제어
  - 단일fnd 모듈 반복 출력
  - 다중 fnd모듈 제어 (타이머)

## Day 2
- Interrupt 학습
  - Fnd : Interrupt에 따른 Fnd 정지 및 시작
  - Led : Interrupt 발생 시 shift 방향 변경
  - LCD : Interrupt 발생 시 멈춤, lcd창에 interrupt 발생 문구 출력. 다시 발생 시 해당 시점 복귀


## Day 3
- UART
  - HyperTerminal 사용한 실습
    - 메세지 출력, BUTTON 반응, Echo Server, FND에 입력된 숫자 출력
  - TimerCounter
    - 0번 인터럽트 - 오버플로우 인터럽트를 이용해서 1초마다 LED 점등
    - OVerflow interrupt 발생 시 LED 점등(1초)
    - OVerflow interrupt 발생 시 FND 숫자 변경(1초) 
