main(){
  unsigned int num1 = 11, num2 = 13, num3 = 21, numBit = 3;
  unsigned char numChar = 4;
  printf("%u %u AND %u OR %u XOR %u\n",
	 num1, num2, num1 & num2, num1 | num2 , num1 ^ num2);
  printf("%u >> %u  = %u\n", num3, numBit, num3>>numBit);
  printf("~%u = %u\n", numChar, (~numChar) & 0xFF);
}
