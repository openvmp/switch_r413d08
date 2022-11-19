/*
 * OpenVMP, 2022
 *
 * Author: Roman Kuzmenko
 * Created: 2022-09-24
 *
 * Licensed under Apache License, Version 2.0.
 */

#include "switch_r413d08/node.hpp"

namespace switch_r413d08 {

Node::Node() : rclcpp::Node::Node("switch_r413d08") {
  intf_ = std::make_shared<Interface>(this);
}

}  // namespace switch_r413d08
