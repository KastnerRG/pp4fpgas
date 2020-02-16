#include "fft.h"

static unsigned short count;
static DTYPE xr[ SIZE ];
static DTYPE xi[ SIZE ];
static DTYPE xr_out[ SIZE ];
static DTYPE xi_out[ SIZE ];
static int   dout[ SIZE ];

void ofdm_receiver( volatile DTYPE *inptr, volatile uint32_t *outptr )
{
#pragma AP interface ap_fifo port=inptr
#pragma AP interface ap_fifo port=outptr
#pragma AP interface ap_ctrl_none port=return

	*outptr++ = dout[ count ];

	xr[ count ] = *inptr++;
	xi[ count ] = *inptr++;
	count++;
	if( count == 1024 ){
		count = 0;
		demod( xr, xi, dout, xr_out, xi_out );
	}
}
