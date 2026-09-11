#ifndef __GETOPT__
#define __GETOPT__

int getopt(int argc, char *argv[], const char *optionS);

#ifdef _DEBUG
void TestGetOpt(int argc, char *argv[]);
#endif //_DEBUG

#endif //__GETOPT__