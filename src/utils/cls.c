void cls(void)
{
#ifdef linux
  // código especifico para linux
  // system ("clear");//poderia ser este mas escolhi este outro pois é mais a cara do C
  system("clear");
#elif defined WIN32
  // código específico para windows
  system("cls");
  printf("\ne' Windows hahahahaha\n\n");
#else
  printf("\e[H\e[2J");
  printf("\nSO não validado\n\n");
#endif
}