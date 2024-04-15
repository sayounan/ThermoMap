# ThermoMap
## Background
ThermoMap is software built to continue the work of a previous year's design named Thermectrode. The intended use is to
monitor the internal temperature of the brain during radio frequency (RF) ablation (burning/melting) procedures in the 
brain to treat drug resistant epilepsy (DRE). The Thermectrode was a thermistor embedded stereo-electroencephalograph 
(sEEG) that can monitor brain temperature while also reading EEG data during neuro-ablation procedures. The Thermectrode 
fed the analog signal to an external circuit that filtered the signal and passed it onto a data acquisition device which 
then passed it onto a computer via USB protocol. This was then displayed as a graph along with a numerical temperature 
reading. The ThermoMap team downsized the hardware significantly by replacing the analog circuits, data acquisition 
device, and computer with a digital temperature sensor connected directly to the Raspberry Pi general purpose 
input/output (GPIO). Another advantage of digitizing the circuit is the ability to run the RF ablator while maintaining 
the ability to read the data without any interference in the signal by RF noise.
## Introduction
The ThermoMap software is designed to give clinicians all the important information during a neuro-ablation procedure at
a glance. The software shows the real time heat transfer within the brain overlaid on patient computerized tomography 
(CT) scans. The temperature is depicted as realtime expanding concentric spheres, color coded to correspond to the 
temperature within each sphere.
### Hardware Setup
#### Sensor &harr; Raspberry Pi Pins
* VCC &harr; 3V3 Power
* GND &harr; Ground
* SDA &harr; GPIO 2 (SDA)
* SCL &harr; GPIO 3 (SCL)
#### Clinical Sensor Placement
* Clinical professionals place the temperature sensor within a reasonable distance of the ablator. Can be placed inside 
the neuro-ablation target. 
### Dependancies
* Linux: [The Mono Project](https://www.mono-project.com)
* MacOS: N/A 
* Windows: N/A
### Software Setup
1. Open the executable file.
2. Click the CT scan image to indicate the location of the heat source.
3. Click the "Start Ablation" button to indicate the start of the ablation procedure and begin displaying temperature 
behavior.