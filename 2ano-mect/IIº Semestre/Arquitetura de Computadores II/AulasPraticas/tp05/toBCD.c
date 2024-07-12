/*
# -----------------------------------
# 2º Ano-2ºSemestre | Abril 2021
# Arquitectura de Computadores II
# Jodionisio Muachifi, 97147, MIECT
*/

unsigned char toBCD(unsigned char value)
{
  return ((value / 10) << 4) + (value % 10);
}