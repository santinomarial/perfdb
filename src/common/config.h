#pragma once
#include <cstdint>

namespace perfdb {

static constexpr uint32_t PAGE_SIZE        = 4096;
static constexpr int32_t  INVALID_PAGE_ID  = -1;
static constexpr int32_t  INVALID_TXN_ID   = -1;
static constexpr int32_t  INVALID_LSN      = -1;
static constexpr int32_t  INVALID_FRAME_ID = -1;
static constexpr size_t   DEFAULT_POOL_SIZE    = 128;
static constexpr size_t   LOG_BUFFER_SIZE      = 32 * 1024 * 1024;

using PageID        = int32_t;
using FrameID       = int32_t;
using LSN           = int32_t;
using TransactionID = int32_t;
using SlotID        = uint16_t;

struct RID {
  PageID page_id  = INVALID_PAGE_ID;
  SlotID slot_id  = 0;

  bool IsValid() const { return page_id != INVALID_PAGE_ID; }
  bool operator==(const RID& other) const {
    return page_id == other.page_id && slot_id == other.slot_id;
  }
  bool operator!=(const RID& other) const { return !(*this == other); }
};

} // namespace perfdb

namespace std {
template <>
struct hash<perfdb::RID> {
  size_t operator()(const perfdb::RID& rid) const noexcept {
    return hash<int64_t>()(
      (static_cast<int64_t>(rid.page_id) << 16) | rid.slot_id
    );
  }
};
} // namespace std
