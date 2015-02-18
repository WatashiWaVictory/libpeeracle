#include "peeracle.h"

vlc_module_begin()
  set_shortname("peeracle")
  set_category(CAT_INPUT)
  set_subcategory(SUBCAT_INPUT_ACCESS)
  set_description("peeracle metadata access")
  set_capability("access", 60)
  add_shortcut("file", "peeracle")
  set_callbacks(AccessOpen, AccessClose)
vlc_module_end ()