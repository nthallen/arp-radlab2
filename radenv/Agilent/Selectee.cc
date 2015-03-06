/**
 * \file Selectee.cc
 */
#include "Selector.h"

Selectee::Selectee(int fd_in, int flag) {
  flags = flag;
  fd = fd_in;
}

Selectee::Selectee() {
  fd = -1;
  flags = 0;
}

Timeout *Selectee::GetTimeout() {
  return NULL;
}

 
