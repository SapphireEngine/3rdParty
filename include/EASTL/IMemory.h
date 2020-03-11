#pragma once

#include <EASTL/utility.h>

void* conf_malloc_internal(size_t size, const char *f, int l, const char *sf);
void* conf_memalign_internal(size_t align, size_t size, const char *f, int l, const char *sf);
void* conf_calloc_internal(size_t count, size_t size, const char *f, int l, const char *sf);
void* conf_realloc_internal(void* ptr, size_t size, const char *f, int l, const char *sf);
void  conf_free_internal(void* ptr, const char *f, int l, const char *sf);

template <typename T, typename... Args>
static T* conf_placement_new(void* ptr, Args&&... args)
{
	return new (ptr) T(eastl::forward<Args>(args)...);
}

template <typename T, typename... Args>
static T* conf_new_internal(const char *f, int l, const char *sf, Args&&... args)
{
	T* ptr = (T*)conf_malloc_internal(sizeof(T), f, l, sf);
	return conf_placement_new<T>(ptr, eastl::forward<Args>(args)...);
}

template <typename T>
static void conf_delete_internal(T* ptr, const char *f, int l, const char *sf)
{
	if ( ptr )
	{
		ptr->~T();
		conf_free_internal(ptr, f, l, sf);
	}
}

#ifndef conf_malloc
#define conf_malloc(size) conf_malloc_internal(size, __FILE__, __LINE__, __FUNCTION__)
#endif
#ifndef conf_memalign
#define conf_memalign(align,size) conf_memalign_internal(align, size, __FILE__, __LINE__, __FUNCTION__)
#endif
#ifndef conf_calloc
#define conf_calloc(count,size) conf_calloc_internal(count, size, __FILE__, __LINE__, __FUNCTION__)
#endif
#ifndef conf_realloc
#define conf_realloc(ptr,size) conf_realloc_internal(ptr, size, __FILE__, __LINE__, __FUNCTION__)
#endif
#ifndef conf_free
#define conf_free(ptr) conf_free_internal(ptr,  __FILE__, __LINE__, __FUNCTION__)
#endif
#ifndef conf_new
#define conf_new(ObjectType, ...) conf_new_internal<ObjectType>(__FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#endif
#ifndef conf_delete
#define conf_delete(ptr) conf_delete_internal(ptr,  __FILE__, __LINE__, __FUNCTION__)
#endif