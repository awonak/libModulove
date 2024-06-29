/**
 * @file synclfo_config.h
 * @author Adam Wonak (https://github.com/awonak)
 * @brief collection of configuration settings for the SyncLFO.
 * @version 0.1
 * @date 2024-06-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef SYNCLFO_CONFIG_H
#define SYNCLFO_CONFIG_H

namespace modulove {
namespace synclfo {

// Configuration settings for the A-RYTH-MATIK module.
struct Config {
    // Indicates that additional Synchronizer hardware components present.
    bool Synchronizer;
};

}  // namespace synclfo
}  // namespace modulove

#endif