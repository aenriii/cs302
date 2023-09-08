# hi! this is my repo for cs302


i know im very much overcomplicating this but its really funny to me
so i keep doing it anyways.

in this repo you'll find `utils`, a personal library of sorts that i
use for all my projects, and `assignment-num` projects, which are
assignments for cs302.

**i turned off copilot for this, all of this code is hand written**

## makefile magic

### building all assignments

to build all assignments, run the following simple* command:

```sh

make compile_all_assignments

```

*: this assumes you have `make` and `gcc` installed on a posix
compatible system.

### packaging all assignments

to package all assignments, run the following simple* command:

```sh

make package_all_assignments

```

*: this assumes you have all the commands from `compile_all_assignments`
as well as `tar` installed on a posix compatible system.

### cleaning up the `assignment-*/{utils,config.h}` spam

to clean up the `assignment-*/{utils,config.h}` spam, run the following
simple command:

```sh

make clean

```

### managing `utils`

managing `utils` is actually done entirely by the makefile itself,
when you run any compilation command you'll see the utils directory
appear in each assignment directory, and when you run any cleanup
command you'll see the utils directory disappear from each assignment.

### compiling just one assignment

to compile just one assignment, run the following command*:

```sh

make compile_assignment ASSIGNMENT=1

```

*again, assumes you have `make` and `gcc` installed on a posix
compatible system.

(also its only this way because of how make works)

### packaging just one assignment

to package just one assignment, run the following command*:

```sh

make package_assignment ASSIGNMENT=1

```

*assumes you have all the commands from `package_all_assignments`

### running one assignment

to run just one assignment, run the following command*:

```sh

make run_assignment ASSIGNMENT=1

```

*assumes you have all the commands from `compile_assignment`
