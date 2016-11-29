// FYI: Для littleBits доступны 3 входных и 3 выходных пина
// Три правых - ввод
const int top_input_pin = 0; // только digital обмены!
const int middle_input_pin = A0;
const int bottom_input_pin = A1;

// Три левых - вывод
const int top_output_pin = 1; // только digital обмены!
const int middle_output_pin = 5; // используй для вывода PWM значений
const int bottom_output_pin = 9;

// и блок ГЛОБАЛЬНЫХ переменных, которые мы будем использовать для ввода и вывода

int darknessLevel = 0; // в эту переменную мы читаем текущий уровень темноты
int signalCloudbit = LOW; // в эту переменную мы пишем HIGH когда хотим послать сообщение в IFFT через CloudBit


void setup()
{	
	// инициализируем 3 левых пина на ввод
	pinMode(top_input_pin, INPUT);
	pinMode(bottom_input_pin, INPUT);
	pinMode(middle_input_pin, INPUT);

	// инициализируем 3 правых пина на вывод
	pinMode(top_output_pin, OUTPUT);
	pinMode(middle_output_pin, OUTPUT);
	pinMode(bottom_output_pin, OUTPUT);

	// начинаем обмен данными
	Serial.begin(9600);

}

void loop()
{
	// поскольку все переменные уже объявлены и все пины инициализированы...
	// нам остается только читать писать :)

	// прочитаем аналоговый сигнал с серединного пина в переменную darknessLevel
	darknessLevel = analogRead(middle_input_pin);
	// сигнал, который содержится в darknessLevel, описан в долях от 1024, а нам надо в долях от 255!
	// поэтому мы его map, переприсвоив значение darknessLevel новому значению, сделанному методом map
	darknessLevel = map(darknessLevel, 0, 1024, 0, 255);

	// теперь выведем его в вывод порта...
	Serial.println(darknessLevel);
	// и в o21 NUMBER!
	analogWrite(middle_output_pin, darknessLevel);

	// прочитаем цифрововой сигнал с модуля cloudBit в переменную signalCloudbit
	signalCloudbit = digitalRead(top_input_pin); // если сигнал ВКЛ (HIGH) - надо включать свет :)

	// если темнота близка к полной (полная == 255) или cloudbit получил сигнал high...
	if (darknessLevel > 240 || signalCloudbit == HIGH) 
	{
		// то мы отдаем команду в правый верхний порт ВКЛ
		digitalWrite(top_output_pin, HIGH);
		// и напишем уровень темноты в o21 NUMBER!
		analogWrite(middle_output_pin, darknessLevel);
	}
	else // то есть не темно и команды включиться тоже не было
	{
		// то мы отдаем команду в правый верхний порт ВЫКЛ
		digitalWrite(top_output_pin, LOW);
		// и напишем уровень темноты в o21 NUMBER!
		analogWrite(middle_output_pin, darknessLevel);
	}

}
