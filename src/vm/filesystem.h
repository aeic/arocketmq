#ifndef AROCKETMQ_VM_FILESYSTEM_H_
#define AROCKETMQ_VM_FILESYSTEM_H_

#if defined(__cplusplus) && __cplusplus >= 201703L && defined(__has_include)
#if __has_include(<filesystem>)
#define GHC_USE_STD_FS
#include <filesystem>
#endif  // __has_include(<filesystem>)
#endif
#ifndef GHC_USE_STD_FS
#include <ghc/fs_fwd.hpp>
#endif  // GHC_USE_STD_FS

namespace arocketmq {

#ifdef GHC_USE_STD_FS

namespace fs {

using namespace std::filesystem;
using ifstream = std::ifstream;
using ofstream = std::ofstream;
using fstream = std::fstream;

}  // namespace fs

#else  // GHC_USE_STD_FS

namespace fs = ghc::filesystem;

#endif  // GHC_USE_STD_FS

}  // namespace arocketmq

#endif  // AROCKETMQ_VM_FILESYSTEM_H_
