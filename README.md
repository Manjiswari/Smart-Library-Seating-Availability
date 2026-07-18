# Smart Library Seat Availability Indicator System

This project was developed to solve a common problem faced by students in university libraries—finding an available seat during busy hours. Instead of walking around the library searching for an empty seat, the system shows the number of available seats in real time.

The project uses Arduino UNO, ESP32, and IR sensors to detect seat occupancy. The available seat count is displayed on an LCD, and a web dashboard allows the same information to be viewed remotely.

---

## Features

- Detects whether a library seat is occupied using IR sensors
- Shows the available seat count in real time
- LCD display for quick seat availability information
- Web dashboard built using ESP32 and Wi-Fi
- Simple, low-cost, and easy to expand for larger libraries

---

## Technologies Used

### Hardware
- Arduino UNO
- ESP32
- IR Sensors
- 16×2 LCD Display
- LEDs
- Buzzer

### Software
- Arduino IDE
- Embedded C/C++
- HTML
- CSS
- JavaScript

---

## How It Works

1. IR sensors monitor each seat.
2. The Arduino and ESP32 read the sensor values.
3. The system calculates the number of available seats.
4. The updated seat count is displayed on the LCD.
5. The same information is available through a web page over Wi-Fi.

---

## Project Structure

```
Smart-Library-Seating-Availability/
│── Arduino_Code/
│── ESP32_Code/
│── Web_Dashboard/
│── Images/
│── Report/
│── README.md
```

---

## Future Improvements

- Mobile app for checking seat availability
- Cloud-based monitoring
- RFID-based seat reservation
- Support for larger libraries
- Integration with smart campus services

---

## Team Members

- J. Manjiswari
- M. Jayasree
- P. V. R. Praveena
- S. K. Karishma
- K. Bhavana
- Gorantla Vishnu

---

## Guide

**Prof. Dr. Gayathri Dhara**  
Assistant Professor, Senior Grade 1  
School of Computer Science and Engineering  
VIT-AP University

---

## License

This project is licensed under the MIT License.
