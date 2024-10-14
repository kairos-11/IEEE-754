#include <stdio.h>
#include <math.h>


float absolute(float num){
	return (num < 0) ? -num : num;
}

void int_to_bin(int num, char *bin){
	for (int i = 7; i >= 0; i--) {
        bin[i] = (num % 2) ? '1' : '0';
        num /= 2;
    }
}

void frac_to_bin(double frac, char *bin){
	int cnt = 0, seen_cnt = 0;
	double seen[1000];
	while (frac > 0 && cnt < 23){
		for (int i = 0; i < seen_cnt; i++){
			if (seen[i] == frac){
				return;
			}
		}
		seen[seen_cnt++] = frac;
		frac *= 2;
		if (frac >= 1){
			bin[cnt++] = '1';
			frac -= 1;
		} else {
			bin[cnt++] = '0';
		}
	}
	if (cnt == 23 && frac != 0){
		bin[cnt-1] = '1';
	}
}

void find_exp(double *num, char *res){
	int i = 1;
	int exp = 0;
	if (*num < 1){
		while (*num < 1){
			i *= 2;
			exp += 1;
			*num = *num / (i / 2) / (1.0 / i);
			//printf("%f\n", num);
		}
		exp = -exp;
	} else {
		while (*num > 2){
			i *= 2;
			exp += 1;
			*num = *num * (i / 2) / (i);
			//printf("%f\n", num);
		}
	}
	exp += 127;
	int_to_bin(exp, res);
		
}


void convert_to(double num, char *res){
	res[0] = (num < 0) ? '1' : '0';
	char exp[8];
	char frac[23];
	find_exp(&num, exp);
	num -= (int)num;
	frac_to_bin(num, frac);
	printf("%s\n", exp);
	for (int i = 0; i < 8; i++){
		res[i+1] = exp[i];
	}
	for (int i = 0; i < 23; i++){
		res[i+9] = frac[i];
	}
}

int bin_to_int(char *bin, int sz){
	int res = 0;
	int pw = 1;
	for (int i = sz-1; i >= 0; i--){
		res += (bin[i] - '0') * pw;
		pw *= 2;
	}

	return res;
}

float bin_to_frac(char *bin, int sz){
	float res = 0;
	double pw = 1.0 / 2;
	for (int i = 0; i < sz; i++){
		res += (bin[i] - '0') * pw;
		pw /= 2.0;
	}
	return res;
}

float convert_from(int sgn_bit, char *bin_exp, char *bin_frac){
	int sgn = (sgn_bit = 0) ? 1 : -1;
	float frac = bin_to_frac(bin_frac, 23);
	int exp = bin_to_int(bin_exp, 8);
	float res = sgn * (1 + frac) * pow(2, (exp - 127));
	return res;
}

int main() {
	int choice;
	printf("Введите 0, если хотите перевести вещ. число в IEEE 754, и 1 если хотите перевести из IEEE 754 в вещ.число\n");
	scanf("%d", &choice);
	if (choice == 0){
	    double num;
	    scanf("%lf", &num);
		char res[33];
		convert_to(num, res);
		res[32] = '\0';
		printf("%s\n", res);
	} else if (choice == 1){
		char num[32];
		scanf("%32s", num);
		char sgn_bit = num[0];
		char exp[9];
		char frac[24];
		for (int i = 1; i < 9; i++){
			exp[i-1] = num[i];
		}
		for (int i = 9; i < 32; i ++){
			frac[i-9] = num[i];
		}
		printf("%f\n", convert_from(sgn_bit, exp, frac));
	}
	
    return 0;
}
 
