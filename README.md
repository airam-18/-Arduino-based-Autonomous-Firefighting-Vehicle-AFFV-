This project presents an Arduino-based Autonomous Firefighting Vehicle (AFFV) developed as an educational prototype to demonstrate the integration of embedded systems, robotics, and autonomous navigation. The robot is capable of detecting small flame sources using infrared (IR) sensors, navigating toward them, avoiding obstacles with an ultrasonic sensor, and activating a water pump to extinguish the detected fire.

The final prototype extends the original implementation by incorporating an HC-SR04 ultrasonic sensor for obstacle avoidance. While this feature was not included in the reference tutorial, it was integrated without significant changes to the overall system architecture.

Note: The IR flame sensor values provided in the source code may require calibration depending on the environment. Since the sensors operate by detecting infrared light, bright rooms, direct sunlight, or strong artificial lighting can lead to false positives. Users are encouraged to adjust the threshold values according to their testing conditions.

This repository contains the source code, hardware configuration, and documentation necessary to reproduce the prototype. The project was developed for educational and research purposes and is not intended for real-world firefighting applications.
This was the final prototipe:
<img width="2000" height="1500" alt="image" src="https://github.com/user-attachments/assets/2803cdb7-ccc7-4365-b50b-f4836b8c1351" />

Also the number for the ir senzor needs to be modify for your needs.( for a brighter room, the ir senzor will modify the values and be aware that, because it's working based on light, it can confuse bright light with fire)
The video that i used to build the prototipe:
https://www.bing.com/videos/riverview/relatedvideo?q=fire+car+arduino&&mid=D8AFAD7C1F177E71FEF3D8AFAD7C1F177E71FEF3&churl=https%3a%2f%2fwww.youtube.com%2fchannel%2fUCMWpEy4e1hVE7YHDZlcQNFw&FORM=VRDGAR
The ultrasound doesnt apear in the video, but is not hard to add.
you can check this video out:
https://www.bing.com/videos/riverview/relatedvideo?q=ultrasound+arduino&&mid=759815FA09C5848B479A759815FA09C5848B479A&churl=https%3a%2f%2fwww.youtube.com%2fchannel%2fUCdhDOlwIuY0yR-KxlblnsxQ&mmscn=mtsc&aps=14&FORM=VRDGAR
