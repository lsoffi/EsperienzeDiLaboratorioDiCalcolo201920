main() {
  char string1[50] = "Libiam nei lieti calici";
  char string2[50] = "Amami, Alfredo!";
  char * const p1 = string1;
  printf("%s\n", p1);
  p1[17] = 's';
  printf("%s\n", p1);
  p1 = string2;
  printf("%s\n", p1);
}
