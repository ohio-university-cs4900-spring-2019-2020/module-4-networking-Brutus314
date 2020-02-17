# module-4-networking-Brutus314
module-4-networking-Brutus314 created by GitHub Classroom

This module will require 2 instances of it running at the same time.
In the aftr.conf file, one instance must have NetServerListenPort=12683.
The other must have NetServerListenPort=12682.
When launching the instances, one may be very slow at first. This is because
it sends a message on every world update, and sending a message is slow when
it fails. The same is true for closing down.
When both instances are running, they should be able to see each other by a cube
tracking the location of the other instance. Moving in one instance moves the cube
in the other. Additionally, pressing '1' will stack a cube near the start in both
instances.
