#include <Arduino.h>
#include <vector>

void splitData(const String& dataIn, const String& delimiter, float sensordata[], int maxSize) {
    int startIndex = 0;
    int endIndex = dataIn.indexOf(delimiter);
    int count = 0;
    
    while (endIndex != -1 && count < maxSize) {
        String token = dataIn.substring(startIndex, endIndex);
        sensordata[count++] = token.toFloat(); // Convert string to float and add to the array
        startIndex = endIndex + delimiter.length();
        endIndex = dataIn.indexOf(delimiter, startIndex);
    }
    
    // Add the last token after the last delimiter
    if (startIndex < dataIn.length() && count < maxSize) {
        sensordata[count++] = dataIn.substring(startIndex).toFloat(); // Convert string to float and add to the array
    }
}