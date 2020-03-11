bool MemAllocInit()
{
	// No op but this is where you would initialize your memory allocator and bookkeeping data in a real world scenario
	return true;
}

void MemAllocExit()
{
	// Return all allocated memory to the OS. Analyze memory usage, dump memory leaks, ...
}

#include <stdlib.h>


void mmgrSetLogFileDirectory(const char* directory)
{
}

void mmgrSetExecutableName(const char* name, size_t length)
{
}

#ifdef _MSC_VER
#include <memory.h>
#include <EASTL/EABase/eabase.h>
void* conf_malloc(size_t size)
{
	return _aligned_malloc(size, EA_PLATFORM_MIN_MALLOC_ALIGNMENT);
}

void* conf_calloc(size_t count, size_t size)
{
	size_t sz = count * size;
	void* ptr = conf_malloc(sz);
	memset(ptr, 0, sz);
	return ptr;
}

void* conf_memalign(size_t alignment, size_t size)
{
	return _aligned_malloc(size, alignment);
}

void* conf_realloc(void* ptr, size_t size)
{
	return _aligned_realloc(ptr, size, EA_PLATFORM_MIN_MALLOC_ALIGNMENT);
}

void conf_free(void* ptr)
{
	_aligned_free(ptr);
}
#else
void* conf_malloc(size_t size)
{
	return malloc(size);
}

void* conf_calloc(size_t count, size_t size)
{
	return calloc(count, size);
}

void* conf_memalign(size_t alignment, size_t size)
{
	void* result;
	if ( posix_memalign(&result, alignment, size) ) result = 0;
	return result;
}

void* conf_realloc(void* ptr, size_t size)
{
	return realloc(ptr, size);
}

void conf_free(void* ptr)
{
	free(ptr);
}
#endif

void* conf_malloc_internal(size_t size, const char *f, int l, const char *sf)
{
	return conf_malloc(size);
}

void* conf_memalign_internal(size_t align, size_t size, const char *f, int l, const char *sf)
{
	return conf_memalign(align, size);
}

void* conf_calloc_internal(size_t count, size_t size, const char *f, int l, const char *sf)
{
	return conf_calloc(count, size);
}

void* conf_realloc_internal(void* ptr, size_t size, const char *f, int l, const char *sf)
{
	return conf_realloc(ptr, size);
}

void conf_free_internal(void* ptr, const char *f, int l, const char *sf)
{
	conf_free(ptr);
}