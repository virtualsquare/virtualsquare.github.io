# PandOS

## Introduction

The **PandOS** operating system is a *no.* phase/layer project consisting in the implementation of a kernel/OS designed to run on [µMPS](umps.md).

From [*The Student Guide to the PandOS Operating System Project*](#Documentation):

> The PandOS operating system is similar to the *T.H.E.* system outlined by Dijkstra back in 1968.
> Dijkstra's paper described an OS divided into six layers.
> Each layer *i* was an ADT or abstract machine to layer *i* + 1; successively building up the capabilities of the system for each new layer to build upon.
> The operating system described here also contains multiple layers, though PandOS is not as complete as Dijkstra's.
>
> PandOS is actually the latest instantiation of an older "learning' operating system design.
> Ozalp Babaoglu and Fred Schneider originally described this operating system, calling it the *HOCA OS*, for implementation on the Cornell Hypothetical Instruction Processor (*CHIP*).
> Later, Renzo Davoli and Mauro Morsiani reworked HOCA, calling it *TINA* and *ICAROS*, for implementation on the Microprocessor (without) Pipeline Stages (*MPS*).
> A couple of years after TINA saw the development of *Kaya* for implementation on μMPS and later, μMPS2.
>
> PandOS is the latest revamping-modernization of this design for implementation on μMPS3.

### Kaya

The Kaya project is the predecessor of PandOS, developed for µMPS and µMPS2.

Being µMPS3 **NOT** backward compatible with software developed for previous versions of the architecture (µMPS and µMPS2), Kaya has been superseded by PandOS and therefore retired.

---

## Downloads

The PandOS project described in the [*The Student Guide to the PandOS Operating System Project*](#Documentation) recommends the use of some test files, sample Makefiles, and some other miscellaneous header files.

- [const.h](src/const.h): This header file contains utility constants & macro definitions
- [types.h](src/types.h): This header file contains utility types definitions

### Phase 1

- [P1-Makefile](src/P1-Makefile)
- [p1test.c](src/p1test.c)

### Phase 2

- [p2test.c](src/p2test.c)

---

## Levels

### Level 0: The base hardware of μMPS3

Though μMPS3 carries the designation of "3", it is **NOT** backward compatible for operating system code developed for μMPS or μMPS2.

### Level 1: The additional services provided in BIOS

This includes the services provided by the BIOS-Excpt handler, the BIOS-TLB-Refill handler, and the additional BIOS services/instructions (i.e. **LDST**, **LDCXT**, **PANIC**, and **HALT**).

The [*μMPS3 Principles of Operation*](umps.md#Documentation) contains a complete description of both Level 0 and 1.

### Level 2: The Queues Manager

(Phase 1 - described in [Chapter 2](#Documentation))

Based on the key operating systems concept that active entities at one layer are just data structures at lower layers, this layer supports the management of queues of structures: *pcb*'s.

### Level 3: The Kernel

(Phase 2 – described in [Chapter 3](#Documentation))

This level implements eight new kernel-mode process management and synchronization primitives in addition to multiprogramming, a process scheduler, device interrupt handlers, and deadlock detection.

### Level 4: The Support Level - The Basics

(Phase 3 – described in [Chapter ??](#Documentation))

Level 3 is extended to support a system that can support multiple user-level processes that each run in their own virtual address space.
Furthermore, support is provided to read/write to character-oriented devices.

### Level 5: The Support Level - DMA Devices

(Phase 4 – described in [Chapter ??](#Documentation))

An extension of Level 4 providing I/O support for DMA devices: disk drives and flash devices.
Furthermore, this level implements a more realistic backing store implementation.

### Level 6: The Sleep/Delay Facility

(Phase 5 – described in [Chapter ??](#Documentation))

This level provides the Support Level with a sleep/delay facility.

### Level 7: Cooperating User Processes

(Phase 6 – described in [Chapter ??](#Documentation))

This level introduces a shared memory space and user-level synchronization primitives to facilitate cooperating processes.

### Level 8: The File System

(Phase 7 - optional)

This level implements the abstraction of a flat file system by implementing primitives necessary to create, rename, delete, open, close, and modify files.

### Level 9: The Interactive Shell

why not?

---

## Documentation

- Michael Goldweber, Renzo Davoli, *The Student Guide to the PandOS Operating System Project*, 2020. [PDF](doc/pandos.pdf)

### Historical documentation

- Michael Goldweber, Renzo Davoli, *The Student Guide to the Kaya Operating System Project*, 2011. [PDF](https://www.iro.umontreal.ca/~monnier/2245/h2012/student-guide.pdf)
