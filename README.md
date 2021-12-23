# papyMonitor Arduino

papyMonitor-arduino contains the necessary files to work with an Arduino board together with the papyMonitor-gui application.

## Installation

There are two folders

The **examples** folder contains various examples and can be downloaded to a folder of your choice

The **papyMonitor** folder is a library that you **must** put on your sketchbook location. To see where your sketchbook location is, open the Arduino IDE then select Files->Preferences: A popup windows will show the "Settings" tab, the location is under the "Sketchbook location".
Open this location on your disk and you'll find a folder "libraries". Copy the folder "papyMonitor" inside the folder "libraries". That's it!

## Usage/Documentation

In summary, for each sketch you make (.ino file) you must write a matching .lua file for the papyMonitor-gui to understand what is coming from the serial port

See the README file in the examples folder to see instructions on how to use the library with your .ino file

See TODO to see how to manage the .lua configuration file

