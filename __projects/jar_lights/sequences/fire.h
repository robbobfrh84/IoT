bool gReverseDirection = false;
#define COOLING  55
#define SPARKING 120

void Fire2012() {
  static byte heat[NUM_LEDS];
    for( int i = 0; i < NUM_LEDS; i++) { // Step 1.  Cool down every cell a little
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
    for( int k= NUM_LEDS - 1; k >= 2; k--) { // Step 2.  Heat from each cell drifts 'up' and diffuses a little
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    if( random8() < SPARKING ) { // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }
    for( int j = 0; j < NUM_LEDS; j++) { // Step 4.  Map from heat cells to LED colors
      CRGB color = HeatColor( heat[j]);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
}

void fire() {
  Fire2012(); // run simulation frame
  FastLED.show(); // display this frame
  FastLED.delay(1000 / 60);
}

