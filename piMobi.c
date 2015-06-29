#include "stdio.h"
#include "errno.h"
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdlib.h>
//#include <linux/i2c.h>
//#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include "lsl_c.h"
#include "pwm.h" // courtesy of Chris Hagen
//#include "ads1015drvr.h"
#include "pthread.h"

int quit_now;

typedef struct _listen_data{
  int lsl_sr;
  int lsl_channs;
  char uid[256];
}t_listen_data;

void *listen(void *data){


/*   lsl_streaminfo info; */
/*   lsl_outlet outlet; */
/*   t_ads1015 *ads1015; */
/*   t_listen_data *d = (t_listen_data *)data; */

/*   int usleep_time; */
/*   usleep_time = (int)1000000/d->lsl_sr;  */
/*  // set up the LSL outlet */
/*   /\* info = lsl_create_streaminfo("piMobi", "piMobi", d->lsl_channs, d->lsl_sr, cft_int32, d->uid); *\/ */
/*   /\* outlet = lsl_create_outlet(info, 0, 360); *\/ */
/*   printf("lsl_local_clock %f\n", lsl_local_clock()); */

/*   // set up the ads1015 */
/*   ads1015 = ads1015_create(); */
/*   ads1015->input_sel = A0; */
/*   ads1015->gains = FOURPT096V; */
/*   ads1015->dr = DR250; */
/*   ads1015_set_configuration(ads1015); */

  printf("now reading from device...\n");
  int foo = 1;
  //pthread_mutex_lock(&device_lock);
  while(quit_now==0)
    {
      printf("new thread...%d\n", quit_now);
      //ads1015_read_once(ads1015);
      //printf("%d\n",ads1015->val);
      /* lsl_push_sample_i(outlet, &foo);//&ads1015->val); */
      //  pthread_mutex_unlock(&device_lock);
      sleep(1);//usleep(usleep_time);
    }

/*   ads1015_kill(ads1015); */
/*   /\* lsl_destroy_outlet(outlet); *\/ */

  pthread_exit(NULL);
}

int main(int argc, char **argv){

 
  pthread_t listen_thread;
  

  // TODO parse command line arguments
  // or provide a config file -- probably a better choice
  
  t_listen_data *data;
  data = malloc(sizeof(t_listen_data));

  data->lsl_channs = 1;
  data->lsl_sr = 1000;
  
  
  char q_str[256] = {0};
  printf("q_str %s\n", q_str);

  char hostname[256];
  int len;
 
  /* strcpy(data->uid, "piMobi"); */
  /* int foo = gethostname(hostname, len); */
  /* if(foo==0) */
  /*   strcat(data->uid, hostname);  */
  /* //printf("hostname: %s uid: %s\n", hostname, uid); */
  
  /* // setup TTL signal */
  /* setup(PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT, DELAY_VIA_PCM); */

  /* int gpio = 17; */
  /* int channel = 0; */
  /* int subcycle_time_us = 100000; */


  /* // pwm on gpio 17 */
  /* init_channel(channel, subcycle_time_us); */
  /* add_channel_pulse(channel, gpio, 10, 200); */

  /* // initialize the quit flag */
  quit_now = 0;

 
  
  /* // launch the listen thread for LSL/I2c */
  int rc = pthread_create(&listen_thread, NULL, listen, (void *)data);
 
  while(quit_now==0)
    {
      printf("hit 'q' to exit\n");
      scanf("%s", q_str);
      if(strcmp(q_str, "q")==0)
	quit_now = 1;
    }
  //sleep(5);

  quit_now = 1;
  /* pthread_join(listen_thread, NULL); */
  /* // clean up */
  /* shutdown(); // destroy TTL */
  free(data);


  
  return 0;
}
