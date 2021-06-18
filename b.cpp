int fun(int a,int b) {
	printint(a);
	printint(b);
}
int cnt=0;
int f(int x) {
	cnt=cnt+1;
	return cnt;
}
int main() {
	fun(f(1),f(1));
	return 0;
}
