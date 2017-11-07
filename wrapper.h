void start_ADC(int, int, int);
void stop_ADC(void);
void collect_data(void);
long int read_channel_raw(int);
double read_channel_volts(int);
void read_all_channels_raw(long int *, int ch);
void read_all_channels_volts(double *, int ch);
