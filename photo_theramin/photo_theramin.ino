// Optical Theramin

// Pin Definitions
#define PHONES 9 // Headphones connected to digital pin 9
#define PHOTOCELL 0 // Photocell analog in pin 0

// Variable definitions
long val = 0; // Raw value from photocell
long max_read = 0; // Maximum value from calibation phase
long min_read = 1000; // Minimum value from calibration phase
double f = 0; // Frequency of sound
double norm_f = 0; // Normalized frequency
double log_f = 0; // Logarithm of normalized frequency
int i_log_f = 0; // Rounded logarithm
int i = 0; // Loop dummy variable
double factor = 0; // Scaling factor for calibration
double shift = 0; // Shift for calibration
long max_freq = 1048; // Maximum desired frequency after calibration
long min_freq = 131; // Minimum desired frequency after calibration

// Magic numbers that make the intervals sound pleasing
double gap = 1.148698355; // Ratio of consecutive notes (pentatonic)
                          // It's the 5th root of 2
// double gap = 1.059463094; // Ratio of consecutive notes (chromatic)
                          // It's the 12th root of 2
                          
void setup() {
  pinMode(PHONES, OUTPUT); // Sets the digital pin as output
  
  // Calibration loop to determine a reasonable range of light
  // levels (min_read to max_read) and map that to frequencies
  // between min_freq and max_freq
  for (i=0; i<500; i++) {
    val = analogRead(PHOTOCELL);  // Read photocell
    tone(PHONES, val); // Play the raw tone to guide calibration
    if (val > max_read) { // As the values climb, store the largest
      max_read = val;
    }
    if (val < min_read) {
      min_read = val;
    }
    delay(10); // Reasonable delay
  }
  
  // Now we use the calibration to calculate scale and shift 
  // parameters.
  factor = (double)(max_freq - min_freq) / (double) (max_read - min_read); // Scale parameter
  
  // It's like slope
  
  shift = factor * min_read - min_freq; // Shift parameter; it's like an offset
}

void loop() {
  val = analogRead(PHOTOCELL); // Read the photocell
  /*
   * This linearly maps the frequency to a value between
   * min_freq and max_freq according to the calibration
   * result.
   */
  f = factor * val - shift;
  
  norm_f = f / (double)min_freq; // Dividing an exponential function by the min value
  log_f = log(norm_f) / log(gap); // Allows us to take the log (base gap) and the result
  i_log_f = round(log_f); // is the number of notes above the lowest, once we round it.
  f = min_freq * pow(gap, i_log_f); // We better "unlog" it.
  
  tone(PHONES, f); // This produces the tone signal.
}
