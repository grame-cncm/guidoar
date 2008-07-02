/*
	GUIDO Library
	Copyright (C) 2002  Holger Hoos, Juergen Kilian, Kai Renz

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

/*
	changes log:
	03/07/15 jk: added unicode file support, for unicode files produced by the Sibelius2GUIDO Plugin
*/

#include "guido.h"
#include "guidoparse.hpp"
#include "guidolex.cpp"
#include "guidoparse.cpp"


int gd_error(const char *msg); 

/* --- initialisation, has to be called before
       any other gd_*  function is called --- */
void gd_init(void) {
	gd_imp_init();
}

void gd_exit(void) 
{
	// this is important, so that the Parser does not
	// get scrambled ...

//	if (guido_current_buffer != NULL)
//		guido_delete_buffer(guido_current_buffer);
	gd_imp_exit();
}

/* --- parser interface: --- */
int parse_mode;

long int lnr = 1;
long int cnr = 0;
long int cmnt_level;

static int checkUnicode(FILE *fd) 
{
	rewind( fd );
	if ( fd ) {
		int c = fgetc( fd );
		if( c == 0xff || c == 0xfe) {
			c = fgetc( fd );
			if( c == 0xfe || c == 0xff )
				return 1;
		}
	}
	return 0;
}

static void uniconv(const char *filename) 
{
	FILE * fd = fopen(filename,"rb");	// open file
	if (!fd) return;				

	if (checkUnicode (fd)) {
		fseek(fd, 0, SEEK_END);
		long int len = ftell(fd);
		char * content = new char[len+1];
		if( content ) {
			rewind( fd );			
			fread (content, 1, len, fd);
			fclose(fd);
			
			fd = fopen(filename,"wt");
			if (fd) {
				int i;
				for( i = 0; i < len; i++ ) {
					if( content[i] > 0 && content[i] <= 0x7f )
						fputc(content[i], fd);
				}
				fclose( fd );
			}
			delete [] content;			
		}
	}
}

int gd_parse_buffer(const char *buffer) 
{
	lnr = 1;
	cnr = 0;

	int res;
	if (!*buffer) return -1;		// error for empty buffers

	YY_BUFFER_STATE b;
    /*Copy string into new buffer and Switch buffers*/
    b = guido_scan_string (buffer);

    /*Parse the string*/
    res = guidoparse();

    /*Delete the new buffer*/
    guido_delete_buffer(b);

	BEGIN(INITIAL);

	guidorestart(guidoin);
//	fclose(guidoin);
	gd_exit();
	return res;
}

int gd_parse(const char *filename, int mode) 
{
	int res;
	uniconv(filename);
	if((guidoin= fopen(filename,"r")) == NULL){
		gd_error("Could not open file");
		return -1;
	}
	
	res = guidoparse();

	guidorestart(guidoin);
	fclose(guidoin);
	gd_exit();	
	return res;
}
