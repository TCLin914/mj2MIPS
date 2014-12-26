class Testcase{
   public static void main(String[] a){
        System.out.println(new BS().test(5));
        }
}
class CS{
        int b;
        public int test(int c){
            	int m1;
		int m2;
		m1 = 1;
		m2 = 2;
		b = 3;
		return m1*m2*b-c;
        }
}
class BS extends CS{
	int e;
	int c;
	int d;
	public int testb(int a){
		b=1;
		return a+b;
	}
}
