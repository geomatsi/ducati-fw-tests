volatile int *GPIO1_DATAOUT;
volatile int *GPIO1_OE;

int main(void)
{
	volatile int i;

	GPIO1_DATAOUT = (int *) 0xfff1013c;
	GPIO1_OE = (int *) 0xfff10134;

	*GPIO1_OE &= ~(1 << 8);

	while( 1 ) {
		for( i = 0; i < 100000; i++ );
		*GPIO1_DATAOUT ^= (1 << 8);
	}
}
