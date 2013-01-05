class Main
{
    public static void main(String []args)
    {
        int i = 2;
        int j = 6;
        int N = Integer.parseInt("10000000000",2);
        int M = Integer.parseInt("10101", 2);
        int T = ~0;
        T = T<<7;
        T = T | 3;
        N = N & T;
        M = M <<  i ;
        N = N | M;
    }
}
