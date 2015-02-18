#ifndef PEERACLE_PLUGIN_H_
#define PEERACLE_PLUGIN_H_

#define MODULE_STRING "peeracle"

#include <vlc_common.h>
#include <vlc_plugin.h>
#include <vlc_access.h>

int AccessOpen( vlc_object_t *p_this );
void AccessClose( vlc_object_t *p_this );

#endif  // PEERACLE_PLUGIN_H_