# nmobjdump

Recode in C, nm and objdump commands.

The <strong>nm</strong> command ships with a number of later versions of Unix and similar operating systems. nm is used to examine binary files (including libraries, compiled object modules, shared-object files, and standalone executables) and to display the contents of those files, or meta information stored in them, specifically the symbol table. The output from nm distinguishes between various symbol types. For example, it differentiates between a function that is supplied by an object module and a function that is required by it. nm is used as an aid for debugging, to help resolve problems arising from name conflicts and C++ name mangling, and to validate other parts of the toolchain.

The <strong>objdump</strong> command is a command-line program for displaying various information about object files on Unix-like operating systems. For instance, it can be used as a disassembler to view an executable in assembly form. It is part of the GNU Binutils for fine-grained control over executables and other binary data.

<h3>Usage</h3>
./nm binary_file<br>
./objdump binary_file

<h3>Description</h3>
binary_file (including libraries, compiled object modules, shared-object files, and standalone executables).
