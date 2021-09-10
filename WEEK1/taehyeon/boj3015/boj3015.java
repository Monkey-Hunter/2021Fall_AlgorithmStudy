package taehyeon.boj3015;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

class Pair{
    int x;  // 키
    int y;  // 키가 같은 사람 수

    public Pair(int x, int y){
        this.x = x;
        this.y = y;
    }
}

public class boj3015 {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        Stack<Pair> stack = new Stack<>();
        int N = Integer.parseInt(br.readLine());
        long ptr=0;

        for(int i=0; i<N; i++){
            int input = Integer.parseInt(br.readLine());
            Pair P = new Pair(input,1);

            while(!stack.isEmpty()){
                if(stack.peek().x <= P.x){
                    ptr += stack.peek().y;
                    
                    if(stack.peek().x == P.x){
                        P.y += stack.peek().y;
                    }
                    stack.pop();
                }
                else break;
            }

            if(!stack.isEmpty()) ptr++;
            
            stack.push(P);
        }
       System.out.println(ptr); 
    }
}
