#ifndef DEBUG
#define DEBUG

#ifdef __TEST
#define DEBUG_LOG(x) x
#else
#define DEBUG_LOG(x) // x
#endif

#endif /* !DEBUG*/