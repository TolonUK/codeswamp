#pragma once

#ifdef DLLEXPORT
#define harvester_export __declspec(dllexport)
#else
#define harvester_export 
#endif
