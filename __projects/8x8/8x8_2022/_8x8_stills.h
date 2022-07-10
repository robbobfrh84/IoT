void _8x8_stills_draw(int a[]) {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      int id = (x*8) + y;
      pixels.setPixelColor( id, pixels.Color( r[a[id]] ,g[a[id]], b[a[id]] ) );
    }
  }
}

void _8x8_stills(String still, int showTime) {

  Serial.println("Showing still: "+still);

  if (still == "swatch") {
    int a[] = {
       0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 1, 2, 3, 4, 0, 0,
       0, 0, 5, 6, 7, 8, 0, 0,
       0, 0, 9,10,11,12, 0, 0,
       0, 0,13,14,15, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0,
    };
    _8x8_stills_draw(a);
  }

  if (still == "bob") {
    int a[] = {
       0, 0, 3, 3, 3, 0, 0, 0,
       0, 3, 3, 3, 3, 3, 0, 0,
       3, 6, 6, 4, 6, 4, 0, 0,
       0,13,13,13,13,13, 0, 0,
       0, 9,13,13, 1, 9, 0, 0,
      13, 0, 9, 9, 9, 0,13, 0,
       0, 0,12,12,12,11, 0, 0,
       0,11, 0, 0, 0, 0, 0, 0,
    };
    _8x8_stills_draw(a);
  }

  pixels.show();
  delay(showTime);
  
}
