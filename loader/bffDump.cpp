/*
 * Copyright (C) 2001, Sun Microsystems, Inc
 * Copyright (C) 2001, The University of Queensland
 *
 * See the file "LICENSE.TERMS" for information on usage and
 * redistribution of this file, and for a DISCLAIMER OF ALL
 * WARRANTIES.
 *
 */

/* File: bffDump_skel.cc
 * Desc: Skeleton driver for a binary-file dumper program.
 *
 * This file is a generic skeleton for a binary-file dumper,
 * it dumps all the information it finds about sections in the
 * file, and it displays any code sections in raw hexadecimal
 * notation.
 */

#include "BinaryFile.h"

static void print_section(SectionInfo *pSect)
{
	ADDRESS a = pSect->uNativeAddr;
	unsigned char *p = (unsigned char *)pSect->uHostAddr;
	for (unsigned off = 0; off < pSect->uSectionSize;) {
		printf("%04X:", a);
		for (int j = 0; (j < 16) && (off < pSect->uSectionSize); ++j) {
			printf(" %02X", *p++);
			a++;
			off++;
		}
		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	// Usage
	if (argc != 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		printf("%s dumps the contents of the given executable file\n", argv[0]);
		return 1;
	}

	// Load the file
	BinaryFile *pbf = NULL;
	BinaryFileFactory bff;
	pbf = bff.Load(argv[1]);

	if (pbf == NULL) {
		return 2;
	}

	// Display program and section information
	// If the DisplayDetails() function has not been implemented
	// in the derived class (ElfBinaryFile in this case), then
	// uncomment the commented code below to display section information.

	pbf->DisplayDetails(argv[0]);

	// This is an alternative way of displaying binary-file information
	// by using individual sections.  The above approach is more general.
	/*
	printf("%d sections:\n", pbf->GetNumSections());
	for (int i = 0; i < pbf->GetNumSections(); ++i) {
		SectionInfo *pSect = pbf->GetSectionInfo(i);
		printf("  Section %s at %X\n", pSect->pSectionName, pSect->uNativeAddr);
	}
	printf("\n");
	*/

	// Display the code section in raw hexadecimal notation
	// Note: this is traditionally the ".text" section in Elf binaries.
	// In the case of Prc files (Palm), the code section is named "code0".

	for (int i = 0; i < pbf->GetNumSections(); ++i) {
		SectionInfo *pSect = pbf->GetSectionInfo(i);
		if (pSect->bCode) {
			printf("  Code section:\n");
			print_section(pSect);
			printf("\n");
		}
	}

	// Display the data section(s) in raw hexadecimal notation

	for (int i = 0; i < pbf->GetNumSections(); ++i) {
		SectionInfo *pSect = pbf->GetSectionInfo(i);
		if (pSect->bData) {
			printf("  Data section: %s\n", pSect->pSectionName);
			print_section(pSect);
			printf("\n");
		}
	}

	pbf->UnLoad();
	return 0;
}
