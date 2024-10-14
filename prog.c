#include <stdio.h>
 

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


int main() {
    double num;
    scanf("%lf", &num);

    int sgn_bit = (num < 0) ? 1 : 0;
    num = absolute(num);
    printf("%d\n", sgn_bit);
    char bin_exp[8]; 
    find_exp(&num, bin_exp);
    printf("%s\n", bin_exp);
	//printf("%lf", num);
    
	num -= (int)num;
	char bin_frac[23];
	frac_to_bin(num, bin_frac);
	printf("%s\n", bin_frac);
    return 0;
}
 
