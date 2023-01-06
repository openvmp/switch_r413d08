# OpenVMP

[![License](./license.svg)](./LICENSE.txt)

This package is a part of [the OpenVMP project](https://github.com/openvmp/openvmp).
But it's designed to be universal and usable independently from the rest of OpenVMP or in a combination with select OpenVMP packages.

## ROS2 package for R413D08

This package implements management and control of R413D08. It could possibly work as well for R421A08, STM8S103, N4D8B08, UD74B08 and others.

*Note: there must be something shared by all these boards
(like a chip or firmware) that should be used in the name of this package
instead of r413d08. If you know what that is, please, let me know.*

This module can be configured to use either local or remote interface
to [Modbus RTU](https://github.com/openvmp/modbus_rtu).
It is recommended to the use the remote interface
(see '**modbus_is_remote**' below) so that the drivers of all devices
use the same way of accessing the bus.

### Parameters

- **switch_r413d08_inverted** _(Default: false)_

  The boolean flag indicating whether ON and OFF are inverted on this device.

- **switch_channels** _(Default: 1)_

  The number of channels.

- **switch_prefix** _(Default: /switch/default)_

  The prefix of the ROS2 interface of this module.
  See 'Publishers' and 'Services' below.

- **modbus_is_remote** _(Default: true)_

  The boolean flag determining whether
  [the Modbus interface](https://github.com/openvmp/modbus/) should be
  initialized within the same process or should be accessed remotely using
  ROS2 interfaces.

  If 'false', an instance of
  [the Modbus RTU module](https://github.com/openvmp/modbus_rtu/) is
  initialized using the corresponding parameters (see the documentation of
  [the Modbus RTU module](https://github.com/openvmp/modbus_rtu/) for more info).

  If 'true', all Modbus commands are executed over DDS using services under
  '**modbus_prefix**' (see below).

- **modbus_prefix** _(Default: /modbus/default)_

  The prefix of [Modbus ROS2 interfaces](https://github.com/openvmp/modbus/)
  (including the registers specific to this device).

- **modbus_leaf_id** _(Default: 1)_

  The ID of this device on the Modbus bus.

### Publishers

- **<switch_r413d08_prefix>/channel<N>/last_changed**

  The timestamp when the state of the corresponding channel was changed for
  the last time.

- **<switch_r413d08_prefix>/channel<N>/last_on**

  The boolean flag of the current state of the corresponding channel.

### Services

- **<switch_r413d08_prefix>/channel<N>/on**

  Turn the certain channel ON.

- **<switch_r413d08_prefix>/channel<N>/off**

  Turn the certain channel OFF.

- **<switch_r413d08_prefix>/channel<N>/toggle**

  Toggle the state of the certain channel.

- **<switch_r413d08_prefix>/change_leaf_id**

  Change the Modbus leaf\_id of this device.

