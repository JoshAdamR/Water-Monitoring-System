// Define constants
const float knownResistance = 4600; // Resistance of the resistor in ohms
const float voltageReference = 5.0; // Voltage reference for ADC (in volts)

// Resistance to salinity mapping
const float resistanceMin = 4000; // Minimum resistance value
const float resistanceMax = 7000; // Maximum resistance value
const float salinityMin = 0; // Minimum salinity value
const float salinityMax = 4615; // Maximum salinity value

// Function to calculate salinity using Practical Salinity Scale formula
float calculateSalinity(float resistance) {
    float salinity = map(resistance, resistanceMax, resistanceMin, salinityMin, salinityMax);
    if (salinity < 0){
      salinity = 0;
    }
    return salinity/10000;
}


float salinitySensor() {
    float analogPin = A2; // Analog pin connected to the electrodes
    // Read analog value from A0 pin
    float sensorValue = analogRead(analogPin);

    // Convert analog value to voltage
    float voltage = sensorValue * (voltageReference / 1024.0);
    
    // Convert voltage to resistance
    float resistance = knownResistance * ((voltageReference / voltage) - 1);

    // Calculate salinity
    float salinity = calculateSalinity(resistance);
    Serial.println(salinity);
    Serial.println(resistance);
    return(salinity);
} 
