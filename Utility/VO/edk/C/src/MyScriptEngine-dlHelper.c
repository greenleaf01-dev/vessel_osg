/**
 * @file MyScriptEngine-dlHelper.c
 *
 */

#ifdef VO_MSE_FUNCPTR_STATIC
  #define VO_MSE_FUNCPTR_STORAGECLASS static
#else
  #define VO_MSE_FUNCPTR_STORAGECLASS
#endif

#if defined(_WIN32)
  #define DEFAULT_MYSCRIPT_ENGINE_LIBRARY_NAME "MyScriptEngine.dll"
  #define DIRSEP "\\"
#elif defined(__linux__) || defined(ANDROID)
  #define DEFAULT_MYSCRIPT_ENGINE_LIBRARY_NAME "libMyScriptEngine.so"
  #define DIRSEP "/"
#elif defined(__APPLE__)
  #define DEFAULT_MYSCRIPT_ENGINE_LIBRARY_NAME "libMyScriptEngine.dylib"
  #define DIRSEP "/"
#else
  #error UNSUPPORTED PLATFORM
#endif

#include <stdlib.h>
#include <string.h>

// -- POSIX dynamic linking support --------------------------------------------

#ifdef _WIN32

  #define WIN32_LEAN_AND_MEAN
  #pragma warning(push)
  #pragma warning(disable: 4668)
  #include <windows.h>
  #pragma warning(pop)
  #define PATH_MAX MAX_PATH

  #define RTLD_LAZY 1
  #define RTLD_NOW 2
  #define RTLD_GLOBAL 4
  #define RTLD_LOCAL 8

  static void* dlopen(char const* fileName, int mode)
  {
    wchar_t buffer[MAX_PATH];

    if (MultiByteToWideChar(CP_UTF8, 0, fileName, -1, buffer, sizeof(buffer) / sizeof(*buffer)))
#if (defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_APP))
      return (void*)LoadPackagedLibrary(buffer, 0);
#else
      return (void*)LoadLibraryW(buffer);
#endif
  
    return NULL;
  }

  static int dlclose(void* handle)
  {
    return FreeLibrary((HMODULE)handle) ? 0 : -1;
  }

  static void* dlsym(void* handle, char const* symbol)
  {
    return GetProcAddress((HMODULE)handle, symbol);
  }

  static char* dlerror(void)
  {
    return NULL;
  }

#else // else of: #ifdef _WIN32

  #include <dlfcn.h>
  #include <limits.h>

#endif // end of else of: #ifdef _WIN32


// -- executable path introspection --------------------------------------------

#if defined(_WIN32)
#if !(defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_APP))
  static size_t getExecutablePathName(char* pathName, size_t pathNameCapacity)
  {
    wchar_t* buffer;
    DWORD length;
    size_t result;

    if (!pathName || pathNameCapacity == 0)
      return 0;

    // we may use a bit too much memory
    buffer = (wchar_t*)malloc(sizeof(wchar_t) * pathNameCapacity);
    if (buffer == NULL)
      return 0;

    length = GetModuleFileNameW(NULL, buffer, (DWORD)pathNameCapacity);

    result = WideCharToMultiByte(CP_UTF8, 0, buffer, length, pathName, (DWORD)pathNameCapacity, NULL, NULL);
    free(buffer);

    return result;
  }
#endif
#elif defined(__linux__) || defined(ANDROID)  /* elif of: #if defined(_WIN32) */
  #include <unistd.h>
  static size_t getExecutablePathName(char* pathName, size_t pathNameCapacity)
  {
    size_t pathNameSize = readlink("/proc/self/exe", pathName, pathNameCapacity - 1);
    pathName[pathNameSize] = '\0';
    return pathNameSize;
  }
#elif defined(__APPLE__) /* elif of: #elif defined(__linux__) || defined(ANDROID) */
  #include <mach-o/dyld.h>
  static size_t getExecutablePathName(char* pathName, size_t pathNameCapacity)
  {
    uint32_t pathNameSize = 0;

    _NSGetExecutablePath(NULL, &pathNameSize);

    if (pathNameSize > pathNameCapacity)
      pathNameSize = (uint32_t)pathNameCapacity;

    if (!_NSGetExecutablePath(pathName, &pathNameSize))
    {
      char real[PATH_MAX];

      if (realpath(pathName, real) != NULL)
      {
        pathNameSize = (uint32_t)strlen(real);
        strncpy(pathName, real, pathNameSize);
      }

      return pathNameSize;
    }

    return 0;
  }
