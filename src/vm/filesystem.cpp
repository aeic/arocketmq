#if defined(__cplusplus) && __cplusplus >= 201703L && defined(__has_include)
#if __has_include(<filesystem>)
#define GHC_USE_STD_FS
#endif  // __has_include(<filesystem>)
#endif
#ifndef GHC_USE_STD_FS
#include <ghc/fs_impl.hpp>
#endif  // GHC_USE_STD_FS
