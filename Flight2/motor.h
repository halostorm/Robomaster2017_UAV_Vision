int motor;
int last_motor;
static unsigned char motor_flag;
void static *motorset(void* data){
	char device[] = "/dev/ttyS0";
	int fd = uartOpen(device);
	if (fd == -1)
		printf("device error");
	uartSet(fd);
	last_motor=31;
	motor=31;
	while(1){
		if(motor!=last_motor)
		{
			motor_flag=(char)motor;
			last_motor=motor;
			//cout<<motor_flag<<endl;
			uartSend(fd, &motor_flag, 1);
		}
	} 
}
class MotorSend {
public:
	MotorSend(){
		if (pthread_create(&motor_thread, NULL, motorset, NULL) != 0)
		{
			printf("motor_thread create");
		}
		pthread_detach(motor_thread);
	}
	void move(){
		if(motor==31)
			motor=32;
		else motor=31;
	}

public:
    pthread_t motor_thread;
};