#else // else of: #elif defined(__APPLE__)
  #error UNSUPPORTED PLATFORM
#endif // end of: #if defined(_WIN32)


// -- define function pointers -------------------------------------------------

#ifdef VO_MSE_FUNC_THROUGH_POINTERS

#define VO_NO_FUNCTIONS
#include <c/MyScriptEngine.h>
#undef VO_NO_FUNCTIONS

#define VO_FUNCTIONS_ONLY

#undef VO_MSE_FUNC
#define VO_MSE_FUNC(type, name, params) VO_MSE_FUNCPTR_STORAGECLASS type (VO_MSE_CALL *name) params = NULL
#undef C_MYSCRIPTENGINE_H
#include <c/MyScriptEngine.h>


// -- library loading / unloading ----------------------------------------------

static void* libraryHandle = NULL;

static void unloadMyScriptEngine(void);

/**
 * Loads the MyScriptEngine library.
 *
 * @param dirName Optional location directory name. When <code>NULL</code>,
 *   system dependent rules are used to locate the library. When this string
 *   starts with <code>"${origin}"</code> it will be expanded to the executable
 *   directory name.
 * @param fileName Optional name of the library. When <code>NULL</code>, the
 *   default library name is used, which is what we recommend you.
 *
 * @return A non zero value if successful.
 */
static int loadMyScriptEngine(const char* dirName, const char* fileName)
{
  int ok = 1;
  void** sym_ptr;

  if (!fileName)
    fileName = DEFAULT_MYSCRIPT_ENGINE_LIBRARY_NAME;

#if !(defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_APP))
  if (dirName)
  {
    char path[PATH_MAX];
    size_t len = 0;
    if (strncmp(dirName, "${origin}", 9) == 0)
    {
      len = getExecutablePathName(path, sizeof(path));
      while (len > 0 && path[len - 1] != *DIRSEP)
        --len;
      if (len > 0)
        --len;
      dirName += 9;
    }
    ok = (len + strlen(dirName) + 1 + strlen(fileName) + 1 < sizeof(path));
    if (ok)
    {
      strcpy(path + len, dirName);
      
      len = strlen(path);
      if (strcmp(path + len - 1, DIRSEP) != 0)
        strcat(path + len, DIRSEP);
      
      strcat(path + len, fileName);

      ok = (libraryHandle = dlopen(path, RTLD_NOW)) != NULL;
    }
  }
  else
#endif
  {
    ok = (libraryHandle = dlopen(fileName, RTLD_NOW)) != NULL;
  }

  // get functions pointers
#undef VO_MSE_FUNC
#define VO_MSE_FUNC(type, name, params)\
  if (ok)\
    ok = (sym_ptr = (void**)&name, *sym_ptr = dlsym(libraryHandle, #name)) != NULL
#undef C_MYSCRIPTENGINE_H
#include <c/MyScriptEngine.h>
#undef VO_MSE_FUNC

  if (libraryHandle != NULL && !ok)
    unloadMyScriptEngine();

  return ok;
}

/**
 * Unloads the MyScriptEngine library.
 */
static void unloadMyScriptEngine()
{
  if (libraryHandle != NULL)
    dlclose(libraryHandle);
  libraryHandle = NULL;

  // reset function pointers
#undef VO_MSE_FUNC
#define VO_MSE_FUNC(type, name, params)\
  name = NULL
#undef C_MYSCRIPTENGINE_H
#include <c/MyScriptEngine.h>
#undef VO_MSE_FUNC
}

#else // else of: #ifdef VO_MSE_FUNC_THROUGH_POINTERS

  #define loadMyScriptEngine(dirName, fileName) true
  #define unloadMyScriptEngine()

#endif // end of else of: #ifdef VO_MSE_FUNC_THROUGH_POINTERS
