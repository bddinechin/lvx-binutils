# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

This is the **LVX binutils** repo: a GNU Binutils checkout with a full LVX target port (`bfd`, `opcodes`, `gas`, `ld`, `binutils`) for the `lvx-mbr` triple. See the parent project's `/home/bd3/lvx-csw/CLAUDE.md` first for architectural background (LVX vs KVX, the MDS pipeline, build/install instructions, LVX-specific source file layout) — this file only covers implementation gotchas specific to this repo that aren't obvious from the code.

Most LVX-specific source in `bfd/`, `opcodes/`, `gas/`, `ld/`, `include/` is either MDS-generated (see the parent CLAUDE.md's "Do not hand-edit" table) or gets reinstalled from `lvx-mds`'s `BE/GBU` backend (`make -C build_lvx/BE/GBU install`, from the sibling `lvx-mds` repo).

## Binutils implementation gotchas

- **`bfd/bfd-in2.h` and `bfd/libbfd.h` are hand-maintained-but-generated files** that must stay in sync with `bfd/reloc.c`'s `BFD_RELOC_LVX_*` enum order. `elfNN_lvx_howto_from_bfd_reloc` in `bfd/elfnn-lvx.c` indexes the HOWTO table by ordinal offset from `BFD_RELOC_LVX_RELOC_START` — `reloc.c` itself has a comment warning that this ordering is load-bearing. Editing `reloc.c` (e.g. removing/renumbering a relocation) without regenerating these two leaves them silently out of sync, which manifests as gas tagging instructions with the *wrong* relocation (e.g. `R_LVX_S38S2_PCREL_UP27` instead of `R_LVX_S27S2_PCREL`) rather than a compile error. Regenerate with `make -C <build>/bfd headers` (uses `automake`'s bundled `doc/chew` tool).

  One further trap: `bfd_arch_lvx`/`bfd_mach_lvx_v1` etc. only exist in `bfd-in2.h` via **hand-patching** — `bfd/archures.c`'s own chew-documented `enum bfd_architecture` was never updated to actually include them. A `headers` regen will silently drop `bfd_arch_lvx` again unless `archures.c` is fixed first. Compare against `lvx-gdb/bfd/archures.c`, where `bfd_arch_lvx` *is* properly added to the source enum (done correctly when porting LVX into that repo) — that's the pattern to follow here too, rather than perpetuating the hand-patch.

- **`binutils/readelf.c` has hardcoded relocation-number literals** in several `case EM_KVX:` blocks (e.g. `is_32bit_pcrel_reloc`'s `reloc_type == 5 /* R_LVX_32_PCREL */`). These must be manually kept in sync whenever `include/elf/lvx.h`'s relocation numbering changes — adding or removing a `RELOC_NUMBER` entry renumbers everything after it, and the compiler won't catch a stale literal; readelf just silently mis-detects the relocation. One instance (`R_LVX_32_PCREL` claimed as `7` instead of `5`, stale from before `R_LVX_PCREL17`/`27` were removed) was found and fixed this way. Grep `binutils/readelf.c` for `EM_KVX` and re-check the literals whenever the reloc table is renumbered.

- **`ld/Makefile.am` changes need `Makefile.in` regenerated**, and this tree is pinned to `automake 1.15.1`/`autoconf 2.69` (per the header comments in the generated files) — a newer installed `automake` will produce a much larger, mostly-cosmetic diff. If only `autoconf` 2.71+ is installed system-wide, Ubuntu's `autoconf2.69` package provides the pinned version separately; point `aclocal`/`automake`/`autoconf` at it via `PATH` for the regen rather than using the system default.
