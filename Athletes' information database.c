#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Attributes{
	char name[50],nationality[15],club[20],position[20],annualincome[20];
	int age;
	float height;
};
struct Output{
	char name[50],nationality[15],club[20],position[20],annualincome[20];
	int age;
	float height;
};
int main()
{
	struct Attributes a[100];
	int number=0,n=0,k;
	FILE *info;
	info=fopen("info.txt","r");
	for(k=0;!feof(info);k++){
		fgets(a[k].name,50,info);
		if(!feof(info)){
			a[k].name[strlen(a[k].name)-1]='\0';
			fgets(a[k].nationality,15,info);
			a[k].nationality[strlen(a[k].nationality)-1]='\0';
			fscanf(info,"%d %f",&a[k].age,&a[k].height);
			fgetc(info); // to absorb newline from file
			fgets(a[k].club,20,info);
			a[k].club[strlen(a[k].club)-1]='\0';
			fgets(a[k].position,20,info);
			a[k].position[strlen(a[k].position)-1]='\0';
			fgets(a[k].annualincome,20,info);
			if(!feof(info)){
				a[k].annualincome[strlen(a[k].annualincome)-1]='\0';
			}
			number++;
		}
	}
	fclose(info);
	printf("\t\tAthlete info: The best place to know more about your favorite sportsman.\n\n");
	do{
		printf("\t\tNumber of athletes currently registered in database = %d\n",number);
		printf("\t\tPlease select an option.\n");
		printf("\t\t1) Enter New Athlete. (Only for admin)\n\t\t2) Search for an athlete.\n\t\t3) Edit information. (Only for admin)\n\t\t4) Show list of players\n\t\t5) List by country\n\t\t6) List by club\n\t\tAnything else to quit.\n");
		scanf("%d",&n);
		system("CLS");
		getchar();
		switch(n){
			case 1:
				printf("\t\tPlease Enter password: ");
				char str1[20],str2[20];
				gets(str1);
				FILE *passfile;
				passfile=fopen("password.txt","r");
				fscanf(passfile,"%s",str2);
				if(!strcmp(str1,str2)){
					int N,i;
					FILE *info;
					printf("\t\tAccess Granted.\nPlease enter the number of new athletes.\n");
					scanf("%d",&N);
					getchar();
					info=fopen("info.txt","a");
					for(i=number;i<number+N;i++){
						if(i>0){
							fprintf(info,"\n");
						}
						printf("Athlete number %d:\nPlease enter name: ",i+1);
						gets(a[i].name);
						fputs(a[i].name,info);
						fprintf(info,"\n");
						printf("Please enter country: ");
						gets(a[i].nationality);
						fputs(a[i].nationality,info);
						fprintf(info,"\n");
						printf("Please enter age and height(in metres):\n");
						scanf("%d %f",&a[i].age,&a[i].height);
						fprintf(info,"%d\n%f\n",a[i].age,a[i].height);
						getchar();
						printf("Please enter club:\n");
						gets(a[i].club);
						fputs(a[i].club,info);
						fprintf(info,"\n");
						printf("Please enter position:\n");
						gets(a[i].position);
						fputs(a[i].position,info);
						fprintf(info,"\n");
						printf("Please enter annual income:\n");
						gets(a[i].annualincome);
						fputs(a[i].annualincome,info);
					}
					fclose(info);
					number=i;
				}
				else{
					printf("\t\tPassword does not match. Access denied.\n");
				}
				break;
			case 2:
				printf("Enter athlete name: ");
				int j;
				char search[50],f=0;
				gets(search);
				for(j=0;j<number && !f;j++){
					if(strcmp(search,a[j].name)==0){
						f=1;
						printf("Name: %s\nCountry: %s\nAge: %d\nHeight: %.2fm\nClub: %s\nPosition: %s\nAnnual income: %s\n",a[j].name,a[j].nationality,a[j].age,a[j].height,a[j].club,a[j].position,a[j].annualincome);
					}
				}
				if(!f){
					printf("\t\tThis athlete's information is not registered in the database\n");
				}
				break;
			case 3:
				printf("\t\tPlease enter password\n");
				char str3[20],str4[20];
				FILE *pass;
				gets(str3);
				pass=fopen("password.txt","r");
				fscanf(pass,"%s",str4);
				if(strcmp(str3,str4)==0){
					printf("Access Granted.\n");
					printf("Please search for the athlete whose information you want to edit.\n");
					char change[50],F=0;
					int l;
					gets(change);
					for(l=0;l<number && F==0;l++){
						if(strcmp(change,a[l].name)==0){
							int choice,m;
							F=1;
							printf("\t\tWhich information do you want to update for %s?\n\t\t1) Age\n\t\t2) Club\n\t\t3) Position\n\t\t4) Annual income\n\t\t5) Name\n\t\t6) Country\n\t\t7) Height\n\t\tAnything else to quit\n",a[l].name);
							scanf("%d",&choice);
							getchar();
							if(choice==1){
								printf("Please enter new age: ");
								scanf("%d",&a[l].age);
								getchar();
							}
							else if(choice==2){
									printf("Please enter new club: ");
									gets(a[l].club);
								}
								else if(choice==3){
										printf("Please enter new position: ");
										gets(a[l].position);
									}
									else if(choice==4){
											printf("Please enter new annual income: ");
											gets(a[l].annualincome);
										}
										else if(choice==5){
												printf("Please enter new name: ");
												gets(a[l].name);
											}
											else if(choice==6){
													printf("Please enter new country: ");
													gets(a[l].nationality);
												}
												else if(choice==7){
														printf("Please enter new height: ");
														scanf("%f",&a[l].height);
														getchar();
													}
							FILE *info;
							info=fopen("info.txt","w");
							for(m=0;m<number;m++){
								fprintf(info,"%s\n%s\n%d\n%f\n%s\n%s\n%s",a[m].name,a[m].nationality,a[m].age,a[m].height,a[m].club,a[m].position,a[m].annualincome);
								if(m<number-1){
									fprintf(info,"\n");
								}
							}
							fclose(info);
						}
					}
					if(F==0){
						printf("\t\tThis Athlete's information is not registered in the database.\n");
					}
				}
				else{
					printf("\t\tWrong password. Access denied.\n");
				}
				fclose(pass);
				break;
			case 4:
				printf("Following is a list of all the athletes in the database:\n");
				int l;
				for(l=0;l<number;l++){
					printf("%d) %s\n",l+1,a[l].name);
				}
				break;
			case 5:
				printf("Please enter name of the country: ");
				char nation[15];
				int m,F=0,count=1;
				gets(nation);
				for(m=0;m<number;m++){
					if(strcmp(a[m].nationality,nation)==0 && F==0){
						F=1;
						printf("List of athletes from country %s:\n",a[m].nationality);
					}
					if(strcmp(a[m].nationality,nation)==0){
						printf("%d) %s\n",count,a[m].name);
						count++;
					}
				}
				if(F==0){
					printf("\t\tNo athlete from country %s is registered in the database.\n",nation);
				}
				break;
			case 6:
				printf("Please enter name of the club: ");
				char team[20];
				gets(team);
				int I,F1=0,counter=1;
				for(I=0;I<number;I++){
					if(strcmp(a[I].club,team)==0 && F1==0){
						F1=1;
						printf("List of athletes from club %s:\n",a[I].club);
					}
					if(strcmp(a[I].club,team)==0){
						printf("%d) %s\n",counter,a[I].name);
						counter++;
					}
				}
				if(F1==0){
					printf("\t\tNo athlete from club %s is registered in the database.\n",team);
				}
				break;
		}
	}while(n>=1 && n<=6);
	return 0;
}
