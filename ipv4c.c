#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char *argv[]){
	int network_ip[4];
	int first_ip[4];
	int binary_network_ip[4][8];
	int ip[4];
	int binary_Subnetmask[4][8];
	int subnetMask[4]={0,0,0,0};
	int sm=atoi(argv[2]);
	int max_hosts=pow(2,(32-sm));
	int temp_sm = sm;
	int i,j,x;
	int broadcast[4]={0,0,0,0};
	int last_ip[4];
	int binary_wildcard[4][8];
	int binary_broadcast[4][8];
	char *term_arg_ip = strtok(argv[1], ".");
	if (sm<1 || sm > 32) {
			printf("\033[1;32mThe range of prefix subnetmask must be from 1 to 32.\033[0m\n");
			return 0;
	}
	i=0;
	while (term_arg_ip != NULL){
		ip[i]=atoi(term_arg_ip);
		if (ip[i]<0 || ip[i]>255) {
			printf("\033[1;32mThe range of ipv4 bytes  must be from 1 to 255.\033[0m\n");
			return 0;
		}
		term_arg_ip = strtok(NULL, ".");
		i=i+1;
	}
	for (i = 0;i <4; i++) {
			for ( j = 0; j < 8; j++) {
				if (temp_sm!=0) {
					binary_Subnetmask[i][j] = 1;
					temp_sm = temp_sm-1;
				}else{
					binary_Subnetmask[i][j] = 0;
				}
				if (binary_Subnetmask[i][j]==1) {
					subnetMask[i]=subnetMask[i]+pow(2,7-j);
				}
				if (binary_Subnetmask[i][j]==1) {
					binary_wildcard[i][j] = 0;
				}else{
					binary_wildcard[i][j] =1;
				}
			}
	}
	for (i = 0; i < 4; i++) {
			network_ip[i]=ip[i]&subnetMask[i];
			first_ip[i]=network_ip[i];
	}
	first_ip[3]=first_ip[3]+1;
	for ( i = 0; i < 4; i++) {
	 x=network_ip[i];
	 for (j = 0; j < 8; j++) {
		 if (x>=pow(2,7-j)) {
			 x=x-pow(2,7-j);
			 binary_network_ip[i][j]=1;
		 }else{
			 binary_network_ip[i][j]=0;
		 }
		 binary_broadcast[i][j]=binary_network_ip[i][j] || binary_wildcard[i][j];
		 if (binary_broadcast[i][j]==1) {
			 broadcast[i]=broadcast[i]+pow(2,7-j);

		 }
		 last_ip[i]=broadcast[i];
	 }
	}
	last_ip[3]=last_ip[3]-1;
	printf("\033[0;31mNetWork ip\033[37m:\033[0;33m %d.%d.%d.%d\n\033[0m",network_ip[0],network_ip[1],network_ip[2],network_ip[3]);
	printf("\033[0;31mSubnetMask\033[37m:\033[0;33m  \033[37m/\033[0;33m%d \033[37m-->\033[0;33m %d.%d.%d.%d\n\033[0m",sm,subnetMask[0],subnetMask[1],subnetMask[2],subnetMask[3]);
	printf("\033[0;31mBroadcast ip\033[37m:\033[0;33m  %d.%d.%d.%d\n\033[0m",broadcast[0],broadcast[1],broadcast[2],broadcast[3]);
	printf("\033[0;31mTotal Number of Hosts\033[37m:\033[0;33m  %d\n\033[0m",max_hosts);
	if(max_hosts-2<=0){
		printf("\033[0;31mNumber of Usable Hosts\033[37m:\033[0;33m n/a\n\033[0m");
			printf("\033[0;31mUsable Host IP Range\033[37m:\033[0;33m n/a \n\033[0m");
	}else{
		printf("\033[0;31mNumber of Usable Hosts\033[37m:\033[0;33m  %d\n\033[0m",max_hosts-2);
			printf("\033[0;31mUsable Host IP Range\033[37m:\033[0;33m  %d.%d.%d.%d \033[37m~\033[0;33m %d.%d.%d.%d\n\033[0m",first_ip[0],first_ip[1],first_ip[2],first_ip[3],last_ip[0],last_ip[1],last_ip[2],last_ip[3]);
	}
	return 0;
}
