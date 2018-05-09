// Determine if we are rotating by a positive or negative angle
if (theta < 0) {
  sigma = -1;
}
else {
  sigma = 1;
}

//A functionally equivalent version of the above using ? operator
sigma = theta < 0 ? -1 : 1;
