FTC-4982-2014-Rainbow-Dash-Software
===================================

FIRST Tech Challenge Team #4982 Cafe Bot's software for their third and final robot of the 2014 Block Party season.

Rainbow Dash's program is split into two primary source files:
- Autonomous.c handles the Autonomous segment of the game, driving RD forward and throwing a block in a crate.
- RainbowDash.c handles the Teleop segement of the game, operated by a Driver and Operator via two controllers.

In addition, Rainbow Dash has a third additional source file, RD-Lift.c, which allows the team to
raise and lower the lift while the robot is disabled (it's very hard to manually backdrive the kind of ratios
we put on our robots...).

To compile and use this program, follow the steps below:
- Verify your robot is compatible with Rainbow Dash's program.  This is highly unlikely.
- Download the src folder and place it somewhere on your computer.
- Open up the RobotC IDE and Compile/Download the following five files onto your robot from the src folder:
  - Autonomous.c
  - Teleop.c
  - RD-Lift.c
  - samostat.c
  - program-chooser.c
- Run the "program-chooser" application on your robot's NXT.
  - Select "Dual file" on the NXT when prompted.
  - Select the "Teleop.c" file.

And you're all set!

Note: Neither I nor Cafe Bot own or wrote the program-chooser.c or samostat.c files.  These were provided by FIRST/RobotC and are included in this project only because they are required to run.
