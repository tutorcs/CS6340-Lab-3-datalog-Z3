https://tutorcs.com
WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
int main(){
	int a = 100220;
	int b = 121;
	int c = 21421141;
	
	int a1 = 0;
	int b1 = 0;
	int c1 = 0;

	if (a > b){
		if(a > c){
			a1 = 1;
			b1 = 0;
			c1 = 0;
		}else{
			a1 = 0;
			b1 = 0;
			c1 = 1;
		}
	}else{
		if(b > c){
			a1 = 0;
			b1 = 1;
			c1 = 0;
		}else{
			a1 = 0;
			b1 = 0;
			c1 = 1;
		}
	}
	
	a = a*a1;
	b = b*b1;
	c = c*c1;
}
