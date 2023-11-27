const int potPin = A0; // 滑动变阻器连接到A0
const int button1Pin = 2; // 按钮1连接到D2
const int button2Pin = 3; // 按钮2连接到D3
const int ledSuccess = 4; // 成功的LED连接到D4
const int ledFailure = 5; // 失败的LED连接到D5

int step = 0; // 用于跟踪密码输入的当前步骤

void setup() {
  // 初始化引脚
  pinMode(potPin, INPUT);
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(ledSuccess, OUTPUT);
  pinMode(ledFailure, OUTPUT);
}

void loop() {
  int potValue = analogRead(potPin); // 读取变阻器的值
  bool button1Pressed = digitalRead(button1Pin) == LOW; // 检查按钮1是否被按下
  bool button2Pressed = digitalRead(button2Pin) == LOW; // 检查按钮2是否被按下

  switch (step) {
    case 0: // 第一步：检查变阻器是否调到最高
      if (potValue > 2000) { // 假设950是最大值的阈值
        step = 1;
      }
      break;
    case 1: // 第二步：检查是否按下了按钮1
      if (button1Pressed) {
        step = 2;
      } else if (button2Pressed) { // 如果在步骤1按下了按钮2，则失败
        failure();
      }
      break;
    case 2: // 第三步：检查变阻器是否调到最低
      if (potValue < 50) { // 假设50是最小值的阈值
        step = 3;
      } else if (potValue > 950) { // 如果滑动变阻器回到最大值，则失败
        failure();
      }
      break;
    case 3: // 第四步：检查是否按下了按钮2
      if (button2Pressed) {
        digitalWrite(ledSuccess, HIGH); // 点亮成功的LED
        delay(2000); // 等待2秒
        digitalWrite(ledSuccess, LOW); // 熄灭LED
        step = 0; // 重置步骤
      } else if (button1Pressed) { // 如果在步骤3按下了按钮1，则失败
        failure();
      }
      break;
  }
 
}

void failure() {
  digitalWrite(ledFailure, HIGH); // 点亮失败的LED
  delay(2000); // 等待2秒
  digitalWrite(ledFailure, LOW); // 熄灭LED
  step = 0; // 重置步骤
}