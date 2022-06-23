void cls(void)
{
#ifdef linux
  system("clear");
#elif defined WIN32
  system("cls");
#else
  printf("\e[H\e[2J");
  printf("\nSO não validado\n\n");
#endif
}