#ifdef HW_FILESYSTEM_H_RECURSE_GUARD
#error Recursive header files inclusion detected in hw_filesystem.h
#else //HW_FILESYSTEM_H_RECURSE_GUARD

#define HW_FILESYSTEM_H_RECURSE_GUARD

#ifndef HW_FILESYSTEM_H_GUARD
#define HW_FILESYSTEM_H_GUARD
#pragma once

FileHandle_t FS_Open(const char* pFileName, const char* pOptions);
FileHandle_t FS_OpenPathID(const char* pFileName, const char* pOptions, const char* pathID);
void FS_Close(FileHandle_t file);
bool FS_EndOfFile(FileHandle_t file);
char* FS_ReadLine(char* pOutput, int maxChars, FileHandle_t file);
void FS_AddSearchPath(const char* pPath, const char* pathID);
void FS_CreateDirHierarchy(const char* path, const char* pathID);
int FS_FPrintf(FileHandle_t file, const char* pFormat, ...);
bool FS_FileExists(const char* pFileName);
int FS_FileSize(const char* pFileName);
void FS_FileTimeToString(char* pStrip, int maxCharsIncludingTerminator, int32 fileTime);
void __cdecl FS_FindClose(FileFindHandle_t handle);
const char* FS_FindFirst(const char* pWildCard, FileFindHandle_t* pHandle, const char* pathID);
bool FS_FindIsDirectory(FileFindHandle_t handle);
const char* FS_FindNext(FileFindHandle_t handle);
void FS_Flush(FileHandle_t file);
bool FS_FullPathToRelativePath(const char* pFullpath, char* pRelative);
char FS_GetCharacter(FileHandle_t f);
int FS_GetCurrentDirectory(char* pDirectory, int maxlen);
int32 FS_GetFileTime(const char* pFileName);
void FS_GetInterfaceVersion(char* p, int maxlen);
void FS_GetLocalCopy(const char* pFileName);
const char* FS_GetLocalPath(const char* pFileName, char* pLocalPath, int localPathBufferSize);
void* FS_GetReadBuffer(FileHandle_t file, int* outBufSize);
int FS_IsDirectory(const char* pFileName);
int FS_IsOk(FileHandle_t file);
CSysModule* FS_LoadLibrary(const char* dllName);
void FS_LogLevelLoadFinished(const char* name);
void FS_LogLevelLoadStarted(const char* name);
char* FS_ParseFile(char* pFileBytes, char* pToken, int* pWasQuoted);
void FS_PrintOpenedFiles();
int FS_Read(void* pOutput, int size, FileHandle_t hFile);
void FS_ReleaseReadBuffer(FileHandle_t file, void* buffer);
void FS_RemoveAllSearchPaths();
void FS_RemoveFile(const char* pRelativePath, const char* pathID);
bool FS_RemoveSearchPath(const char* pPath);
void FS_Rename(const char* originalName, const char* newName);
void FS_Seek(FileHandle_t file, int pos, FileSystemSeek_t seekType);
int FS_SetVBuf(FileHandle_t stream, char* buffer, int mode, size_t size);
unsigned int FS_Size(FileHandle_t file);
unsigned int FS_Tell(FileHandle_t file);
void FS_Unlink(const char* filename);
int FS_Write(const void* pInput, int size, FileHandle_t hFile);

#endif //HW_FILESYSTEM_H_GUARD

#undef HW_FILESYSTEM_H_RECURSE_GUARD
#endif //HW_FILESYSTEM_H_RECURSE_GUARD
