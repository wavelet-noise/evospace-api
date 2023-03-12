#pragma once
#ifdef EVOSPACE_RELEASE_CHECK
#define ensure_release(ARG) ensure(ARG)
#else
#define ensure_release(ARG) (ARG)
#endif