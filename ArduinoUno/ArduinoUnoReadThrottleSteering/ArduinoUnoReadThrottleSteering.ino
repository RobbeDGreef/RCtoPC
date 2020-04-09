/* You can choose any PWM pin (pins 0-7 AFAIK) */
#define THROTTLEPIN   2
#define STEERINGPIN   7

/* The serial connection info */
#define BAUDRATE      9600
#define SERIAL_CONFIG SERIAL_8N1 /* Means 8 bytes of data, no parity enabled and 1 stop bit */  

/* Because the serial.write() only writes bytes */
void writeserial(uint16_t data)
{
    /* Standard big endian translate and write */
    Serial.write((data >> 8) & 0xFF);
    Serial.write(data & 0xFF);
}

void setup()
{
    /* Setting up serial */
    Serial.begin(BAUDRATE, SERIAL_CONFIG);

    /* Setting up the receiving pins */
    pinMode(STEERINGPIN, INPUT);
    pinMode(THROTTLEPIN, INPUT);
}

void loop()
{
    uint16_t steering = pulseIn(STEERINGPIN, HIGH);
    uint16_t throttle = pulseIn(THROTTLEPIN, HIGH);

    /* Sending a start byte first */
    Serial.write(0);
    writeserial(steering);
    writeserial(throttle);
}
