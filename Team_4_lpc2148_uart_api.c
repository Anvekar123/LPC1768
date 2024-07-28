
void configure_baudrate (unsigned int baud, unsigned int clk)
{
  void reg_fld_wr (U0LCR_OFF, U0LCR_DLAB_HPOS,
                 U0LCR_DLAB_LPOS,1);
   unsigned int divisor_value = clk/baud;
   unsigned int baud_rate = (clk/16 * divisor_value);

  void reg_fld_wr (U0DLL_OFF, 7,
                 0,divisor_value);
  void reg_fld_wr (U0DLM_OFF, 7,
                 0,divisor_value);
  void reg_fld_wr (U0LCR_OFF, U0LCR_DLAB_HPOS,
                 U0LCR_DLAB_LPOS,0);


}

enum data_width{ e_five, e_six, e_seven, e_eight };
static void configure_data_width (enum data_width ln)
{
void reg_fld_wr (U0LCR_OFF, U0LCR_WLS_HPOS,
                 U0LCR_WLS_LPOS, ln);

}

enum stop_bit { e_stp_bit_1, e_stp_bit_2 }; 

static void configure_stop_bit (enum stop_bit stop)
{
void reg_fld_wr (U0LCR_OFF, U0LCR_STPBIT_HPOS,
                 U0LCR_STPBIT_LPOS, stop);
}



enum parity_bit{ e_odd, e_even, e_no };

static void configure_parity (enum parity_bit par)
{

void reg_fld_wr (U0LCR_OFF, U0LCR_PARSEL_HPOS,
                 U0LCR_PEN_LPOS, par);

}


void transmit_data (unsigned char data)
{
unsigned char check_data_prst = reg_fld_rd(U0LSR_OFF, U0LSR_THRE_HPOS, U0LSR_THRE_LPOS); // check if THRE is empty (set to 1) 
if (check_data_prst) // if empty
{
reg_wr (U0THR_OFF, data);
}
// return value keeping as void.... instead of int  
}

int receive_data (unsigned char *data)
{
  int err = 0;
unsigned char check_data_prst = reg_fld_rd(U0LSR_OFF, U0LSR_DR_HPOS, U0LSR_DR_LPOS); // check if RDR is 1 

if (check_data_prst!=0) // check for errors 
{
    unsigned char check_error = reg_fld_rd(U0LSR_OFF , U0LSR_BI_HPOS, U0LSR_OE_LPOS); // check for bit 1 to bit 4  for errors
    if (check_error) // if any errors present check condition
    {
  
    if (OE_ERR(check_error))
    {
        err=RX_OE;
        return err;
    }
    else if (PE_ERR(check_error))
    {
        err=RX_PE;
        return err;
    }
    else if (FE_ERR(check_error))
    {
        err=RX_FE;
        return err;
    }
    else if (BI_ERR(check_error))
    {
        err=RX_BI;
        return err;
    }
    
    }

    else // if no error present store the data
    {
        *data = reg_rd(U0RBR_OFF);
       return err;

    }  

    return err; // if no data present return 0
  
}
}

