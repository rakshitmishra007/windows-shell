#ifndef _DLL_H_
#define _DLL_H_

#if BUILDING_DLL
#define DLLIMPORT __declspec(dllexport)
#else
#define DLLIMPORT __declspec(dllimport)
#endif

DLLIMPORT char *system_info();
DLLIMPORT char *process_list();
DLLIMPORT char *current_dir();
DLLIMPORT void system_shutdown();
DLLIMPORT char *idletime();
DLLIMPORT char *unknown_command();
DLLIMPORT char *list_files();

#endif
