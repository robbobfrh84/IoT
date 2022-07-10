boolean valIn(int arr[], int x, int rng) {
  for (int i = 0; i < rng; i++) {
    if (arr[i] == x){
      return true;
    }
  }
  return false;
}
