# Compressor VST Program

This program is a compressor VST plugin made using JUCE and Foleys Framework for the GUI. It allows users to adjust compressor parameters such as threshold, attack, release, and ratio using sliders. The program also features a plot that analyzes the input and output of the compressor. 

![Application screenshot](./Source/resources/screenshot.PNG)

It implements some basics paterns to make a complête GUI, but the dsp stays juce's default one

## JUCE
    This program has been made using juce framework and foleys librairy for GUI.

## Still Todo
    Add comunication with slider to change their lookandfeel dynamically.
    
    Cracks in the sound... Analyzer ?

## Use it
    To use this code and play with, install juce, add the relevant foleys librairy gui module and clone this repository.
    Then every thing should work.

## Issues encountered :

    Allow the binary_data in foleys's module parameter, other one no one can load images.

## Installation

To install the compressor VST program, simply download the appropriate version for your operating system and follow the installation instructions for your DAW.

## Usage

Once installed, the compressor VST program can be used like any other VST plugin in your DAW. Simply add it to a track or bus and adjust the compressor parameters to your liking.

## License

This program is licensed under the [MIT License](LICENSE).
