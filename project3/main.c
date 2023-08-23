#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


int main() {
	/*open users file*/
	FILE* users = fopen("users.txt", "a+");

	/*define the variables*/
	int count_users;
	int count_words;
	int login_status = NOT_LOGED_IN;
	int count_halls = INITIAL_NUMBER;
	int count_foods = INITIAL_NUMBER;
	int count_coupons = INITIAL_NUMBER;
	int error_status = NO_ERROR;
	int i;
	int j;
	int k;
	int current_user_id;

	/*check if users is null*/
	if (users == NULL) {
		error_status = ERROR;
	}
	
	/*define number of users*/
	count_users = count_file_lines(users) + 1;

	/*read users*/
	Users *users_list = (Users *)malloc(sizeof(Users));
	users_list = read_data(count_users, &error_status, users);
	
	/*close the file*/
	fclose(users);

	Commands *commands_word;
	Halls *halls_list = (Halls *)malloc(sizeof(Halls));
	/*check if memory is allocated*/
	if (halls_list == NULL) {
		error_status = ERROR;
	}
	halls_list->next = NULL;

	Foods *foods_list = (Foods *)malloc(sizeof(Foods));
	/*check if memory is allocated*/
	if (foods_list == NULL) {
		error_status = ERROR;
	}
	foods_list->next = NULL;

	Coupons *coupons_list = (Coupons *)malloc(sizeof(Coupons));
	/*check if memory is allocated*/
	if (coupons_list == NULL) {
		error_status = ERROR;
	}
	coupons_list->next = NULL;

	/*define command array to get the command from user*/
	char command[MAX_ARRAY_SIZE];


	while (TRUE) {
		/*get command from user*/
		gets(command);
		count_words = count_line_word(command);
		commands_word = (Commands *)calloc(count_words, sizeof(Commands));

		/*check if memory is allocated*/
		if (commands_word == NULL) {
			error_status = ERROR;
		}

		/*check if error happens*/
		if (error_status == ERROR) {
			printf("error happens\n");
			break;
		}

		/*split the commands words*/
		j = 0;
		for (i = 0; i < count_words; i++) {
			k = 0;
			if (command[j] == ' ') {
				j = j + 1;
			}
			while (command[j] != ' ' && command[j] != NULL) {
				commands_word[i].word[k] = command[j];
				j = j + 1;
				k = k + 1;
			}
		}

		/*check what command is*/
		if (strcmp(commands_word[0].word, "login") == 0) {

			/*check login status*/
			if (login_status == NOT_LOGED_IN) {

				/*check if command is in the right order*/
				if (count_words == 3) {
					user_login(&login_status, count_users, &current_user_id, commands_word, users_list);
				}
				else {
					printf("wrong commands\n");
				}
			}
			else {
				printf("a user already loged in\n");
			}
		}

		/*check what command is*/
		else if (strcmp(commands_word[0].word, "signup") == 0) {

			/*check log in status*/
			if (login_status == NOT_LOGED_IN) {

				/*check if command is in the right order*/
				if (count_words == 4) {
					users_list = user_singup(count_words, &count_users, &error_status, commands_word, users_list);
				}
				else {
					printf("wrong commands\n");
				}
			}
			else {
				printf("user loged in\n");
			}
		}


		/*check what command is*/
		else if (strcmp(commands_word[0].word, "logout") == 0) {

			/*check log in status*/
			if (login_status != NOT_LOGED_IN) {

				/*chek if command is in the right order*/
				if (count_words == 1) {
					user_logout(&login_status);
				}
				else {
					printf("wrong commands\n");
				}
			}
			else {
				printf("access denied\n");
			}
		}

		/*check what command is*/
		else if (strcmp(commands_word[0].word, "add_hall") == 0) {

			/*check log in status*/
			if (login_status == AMIN_LOGED_IN) {

				/*check if command is in the right order*/
				if (count_words == 4) {
					halls_list = add_hall(&count_halls, &error_status, commands_word, halls_list);
				}
				else {
					printf("wrong commands\n");
				}
			}
			else {
				printf("permission denied\n");
			}
		}

		/*check what command is*/
		else if (strcmp(commands_word[0].word, "add_food") == 0) {

			/*check log in status*/
			if (login_status == AMIN_LOGED_IN) {

				/*check if command is in the right order*/
				if (count_words == 7) {
					foods_list = add_food(&count_foods, count_halls, &error_status, commands_word, foods_list, halls_list);
				}
				else {
					printf("wrong commands\n");
				}
			}
			else {
				printf("permission denied\n");
			}
		}

		/*check what command is*/
		else if (strcmp(commands_word[0].word, "add_coupon") == 0) {

			/*check login status*/
			if (login_status == AMIN_LOGED_IN) {

				/*check if command is in the right order*/
				if (count_words == 4) {
					coupons_list = add_coupon(&count_coupons, &error_status, commands_word, coupons_list);
				}
				else {
					printf("wrong commands\n");
				}
			}
			else {
				printf("permission denied\n");
			}
		}

		/*check what command is*/
		else if (strcmp(commands_word[0].word, "get_money") == 0) {

			/*check log in status*/
			if (login_status == NORMAL_USER_LOGED_IN) {

				/*check if command is in the right order*/
				if (count_words == 2) {
					get_money(current_user_id, users_list, commands_word);
				}
				else {
					printf("wrong commands\n");
				}
			}
			else {
				printf("permission denied\n");
			}
		}

		/*check what command is*/
		else if (strcmp(commands_word[0].word, "show_money") == 0) {

			/*check log in ststus*/
			if (login_status == NORMAL_USER_LOGED_IN) {

				/*check if command is in the right order*/
				if (count_words == 1) {
					show_money(current_user_id, users_list);
				}
				else {
					printf("wrong commands\n");
				}
			}
			else {
				printf("permission denied\n");
			}
		}

		/*check what command is*/
		else if (strcmp(commands_word[0].word, "menu") == 0) {

			/*check log in status*/
			if (login_status == NORMAL_USER_LOGED_IN) {

				/*check if command is in the right order*/
				if (count_words == 1) {
					menu(count_foods, foods_list, halls_list);
				}
				else {
					printf("wrong commands\n");
				}
			}
			else {
				printf("permission denied\n");
			}
		}

		/*check what command is*/
		else if (strcmp(commands_word[0].word, "reserve") == 0) {
			
			/*check log in status*/
			if (login_status == NORMAL_USER_LOGED_IN) {
				
				/*check if command is in the right order*/
				if (count_words == 2) {
					reserve_normal(current_user_id, &error_status, commands_word, users_list, foods_list, halls_list);
				}
				else {
					printf("wrong commands\n");
				}
			}
			else {
				printf("permission denied\n");
			}
		}

		/*check what command is*/
		else if (strcmp(commands_word[0].word, "reserve_discount") == 0) {

			/*check log in status*/
			if (login_status == NORMAL_USER_LOGED_IN) {

				/*check if command is in the right order*/
				if (count_words == 3) {
					reserve_discount(current_user_id, &error_status, commands_word, users_list, foods_list, halls_list, coupons_list);
				}
				else {
					printf("wrong commands\n");
				}
			}
			else {
				printf("permission denied\n");
			}
		}

		/*check what command is*/
		else if (strcmp(commands_word[0].word, "show_reserved") == 0) {

			/*check log in status*/
			if (login_status == NORMAL_USER_LOGED_IN) {

				/*check if command is in the right order*/
				if (count_words == 1) {
					show_reserved(current_user_id, users_list, foods_list, halls_list);
				}
				else {
					printf("wrong commands\n");
				}
			}
			else {
				printf("permission denied\n");
			}
		}

		/*check what command is*/
		else if (strcmp(commands_word[0].word, "food_report") == 0) {

			/*check log in status*/
			if (login_status == AMIN_LOGED_IN) {

				/*check if command is in the right order*/
				if (count_words == 1) {
					food_report(count_foods, &error_status, foods_list);
				}
				else {
					printf("wrong commands\n");
				}
			}
			else {
				printf("permossion denied\n");
			}
		}

		/*check what command is*/
		else if (strcmp(commands_word[0].word, "hall_report") == 0) {

			/*check log in status*/
			if (login_status == AMIN_LOGED_IN) {

				/*check if command is in right order*/
				if (count_words == 1) {
					hall_report(count_halls, &error_status, halls_list);
				}
				else {
					printf("wrong commands\n");
				}
			}
			else {
				printf("permission denied\n");
			}
		}


		/*check what command is*/
		else if (strcmp(commands_word[0].word, "exit") == 0) {

			/*check if command is in the right order*/
			if (count_words == 1) {
				break;
			}
			else {
				printf("wrong commands\n");
			}
		}

		else {
			printf("wrong commands\n");
		}
		

		/*free the commands word*/
		free(commands_word);
	}

	/*free the lists*/
	delete_users_list(count_users, users_list);
	delete_halls_list(count_halls, halls_list);
	delete_foods_list(count_foods, foods_list);
	delete_coupons_list(count_coupons, coupons_list);
	free(commands_word);
	return 0;
}
