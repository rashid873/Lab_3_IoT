from machine import Pin, I2C
import dht
import ssd1306
import time

# Setup I2C for OLED
i2c = I2C(0, scl=Pin(9), sda=Pin(8))
oled = ssd1306.SSD1306_I2C(128, 64, i2c)

# Setup DHT11
sensor = dht.DHT11(Pin(4))

# Button Setup (GPIO0)
button = Pin(0, Pin.IN, Pin.PULL_UP)  

def display_message(message):
    oled.fill(0)
    oled.text(message, 10, 20)
    oled.show()

def read_dht11():
    try:
        sensor.measure()
        temp = sensor.temperature()
        hum = sensor.humidity()
        print(f"🌡 Temp: {temp}°C | 💧 Humidity: {hum}%")

        # Display on OLED
        oled.fill(0)
        oled.text("DHT11 Sensor", 10, 5)
        oled.text(f"Temp: {temp}C", 10, 25)
        oled.text(f"Humidity: {hum}%", 10, 45)
        oled.show()
    
    except OSError as e:
        print("❌ DHT11 error:", e)
        display_message("Sensor Error!")

# Initial message
display_message("Press Btn to Start!")

while True:
    if button.value() == 0:
        read_dht11()
        time.sleep(2)  # Debounce delay