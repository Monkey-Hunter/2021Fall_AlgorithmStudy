package taehyeon.boj11003;

import java.io.*;
import java.util.*;

class Pair {
    int first, second;

    public Pair(int first, int second){
        this.first = first;
        this.second = second;
    }
}

public class boj11003 {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st = new StringTokenizer(br.readLine());
        Deque<Pair> deque = new LinkedList<>();

        int N = Integer.parseInt(st.nextToken());
        int L = Integer.parseInt(st.nextToken());

        st = new StringTokenizer(br.readLine()); 
        // * 새로운 줄을 입력받을 때는 new StringTokenizer을 생성해줘야 함.

        for(int i=0; i<N; i++){

            if(!deque.isEmpty() && deque.peekFirst().second < i-L+1) 
                deque.removeFirst();

            int input = Integer.parseInt(st.nextToken());
            
            while(!deque.isEmpty() && deque.peekLast().first > input)
                deque.removeLast();
            
            deque.addLast(new Pair(input, i));

            bw.write(deque.getFirst().first + " ");
        } 
        bw.flush();
        bw.close();
    }
}
