/*
 * OpenVMP, 2022
 *
 * Author: Roman Kuzmenko
 * Created: 2022-09-24
 *
 * Licensed under Apache License, Version 2.0.
 */

#include "r413d08_driver/node.hpp"

namespace r413d08_driver {

Node::Node() : rclcpp::Node::Node("switch_r413d08") {
  intf_ = std::make_shared<Interface>(this);
}

}  // namespace r413d08_driver
