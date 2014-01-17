// Copyright © 2014 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdio.h>
#include <stdlib.h>

#include <osl/osl.h>

#include <clan/clan.h>

#include <clay/clay.h>

#include <piplib/piplibMP.h>

#include <candl/candl.h>
#include <candl/dependence.h>

#define CLOOG_INT_GMP
#include <cloog/cloog.h>

#include <main/main.h>


// Clan extracts scop from C source code
osl_scop_p clan(char const * const filename)
{
	clan_options_p options = clan_options_malloc();
	options->name = osl_util_strdup(filename);
	options->precision = 0;
	
	FILE * f = fopen(filename, "r");
	
	osl_scop_p scop = clan_scop_extract(f, options);
	
	fclose(f);
	clan_options_free(options);
	
	return scop;
}

// Cloog print C code from scop
void cloog_print(osl_scop_p scop)
{
	CloogState * state = cloog_state_malloc();
	CloogOptions * options = cloog_options_malloc(state);
	options->openscop = 1;
	cloog_options_copy_from_osl_scop(scop, options);
	CloogInput * input = cloog_input_from_osl_scop(options->state, scop);
	struct clast_stmt * clast = cloog_clast_create_from_input(input, options);
	
	clast_pprint(stdout, clast, 0, options);
	
	cloog_clast_free(clast);
	options->scop = NULL; // Don't free the scop
	cloog_options_free(options);
	cloog_state_free(state); // The input is freed inside
}


int main(int argc, char * * argv)
{
	// PIPLib (for Candl)
	pip_init();
	
	if (argc <= 1)
	{
		fprintf(stderr, "Usage: %s <source.c>\n", argv[0]);
		return 1;
	}
	
	// Clan
	osl_scop_p scop = clan(argv[1]);
	
	// PIPLib
	// https://github.com/periscop/piplib/blob/master/include/piplib/piplib.h
	
	// Candl
	candl_scop_usr_init(scop);
	{
		candl_options_p options = candl_options_malloc();
		
		candl_dependence_add_extension(scop, options);
		
		candl_options_free(options);
	}
	candl_scop_usr_cleanup(scop);
	
	// Clay
	// https://github.com/periscop/clay/tree/master/include/clay
	clay_beta_normalize(scop);
	
	// OpenScop
	osl_scop_print(stdout, scop);
	
	// CLooG
	cloog_print(scop);
	
	// Free
	osl_scop_free(scop);
	
	// PIPLib
	pip_close();
	
	return 0;
}
